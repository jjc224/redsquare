#include "ProjectConstants.h"

void logToFile(std::string message)
{
#ifdef DEBUG_LOG_TO_FILE
    std::ofstream outFile("debuglog.log", std::ios::app);
    if(outFile.is_open())
    {
        outFile << message << std::endl;
        outFile.close();
    }
#endif // DEBUG_LOG_TO_FILE
}

void log(std::string message)
{
#ifdef DEBUG_LOGGING
    std::cout << message << std::endl;
    logToFile(message);
#endif //DEBUG_LOGGING
}
