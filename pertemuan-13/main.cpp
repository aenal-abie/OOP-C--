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


// === 2. CLASS MODEL MAHASISWA & MANAGER ===

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


class MahasiswaManager {
private:
    JSONStorage storage;
    std::vector<Mahasiswa> mahasiswaList;

public:
    explicit MahasiswaManager(const std::string& filepath = "mahasiswa.json")
        : storage(filepath) {
        this->loadAll();
        // Seeding sampel awal jika kosong
        if (this->mahasiswaList.empty()) {
            this->tambah("22051204001", "Salwa Salsabila", "Teknik Informatika");
            this->tambah("22051204020", "Ahmad Fauzi", "Sistem Informasi");
        }
    }

    void loadAll() {
        json rawData = this->storage.loadData(json::array());
        this->mahasiswaList.clear();
        for (const auto& item : rawData) {
            this->mahasiswaList.push_back(Mahasiswa::fromJson(item));
        }
    }

    void saveAll() {
        json raw = json::array();
        for (const auto& m : this->mahasiswaList) {
            raw.push_back(m.toJson());
        }
        this->storage.saveData(raw);
    }

    bool tambah(const std::string& nim, const std::string& nama, const std::string& jurusan) {
        for (const auto& m : this->mahasiswaList) {
            if (m.nim == nim) return false;
        }
        this->mahasiswaList.emplace_back(nim, nama, jurusan);
        this->saveAll();
        return true;
    }

    const Mahasiswa* dapatkanMahasiswa(const std::string& nim) const {
        for (const auto& m : this->mahasiswaList) {
            if (m.nim == nim) return &m;
        }
        return nullptr;
    }

    const std::vector<Mahasiswa>& tampilkanSemua() const {
        return this->mahasiswaList;
    }
};


// === 3. CLASS MODEL NILAI & MANAGER (RELASIONAL) ===

class Nilai {
public:
    std::string nim;
    std::string matakuliah;
    double tugas;
    double uts;
    double uas;

    Nilai(std::string nim, std::string mk, double tugas, double uts, double uas)
        : nim(nim), matakuliah(mk), tugas(tugas), uts(uts), uas(uas) {}

    double hitungAkhir() const {
        return (this->tugas * 0.20) + (this->uts * 0.30) + (this->uas * 0.50);
    }

    std::string dapatkanHuruf() const {
        double akhir = this->hitungAkhir();
        if (akhir >= 85.0) return "A";
        else if (akhir >= 75.0) return "B";
        else if (akhir >= 60.0) return "C";
        else if (akhir >= 50.0) return "D";
        else return "E";
    }

    json toJson() const {
        return {
            {"nim", this->nim},
            {"matakuliah", this->matakuliah},
            {"tugas", this->tugas},
            {"uts", this->uts},
            {"uas", this->uas}
        };
    }

    static Nilai fromJson(const json& j) {
        return Nilai(
            j.value("nim", ""),
            j.value("matakuliah", ""),
            j.value("tugas", 0.0),
            j.value("uts", 0.0),
            j.value("uas", 0.0)
        );
    }
};


class NilaiManager {
private:
    JSONStorage storage;
    std::vector<Nilai> nilaiList;

public:
    explicit NilaiManager(const std::string& filepath = "nilai.json")
        : storage(filepath) {
        this->loadAll();
    }

    void loadAll() {
        json rawData = this->storage.loadData(json::array());
        this->nilaiList.clear();
        for (const auto& item : rawData) {
            this->nilaiList.push_back(Nilai::fromJson(item));
        }
    }

    void saveAll() {
        json raw = json::array();
        for (const auto& n : this->nilaiList) {
            raw.push_back(n.toJson());
        }
        this->storage.saveData(raw);
    }

    bool inputNilai(const std::string& nim, const std::string& mk, double tugas, double uts, double uas) {
        this->nilaiList.emplace_back(nim, mk, tugas, uts, uas);
        this->saveAll();
        return true;
    }

    std::vector<Nilai> dapatkanKhs(const std::string& nim) const {
        std::vector<Nilai> hasil;
        for (const auto& n : this->nilaiList) {
            if (n.nim == nim) {
                hasil.push_back(n);
            }
        }
        return hasil;
    }
};


// === 4. PROGRAM UTAMA ===

int main() {
    MahasiswaManager mhsMgr("mahasiswa.json");
    NilaiManager nilaiMgr("nilai.json");

    while (true) {
        std::cout << "\n==================================================\n";
        std::cout << "         PORTAL AKADEMIK (RELASI JSON OOP)        \n";
        std::cout << "==================================================\n";
        std::cout << "1. Registrasi Mahasiswa Baru\n";
        std::cout << "2. Input Nilai Mata Kuliah\n";
        std::cout << "3. Tampilkan Cetak KHS Mahasiswa (JOIN)\n";
        std::cout << "4. Keluar\n";
        std::cout << "--------------------------------------------------\n";
        std::cout << "Pilih Menu (1-4): ";

        std::string pilihan;
        std::getline(std::cin >> std::ws, pilihan);

        if (pilihan == "1") {
            std::cout << "\n--- REGISTRASI MAHASISWA ---\n";
            std::cout << "Masukkan NIM    : ";
            std::string nim;
            std::getline(std::cin, nim);

            std::cout << "Masukkan Nama   : ";
            std::string nama;
            std::getline(std::cin, nama);

            std::cout << "Masukkan Jurusan: ";
            std::string jurusan;
            std::getline(std::cin, jurusan);

            if (mhsMgr.tambah(nim, nama, jurusan)) {
                std::cout << "Sukses mendaftarkan mahasiswa '" << nama << "'.\n";
            } else {
                std::cout << "Gagal! NIM sudah terdaftar.\n";
            }
        }
        else if (pilihan == "2") {
            std::cout << "\n--- INPUT NILAI MATA KULIAH ---\n";
            std::cout << "Masukkan NIM Mahasiswa: ";
            std::string nim;
            std::getline(std::cin, nim);

            // Validasi keberadaan mahasiswa (Foreign Key check)
            const Mahasiswa* mhs = mhsMgr.dapatkanMahasiswa(nim);
            if (!mhs) {
                std::cout << "Error: NIM mahasiswa tidak terdaftar! Silakan registrasi dahulu.\n";
                continue;
            }

            std::cout << "Menginput nilai untuk: " << mhs->nama << " (" << mhs->jurusan << ")\n";
            std::cout << "Nama Mata Kuliah: ";
            std::string mk;
            std::getline(std::cin, mk);

            double tgs, uts, uas;
            std::cout << "Nilai Tugas (0-100): ";
            if (!(std::cin >> tgs)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Error: Input nilai tidak valid!\n"; continue; }
            std::cout << "Nilai UTS (0-100)  : ";
            if (!(std::cin >> uts)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Error: Input nilai tidak valid!\n"; continue; }
            std::cout << "Nilai UAS (0-100)  : ";
            if (!(std::cin >> uas)) { std::cin.clear(); std::cin.ignore(1000, '\n'); std::cout << "Error: Input nilai tidak valid!\n"; continue; }

            nilaiMgr.inputNilai(nim, mk, tgs, uts, uas);
            std::cout << "Sukses memasukkan nilai mata kuliah '" << mk << "'.\n";
        }
        else if (pilihan == "3") {
            std::cout << "\n--- CETAK KARTU HASIL STUDI (KHS) ---\n";
            std::cout << "Masukkan NIM Mahasiswa: ";
            std::string nim;
            std::getline(std::cin, nim);

            const Mahasiswa* mhs = mhsMgr.dapatkanMahasiswa(nim);
            if (!mhs) {
                std::cout << "Error: Mahasiswa tidak ditemukan!\n";
                continue;
            }

            std::cout << "\n========================================================\n";
            std::cout << "                 KARTU HASIL STUDI (KHS)                \n";
            std::cout << "========================================================\n";
            std::cout << "NIM     : " << std::left << std::setw(20) << mhs->nim << " | Nama   : " << mhs->nama << "\n";
            std::cout << "Jurusan : " << std::left << std::setw(20) << mhs->jurusan << "\n";
            std::cout << "--------------------------------------------------------\n";
            std::cout << std::left << std::setw(20) << "Mata Kuliah" << " | "
                      << std::right << std::setw(5) << "Tugas" << " | "
                      << std::setw(5) << "UTS" << " | "
                      << std::setw(5) << "UAS" << " | "
                      << std::setw(6) << "Akhir" << " | Grade\n";
            std::cout << "--------------------------------------------------------\n";

            std::vector<Nilai> khs = nilaiMgr.dapatkanKhs(nim);
            if (khs.empty()) {
                std::cout << "                Belum ada nilai terinput                \n";
            } else {
                for (const auto& n : khs) {
                    double akhir = n.hitungAkhir();
                    std::string grade = n.dapatkanHuruf();
                    std::cout << std::left << std::setw(20) << n.matakuliah << " | "
                              << std::right << std::setw(5) << static_cast<int>(n.tugas) << " | "
                              << std::setw(5) << static_cast<int>(n.uts) << " | "
                              << std::setw(5) << static_cast<int>(n.uas) << " | "
                              << std::fixed << std::setprecision(1) << std::setw(6) << akhir << " |   "
                              << grade << "\n";
                }
            }
            std::cout << "========================================================\n";
        }
        else if (pilihan == "4") {
            std::cout << "\nAplikasi ditutup. Terima kasih!\n";
            break;
        }
        else {
            std::cout << "Pilihan menu tidak valid!\n";
        }
    }

    return 0;
}
