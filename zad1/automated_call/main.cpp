#include <iostream>
#include <thread>
#include <filesystem>
#include "../puzzle_solver/lib/manager.h"

#define BFS 0
#define DFS 1
#define ASTR 2

#define CUR_RUNNED BFS

using namespace std;

void get_average_time(string program_root);

int main(int argc, char *argv[]) {
    string PROJECT_DIR("zad1");
    string STARTS_DIR(R"(files_zad1\start_state_7\)");
    string OUT_BFS(R"(files_zad1\bfs\)");
    string OUT_DFS(R"(files_zad1\dfs\)");
	string OUT_ASTR(R"(files_zad1\astr\)");

    //*
//    string orders[] = {"lrud","lrdu","lurd","ludr",
//    "ldru","ldur","rlud","rldu",
//    "ruld","rudl","rdlu","rdul",
//    "ulrd","uldr","urld","urdl",
//    "udlr","udrl","dlru","dlur",
//    "drlu","drul","dulr","durl"};
    //*/
    string orders[] = {"rdul", "rdlu", "drul", "drlu",
                       "ludr", "lurd", "uldr", "ulrd"};

    string this_path(argv[0]);
    string program_root = this_path.substr(0, this_path.find(PROJECT_DIR));
    string file_dir = program_root + STARTS_DIR;
//	get_average_time(program_root);
//	return 0;
    info_bundle info;
    for (const auto& entry : filesystem::directory_iterator(file_dir)) {
        string file_path = entry.path().string();
        auto fnIdx = file_path.find(STARTS_DIR);
        fnIdx += STARTS_DIR.length();
        string file_name = file_path.substr(fnIdx);
        file_name = file_name.substr(0, file_name.find('.'));
#if CUR_RUNNED == BFS
        string strategy = "bfs";
		string out_dir = OUT_BFS;
#elif CUR_RUNNED == DFS
		string strategy = "dfs";
		string out_dir = OUT_DFS;
#elif CUR_RUNNED == ASTR
		string strategy = "astr";
		string out_dir = OUT_ASTR;
#endif
        for(const auto& order : orders) {
            stringstream out_file_name;
            out_file_name <<  program_root << out_dir << file_name << "_" << strategy << "_" << order;
            string result_file = out_file_name.str() + "_sol.txt";
            string extra_file = out_file_name.str() + "_stats.txt";

            manager manager(strategy, order, file_path, result_file, extra_file);
            manager.find_solution();
        }
    }
    cout << "calkowity czas egzekucji: " << info.get_time() << " ms";
    return 0;
}

void get_average_time(string program_root) {
	string strategy = "bfs";
	string order = "lrud";
	string file_path = program_root + "zad1\\files\\start_state_15.txt";
	string result_file = program_root + "zad1\\files\\solution_15.txt";
	string extra_file = program_root + "zad1\\files\\extra_info_15.txt";
	int length = 100;
	double total = 0;
	for(int i = 0; i < length; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
	for(int i = 0; i < length; i++) {
		std::cout << '|';
		manager manager(strategy, order, file_path, result_file, extra_file);
		manager.find_solution();
		ifstream extra(extra_file);
		string buffer;
		for(int j = 0; j < 5; j++) {
			extra >> buffer;
		}
		total += stod(buffer);
	}
	std::cout << "\naverage: " << (total / (double) length) << '\n';
}