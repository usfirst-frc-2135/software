
#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string>
#include <vector>
//#include <malloc.h>


#define LABVIEW_EPOCH_OFFSET	2082844800
#define DS_POLL_PERIOD			(0xffffffff / 50)

void PrintUsage(const std::string& errMsg);
int HexBufToString(char *inBuf, int bufSize, char *outBuf);
bool ProcessDSFileHeader(std::ifstream& iEvtFile, std::ofstream& oMsgFile, std::ofstream& oCsvFile);
bool ProcessEventBlocks(std::ifstream& iEvtFile, std::ofstream& oMsgFile, std::ofstream& oCsvFile);
bool ProcessLogBlocks(std::ifstream& iLogFile);
void ProcessSearchString(std::fstream& oMsgFile, std::ofstream& oFiltFile, char *srchStr);

void ProcessMessage(const std::string& message, std::ostream& csvStream);

// Print command line usage string

void PrintUsage(const std::string& errMsg)
{
    std::cerr << errMsg << std::endl;
    std::cerr << "Usage: dsParser <log-file> <output-file> [<filter-string>]" << std::endl;
}

// Process the data log blocks

int HexBufToString(char *inBuf, int bufSize, char *outBuf) {
    const char  *cnv = "0123456789abcdef";
    int         i;

    for (i = 0; i < bufSize; i++) {
        outBuf[2*i] = cnv[(inBuf[i] & 0xff) >> 4];
        outBuf[2*i+1] = cnv[inBuf[i] & 0x0f];
    }
    outBuf[2*i] = '\0';

    return i;
}

// Process the data log header at the beginning of the input file

bool ProcessDSFileHeader(std::ifstream& iEvtFile) {
    char    hdrBuf[8];
    char    achar[2*8+1];

    // Pull off the first 8 characters from input file
    iEvtFile.read(hdrBuf, sizeof(hdrBuf));
    if ((iEvtFile.gcount() != sizeof(hdrBuf)) || iEvtFile.eof()) {
        std::cerr << "Error: Received EOF within log file header" << std::endl;
        return false;
    }

    // Process file header and write to output file
    HexBufToString(hdrBuf, sizeof(hdrBuf), achar);
    std::cout << achar << std::endl;

    return true;
}

// Process the data log blocks

bool ProcessEventBlocks(std::ifstream& iEvtFile, std::ofstream& oRawFile, std::fstream& oMsgFile) {
    char    buf[16];
    char    achar[16*2+1];
    int     blockBytes = 0, totalBytes = 8, totalBlocks = 0;
    time_t  ts;

	std::cout << "Info: Processing input ds events file" << std::endl;

    while (1) {
        // Pull off the block header characters from input file
        iEvtFile.read(buf, sizeof(buf));
        totalBytes = totalBytes + (int)iEvtFile.gcount();
        if (iEvtFile.gcount() == 0) {
            std::cout << "Info: No more bytes at start of block: " 
                << totalBytes << " bytes read in block " << totalBlocks << std::endl;
            return true;
        }
        // Check for bad header or end of file and update block count
        if ((iEvtFile.gcount() < sizeof(buf)) || iEvtFile.eof()) {
            std::cerr << "Error: EOF within a log block header or missing bytes: "
                << totalBytes << " bytes read in block " << totalBlocks << std::endl;
            return false;
        }

        // Put header to output files and update byte count
        HexBufToString(buf, sizeof(buf), achar);
        std::cout << achar << " ";
        oRawFile << achar << std::endl;

        // Get timestamp for block
        uint32_t    fs;
        uint32_t    msec;
        char        timeBuf[64];
        char        msecBuf[8];

        // Get number of seconds since 1904 (LabView epoch) and convert to 1970 (Unix epoch)
        ts = ( (buf[0] & 0xff) << 24 | (buf[1] & 0xff) << 16 | 
            (buf[2] & 0xff) << 8 | (buf[3] & 0xff) ) & 0x00000000ffffffff;
        ts -= LABVIEW_EPOCH_OFFSET;

        // Get fractional msec and calculate integer msec digits
        fs = (buf[4] & 0xff) << 24 | (buf[5] & 0xff) << 16 | (buf[6] & 0xff) << 8 | (buf[7] & 0xff);
        msec = (uint32_t) trunc(((double)fs / 0xffffffff) * 1000);

        // Print date and time, then add msec digits
        std::strftime(timeBuf, sizeof(timeBuf), "%y-%m-%d %H:%M:%S.", localtime(&ts));
        std::sprintf(msecBuf, "%03d ", msec);
        std::strcat(timeBuf, msecBuf);
        std::cout << timeBuf;

        // Calculate block length
        blockBytes = (unsigned char)buf[12] << 24 | (unsigned char)buf[13] << 16 |
            (unsigned char)buf[14] << 8 | (unsigned char)buf[15];
        std::cout << "Info: read block " << std::setw(3) << totalBlocks << " of " << std::setw(4) 
            << blockBytes << " bytes | total bytes " << (totalBytes + blockBytes) << std::endl;

        // Process the data bytes in the block

        if (blockBytes > 0) {
            char        *entry = new char[blockBytes + 1];

            iEvtFile.read(entry, blockBytes);
            totalBytes = totalBytes + (int)iEvtFile.gcount();
            if (iEvtFile.gcount() != blockBytes) {
                std::cerr << "Error: Received too few bytes in data block " << totalBlocks << " at block byte " 
                    << iEvtFile.gcount() << " of " << blockBytes << " | bytes read " << totalBytes << std::endl;
                delete entry;
                return false;
            }
            entry[iEvtFile.gcount()] = '\0';

            // Process individual strings denoted by <TagVersion>

            char        *tmpPtr = entry;
            std::vector<char *> strPtr;

            while ((tmpPtr < entry+blockBytes) && (tmpPtr = strstr(tmpPtr, "<TagVersion>")) != NULL) {
                strPtr.push_back(tmpPtr++);
            }

            oRawFile << timeBuf << entry << std::endl;
            
            if (strPtr.size() > 0) {
                // Allocate memory for ordered buffer with timestamps
                char        *ordered = new char[blockBytes + (strPtr.size() * 22) + 1];

                for (std::vector<char *>::reverse_iterator rit = strPtr.rbegin(); rit != strPtr.rend(); rit++) {
                    oMsgFile << timeBuf << *rit << std::endl;
                    **rit = '\0';
                }

                delete ordered;
            }
            else {
                oMsgFile << timeBuf << entry << std::endl;
            }

            delete entry;

            // Pull off the block trailer (or block padding)

            char *trailer = new char[4+1];

            iEvtFile.read(buf, 4);
            totalBytes = totalBytes + (int)iEvtFile.gcount();
            if (iEvtFile.eof()) {
                std::cout << "Info: Received normal EOF at end of trailer block " << totalBlocks
                    << " | bytes read " << totalBytes << std::endl;
                return true;
            }
            if (iEvtFile.gcount() != 4) {
                std::cerr << "Error: Received too few bytes in trailer block " << totalBlocks << " at block byte "
                    << iEvtFile.gcount() << " of 4 | bytes read " << totalBytes << std::endl;
                return false;
            }

            HexBufToString(buf, 4, achar);
            oRawFile << achar << std::endl;

            delete trailer;
        }
        else {
            std::cout << "Info: Byte count is zero in block "
                << totalBlocks << std::endl;
        }

        totalBlocks++;
    }

    return false;
}

/**
* Processes a single message string
*/
void ProcessMessage(const std::string& message, std::ostream& csvStream)
{
#if 0   // saving code to print header one time
    // Print header to csv file
    oCsvFile << "\"Match Time\","
        << "\"Drive Time (s)\","
        << "\"Left Encoder Counts\","
        << "\"Right Encoder Counts\","
        << "\"Left Distance (in)\","
        << "\"Right Distance (in)\","
        << "\"Left CLE\","
        << "\"Right CLE\","
        << "\"Left Motor Output\","
        << "\"Right Motor Output\","
        << "\"Left Error Input\","
        << "\"Right Error Input\""
        << std::endl;
#endif

    // Only process DriveDistance messages
    if (message.find("DTDD") == std::string::npos) {
        return;
    }

    char* msgBuf = new char[message.length() + 1];
    strcpy(msgBuf, message.c_str());
    msgBuf[message.length()] = '\0';

    size_t tokenIdx = 1;
    char* token = strtok(msgBuf, " \n");
    do
    {
        switch (tokenIdx)
        {
        case 3: // Match time
        case 7: // Drive time
        case 11: // L counts
        case 12: // R counts
        case 14: // L dist
        case 15: // R dist
        case 17: // L CLE
        case 18: // R CLE
        case 20: // L Out
        case 21: // R Out
        case 23: // L errIn
            csvStream << "\"" << token << "\",";
            break;

        case 24: // R errIn
            csvStream << "\"" << token << "\"";
            break;

        default:
            break;
        };

        ++tokenIdx;
    } while ((token = strtok(NULL, " \n")) != NULL);

    csvStream << std::endl;

    delete[] msgBuf;
}

// Process the search string into a filtered file

void ProcessSearchString(std::fstream& oMsgFile, std::ofstream& oFiltFile, char *srchStr) {

	char    line[512];
	int		lineCount = 0;

    // Read message file, place selected lines in CSV file

	std::cout << "Re-reading message file for desired tags" << std::endl;
	oMsgFile.seekg(0, oMsgFile.beg);

    while (oMsgFile.getline(line, sizeof(line))) {
		if (std::strstr(line, srchStr) != nullptr) {
			oFiltFile.write(line, strlen(line));
			oFiltFile << std::endl;
		}
		if (++lineCount % 1000 == 0)
			std::cout << "line count " << lineCount << std::endl;
	}
	std::wcout << "Inserted " << lineCount << " lines" << std::endl;
}

// Process the DS log blocks

bool ProcessLogBlocks(std::ifstream& iLogFile)
{
	bool	retCode = false;
	char    buf[8];
	char    achar[8+1];
	int     blockBytes = 0, totalBytes = 8, totalBlocks = 0;

	std::cout << "Info: Processing input ds log file" << std::endl;

	std::ofstream oRawFile("tempRawFile.txt");
	std::ofstream oMsgFile("tempLogFile.txt");

	// Pull off the block header characters from input file
	iLogFile.read(buf, sizeof(buf));
	totalBytes +=  (int)iLogFile.gcount();
	if (iLogFile.gcount() == 0) {
		std::cout << "Info: No bytes at start of block: "
			<< totalBytes << " bytes read in block " << totalBlocks << std::endl;
		return retCode;
	}
	// Check for bad header or end of file and update block count
	if ((iLogFile.gcount() < sizeof(buf)) || iLogFile.eof()) {
		std::cerr << "Error: EOF within a log block header or missing bytes: "
			<< totalBytes << " bytes read in block " << totalBlocks << std::endl;
		return retCode;
	}

	// Put header to display and update byte count
	HexBufToString(buf, sizeof(buf), achar);
	std::cout << achar;

	// Calculate number of seconds since 1904 (LabView epoch) and convert to 1970 (Unix epoch)
	time_t		ts;
	uint32_t    fs;
	uint32_t	ms;

	// Timestamp in LabView form
	ts = ((buf[0] & 0xff) << 24 | (buf[1] & 0xff) << 16 |
		(buf[2] & 0xff) << 8 | (buf[3] & 0xff)) & 0x00000000ffffffff;
	ts -= LABVIEW_EPOCH_OFFSET;

	// Get fractional msec and calculate integer msec digits
	fs = (buf[4] & 0xff) << 24 | (buf[5] & 0xff) << 16 | (buf[6] & 0xff) << 8 | (buf[7] & 0xff);
	ms = (uint32_t)trunc(((double)fs / 0xffffffff) * 1000);

	// Read off the 4 extra leading bytes 
	char	dummy[4];
	iLogFile.read(dummy, sizeof(dummy));
	totalBytes += (int)iLogFile.gcount();
	HexBufToString(dummy, sizeof(dummy), achar);
	std::cout << achar;

	// Process the data bytes in the log entry -- all entries are 35 bytes
	char        timeBuf[64];
	char        msecBuf[8];
	blockBytes = 35;
	char        *entry = new char[blockBytes];
	char		*hexChar = new char[blockBytes * 2 + 1];

	// Entry processing loop
	while (1) {

		// Print date and time, then add msec digits
		std::strftime(timeBuf, sizeof(timeBuf), "%y-%m-%d %H:%M:%S.", localtime(&ts));
		std::sprintf(msecBuf, "%03d ", ms);
		std::strcat(timeBuf, msecBuf);

		if ((totalBlocks % 100) == 0) {
			std::cout << timeBuf;
			std::cout << "Info: read block " << std::setw(3) << totalBlocks << " of " << std::setw(4)
				<< blockBytes << " bytes | total bytes " << (totalBytes + blockBytes) << std::endl;
		}

		iLogFile.read(entry, blockBytes);
		totalBytes = totalBytes + (int)iLogFile.gcount();
		if (iLogFile.gcount() == 0) {
			std::cout << "Info: No bytes at start of block: "
				<< totalBytes << " bytes read in block " << totalBlocks << std::endl;
			retCode = true;		// success is an empty block
			break;
		}
		if (iLogFile.gcount() != blockBytes) {
			std::cerr << "Error: Received too few bytes in data block " << totalBlocks << " at block byte "
				<< iLogFile.gcount() << " of " << blockBytes << " | bytes read " << totalBytes << std::endl;
			break;
		}

		oRawFile << timeBuf;
		for (int i = 0; i < blockBytes; i++) {
			HexBufToString(entry+i, 1, hexChar);
			oRawFile << "=HEX2DEC(\"" << hexChar << "\") ";
		}
		oRawFile << std::endl;

		ms += 20;
		if (ms >= 1000) {
			ts += 1;
			ms -= 1000;
		}

		totalBlocks++;
	}

	// Clean up memory allocators
	delete entry;
	delete hexChar;

	return retCode;
}

//  Main processing - form filenames, open and check file streams

int main(int argc, char* argv[])
{
    char            inEvtName[128];
    char            inLogName[128];

    char            outRawName[128] = "";
    char            outEvtName[128] = "";
	char            outFiltName[128] = "";
	char            outLogName[128] = "";

    // Verify all arguments are present on command line
    if (argc < 3) {
        PrintUsage("Error: Not enough arguments on command line");
        return -1;
    }

    strcpy_s(inEvtName, sizeof(inEvtName), argv[1]);
    strcat_s(inEvtName, sizeof(inEvtName), ".dsevents");
    strcpy_s(inLogName, sizeof(inLogName), argv[1]);
    strcat_s(inLogName, sizeof(inLogName), ".dslog");

    strcpy_s(outRawName, sizeof(outRawName), argv[2]);
    strcat_s(outRawName, sizeof(outRawName), "-raw.txt");
    strcpy_s(outEvtName, sizeof(outEvtName), argv[2]);
    strcat_s(outEvtName, sizeof(outEvtName), "-evt.txt");
    strcpy_s(outLogName, sizeof(outLogName), argv[2]);
    strcat_s(outLogName, sizeof(outLogName), "-log.txt");
//	strcpy_s(outCsvName, sizeof(outCsvName), argv[2]);
//  strcat_s(outCsvName, sizeof(outCsvName), ".csv");

    std::cout << "Info: input DS events file  " << inEvtName << std::endl;
    std::cout << "Info: input DS log file     " << inLogName << std::endl;
    std::cout << "Info: output raw event file " << outRawName << std::endl;
    std::cout << "Info: output event file     " << outEvtName << std::endl;
	std::cout << "Info: output log file       " << outLogName << std::endl;

    // Open the input file
    std::ifstream inEvtFile(inEvtName, std::ifstream::binary);
    if (!inEvtFile.good()) {
        PrintUsage("Error: could not open input DS event file");
        return -1;
    }

    // Report the file size and then rewind
    inEvtFile.seekg(0, inEvtFile.end);
    std::cout << "Info: input events size   " << inEvtFile.tellg() << " bytes" << std::endl;
    inEvtFile.seekg(0, inEvtFile.beg);

    // Open the output raw file as output only
    std::ofstream outRawFile(outRawName);
    if (!outRawFile.good()) {
        PrintUsage("Error: could not open output message file");
        return -1;
    }

    // Open the output event file as in/out file
    std::fstream outEvtFile(outEvtName);
    if (!outEvtFile.good()) {
        PrintUsage("Error: could not open output message file");
        return -1;
    }

	// Check for filter argument
	if (argc >= 4) {
		strcpy_s(outFiltName, sizeof(outFiltName), argv[2]);
		strcat_s(outFiltName, "-");
		strcat_s(outFiltName, argv[3]);
		strcat_s(outFiltName, sizeof(outFiltName), ".filt");
	}
	std::cout << "Info: output filtered file  " << outFiltName << std::endl;

	// Open the output csv file
    std::ofstream outFiltFile(outFiltName);
    if (!outFiltFile.good()) {
        PrintUsage("Error: could not open output CSV file");
        return -1;
    }

    // Print file name in first line of msg file
    outEvtFile << "Text from file: " << inEvtName << std::endl;

    // Process header and if valid, the blocks
    if (ProcessDSFileHeader(inEvtFile)) {
        ProcessEventBlocks(inEvtFile, outRawFile, outEvtFile);
        ProcessSearchString(outEvtFile, outFiltFile, argv[3]);
    }

	// Open the output event file as in/out file
	std::ifstream inLogFile(inLogName, std::ifstream::binary);
	if (!inLogFile.good()) {
		PrintUsage("Error: could not input DS log file");
		return -1;
	}

	if (ProcessDSFileHeader(inLogFile)) {
		ProcessLogBlocks(inLogFile);
	}

    // Close up files to be polite
    inEvtFile.close();
    outRawFile.close();
    outEvtFile.close();
    outFiltFile.close();

    return 0;
}
