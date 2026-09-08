#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

// === 1. CLASS PRODUK ===

class Produk {
public:
    int idProduk;
    std::string nama;
    double harga;

    Produk(int id, std::string n, double h)
        : idProduk(id), nama(n), harga(h) {}
};


// === 2. CLASS ITEM KERANJANG ===

class ItemKeranjang {
public:
    Produk produk;
    int qty;

    ItemKeranjang(const Produk& p, int q)
        : produk(p), qty(q) {}

    double hitungSubtotal() const {
        return this->produk.harga * this->qty;
    }
};


// === 3. CLASS KERANJANG BELANJA ===

class Keranjang {
public:
    std::vector<ItemKeranjang> daftarItem;

    void tambahItem(const Produk& produk, int qty) {
        // Cek apakah produk sudah ada di keranjang, jika ada tambahkan qty
        for (auto& item : daftarItem) {
            if (item.produk.idProduk == produk.idProduk) {
                item.qty += qty;
                return;
            }
        }
        daftarItem.push_back(ItemKeranjang(produk, qty));
    }

    double hitungTotal() const {
        double total = 0.0;
        for (const auto& item : daftarItem) {
            total += item.hitungSubtotal();
        }
        return total;
    }

    void cetakStruk(double bayar) const {
        double total = hitungTotal();
        double diskon = (total > 100000.0) ? (total * 0.10) : 0.0;
        double totalAkhir = total - diskon;
        double kembalian = bayar - totalAkhir;

        std::cout << "\n=============================================\n";
        std::cout << "             STRUK KASIR MINI MART           \n";
        std::cout << "=============================================\n";
        for (const auto& item : daftarItem) {
            std::cout << std::left << std::setw(18) << item.produk.nama << " "
                      << std::right << std::setw(2) << item.qty << "x Rp "
                      << std::setw(8) << static_cast<long long>(item.produk.harga) << " | Rp "
                      << std::setw(9) << static_cast<long long>(item.hitungSubtotal()) << "\n";
        }
        std::cout << "---------------------------------------------\n";
        std::cout << std::left << std::setw(16) << "Total Kotor"     << " : Rp " << std::right << std::setw(15) << static_cast<long long>(total) << "\n";
        std::cout << std::left << std::setw(16) << "Diskon (10%)"    << " : Rp " << std::right << std::setw(15) << static_cast<long long>(diskon) << "\n";
        std::cout << std::left << std::setw(16) << "Total Akhir"     << " : Rp " << std::right << std::setw(15) << static_cast<long long>(totalAkhir) << "\n";
        std::cout << std::left << std::setw(16) << "Bayar"           << " : Rp " << std::right << std::setw(15) << static_cast<long long>(bayar) << "\n";
        std::cout << std::left << std::setw(16) << "Kembalian"       << " : Rp " << std::right << std::setw(15) << static_cast<long long>(kembalian) << "\n";
        std::cout << "=============================================\n";
        std::cout << "     Terima Kasih Telah Berbelanja di Toko Kami\n";
        std::cout << "=============================================\n\n";
    }

    void kosongkan() {
        daftarItem.clear();
    }
};


// === 4. PROGRAM UTAMA ===

int main() {
    // Inisialisasi Katalog Produk
    std::vector<Produk> katalog = {
        Produk(1, "Buku Tulis", 5000),
        Produk(2, "Pensil 2B", 3000),
        Produk(3, "Penggaris 30cm", 4000),
        Produk(4, "Penghapus", 2000),
        Produk(5, "Modul C++ OOP", 85000)
    };

    Keranjang keranjang;

    while (true) {
        std::cout << "\n=============================================\n";
        std::cout << "          DASHBOARD KASIR MINI (UTS)         \n";
        std::cout << "=============================================\n";
        std::cout << "1. Lihat Katalog Produk\n";
        std::cout << "2. Tambah Produk ke Keranjang\n";
        std::cout << "3. Lihat Isi Keranjang\n";
        std::cout << "4. Proses Pembayaran & Struk\n";
        std::cout << "5. Keluar\n";
        std::cout << "---------------------------------------------\n";
        std::cout << "Pilih Menu (1-5): ";

        int pilihan;
        if (!(std::cin >> pilihan)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Masukkan angka pilihan yang valid!\n";
            continue;
        }

        if (pilihan == 1) {
            std::cout << "\n--- KATALOG PRODUK ---\n";
            for (const auto& p : katalog) {
                std::cout << "[" << p.idProduk << "] " << std::left << std::setw(20) << p.nama 
                          << " - Rp " << static_cast<long long>(p.harga) << "\n";
            }
        }
        else if (pilihan == 2) {
            std::cout << "Masukkan ID Produk: ";
            int idProd;
            if (!(std::cin >> idProd)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Input ID harus berupa angka!\n";
                continue;
            }

            const Produk* produkPilihan = nullptr;
            for (const auto& p : katalog) {
                if (p.idProduk == idProd) {
                    produkPilihan = &p;
                    break;
                }
            }

            if (!produkPilihan) {
                std::cout << "Error: ID Produk tidak ditemukan!\n";
                continue;
            }

            std::cout << "Masukkan Kuantitas untuk '" << produkPilihan->nama << "': ";
            int qty;
            if (!(std::cin >> qty) || qty <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Kuantitas harus berupa angka lebih dari 0!\n";
                continue;
            }

            keranjang.tambahItem(*produkPilihan, qty);
            std::cout << "Sukses menambahkan " << qty << "x '" << produkPilihan->nama << "' ke keranjang.\n";
        }
        else if (pilihan == 3) {
            std::cout << "\n--- ISI KERANJANG BELANJA ---\n";
            if (keranjang.daftarItem.empty()) {
                std::cout << "[Keranjang Kosong]\n";
            } else {
                for (const auto& item : keranjang.daftarItem) {
                    std::cout << "- " << std::left << std::setw(18) << item.produk.nama 
                              << " : " << item.qty << "x Rp " << static_cast<long long>(item.produk.harga)
                              << " = Rp " << static_cast<long long>(item.hitungSubtotal()) << "\n";
                }
                std::cout << "Total Sementara : Rp " << static_cast<long long>(keranjang.hitungTotal()) << "\n";
            }
        }
        else if (pilihan == 4) {
            if (keranjang.daftarItem.empty()) {
                std::cout << "Error: Keranjang belanja kosong! Tambahkan produk dahulu.\n";
                continue;
            }

            double total = keranjang.hitungTotal();
            double diskon = (total > 100000.0) ? (total * 0.10) : 0.0;
            double totalAkhir = total - diskon;

            std::cout << "\nTotal Belanja Bersih Anda: Rp " << static_cast<long long>(totalAkhir) << "\n";
            std::cout << "Masukkan Nominal Uang Bayar: Rp ";
            double bayar;
            if (!(std::cin >> bayar)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Harap masukkan nominal angka yang valid!\n";
                continue;
            }

            if (bayar < totalAkhir) {
                std::cout << "Error: Nominal uang bayar kurang dari total belanja!\n";
                continue;
            }

            keranjang.cetakStruk(bayar);
            // Reset keranjang setelah transaksi selesai
            keranjang.kosongkan();
        }
        else if (pilihan == 5) {
            std::cout << "\nAplikasi ditutup. Terima kasih!\n";
            break;
        }
        else {
            std::cout << "Pilihan menu tidak valid!\n";
        }
    }

    return 0;
}
