#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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

    json loadData(const json& defaultValue = json::array()) {
        if (!std::filesystem::exists(this->filepath)) {
            this->saveData(defaultValue);
            return defaultValue;
        }
        try {
            std::ifstream file(this->filepath);
            if (!file.is_open()) return defaultValue;
            json data;
            file >> data;
            return data.is_array() ? data : defaultValue;
        } catch (const std::exception&) {
            return defaultValue;
        }
    }

    bool saveData(const json& data) {
        try {
            std::filesystem::path p(this->filepath);
            if (p.has_parent_path()) {
                std::filesystem::create_directories(p.parent_path());
            }
            std::ofstream file(this->filepath);
            if (!file.is_open()) return false;
            file << std::setw(4) << data << std::endl;
            return true;
        } catch (const std::exception&) {
            return false;
        }
    }
};


// === 2. CLASS MODEL MAHASISWA ===

class Mahasiswa {
public:
    std::string nim;
    std::string nama;
    std::string jurusan;

    Mahasiswa(std::string nim, std::string nama, std::string jurusan)
        : nim(nim), nama(nama), jurusan(jurusan) {}

    // Konversi objek Mahasiswa menjadi format JSON (Serialisasi)
    json toJson() const {
        return {
            {"nim", this->nim},
            {"nama", this->nama},
            {"jurusan", this->jurusan}
        };
    }

    // Membangun objek Mahasiswa dari format JSON (Deserialisasi)
    static Mahasiswa fromJson(const json& j) {
        return Mahasiswa(
            j.value("nim", ""),
            j.value("nama", ""),
            j.value("jurusan", "")
        );
    }
};


// === 3. CLASS REPOSITORY / MANAGER ===

class MahasiswaManager {
private:
    JSONStorage storage;
    std::vector<Mahasiswa> mahasiswaList;

public:
    explicit MahasiswaManager(const std::string& filepath = "mahasiswa.json")
        : storage(filepath) {
        this->loadAll();
    }

    // Memuat seluruh data mahasiswa dari JSON ke memori dalam bentuk objek
    void loadAll() {
        json rawData = this->storage.loadData(json::array());
        this->mahasiswaList.clear();
        for (const auto& item : rawData) {
            this->mahasiswaList.push_back(Mahasiswa::fromJson(item));
        }
    }

    // Menyimpan seluruh objek mahasiswa dari memori kembali ke berkas JSON
    void saveAll() {
        json rawData = json::array();
        for (const auto& mhs : this->mahasiswaList) {
            rawData.push_back(mhs.toJson());
        }
        this->storage.saveData(rawData);
    }

    std::pair<bool, std::string> tambah(const std::string& nim, const std::string& nama, const std::string& jurusan) {
        // Validasi keunikan NIM
        for (const auto& mhs : this->mahasiswaList) {
            if (mhs.nim == nim) {
                return {false, "Gagal! Mahasiswa dengan NIM " + nim + " sudah terdaftar."};
            }
        }

        // Tambahkan objek baru
        Mahasiswa mhsBaru(nim, nama, jurusan);
        this->mahasiswaList.push_back(mhsBaru);
        this->saveAll();
        return {true, "Sukses mendaftarkan mahasiswa '" + nama + "'."};
    }

    const std::vector<Mahasiswa>& tampilkanSemua() const {
        return this->mahasiswaList;
    }
};


// === 4. PROGRAM UTAMA ===

int main() {
    MahasiswaManager manager("mahasiswa.json");

    while (true) {
        std::cout << "\n==================================================\n";
        std::cout << "   PORTAL MAHASISWA OOP - CREATE & READ (JSON)    \n";
        std::cout << "==================================================\n";
        std::cout << "1. Tambah Mahasiswa (Create)\n";
        std::cout << "2. Tampilkan Daftar Mahasiswa (Read)\n";
        std::cout << "3. Keluar\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Pilih Menu (1-3): ";

        std::string pilihan;
        std::getline(std::cin >> std::ws, pilihan);

        if (pilihan == "1") {
            std::cout << "\n--- TAMBAH MAHASISWA BARU ---\n";
            std::cout << "Masukkan NIM    : ";
            std::string nim;
            std::getline(std::cin, nim);

            std::cout << "Masukkan Nama   : ";
            std::string nama;
            std::getline(std::cin, nama);

            std::cout << "Masukkan Jurusan: ";
            std::string jurusan;
            std::getline(std::cin, jurusan);

            auto [sukses, pesan] = manager.tambah(nim, nama, jurusan);
            std::cout << pesan << "\n";
        }
        else if (pilihan == "2") {
            std::cout << "\n--- DAFTAR MAHASISWA AKTIF ---\n";
            const auto& mhsList = manager.tampilkanSemua();
            if (mhsList.empty()) {
                std::cout << "[Belum ada data mahasiswa terdaftar]\n";
            } else {
                int idx = 1;
                for (const auto& m : mhsList) {
                    std::cout << idx++ << ". NIM: " << std::left << std::setw(12) << m.nim 
                              << " | Nama: " << std::left << std::setw(15) << m.nama 
                              << " | Jurusan: " << m.jurusan << "\n";
                }
            }
        }
        else if (pilihan == "3") {
            std::cout << "\nAplikasi ditutup. Terima kasih!\n";
            break;
        }
        else {
            std::cout << "Pilihan menu tidak valid!\n";
        }
    }

    return 0;
}
