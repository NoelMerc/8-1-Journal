#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <string> // Added for std::string and std::getline

class ItemTracker {
private:
    std::map<std::string, int> frequencyMap;

public:
    void readInputFile(const std::string& filename) {
        std::ifstream inputFile(filename);
        if (!inputFile.is_open()) {
            std::cerr << "Error: Unable to open input file.\n";
            exit(EXIT_FAILURE);
        }

        std::string item;
        while (std::getline(inputFile, item)) {
            frequencyMap[item]++;
        }

        inputFile.close();
    }

    void printFrequency() const {
        for (const auto& pair : frequencyMap) {
            std::cout << pair.first << " " << pair.second << std::endl;
        }
    }

    void printHistogram() const {
        for (const auto& pair : frequencyMap) {
            std::cout << pair.first << " " << std::string(pair.second, '*') << std::endl;
        }
    }

    int getFrequency(const std::string& item) const {
        return frequencyMap.count(item) ? frequencyMap.at(item) : 0;
    }

    void backupData(const std::string& filename) const {
        std::ofstream outputFile(filename);
        if (!outputFile.is_open()) {
            std::cerr << "Error: Unable to open output file.\n";
            exit(EXIT_FAILURE);
        }

        for (const auto& pair : frequencyMap) {
            outputFile << pair.first << " " << pair.second << std::endl;
        }

        outputFile.close();
    }
};

int main() {
    ItemTracker tracker;
    tracker.readInputFile("CS210_Project_Three_Input_File.txt");

    int choice;
    std::string item;
    do {
        std::cout << "Menu:\n"
            "1. Search for an item\n"
            "2. Print frequency of all items\n"
            "3. Print histogram\n"
            "4. Exit\n"
            "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter item to search: ";
            std::cin >> item;
            std::cout << "Frequency of " << item << ": " << tracker.getFrequency(item) << std::endl;
            break;
        case 2:
            tracker.printFrequency();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            tracker.backupData("frequency.dat");
            std::cout << "Data backed up successfully. Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}