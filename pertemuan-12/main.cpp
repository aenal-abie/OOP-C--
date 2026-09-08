#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
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

    json toJson() const {
        return {
            {"nim", this->nim},
            {"nama", this->nama},
            {"jurusan", this->jurusan}
        };
    }

    static Mahasiswa fromJson(const json& j) {
        return Mahasiswa(
            j.value("nim", ""),
            j.value("nama", ""),
            j.value("jurusan", "")
        );
    }
};


// === 3. CLASS REPOSITORY / MANAGER (CRUD LENGKAP) ===

class MahasiswaManager {
private:
    JSONStorage storage;
    std::vector<Mahasiswa> mahasiswaList;

public:
    explicit MahasiswaManager(const std::string& filepath = "mahasiswa.json")
        : storage(filepath) {
        this->loadAll();
    }

    void loadAll() {
        json rawData = this->storage.loadData(json::array());
        this->mahasiswaList.clear();
        for (const auto& item : rawData) {
            this->mahasiswaList.push_back(Mahasiswa::fromJson(item));
        }
    }

    void saveAll() {
        json rawData = json::array();
        for (const auto& mhs : this->mahasiswaList) {
            rawData.push_back(mhs.toJson());
        }
        this->storage.saveData(rawData);
    }

    // 1. CREATE
    std::pair<bool, std::string> tambah(const std::string& nim, const std::string& nama, const std::string& jurusan) {
        for (const auto& mhs : this->mahasiswaList) {
            if (mhs.nim == nim) {
                return {false, "Gagal! Mahasiswa dengan NIM " + nim + " sudah terdaftar."};
            }
        }
        Mahasiswa mhsBaru(nim, nama, jurusan);
        this->mahasiswaList.push_back(mhsBaru);
        this->saveAll();
        return {true, "Sukses mendaftarkan mahasiswa '" + nama + "'."};
    }

    // 2. READ ALL
    const std::vector<Mahasiswa>& tampilkanSemua() const {
        return this->mahasiswaList;
    }

    // 3. READ SINGLE
    Mahasiswa* dapatkanMahasiswa(const std::string& nim) {
        for (auto& mhs : this->mahasiswaList) {
            if (mhs.nim == nim) {
                return &mhs;
            }
        }
        return nullptr;
    }

    // 4. UPDATE
    std::pair<bool, std::string> ubah(const std::string& nim, const std::string& namaBaru, const std::string& jurusanBaru) {
        Mahasiswa* mhs = this->dapatkanMahasiswa(nim);
        if (mhs) {
            mhs->nama = namaBaru;
            mhs->jurusan = jurusanBaru;
            this->saveAll();
            return {true, "Sukses memperbarui data mahasiswa NIM " + nim + "."};
        }
        return {false, "Gagal! Mahasiswa dengan NIM " + nim + " tidak ditemukan."};
    }

    // 5. DELETE
    std::pair<bool, std::string> hapus(const std::string& nim) {
        auto it = std::find_if(this->mahasiswaList.begin(), this->mahasiswaList.end(),
                               [&nim](const Mahasiswa& m) { return m.nim == nim; });
        if (it != this->mahasiswaList.end()) {
            this->mahasiswaList.erase(it);
            this->saveAll();
            return {true, "Sukses menghapus mahasiswa dengan NIM " + nim + "."};
        }
        return {false, "Gagal! Mahasiswa dengan NIM " + nim + " tidak ditemukan."};
    }
};


// === 4. PROGRAM UTAMA ===

int main() {
    MahasiswaManager manager("mahasiswa.json");

    while (true) {
        std::cout << "\n==================================================\n";
        std::cout << "    PORTAL MAHASISWA OOP - CRUD LENGKAP (JSON)    \n";
        std::cout << "==================================================\n";
        std::cout << "1. Tambah Mahasiswa (Create)\n";
        std::cout << "2. Tampilkan Daftar Mahasiswa (Read)\n";
        std::cout << "3. Ubah Data Mahasiswa (Update)\n";
        std::cout << "4. Hapus Mahasiswa (Delete)\n";
        std::cout << "5. Keluar\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Pilih Menu (1-5): ";

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
            std::cout << "\n--- UBAH DATA MAHASISWA ---\n";
            std::cout << "Masukkan NIM mahasiswa yang akan diubah: ";
            std::string nim;
            std::getline(std::cin, nim);

            Mahasiswa* mhs = manager.dapatkanMahasiswa(nim);
            if (!mhs) {
                std::cout << "Error: NIM mahasiswa tidak terdaftar!\n";
                continue;
            }

            std::cout << "Data Lama -> Nama: " << mhs->nama << " | Jurusan: " << mhs->jurusan << "\n";
            std::cout << "Masukkan Nama Baru   : ";
            std::string namaBaru;
            std::getline(std::cin, namaBaru);

            std::cout << "Masukkan Jurusan Baru: ";
            std::string jurusanBaru;
            std::getline(std::cin, jurusanBaru);

            auto [sukses, pesan] = manager.ubah(nim, namaBaru, jurusanBaru);
            std::cout << pesan << "\n";
        }
        else if (pilihan == "4") {
            std::cout << "\n--- HAPUS DATA MAHASISWA ---\n";
            std::cout << "Masukkan NIM mahasiswa yang akan dihapus: ";
            std::string nim;
            std::getline(std::cin, nim);

            std::cout << "Apakah Anda yakin ingin menghapus mahasiswa NIM " << nim << "? (y/n): ";
            std::string yakin;
            std::getline(std::cin, yakin);

            if (yakin == "y" || yakin == "Y") {
                auto [sukses, pesan] = manager.hapus(nim);
                std::cout << pesan << "\n";
            } else {
                std::cout << "Penghapusan dibatalkan.\n";
            }
        }
        else if (pilihan == "5") {
            std::cout << "\nAplikasi ditutup. Terima kasih!\n";
            break;
        }
        else {
            std::cout << "Pilihan menu tidak valid!\n";
        }
    }

    return 0;
}
