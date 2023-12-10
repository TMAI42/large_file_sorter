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

#include "lib/file_line_generator.hpp"

namespace helpers {

    void generate_random_file_of_doubles(const std::string& filename, size_t file_size = 1073741824) {
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
        auto gen = read_lines(filename);

        std::cout << "Start iterating...\n"
                     "* press Enter to get next line\n"
                     "* enter anything to stop process\n\n"
                     "File:\n";

        while (gen.move_next()) {
            std::cout << gen.current_value();
            if ('\n' != std::cin.get()) { // returns if it gets something except Enter key
                break;
            }
        }
    }
}

#endif //HELPER_FUNCTIONS_HPP
