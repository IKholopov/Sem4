#ifndef CUSTOM_MALLOC_H
#define CUSTOM_MALLOC_H

#include <fstream>
#include <sstream>

#define LOG_PATH "log.txt"

class Logger
{
    public:
        static Logger& logger();
        friend std::stringstream& operator<<(Logger& log, std::stringstream& input)
        {
            log.logFile << input.str();
            return input;
        }

    private:
        Logger();
        ~Logger();
        std::ofstream logFile;
};


#endif
