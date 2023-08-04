#include "check_value.h"
#include "random_value.h"
#include "high_scores.h"
#include <iostream>
#include <string>

bool is_number(const std::string& s)
{
    for (char const &ch : s) {
        if (!std::isdigit(ch)) return false;
    }
    return true;
}

bool valid_arguments(const int argc, const char** argv) {
    const std::string key = argv[1];

    if (key == "-table") return true;

    else if (argc > 2) {
        const std::string value = argv[2];

        return (is_number(value)) &&
               ((key == "-max"   && std::stoi(value) > 0) ||
                (key == "-level" && std::stoi(value) > 0 && std::stoi(value) < 4));
    } else return false;
}

std::string set_user() {
    std::string user_name;
    std::cout << "Please enter your name:" << std::endl;
    std::cin >> user_name;

    return user_name;
}

int main(const int argc, const char** argv) {
    if (argc > 1 && valid_arguments(argc, argv)) {
        const std::string key = argv[1];
        
        if (key == "-table") show_high_scores();
        
        else if (argc > 2) {
            const std::string user_name = set_user();

            if (key == "-max") {
                const int max_value = std::stoi(argv[2]);

                save_results(user_name, check_value(random_value(max_value)));
            } else if (key == "-level") {
                const int level = std::stoi(argv[2]);
                int max_value = 0;

                if      (level == 1) max_value = 10;
                else if (level == 2) max_value = 50;
                else if (level == 3) max_value = 100;

                save_results(user_name, check_value(random_value(max_value)));
            }
        }
    } else if (argc == 1) { // default case without arguments (0..9)
        const std::string user_name = set_user();

        save_results(user_name, check_value(random_value(10)));
    } else {
        std::cout << "Bad arguments! Usage:" << std::endl;
        std::cout << " Key   | Value" << std::endl;
        std::cout << "---------------------" << std::endl;
        std::cout << "-max   | integer > 0" << std::endl;
        std::cout << "-level | integer 1..3" << std::endl;
        std::cout << "-table | nothing" << std::endl;
    }
    return 0;
}
