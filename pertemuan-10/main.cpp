#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// === 1. CLASS STORAGE WRAPPER ===

class JSONStorage {
private:
    std::string filepath;

public:
    explicit JSONStorage(const std::string& path) : filepath(path) {}

    // Membaca data JSON secara aman. Jika berkas tidak ada, buat berkas baru dengan default value
    json loadData(const json& defaultValue = json::object()) {
        if (!std::filesystem::exists(this->filepath)) {
            this->saveData(defaultValue);
            return defaultValue;
        }

        try {
            std::ifstream file(this->filepath);
            if (!file.is_open()) {
                return defaultValue;
            }
            json data;
            file >> data;
            return data;
        } catch (const std::exception& e) {
            std::cerr << "[Storage Error] Gagal memuat berkas '" << this->filepath 
                      << "': " << e.what() << "\n";
            return defaultValue;
        }
    }

    // Menyimpan data terstruktur ke berkas JSON secara aman
    bool saveData(const json& data) {
        try {
            // Pastikan folder induk berkas sudah dibuat
            std::filesystem::path p(this->filepath);
            if (p.has_parent_path()) {
                std::filesystem::create_directories(p.parent_path());
            }

            std::ofstream file(this->filepath);
            if (!file.is_open()) {
                return false;
            }
            file << std::setw(4) << data << std::endl;
            return true;
        } catch (const std::exception& e) {
            std::cerr << "[Storage Error] Gagal menyimpan ke berkas '" << this->filepath 
                      << "': " << e.what() << "\n";
            return false;
        }
    }

    std::string getFilepath() const {
        return this->filepath;
    }
};


// === 2. PROGRAM UTAMA ===

int main() {
    std::cout << "==================================================\n";
    std::cout << "          UJI COBA CLASS STORAGE WRAPPER          \n";
    std::cout << "==================================================\n";

    // Instansiasi objek StorageManager dengan file konfigurasi
    JSONStorage configStorage("settings.json");

    // Konfigurasi default jika file belum ada
    json defaultConfig = {
        {"nama_aplikasi", "Portal Belajar C++ OOP"},
        {"versi", "1.0.0"},
        {"tema_gelap", true}
    };

    json settings = configStorage.loadData(defaultConfig);
    std::cout << "Pengaturan Saat Ini:\n";
    std::cout << settings.dump(4) << "\n";
    std::cout << "--------------------------------------------------\n";

    // Ubah pengaturan secara interaktif
    std::cout << "Ubah ke mode terang? (y/n): ";
    std::string ubah;
    std::getline(std::cin >> std::ws, ubah);

    if (ubah == "y" || ubah == "Y") {
        settings["tema_gelap"] = false;
        if (configStorage.saveData(settings)) {
            std::cout << "\nSukses memperbarui berkas 'settings.json' melalui objek JSONStorage.\n";
            std::cout << "Pengaturan Terbaru:\n";
            std::cout << configStorage.loadData().dump(4) << "\n";
        } else {
            std::cout << "\nGagal memperbarui berkas.\n";
        }
    }

    std::cout << "==================================================\n";
    return 0;
}
