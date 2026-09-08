#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// === 1. CLASS BUKU ===

class Buku {
public:
    std::string judul;
    std::string penulis;
    bool tersedia;

    Buku(std::string judul, std::string penulis)
        : judul(judul), penulis(penulis), tersedia(true) {}

    std::string tampilkanInfo() const {
        std::string status = this->tersedia ? "Tersedia" : "Sedang Dipinjam";
        return "'" + this->judul + "' oleh " + this->penulis + " [" + status + "]";
    }
};


// === 2. CLASS ANGGOTA (AGREGASI DENGAN BUKU) ===

class Anggota {
public:
    std::string nama;
    std::string nomorAnggota;
    std::vector<Buku*> bukuDipinjam; // Menyimpan pointer ke objek Buku

    Anggota(std::string nama, std::string noAnggota)
        : nama(nama), nomorAnggota(noAnggota) {}

    void pinjamBuku(Buku& buku) {
        // Cek ketersediaan buku
        if (buku.tersedia) {
            buku.tersedia = false;
            this->bukuDipinjam.push_back(&buku);
            std::cout << "[Sukses] Anggota " << this->nama << " berhasil meminjam buku '" 
                      << buku.judul << "'.\n";
        } else {
            std::cout << "[Gagal] Buku '" << buku.judul 
                      << "' sedang tidak tersedia / dipinjam orang lain.\n";
        }
    }

    void kembalikanBuku(Buku& buku) {
        auto it = std::find(this->bukuDipinjam.begin(), this->bukuDipinjam.end(), &buku);
        if (it != this->bukuDipinjam.end()) {
            buku.tersedia = true;
            this->bukuDipinjam.erase(it);
            std::cout << "[Sukses] Anggota " << this->nama << " telah mengembalikan buku '" 
                      << buku.judul << "'.\n";
        } else {
            std::cout << "[Gagal] Anggota " << this->nama << " tidak membawa buku '" 
                      << buku.judul << "'!\n";
        }
    }

    void tampilkanInfo() const {
        std::cout << "Nama Anggota   : " << this->nama << " (ID: " << this->nomorAnggota << ")\n";
        if (!this->bukuDipinjam.empty()) {
            std::cout << "Buku Dipinjam  :\n";
            for (size_t i = 0; i < this->bukuDipinjam.size(); ++i) {
                std::cout << "  " << (i + 1) << ". " << this->bukuDipinjam[i]->judul 
                          << " (" << this->bukuDipinjam[i]->penulis << ")\n";
            }
        } else {
            std::cout << "Buku Dipinjam  : [Tidak Ada]\n";
        }
        std::cout << "--------------------------------------------------\n";
    }
};


// === 3. PROGRAM UTAMA ===

int main() {
    std::cout << "==================================================\n";
    std::cout << "      SIMULATOR RELASI ASOSIASI OBJEK (OOP)       \n";
    std::cout << "==================================================\n";

    // 1. Buat Objek Buku
    Buku buku1("C++ OOP Essentials", "Dr. Salwa");
    Buku buku2("Clean Architecture", "Robert Martin");

    // 2. Buat Objek Anggota
    Anggota anggota("Ahmad Fauzi", "MHS-001");

    // Tampilkan kondisi awal
    std::cout << "Kondisi Awal:\n";
    std::cout << buku1.tampilkanInfo() << "\n";
    std::cout << buku2.tampilkanInfo() << "\n";
    std::cout << "--------------------------------------------------\n";

    // 3. Proses Peminjaman
    anggota.pinjamBuku(buku1);
    anggota.pinjamBuku(buku2);
    // Coba pinjam buku yang sama lagi (seharusnya gagal)
    anggota.pinjamBuku(buku1);
    std::cout << "--------------------------------------------------\n";

    // Tampilkan info anggota
    std::cout << "Status Anggota setelah meminjam:\n";
    anggota.tampilkanInfo();

    // 4. Proses Pengembalian
    anggota.kembalikanBuku(buku1);
    std::cout << "--------------------------------------------------\n";

    std::cout << "Status Anggota setelah pengembalian:\n";
    anggota.tampilkanInfo();
    std::cout << "==================================================\n";

    return 0;
}
