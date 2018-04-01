
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

/**
 * Processes a single message string
 */
void ProcessMessage(const std::string& message, std::ostream& csvStream)
{
  // Only process DriveDistance messages
  if (message.find("DTDD") == std::string::npos)
    {
      return;
    }

  char* msgBuf = new char[message.length()+1];
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
    }
  while ((token = strtok(NULL, " \n")) != NULL);

  csvStream << std::endl;

  delete [] msgBuf;
}


int main(int argc, char* argv[])
{
  if (argc < 4)
    {
      std::cerr << "Usage: eventParser <events-file> <message-file> <csv-file>" << std::endl;
      return 1;
    }

  std::cout << "Info: opening " << argv[1] << std::endl;

  FILE* eventFile = fopen(argv[1], "r");
  if (!eventFile)
    {
      std::cerr << "Error: could not open log file " << argv[1] << std::endl;
      return -1;
    }

  std::ofstream msgFile(argv[2]);
  if (msgFile.good() == false)
    {
      std::cerr << "Error: could not open message file " << argv[2] << std::endl;
      return -1;
    }

  std::ofstream csvFile(argv[3]);
  if (csvFile.good() == false)
    {
      std::cerr << "Error: could not open CSV file " << argv[3] << std::endl;
      return -1;
    }
  csvFile << "\"Match Time\","
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

  const char* matchStr = "<TagVersion>1";
  size_t matchIdx = 0;
  char curChar = '\0';
  while ((curChar = fgetc(eventFile)) != EOF)
    {
      if (curChar == matchStr[matchIdx])
	{
	  if (matchIdx == strlen(matchStr) - 1)
	    {
	      // If whole string now matched, get line and split into individual messages

	      char* lineBuf = NULL;
	      size_t lineLen = 0;
	      ssize_t status = getdelim(&lineBuf, &lineLen, '\0', eventFile);
	      if (status > 0)
		{
		  char* token = strtok(lineBuf, " \n");
		  std::string message = matchStr;
		  do
		    {
		      if (strncmp(token, matchStr, strlen(matchStr)) == 0)
			{
			  msgFile << message << std::endl;

			  ProcessMessage(message, csvFile);

			  message = matchStr;
			}
		      else
			{
			  message += ' ';
			  message += token;
			}
		    }
		  while ((token = strtok(NULL, " \n")) != NULL);
		}

	      free((void*)lineBuf);

	      matchIdx = 0;
	    }
	  else
	    {
	      // Else, look for next char in match string
	      ++matchIdx;
	    }
	}
      else
	{
	  // Reset match string index
	  matchIdx = 0;

	  if (curChar == matchStr[matchIdx])
	    {
	      // If new character matches first char in match string, increment index
	      ++matchIdx;
	    }
	}
    }

  fclose(eventFile);

  return 0;
}
