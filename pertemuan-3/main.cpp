#include <iostream>
#include <string>

class Buku {
public:
    std::string judul;
    std::string penulis;
    int stok;

    // Constructor berparameter dengan validasi
    Buku(std::string judul, std::string penulis, int stok)
        : judul(judul), penulis(penulis) {
        // Validasi stok pada constructor
        if (stok < 0) {
            std::cout << "[Warning] Stok buku '" << this->judul << "' bernilai negatif (" 
                      << stok << "). Otomatis di-reset menjadi 0.\n";
            this->stok = 0;
        } else {
            this->stok = stok;
        }
    }

    // Destructor
    ~Buku() {
        // Otomatis dipanggil saat objek dihancurkan / keluar dari scope
    }

    void tampilkanInfo() {
        std::cout << "Judul Buku : " << this->judul << "\n";
        std::cout << "Penulis    : " << this->penulis << "\n";
        std::cout << "Stok       : " << this->stok << " eksemplar\n";
        std::cout << "----------------------------------------\n";
    }
};

int main() {
    std::cout << "=============================================\n";
    std::cout << "       SIMULATOR CONSTRUCTOR VALIDATION      \n";
    std::cout << "=============================================\n";

    // Inisialisasi buku pertama dengan stok valid
    std::cout << "Instansiasi Buku A (Stok valid):\n";
    Buku bukuA("Belajar C++ untuk Pemula", "Ronaldo", 12);
    bukuA.tampilkanInfo();

    // Inisialisasi buku kedua dengan stok negatif (Memicu Warning & Reset)
    std::cout << "Instansiasi Buku B (Stok negatif):\n";
    Buku bukuB("Struktur Data Lanjutan", "Agus", -5);
    bukuB.tampilkanInfo();

    return 0;
}
