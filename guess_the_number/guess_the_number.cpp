#include <check_value.h>
#include <random_value.h>
#include <high_scores.h>
#include <iostream>
#include <string>


int main(int argc, char** argv) {
    std::string usr_name;
    std::cout << "Please enter your name:" << std::endl;
    std::cin >> usr_name;

    if (argc > 1) {
        // -max
        if (argv[1] == "-max") {
            save_results(usr_name, check_value(random_value(std::stoi(argv[2]))));
        }
    }
    return 0;
}