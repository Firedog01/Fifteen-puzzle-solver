#include <iostream>
#include "lib/manager.h"

struct test {
    int a;
    ~test() {
        this->a = 0;
        std::cout << "destructor called\n";
    }
};

int main(int argc, char *argv[]) {
//    test* t = new test;
//    t->a = 5;
//    std::cout << "a: " << t->a << "t: " << t << '\n';
//    std::queue<test> v;
//    v.push(*t); // czy tu jest tworzona kopia? nie!
//    std::cout << "v[0]: " << v.front().a << "t: " << &v.front() << '\n';
//    v.pop(); // pop calls destructor.
//    std::cout << "a pop: " << t->a << '\n';
//    return 0;

    std::cout << "sizeof(std::size_t): " << sizeof(std::size_t) << '\n'
              << "sizeof(uint64_t): " << sizeof(uint64_t) << '\n';
    if(argc != 6) {
        std::cout << "Incorrect number of parameters!\n"
                  << "Every call should have exactly 5 arguments.\n";
        std::ofstream file("../../output_main.txt");
        file << "incorrect number of args";
        return 1;
    }
    manager manager(argv);
    manager.findSolution();
    return 0;
}


