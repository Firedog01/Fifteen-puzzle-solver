#include <cstdlib>
#include <regex>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <filesystem>
#include "../puzzle_solver/lib/manager.h"

void windowsProcess(char** argv);

using namespace std;

int main(int argc, char *argv[]) {
//    windowsProcess(argv);
    string PROJECT_DIR("zad1"); // możliwe że u ciebie to będzie cmake-build-debug
    string STARTS_DIR(R"(files_zad1\start_state_7\)");
    string OUT_BFS(R"(files_zad1\bfs\)");

    /*
    string orders[] = {"lrud","lrdu","lurd","ludr",
"ldru","ldur","rlud","rldu",
"ruld","rudl","rdlu","rdul",
"ulrd","uldr","urld","urdl",
"udlr","udrl","dlru","dlur",
"drlu","drul","dulr","durl"};
    //*/
    string orders[] = {"rdul", "rdlu", "drul", "drlu",
                       "ludr", "lurd", "uldr", "ulrd"};

    string this_path(argv[0]);
    string program_root = this_path.substr(0, this_path.find(PROJECT_DIR));
    string file_dir = program_root + STARTS_DIR;
    std::cout << program_root << '\n' << file_dir << '\n';

    info_bundle info;
    for (const auto& entry : filesystem::directory_iterator(file_dir)) {
        string file_path = entry.path().string();
        std::cout << file_path << '\n';
        auto fnIdx = file_path.find(STARTS_DIR);
        fnIdx += STARTS_DIR.length();
        string file_name = file_path.substr(fnIdx);
        file_name = file_name.substr(0, file_name.find('.'));
        std::cout << file_name << '\n';
        // 4x4_01_0001_astr_manh_sol.txt
        // 4x4_01_0001_astr_manh_stats.txt
        string strategy = "bfs";
        for(const auto& order : orders) {
            stringstream out_file_name;
            out_file_name <<  program_root << OUT_BFS << file_name << "_" << strategy << "_" << order;
            string result_file = out_file_name.str() + "_sol.txt";
            string extra_file = out_file_name.str() + "_stats.txt";
            std::cout << "input: " << file_path << " output: " << result_file << '\n';
//            manager manager(strategy, order, file_path, result_file, extra_file);
//            manager.findSolution();
        }
    }
    cout << "calkowity czas egzekucji dla bfs: " << info.getExecutionTime() << " ms";
    return 0;
}

void windowsProcess(char** argv) {
    info_bundle info;
    string exe_path(regex_replace(argv[0], regex("automated_call"), "puzzle_solver"));
    string path_with_args(exe_path + " bfs LRUD ../../files/start_state.txt ../../files/solution.txt ../../files/extra_info.txt");
    // https://stackoverflow.com/questions/12862739/convert-string-to-char
    char* args = (char *)alloca(path_with_args.size() + 1);
    memcpy(args, path_with_args.c_str(), path_with_args.size() + 1);

    ifstream file;
    string buffer;

    double sum = 0;
    int len = 100;

    for(int i = 0; i < len; i++) {
        // additional information
        STARTUPINFOA si;
        PROCESS_INFORMATION pi;
//        if(i % 1 == 0) {
//            cout << i << '\n';
//        }

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
        for(int i = 0; i < 5; i++) {
            file >> buffer;
        }
        file.close();
        sum += stod(buffer);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    cout << "suma: " << sum << " ms, srednio: " << sum / len << " ms\n"
              << "total elapsed: " << info.getExecutionTime() / 1000 << " s\n";
}
