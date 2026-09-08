#include <iostream>
#include <string>

// === 1. DEFINISI CLASS ===

class Mahasiswa {
public:
    std::string nama;
    std::string nim;

    // Constructor
    Mahasiswa(std::string nama, std::string nim) {
        this->nama = nama;
        this->nim = nim;
    }

    // Member Function (Metode)
    void belajar() {
        std::cout << "[Mahasiswa] " << this->nama << " dengan NIM " << this->nim
                  << " sedang giat belajar pemrograman C++!\n";
    }

    void tampilkanInfo() {
        std::cout << "Mahasiswa { nama: \"" << this->nama << "\", nim: \"" << this->nim << "\" }\n";
    }
};


class Mobil {
public:
    std::string merk;
    std::string warna;

    // Constructor
    Mobil(std::string merk, std::string warna) {
        this->merk = merk;
        this->warna = warna;
    }

    // Member Function (Metode)
    void jalan() {
        std::cout << "[Mobil] Mobil " << this->merk << " berwarna " << this->warna
                  << " sedang dikendarai di jalan raya.\n";
    }

    void tampilkanInfo() {
        std::cout << "Mobil { merk: \"" << this->merk << "\", warna: \"" << this->warna << "\" }\n";
    }
};


// === 2. PROGRAM UTAMA (INSTANSIASI) ===

int main() {
    std::cout << "==================================================\n";
    std::cout << "        DEMONSTRASI CLASS & OBJECT DI C++         \n";
    std::cout << "==================================================\n";

    // Instansiasi Objek Mahasiswa di Stack
    Mahasiswa mhs1("Salwa Salsabila", "22051204001");
    Mahasiswa mhs2("Ahmad Fauzi", "22051204020");

    // Instansiasi Objek Mobil di Stack
    Mobil mobil1("Honda Civic", "Hitam");
    Mobil mobil2("Toyota Avanza", "Putih");

    // Memanggil metode objek
    std::cout << "\n--- Aktivitas Objek Mahasiswa ---\n";
    mhs1.belajar();
    mhs2.belajar();

    std::cout << "\n--- Aktivitas Objek Mobil ---\n";
    mobil1.jalan();
    mobil2.jalan();

    // Inspeksi Properti Objek
    std::cout << "\n--- Inspeksi Struktur Objek (Property & Value) ---\n";
    std::cout << "Data objek mhs1   : ";
    mhs1.tampilkanInfo();

    std::cout << "Data objek mobil1 : ";
    mobil1.tampilkanInfo();

    std::cout << "==================================================\n";

    return 0;
}
