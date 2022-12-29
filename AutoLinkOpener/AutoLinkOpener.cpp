#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>

// Open the specified URL in the default web browser
void openUrl(const std::string& url) {
    // Use the "start" command to open the URL on Windows
    std::string command = "start " + url;
    system(command.c_str());
}

int main() {
    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(5, 10);

    std::cout << "Choose a rate limit option:" << std::endl;
    std::cout << "1. No delay" << std::endl;
    std::cout << "2. Single number delay" << std::endl;
    std::cout << "3. Random delay" << std::endl;

    int option;
    std::cin >> option;

    int delay;
    if (option == 2) {
        std::cout << "Enter delay in seconds: ";
        std::cin >> delay;
    }

    if (option == 3) {
        std::cout << "Enter minimum delay in seconds: ";
        int minDelay;
        std::cin >> minDelay;

        std::cout << "Enter maximum delay in seconds: ";
        int maxDelay;
        std::cin >> maxDelay;
        dis = std::uniform_int_distribution<>(minDelay, maxDelay);
        delay = dis(gen);
    }

    // Open the file of URLs
    std::ifstream file("urls.txt");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file" << std::endl;
        return 1;
    }

    // Read the file line by line
    std::string line;
    int line_count = 0;
    while (std::getline(file, line)) {
        ++line_count;
    }
    file.clear();
    file.seekg(0, std::ios::beg);

    // Read the file line by line
    int count = 0;
    while (std::getline(file, line)) {
        // Open the URL in the default web browser
        openUrl(line);

        // Rate limit the requests
        if (option == 1) {
            // No delay
        }
        else if (option == 2 || option == 3) {
            std::this_thread::sleep_for(std::chrono::seconds(delay));
        }

        // Print the progress
        std::cout << line_count - ++count << " URLs left" << std::endl;
    }

    return 0;
}
