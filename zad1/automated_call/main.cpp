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

    std::string exe_path(std::regex_replace(argv[0], std::regex("automated_call"), "puzzle_solver"));
    std::string path_with_args(exe_path + " bfs LRUD ../../start_state.txt end_state.txt extra_info.txt");
    // https://stackoverflow.com/questions/12862739/convert-string-to-char
    char* args = (char *)alloca(path_with_args.size() + 1);
    memcpy(args, path_with_args.c_str(), path_with_args.size() + 1);

//    LPCSTR lpApplicationName = exe_path.c_str();
//    LPSTR lpCommandLine = exe_path + args;
    // start the program up
    int retCode = CreateProcessA (
        NULL,
        args,
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        TRUE,                  // Set handle inheritance to FALSE
        0,     // Opens file in a separate console
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory
        &si,            // Pointer to STARTUPINFO structure
        &pi           // Pointer to PROCESS_INFORMATION structure
    );
    WaitForSingleObject(pi.hProcess, 10000);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    std::cout << "Subprocess returned: " << retCode << '\n';
    return 0;
}
