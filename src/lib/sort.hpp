//
// Created by tmai42 on 12/10/23.
//

#ifndef LARGE_FILE_SORTER_EXTERNAL_SORT_HPP
#define LARGE_FILE_SORTER_EXTERNAL_SORT_HPP

#include <algorithm>
#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <cstddef>
#include <cstdint>
#include <vector>
#include <queue>

namespace sorting_algorithms {

    void merge_chunks(const std::string& binary_file_name, const std::vector<size_t>& chunk_starts, const size_t max_chunk_size, const std::string& output_file_name) {
        std::ifstream binary_file(binary_file_name, std::ios::binary);
        std::ofstream output_file(output_file_name, std::ios::out);

        std::vector<std::pair<double, size_t>> heap; // here could be priority queue, but std has bag in it when sorting floats/doubles in 23 standard in gcc
        heap.reserve(chunk_starts.size());
        std::vector<size_t> read_doubles(chunk_starts.size(), 0);
        std::vector<size_t> positions = chunk_starts;

        for (size_t i = 0; i < chunk_starts.size(); ++i) {
            binary_file.seekg(positions[i], std::ios::beg);
            double value;
            if (binary_file.read(reinterpret_cast<char*>(&value), sizeof(value))) {
                heap.emplace_back(value, i);
                positions[i] += sizeof(double);
                read_doubles[i]++;
            }
        }

        while (!heap.empty()) {
            auto min_it = std::min_element(heap.begin(), heap.end());
            auto [min_value, min_index] = *min_it;

            output_file << std::scientific << min_value << '\n';
            heap.erase(min_it);

            if (read_doubles[min_index] < max_chunk_size) {
                binary_file.seekg(positions[min_index], std::ios::beg);
                double next_value;
                if (binary_file.read(reinterpret_cast<char*>(&next_value), sizeof(next_value))) {
                    heap.emplace_back(next_value, min_index);
                    positions[min_index] += sizeof(double);
                    read_doubles[min_index]++;
                }
            }
        }
    }

    void write_chunk_to_file(const std::vector<double> &chunk, std::ofstream &file) {
        for (double value: chunk) {
            file.write(reinterpret_cast<const char *>(&value), sizeof(double));
        }
    }

    void external_sort(const std::string &input_filename, const std::string &output_filename, size_t max_memory) {

        std::ifstream input_data(input_filename);
        std::string line;
        size_t memory_threshold = max_memory / 5 * 2; // We want to leave memory for sorting
        size_t max_chunk_size = memory_threshold / sizeof(double);
        std::vector<double> chunk;

        // Temporary file to store sorted chunks
        const std::string temp_filename = "temp.bin";
        std::ofstream temp_file(temp_filename, std::ios::binary);

        size_t chunk_count = 0;

        // Read, sort, and write chunks to temp file
        while (std::getline(input_data, line)) {
            chunk.emplace_back(std::stod(line));
            if (chunk.size() >= max_chunk_size) {
                std::sort(chunk.begin(), chunk.end());
                write_chunk_to_file(chunk, temp_file);
                chunk_count++;
                chunk.clear();
            }
        }

        if (!chunk.empty()) {
            std::sort(chunk.begin(), chunk.end());
            write_chunk_to_file(chunk, temp_file);
            chunk_count++;
        }

        input_data.close();
        temp_file.close();

        std::ifstream temp_input(temp_filename, std::ios::binary);

        std::vector<size_t> chunk_starts;

        for (size_t i = 0; i < chunk_count; ++i) {
            chunk_starts.push_back(i * max_chunk_size * sizeof(double));
        }

        merge_chunks(temp_filename, chunk_starts, max_chunk_size, output_filename);

        std::remove(temp_filename.c_str());
    }

}

#endif //LARGE_FILE_SORTER_EXTERNAL_SORT_HPP
