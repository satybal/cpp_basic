// Read files and prints top k word by frequency

// sample launch 
//   ./count_words_async ../Gatsby0.txt ../Gatsby1.txt ../Gatsby2.txt ../Gatsby3.txt ../Gatsby4.txt

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>
#include <chrono>
#include <future>

const size_t TOPK = 10;

using Counter = std::map<std::string, std::size_t>;

std::string tolower(const std::string &str);

Counter thread_counter(std::istream& stream);

void print_topk(std::ostream& stream, const Counter& counter, const size_t k);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }
    
    // starting timer
    auto start = std::chrono::high_resolution_clock::now();

    // openning book files
    std::vector<std::ifstream> files; 
    for (int i=1; i<argc; ++i) {
        files.push_back(std::ifstream(argv[i]));
    }

    // starting a counting thread for each book
    std::vector<std::future<Counter>> counters;
    for (size_t i=0; i<files.size(); ++i) {
        counters.push_back(std::async(thread_counter, std::ref(files[i])));
    }

    // gathering results for each book
    std::vector<Counter> results;
    for (size_t i=0; i<files.size(); ++i) {
        results.push_back(counters[i].get());
    }

    // compiling the results into one 
    Counter total_result = results[0];
    for (size_t i=1; i<results.size(); ++i) {
        for (const auto& [key, value]: results[i]) {
            total_result[key] += results[i][key];
        }
    }

    // showing results
    print_topk(std::cout, total_result, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";

    return 0;
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

Counter thread_counter(std::istream& stream) {
    Counter out;
    std::string word;
    
    while (stream >> word)
        ++out[tolower(word)];

    return out;
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}