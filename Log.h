#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class Log
{
    private:
        static std::ofstream logFile;
        static std::string lastUse;
    public:

        static void log(std::string msg, std::string sender)
        {
            if (lastUse != sender)
                logFile << sender << ": \n\t" << msg << std::endl;
            else
                logFile << "\t" << msg << std::endl;
            lastUse = sender;
        }

        static void log(std::vector<std::string> msg, std::string sender)
        {
            std::stringstream msgSS;
            for (std::string s : msg)
                msgSS << s << " ";
            if (lastUse != sender)
                logFile << sender << ": \n\t" << msgSS.str() << std::endl;
            else
                logFile << "\t" << msgSS.str() << std::endl;
            lastUse = sender;
        }
};