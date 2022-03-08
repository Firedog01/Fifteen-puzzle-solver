#include <cstdlib>
#include <regex>
#include <Windows.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // additional information
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    // set the size of the structures
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    std::string temp(std::regex_replace(argv[0], std::regex("automated_call"), "puzzle_solver"));
//    temp += " bfs LRUD ../../start_state.txt end_state.txt extra_info.txt";
    LPCSTR lpApplicationName = temp.c_str();
    std::cout << lpApplicationName << '\n';

    // start the program up
    CreateProcessA (
        "C:\\Users\\janru\\Programowanie\\SISE\\zad1\\build\\puzzle_solver\\puzzle_solver.exe",   // the path
        GetCommandLineA(),                // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,     // Opens file in a separate console
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
    );
    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    std::cin >> temp;
    return 0;
}
