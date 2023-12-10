//
// Created by tmai42 on 12/10/23.
//

#ifndef HELPER_FUNCTIONS_HPP
#define HELPER_FUNCTIONS_HPP

#include <iostream>
#include <fstream>
#include <random>
#include <limits>
#include <sstream>
#include <iomanip>
#include <chrono>

#include "lib/file_line_generator.hpp"
#include "lib/sort.hpp"

namespace helpers {

    void generate_random_file_of_doubles(const std::string& filename, size_t file_size = 1073741824 /* 1 GB oin bytes */) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> dist(std::numeric_limits<double>::min(), std::numeric_limits<double>::max());

        size_t bytes_written = 0;
        while (bytes_written < file_size) {
            const double number = dist(gen);
            std::stringstream ss;
            ss << std::scientific << std::setprecision(5) << number << std::endl;

            std::string numStr = ss.str();
            const size_t numBytes = numStr.size();

            if (bytes_written + numBytes > file_size) break;

            file << numStr;
            bytes_written += numBytes;
        }
    }

    void iterate_through_file(const std::string& filename){
        file_line_generator generator(filename);

        std::cout << "Start iterating...\n"
                     "* press Enter to get next line\n"
                     "* enter anything to stop process\n\n"
                     "File:\n";

        while (auto value_opt = generator.next()) {
            std::cout << *value_opt;
            if ('\n' != std::cin.get()) { // returns if it gets something except Enter key
                break;
            }
        }
    }

    bool is_sorted(const std::string& filename) {
        file_line_generator generator(filename);
        double previous_value = -std::numeric_limits<double>::min();

        while (auto value_opt = generator.next()) {
            double value = *value_opt;
            if (value < previous_value) {
                return false;  // Data is not sorted
            }
            previous_value = value;
        }

        return true;  // All data is sorted
    }

    void sort(const std::string &input_filename, const std::string &output_filename){
        auto begin = std::chrono::high_resolution_clock::now();

        sorting_algorithms::external_sort(input_filename, output_filename, 104857600); // 100 MB

        auto spend_time = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - begin);
        std::cout<<"Sorting takes: " << spend_time << "\n";

        std::cout << output_filename << (is_sorted(output_filename) ? " is sorted!\n" : "is NOT sorted!") << std::endl;

    }

}

#endif //HELPER_FUNCTIONS_HPP
