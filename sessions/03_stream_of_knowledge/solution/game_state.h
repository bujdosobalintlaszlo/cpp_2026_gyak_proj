#pragma once
#include <cstdio>  // For C-style I/O (Side Quest 4)
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>
#include <vector>

// StreamGuard: RAII class to save/restore stream formatting state
class StreamGuard {
    std::ios& stream_;
    std::ios::fmtflags flags_;
    std::streamsize precision_;
    char fill_;

   public:
    explicit StreamGuard(std::ios& stream)
        : stream_(stream), flags_(stream.flags()), precision_(stream.precision()),
          fill_(stream.fill()) {}

    ~StreamGuard() {
        stream_.flags(flags_);
        stream_.precision(precision_);
        stream_.fill(fill_);
    }

    // Prevent copying
    StreamGuard(const StreamGuard&) = delete;
    StreamGuard& operator=(const StreamGuard&) = delete;
};

class GameState {
   private:
    std::string characterName_;
    std::string characterClass_;
    int level_;
    int gold_;
    std::string location_;
    std::vector<std::string> inventory_;

   public:
    GameState() : level_(1), gold_(0) {}

    GameState(const std::string& name, const std::string& charClass, int level, int gold,
              const std::string& loc)
        : characterName_(name), characterClass_(charClass), level_(level), gold_(gold),
          location_(loc) {}

    // Getters (const!)
    const std::string& getName() const { return characterName_; }
    const std::string& getClass() const { return characterClass_; }
    int getLevel() const { return level_; }
    int getGold() const { return gold_; }
    const std::string& getLocation() const { return location_; }
    const std::vector<std::string>& getInventory() const { return inventory_; }

    // Setters
    void setName(const std::string& name) { characterName_ = name; }
    void setClass(const std::string& charClass) { characterClass_ = charClass; }
    void setLevel(int level) { level_ = level; }
    void setGold(int gold) { gold_ = gold; }
    void setLocation(const std::string& loc) { location_ = loc; }

    void addItem(const std::string& item) { inventory_.push_back(item); }

    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for writing: " << filename << "\n";
            return false;
        }

        // Write character data
        file << "# Character Data\n";
        file << characterName_ << "\n";
        file << characterClass_ << "\n";
        file << level_ << "\n";
        file << gold_ << "\n";
        file << location_ << "\n";

        // Write inventory
        file << "# Inventory\n";
        file << inventory_.size() << "\n";
        for (const auto& item : inventory_) {
            file << item << "\n";
        }

        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error: Could not open file for reading: " << filename << "\n";
            return false;
        }

        std::string line;

        // Skip comment line
        std::getline(file, line);

        // Read character data
        std::getline(file, characterName_);
        std::getline(file, characterClass_);

        if (!(file >> level_) || level_ < 1 || level_ > 100) {
            std::cerr << "Error: Invalid level in save file\n";
            return false;
        }

        if (!(file >> gold_) || gold_ < 0) {
            std::cerr << "Error: Invalid gold amount in save file\n";
            return false;
        }

        file.ignore();  // Skip newline after gold
        std::getline(file, location_);

        // Read inventory
        std::getline(file, line);  // Skip comment
        int itemCount;
        if (!(file >> itemCount) || itemCount < 0 || itemCount > 1000) {
            std::cerr << "Error: Invalid item count in save file\n";
            return false;
        }

        file.ignore();  // Skip newline
        inventory_.clear();
        for (int i = 0; i < itemCount; i++) {
            std::string item;
            std::getline(file, item);
            if (item.empty()) {
                std::cerr << "Error: Empty item name in save file\n";
                return false;
            }
            inventory_.push_back(item);
        }

        return true;
    }

    void display() const {
        std::cout << "\nCharacter: " << characterName_ << "\n";
        std::cout << "Class: " << characterClass_ << "\n";
        std::cout << "Level: " << level_ << "\n";
        std::cout << "Gold: " << gold_ << "\n";
        std::cout << "Location: " << location_ << "\n";
        std::cout << "Inventory: ";
        if (inventory_.empty()) {
            std::cout << "(empty)";
        } else {
            for (size_t i = 0; i < inventory_.size(); i++) {
                std::cout << inventory_[i];
                if (i < inventory_.size() - 1)
                    std::cout << ", ";
            }
        }
        std::cout << "\n";
    }

    // Side Quest 4: C-style I/O implementation
    bool saveToFileC(const char* filename) const {
        FILE* file = fopen(filename, "w");

        if (!file) {
            fprintf(stderr, "Error: Could not open file for writing: %s\n", filename);
            return false;
        }

        // Write character data
        fprintf(file, "# Character Data\n");
        fprintf(file, "%s\n", characterName_.c_str());
        fprintf(file, "%s\n", characterClass_.c_str());
        fprintf(file, "%d\n", level_);
        fprintf(file, "%d\n", gold_);
        fprintf(file, "%s\n", location_.c_str());

        // Write inventory
        fprintf(file, "# Inventory\n");
        fprintf(file, "%zu\n", inventory_.size());
        for (const auto& item : inventory_) {
            fprintf(file, "%s\n", item.c_str());
        }

        fclose(file);
        return true;
    }

    bool loadFromFileC(const char* filename) {
        FILE* file = fopen(filename, "r");

        if (!file) {
            fprintf(stderr, "Error: Could not open file for reading: %s\n", filename);
            return false;
        }

        char buffer[256];

        // Skip comment line
        fgets(buffer, sizeof(buffer), file);

        // Read character data
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline
        characterName_ = buffer;

        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = 0;
        characterClass_ = buffer;

        if (fscanf(file, "%d", &level_) != 1 || level_ < 1 || level_ > 100) {
            fprintf(stderr, "Error: Invalid level in save file\n");
            fclose(file);
            return false;
        }

        if (fscanf(file, "%d", &gold_) != 1 || gold_ < 0) {
            fprintf(stderr, "Error: Invalid gold amount in save file\n");
            fclose(file);
            return false;
        }

        fgets(buffer, sizeof(buffer), file);  // Skip newline
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = 0;
        location_ = buffer;

        // Read inventory
        fgets(buffer, sizeof(buffer), file);  // Skip comment
        int itemCount;
        if (fscanf(file, "%d", &itemCount) != 1 || itemCount < 0 || itemCount > 1000) {
            fprintf(stderr, "Error: Invalid item count in save file\n");
            fclose(file);
            return false;
        }

        fgets(buffer, sizeof(buffer), file);  // Skip newline
        inventory_.clear();
        for (int i = 0; i < itemCount; i++) {
            fgets(buffer, sizeof(buffer), file);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 0) {
                fprintf(stderr, "Error: Empty item name in save file\n");
                fclose(file);
                return false;
            }
            inventory_.push_back(buffer);
        }

        fclose(file);
        return true;
    }
};
