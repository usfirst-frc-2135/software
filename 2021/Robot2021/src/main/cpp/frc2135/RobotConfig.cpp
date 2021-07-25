/*
 * RobotConfig.cpp
 *
 *  Created on: Jan 13, 2018
 *      Author: Administrator
 */

#include <algorithm>
#include <fstream>  // std::ifstream
#include <map>
#include <string.h> // strncmp
#ifdef _WIN32       // gethostname
    #include <winsock.h>
#else
    #include <unistd.h>
#endif

#include "frc2135/RobotConfig.h"

#include <frc/Filesystem.h>
#include <frc/RobotBase.h>
#include <spdlog/fmt/bundled/ranges.h>
#include <spdlog/spdlog.h>
#include <wpi/SmallString.h>

//////////////////////////////////////////////////////////

namespace frc2135
{
    RobotConfig *RobotConfig::currentConfig = nullptr;

    //////////////////////////////////////////////////////////

    void trimWhitespace(std::string &line)
    {
        line.erase(
            std::remove_if(
                line.begin(),
                line.end(),
                [](char c) { return (c == '\r' || c == '\t' || c == ' ' || c == '\n'); }),
            line.end());
    }

    ////////////////////////////////////////////////////////////////////////////////

    RobotConfig::RobotConfig()
    {
        spdlog::info("RobotConfig -- LoadConfig Started  --");
        LoadConfig();
        spdlog::info("RobotConfig -- LoadConfig Finished --");
        spdlog::info("RobotConfig -- DumpConfig Started  --");
        DumpConfig();
        spdlog::info("RobotConfig -- DumpConfig Finished --");
    }

    RobotConfig::~RobotConfig() {}

    ////////////////////////////////////////////////////////////////////////////////

    RobotConfig *RobotConfig::GetInstance()
    {
        if (RobotConfig::currentConfig == nullptr)
        {
            spdlog::info("RobotConfig -- Creating new RobotConfig object");
            RobotConfig::currentConfig = new RobotConfig();
        }

        return RobotConfig::currentConfig;
    }

    ////////////////////////////////////////////////////////////////////////////////

#include <frc/Filesystem.h>

    void RobotConfig::GetConfigFileName(std::string &fileName)
    {
        // Initialize with the absolute path to the home directory
        wpi::SmallString<64> deployDirectory;
        frc::filesystem::GetDeployDirectory(deployDirectory);
        deployDirectory.append("/");

        // Default the host name of the roboRIO
        char nameBuf[] = "roborio-2135";

        // If running on RoboRIO, get its name
        if (frc::RobotBase::IsReal())
            gethostname(nameBuf, sizeof(nameBuf));

        // Add the robot number to the file name
        fileName.append(nameBuf, 8, 4);
        fileName.append("_configuration.txt");
        fileName.insert(0, deployDirectory.str());
    }

    ////////////////////////////////////////////////////////////////////////////////

    bool RobotConfig::LoadConfig()
    {
        std::string fileName;

        GetConfigFileName(fileName);
        std::ifstream configFile(fileName);
        if (configFile.good() == false)
        {
            spdlog::error("RobotConfig -- No such file {}", fileName);
            return false;
        }

        m_configMap.clear();

        spdlog::info("RobotConfig -- Loading File {}", fileName);
        while (configFile.eof() == false)
        {
            std::string name;
            std::string valueStr;
            std::string delimiter = "=";
            std::string line;

            while (getline(configFile, line))
            {
                name = ""; // Reset

                trimWhitespace(line);
                if (line[0] == '#') // Skipping comment line
                    continue;

                size_t pos = 0;
                if ((pos = line.find(delimiter)) != std::string::npos)
                {
                    name = line.substr(0, pos);
                    trimWhitespace(name);
                    line.erase(0, pos + delimiter.length());
                    trimWhitespace(line);
                    valueStr = line;
                }

                if (!name.empty())
                    m_configMap[name] = valueStr;

                if (configFile.bad() == true)
                {
                    spdlog::error("RobotConfig -- configFile {} bad", fileName);
                    return false;
                }
            }
        }

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // will return false only if there is no value found or specified (default or from file)

    bool RobotConfig::GetValueAsString(const std::string &name, std::string &valueStr, std::string defaultStr)
    {
        bool rtnStatus = false;

        valueStr = m_configMap[name];

        if (!valueStr.empty())
        {
            rtnStatus = true;
        }
        else // this name was not found in m_configMap, so add it using defaultValue.
        {
            if (!defaultStr.empty())
            {
                valueStr = defaultStr;
                m_configMap[name] = valueStr;
                spdlog::warn("RobotConfig -- {} NOT found - using default value {}", name, defaultStr);
                rtnStatus = true;
            }
            else
                spdlog::error("RobotConfig -- {} NOT found and no default value", name);
        }

        return rtnStatus;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Returns true if successful, puts value in valueInt.

    bool RobotConfig::GetValueAsInt(const std::string &name, int &valueInt, int defaultInt)
    {
        bool rtnStatus = false;

        std::string valueStr = m_configMap[name];

        if (!valueStr.empty())
        {
            valueInt = stoi(valueStr); // convert to int
            rtnStatus = true;
        }
        else // this name is not found in m_configMap, so add it if there is a default specified
        {
            if (defaultInt != DUMMY_DEFAULT_INT)
            {
                valueInt = defaultInt;
                std::string valueStr = std::to_string(defaultInt);
                m_configMap[name] = valueStr;
                spdlog::warn("RobotConfig -- {} not found - using default value {}", name, defaultInt);
                rtnStatus = true;
            }
            else
                spdlog::error("RobotConfig -- {} not found and no default value", name);
        }

        return rtnStatus;
    }

    ////////////////////////////////////////////////////////////////////////////////

    // Returns true if given name is found in config map & puts its value in valueBool.
    //     default bool if no default is specified  will be false

    bool RobotConfig::GetValueAsBool(const std::string &name, bool &valueBool, bool defaultBool)
    {
        bool rtnStatus = false;

        std::string valueStr = m_configMap[name];

        if (!valueStr.empty())
        {
            // Assumes that value string is always lowercase 'true' or '1'.
            if ((valueStr == "true") || (valueStr == "1"))
                valueBool = true;
            else
                valueBool = false;
            rtnStatus = true;
        }
        else // not found in m_configMap, so use default.
        {
            valueBool = defaultBool;
            std::string defaultStr("false");
            if (defaultBool)
                defaultStr = "true";
            m_configMap[name] = defaultStr;
            spdlog::warn("RobotConfig -- {} not found - using default value {}", name, defaultBool);
            rtnStatus = true;
        }

        return rtnStatus;
    }

    ////////////////////////////////////////////////////////////////////////////////

    bool RobotConfig::GetValueAsFloat(const std::string &name, float &valueFloat, float defaultFloat)
    {
        bool rtnStatus = false;

        std::string valueStr = m_configMap[name];

        if (!valueStr.empty())
        {
            valueFloat = stof(valueStr); // convert stored value to float
            rtnStatus = true;
        }
        else
        {
            if (defaultFloat != DUMMY_DEFAULT_FLOAT)
            {
                valueFloat = defaultFloat;
                std::string defaultStr = std::to_string(defaultFloat);
                m_configMap[name] = defaultStr;
                spdlog::warn("RobotConfig -- {} not found using default value {}", name, defaultFloat);
                rtnStatus = true;
            }
            else
                spdlog::error("RobotConfig -- {} not found and no default value specified", name);
        }

        return rtnStatus;
    }

    ////////////////////////////////////////////////////////////////////////////////

    bool RobotConfig::GetValueAsDouble(const std::string &name, double &valueDouble, double defaultDouble)
    {
        bool rtnStatus = false;

        std::string valueStr = m_configMap[name];

        if (!valueStr.empty())
        {
            valueDouble = stod(valueStr); // convert stored value to double
            rtnStatus = true;
        }
        else
        {
            if (defaultDouble != DUMMY_DEFAULT_DOUBLE)
            {
                valueDouble = defaultDouble;
                std::string defaultStr = std::to_string(defaultDouble);
                m_configMap[name] = defaultStr;
                spdlog::warn("RobotConfig -- {} not found - using default value {}", name, defaultDouble);
                rtnStatus = true;
            }
            else
                spdlog::error("RobotConfig -- {} not found and no default value specified", name);
        }

        return rtnStatus;
    }

    ////////////////////////////////////////////////////////////////////////////////

    void RobotConfig::DumpConfig()
    {
        for (auto it = m_configMap.begin(); it != m_configMap.end(); it++)
            spdlog::info("    {} = {}", it->first, it->second);

        // This is testing the get functions with our dummy file. We can remove this once we are confident with the functions.

#if defined(CONFIG_TESTING)
        float valueFloat;
        if (GetValueAsFloat("AutonDriveSpeed", valueFloat))
            spdlog::info("Test0: AutonDriveSpeed {}", valueFloat);
        else
            spdlog::error("Test0: AutonDriveSpeed could not get float value.");

        int valueInt;
        if (GetValueAsInt("BlahBlah", valueInt))
            spdlog::info("Test1: BlahBlah (as int) {}", valueInt);
        else
            spdlog::error("Test1: BlahBlah could not get int value.");

        bool valueBool;
        if (GetValueAsBool("BlahBlah", valueBool))
            spdlog::info("Test2: BlahBlah (as bool) {}", valueBool);
        else
            spdlog::error("Test2: BlahBlah could not get bool value.");

        if (GetValueAsBool("NatureWalk", valueBool))
            spdlog::info("Test3: NatureWalk {}", valueBool);
        else
            spdlog::error("Test3: NatureWalk could not get value.");

        if (GetValueAsFloat("DeprecatedClimber", valueFloat))
            spdlog::info("Test4: DeprecatedClimber {}", valueFloat);
        else
            spdlog::error("Test4: DeprecatedClimber could not get float value.");

        if (GetValueAsInt("ThingOne", valueInt))
            spdlog::info("Test5: ThingOne {}", valueInt);
        else
            spdlog::error("Test5: ThingOne could not get int value.");

        if (GetValueAsInt("ThingTwo", valueInt))
            spdlog::info("Test6: ThingTwo {}", valueInt);
        else
            spdlog::error("Test6: ThingTwo could not get int value.");

        if (GetValueAsBool("PeopleOut", valueBool))
            spdlog::info("Test7: PeopleOut (as bool) {}", valueBool);
        else
            spdlog::error("Test7: PeopleOut could not get bool value.");

        std::string valueString;
        if (GetValueAsString("PeopleOut", valueString))
            spdlog::info("Test8: PeopleOut (as string) {}", valueString);
        else
            spdlog::error("Test8: PeopleOut (as string) could not get value.");

        if (GetValueAsFloat("Keyboard", valueFloat, 22.5))
            spdlog::info("Test9: Keyboard {}", valueFloat);
        else
            spdlog::error("Test9: Keyboard could not get float value.");

        // The expected value of Keyboard should be 22.5
        if (GetValueAsFloat("Keyboard", valueFloat, 56.7))
            spdlog::info("Test10: Keyboard {}", valueFloat);
        else
            spdlog::error("Test10: Keyboard could not get float value.");

        if (GetValueAsFloat("Mouse", valueFloat))
            spdlog::info("Test11: Mouse {}", valueFloat);
        else
            spdlog::error("Test11: Keyboard could not get float value.");

        if (GetValueAsInt("Fence", valueInt))
            spdlog::info("Test12: Fence (as int) {}", valueInt);
        else
            spdlog::error("Test12: Fence could not get int value.");

        if (GetValueAsInt("Gate", valueInt, 999999))
            spdlog::info("Test13: Gate (int) {}", valueInt);
        else
            spdlog::error("Test13: Gate could not get int value.");

        if (GetValueAsBool("Tea", valueBool))
            spdlog::info("Test14: Tea (as bool) {}", valueBool);
        else
            spdlog::error("Test14: Tea could not get bool value.");

        if (GetValueAsFloat("Chair", valueFloat, DUMMY_DEFAULT_FLOAT))
            spdlog::info("Test15: Chair (as float) {}", valueFloat);
        else
            spdlog::error("Test15: Chair could not get float value.");

        if (GetValueAsString("Sweatpants", valueString))
            spdlog::info("Test16: Sweatpants (as string) {}", valueString);
        else
            spdlog::error("Test16: Sweatpants (as string) could not get value.");
#endif
    }

} /* namespace frc2135 */
