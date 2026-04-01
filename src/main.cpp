/**
 * @file main.cpp
 * @author zuudevs (zuudevs@gmail.com)
 * @brief A CLI utility for reading files.
 * @version 1.0.0
 * @date 2026-04-01
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <algorithm>
#include <cstdint>
#include <print>
#include <fstream>
#include <string>
#include <string_view>
#include <cstdio>

namespace credit {
    [[maybe_unused]] constexpr std::string_view author = "zuudevs";
    [[maybe_unused]] constexpr std::string_view email = "zuudevs@gmail.com";
    [[maybe_unused]] constexpr std::string_view repository = "https://github.com/zuudevs/rdfile.git";
    [[maybe_unused]] constexpr std::string_view version = "1.0.0";
}

namespace ansi {
    [[maybe_unused]] constexpr std::string_view black = "\033[0;30m"; 
    [[maybe_unused]] constexpr std::string_view red = "\033[0;31m"; 
    [[maybe_unused]] constexpr std::string_view green = "\033[0;32m"; 
    [[maybe_unused]] constexpr std::string_view yellow = "\033[0;33m"; 
    [[maybe_unused]] constexpr std::string_view blue = "\033[0;34m"; 
    [[maybe_unused]] constexpr std::string_view purple = "\033[0;35m"; 
    [[maybe_unused]] constexpr std::string_view cyan = "\033[0;36m"; 
    [[maybe_unused]] constexpr std::string_view white = "\033[0;37m";
    [[maybe_unused]] constexpr std::string_view reset = "\033[0m";
}

[[nodiscard]] inline 
std::string colorize(
    std::string_view str, 
    std::string_view color
) noexcept {
    return std::string(color) + std::string(str) + std::string(ansi::reset);
}

void print_about() {
    std::println(
		"{}", 
		colorize("=== About rdfile ===", ansi::purple)
	);
    std::println("rdfile (Read File) is a simple command line utility");
    std::println("which is designed to read and display the text contents of a file.");
    std::println();
    std::println(
		"{:<12} {}", "Author:", 
		colorize(credit::author, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Email:", 
		colorize(credit::email, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Repository:", 
		colorize(credit::repository, ansi::blue)
	);
    std::println(
		"{:<12} {}", "Version:", 
		colorize(credit::version, ansi::blue)
	);
}

void print_version() {
    std::println(
		"rdfile version {}", 
		colorize(credit::version, ansi::blue)
	);
    std::println(
		"--------------------------------------------------"
	);
    std::println(
		"Maintained by {}", 
		colorize(credit::author, ansi::blue)
	);
}

void print_help() {
    std::println(
		"{} rdfile [OPTIONS] <file>", 
		colorize("Usage:", ansi::blue)
	);
    std::println();
    std::println(
		"{}", 
		colorize("Options:", ansi::blue)
	);
    std::println(
		"  {:<18} Show this help message", 
		colorize("-h, --help", ansi::cyan)
	);
    std::println(
		"  {:<18} Show version information", 
		colorize("-v, --version", ansi::cyan)
	);
    std::println(
		"  {:<18} Show application about/credits", 
		colorize("-a, --about", ansi::cyan)
	);
    std::println(
		"  {:<18} Show line numbers", 
		colorize("-n, --number", ansi::cyan)
	);
}

void show_content(std::string_view filename, bool with_number = false) {
    std::ifstream file(filename.data());
    if (!file) {
        std::println(
			stderr, 
			"{} cannot open '{}' (No such file or permission denied)", 
            colorize("ERROR:", ansi::red), 
			filename
		);
        return;
    }

    std::string line;
    uint32_t iter{0};

    while (std::getline(file, line)) {
		size_t pos;
		while ((pos = line.find('\t')) != std::string::npos) {
			line.replace(pos, 1, "    ");
		}

        if (with_number) {
            std::println("{}{: >6}{} | {}", 
                ansi::cyan, 
                ++iter, 
                ansi::reset,
                line
            );
        } else {
            std::println("{}", line);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string_view arg1 = argv[1];

    if (arg1 == "-h" || arg1 == "--help") {
        print_help();
    } else if (arg1 == "-v" || arg1 == "--version") {
        print_version();
    } else if (arg1 == "-a" || arg1 == "--about") {
        print_about();
    } else if (arg1 == "-n" || arg1 == "--number") {
        if (argc < 3) {
            std::println(
				stderr, 
				"{} Missing filename after {}", 
                colorize("ERROR:", ansi::red), 
				arg1
			);
            return 1;
        }
        std::string_view arg2 = argv[2];
        if (arg2.starts_with("-")) {
            std::println(
				stderr, 
				"{} Invalid filename '{}'", 
                colorize("ERROR:", ansi::red), 
				arg2
			);
            return 1;
        }
        show_content(arg2, true);
    } else if (arg1.starts_with("-")) {
        std::println(
			stderr, 
			"{} Unknown option {}", 
            colorize("ERROR:", ansi::red), 
			arg1
		);
        return 1;
    } else {
        show_content(arg1, false);
    }

    return 0;
}