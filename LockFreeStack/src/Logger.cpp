#include <Logger.h>
#include <fstream>

Logger&Logger::logger()
{
    static Logger logger;
    return logger;
}

Logger::Logger():logFile(std::ofstream(LOG_PATH))
{
    logFile << "New Session " << std::endl;
}

Logger::~Logger()
{
    logFile.close();
}
