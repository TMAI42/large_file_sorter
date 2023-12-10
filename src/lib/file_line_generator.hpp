//
// Created by tmai42 on 12/10/23.
//

#ifndef LINE_GENERATOR_HPP
#define LINE_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <fstream>
#include <optional>
#include <limits>

class file_line_generator {
public:
    file_line_generator(const std::string& filename) : file(filename) {
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file: " + filename);
        }
    }

    std::optional<double> next() {
        std::string line;
        if (std::getline(file, line)) {
            return std::stod(line);
        }
        return {};
    }

private:
    std::ifstream file;
};


#endif //LINE_GENERATOR_HPP
