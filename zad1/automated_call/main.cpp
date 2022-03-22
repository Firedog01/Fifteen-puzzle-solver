#include <iostream>
#include <thread>
#include <filesystem>
#include "../puzzle_solver/lib/manager.h"


using namespace std;

int main(int argc, char *argv[]) {
    string PROJECT_DIR("zad1");
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

    info_bundle info;
    for (const auto& entry : filesystem::directory_iterator(file_dir)) {
        string file_path = entry.path().string();
        auto fnIdx = file_path.find(STARTS_DIR);
        fnIdx += STARTS_DIR.length();
        string file_name = file_path.substr(fnIdx);
        file_name = file_name.substr(0, file_name.find('.'));
        string strategy = "bfs";
        for(const auto& order : orders) {
            stringstream out_file_name;
            out_file_name <<  program_root << OUT_BFS << file_name << "_" << strategy << "_" << order;
            string result_file = out_file_name.str() + "_sol.txt";
            string extra_file = out_file_name.str() + "_stats.txt";

            manager manager(strategy, order, file_path, result_file, extra_file);
            manager.find_solution();
        }
    }
    cout << "calkowity czas egzekucji dla bfs: " << info.get_time() << " ms";
    return 0;
}