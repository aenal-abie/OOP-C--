#include <iostream>
#include <string>
#include <vector>
#include <memory>

// === 1. CLASS ABSTRAK INDUK ===

class Hewan {
public:
    virtual ~Hewan() = default;

    // Pure virtual function
    virtual std::string bersuara() const = 0;

    // Nama jenis hewan
    virtual std::string getNamaJenis() const = 0;

    // Metode biasa (konkrit) yang otomatis diwarisi
    void tidur() const {
        std::cout << "[Hewan] Objek " << this->getNamaJenis() 
                  << " sedang tertidur pulas... Zzz\n";
    }
};


// === 2. SUBCLASS (KELAS TURUNAN) ===

class Kucing : public Hewan {
public:
    std::string getNamaJenis() const override {
        return "Kucing";
    }

    std::string bersuara() const override {
        return "Meow! Meow! 🐱";
    }
};


class Anjing : public Hewan {
public:
    std::string getNamaJenis() const override {
        return "Anjing";
    }

    std::string bersuara() const override {
        return "Guk! Guk! 🐶";
    }
};


// === 3. FUNGSI POLIMORFIK UTAMA ===

void perdengarkanSuara(const Hewan& hewan) {
    // Fungsi ini menerima referensi polimorfik ke Base Class Hewan
    std::cout << "Hewan jenis " << hewan.getNamaJenis() 
              << " mengeluarkan suara: " << hewan.bersuara() << "\n";
}


// === 4. PROGRAM UTAMA ===

int main() {
    std::cout << "==================================================\n";
    std::cout << "         VIRTUAL ANIMAL PETTING YARD (OOP)        \n";
    std::cout << "==================================================\n";

    // 1. Coba instansiasi kelas abstrak:
    // Baris berikut akan memicu error kompilasi jika diaktifkan:
    // Hewan h; // error: cannot declare variable 'h' to be of abstract type 'Hewan'

    // 2. Instansiasi objek turunan
    Kucing kitty;
    Anjing doggy;

    // 3. Menguji pemanggilan metode konkrit yang diwarisi
    kitty.tidur();
    doggy.tidur();
    std::cout << "--------------------------------------------------\n";

    // 4. Demonstrasi Polimorfisme menggunakan Koleksi Smart Pointer
    std::vector<std::unique_ptr<Hewan>> daftarPeliharaan;
    daftarPeliharaan.push_back(std::make_unique<Kucing>());
    daftarPeliharaan.push_back(std::make_unique<Anjing>());
    daftarPeliharaan.push_back(std::make_unique<Kucing>());
    daftarPeliharaan.push_back(std::make_unique<Anjing>());

    std::cout << "Perulangan Polimorfik pada daftar hewan:\n";
    for (const auto& pet : daftarPeliharaan) {
        perdengarkanSuara(*pet);
    }

    std::cout << "==================================================\n";

    return 0;
}
