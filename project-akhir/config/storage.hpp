#ifndef STORAGE_HPP
#define STORAGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JSONStorage {
public:
    // Membaca data dari berkas JSON secara aman
    static json loadData(const std::string& filepath, const json& defaultValue = json::array()) {
        if (!std::filesystem::exists(filepath)) {
            saveData(filepath, defaultValue);
            return defaultValue;
        }

        try {
            std::ifstream file(filepath);
            if (!file.is_open()) {
                return defaultValue;
            }
            json data;
            file >> data;
            return data;
        } catch (const std::exception&) {
            return defaultValue;
        }
    }

    // Menyimpan data terstruktur ke berkas JSON secara aman
    static bool saveData(const std::string& filepath, const json& data) {
        try {
            std::filesystem::path p(filepath);
            if (p.has_parent_path()) {
                std::filesystem::create_directories(p.parent_path());
            }

            std::ofstream file(filepath);
            if (!file.is_open()) {
                return false;
            }
            file << std::setw(4) << data << std::endl;
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
};

#endif // STORAGE_HPP
