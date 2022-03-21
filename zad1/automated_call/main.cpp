#include <cstdlib>
#include <regex>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include "../puzzle_solver/lib/info/info_bundle.h"

void windowsProcess(char** argv);

int main(int argc, char *argv[]) {
//    windowsProcess(argv);

    return 0;
}

void windowsProcess(char** argv) {
    info_bundle info;
    std::string exe_path(std::regex_replace(argv[0], std::regex("automated_call"), "puzzle_solver"));
    std::string path_with_args(exe_path + " bfs LRUD ../../files/start_state.txt ../../files/end_state.txt ../../files/extra_info.txt");
    // https://stackoverflow.com/questions/12862739/convert-string-to-char
    char* args = (char *)alloca(path_with_args.size() + 1);
    memcpy(args, path_with_args.c_str(), path_with_args.size() + 1);

    std::ifstream file;
    std::string buffer;

    double sum = 0;
    int len = 100;

    for(int i = 0; i < len; i++) {
        // additional information
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
        if(i % 1 == 0) {
            std::cout << i << '\n';
        }

        // set the size of the structures
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // start the program up
        CreateProcessA (
                nullptr,
                args,
                nullptr,                   // Process handle not inheritable
                nullptr,                   // Thread handle not inheritable
                1,                  // Set handle inheritance to true
                0,     // Opens file in a separate console
                nullptr,           // Use parent's environment block
                nullptr,           // Use parent's starting directory
                &si,            // Pointer to STARTUPINFO structure
                &pi           // Pointer to PROCESS_INFORMATION structure
        );
        WaitForSingleObject(pi.hProcess, INFINITE);

        file.open("../../files/extra_info.txt");
        file >> buffer;
        file.close();
        sum += std::stod(buffer);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    std::cout << "suma: " << sum << " ms, srednio: " << sum / len << " ms\n"
              << "total elapsed: " << info.getExecutionTime() / 1000 << " s\n";
}
