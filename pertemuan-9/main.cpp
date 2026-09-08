#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <filesystem>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

const std::string FILEPATH = "mahasiswa.json";

// Membaca data dari file JSON. Jika file tidak ada atau error, kembalikan array kosong []
json muatData() {
    if (!std::filesystem::exists(FILEPATH)) {
        return json::array();
    }

    try {
        std::ifstream file(FILEPATH);
        if (!file.is_open()) {
            return json::array();
        }
        json data;
        file >> data;
        return data.is_array() ? data : json::array();
    } catch (const std::exception& e) {
        return json::array();
    }
}

// Menyimpan data array JSON ke dalam file dengan format indentasi 4 spasi
bool simpanData(const json& data) {
    try {
        std::ofstream file(FILEPATH);
        if (!file.is_open()) {
            return false;
        }
        file << std::setw(4) << data << std::endl;
        return true;
    } catch (const std::exception& e) {
        return false;
    }
}

int main() {
    std::cout << "==================================================\n";
    std::cout << "      PROGRAM PERSISTENSI FILE STORAGE (JSON)     \n";
    std::cout << "==================================================\n";

    // 1. Muat data lama dari file
    json daftarMahasiswa = muatData();

    std::cout << "Berhasil memuat " << daftarMahasiswa.size() 
              << " data mahasiswa dari berkas '" << FILEPATH << "'.\n";

    if (!daftarMahasiswa.empty()) {
        std::cout << "\n--- Daftar Mahasiswa Saat Ini ---\n";
        int idx = 1;
        for (const auto& mhs : daftarMahasiswa) {
            std::string nim = mhs.value("nim", "-");
            std::string nama = mhs.value("nama", "-");
            std::string jurusan = mhs.value("jurusan", "-");
            std::cout << idx++ << ". NIM: " << std::left << std::setw(12) << nim
                      << " | Nama: " << std::left << std::setw(15) << nama
                      << " | Jurusan: " << jurusan << "\n";
        }
    } else {
        std::cout << "\n[Belum ada data mahasiswa terdaftar]\n";
    }

    std::cout << "--------------------------------------------------\n";

    // 2. Form tambah data baru
    std::cout << "Apakah ingin menambah data mahasiswa baru? (y/n): ";
    std::string tambahLagi;
    std::getline(std::cin >> std::ws, tambahLagi);

    if (tambahLagi == "y" || tambahLagi == "Y") {
        std::cout << "Masukkan NIM    : ";
        std::string nim;
        std::getline(std::cin >> std::ws, nim);

        // Validasi sederhana agar NIM tidak duplikat
        bool duplikat = false;
        for (const auto& mhs : daftarMahasiswa) {
            if (mhs.value("nim", "") == nim) {
                duplikat = true;
                break;
            }
        }

        if (duplikat) {
            std::cout << "Gagal! Mahasiswa dengan NIM tersebut sudah terdaftar.\n";
            std::cout << "==================================================\n";
            return 0;
        }

        std::cout << "Masukkan Nama   : ";
        std::string nama;
        std::getline(std::cin, nama);

        std::cout << "Masukkan Jurusan: ";
        std::string jurusan;
        std::getline(std::cin, jurusan);

        json mahasiswaBaru = {
            {"nim", nim},
            {"nama", nama},
            {"jurusan", jurusan}
        };

        // Tambahkan ke array memori
        daftarMahasiswa.push_back(mahasiswaBaru);

        // 3. Simpan kembali array ke file JSON
        if (simpanData(daftarMahasiswa)) {
            std::cout << "\nSukses! Data '" << nama << "' berhasil disimpan secara permanen di '" << FILEPATH << "'.\n";
        } else {
            std::cout << "\nGagal menyimpan data ke berkas.\n";
        }
    }

    std::cout << "==================================================\n";
    return 0;
}
