//
// Created by tmai42 on 12/10/23.
//

#ifndef LINE_GENERATOR_HPP
#define LINE_GENERATOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <coroutine>

class file_line_generator {
public:
    struct promise_type {
        std::string current_line;
        std::ifstream file;
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }

        promise_type() = default;
        ~promise_type() = default;

        file_line_generator get_return_object() {
            return {handle_type::from_promise(*this)};
        }

        std::suspend_always yield_value(std::string line) {
            current_line = std::move(line);
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            std::exit(1);
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    file_line_generator(handle_type h) : handle(h) {}
    ~file_line_generator() { if (handle) handle.destroy(); }

    file_line_generator(const file_line_generator&) = delete;
    file_line_generator& operator=(const file_line_generator&) = delete;

    file_line_generator(file_line_generator&& other) noexcept : handle(other.handle) {
        other.handle = nullptr;
    }

    file_line_generator& operator=(file_line_generator&& other) noexcept {
        if (this != &other) {
            handle = other.handle;
            other.handle = nullptr;
        }
        return *this;
    }

    bool move_next() { return handle ? (handle.resume(), !handle.done()) : false; }
    [[nodiscard]] std::string current_value() const { return handle.promise().current_line; }

private:
    handle_type handle;
};

file_line_generator read_lines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        co_yield line;
    }
}


#endif //LINE_GENERATOR_HPP
