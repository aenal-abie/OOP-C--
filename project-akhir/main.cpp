#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include "models/buku.hpp"
#include "models/anggota.hpp"
#include "models/peminjaman.hpp"

int main() {
    // Inisialisasi manajer data (CRUD + Storage)
    BukuManager bukuMgr("data/buku.json");
    AnggotaManager anggotaMgr("data/anggota.json");
    PeminjamanManager pinjamMgr(bukuMgr, anggotaMgr, "data/peminjaman.json");

    while (true) {
        std::cout << "\n=======================================================\n";
        std::cout << "        DASHBOARD UTAMA PORTAL PERPUSTAKAAN OOP        \n";
        std::cout << "=======================================================\n";
        std::cout << "1. Manajemen Buku (Katalog)\n";
        std::cout << "2. Manajemen Anggota\n";
        std::cout << "3. Transaksi Peminjaman\n";
        std::cout << "4. Transaksi Pengembalian\n";
        std::cout << "5. Log Riwayat Peminjaman (JOIN)\n";
        std::cout << "6. Keluar\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Pilih Menu Utama (1-6): ";

        std::string menu;
        std::getline(std::cin >> std::ws, menu);

        // ----------------------------------------------------
        // MENU 1: MANAJEMEN BUKU (CRUD)
        // ----------------------------------------------------
        if (menu == "1") {
            while (true) {
                std::cout << "\n--- MANAJEMEN BUKU ---\n";
                std::cout << "1. Tambah Buku (Create)\n";
                std::cout << "2. Tampilkan Buku (Read)\n";
                std::cout << "3. Ubah Buku (Update)\n";
                std::cout << "4. Hapus Buku (Delete)\n";
                std::cout << "5. Kembali ke Menu Utama\n";
                std::cout << "Pilih Sub-Menu (1-5): ";

                std::string pilih;
                std::getline(std::cin >> std::ws, pilih);

                if (pilih == "1") {
                    std::cout << "Masukkan Judul Buku: ";
                    std::string judul;
                    std::getline(std::cin >> std::ws, judul);

                    std::cout << "Masukkan Penulis   : ";
                    std::string penulis;
                    std::getline(std::cin, penulis);

                    std::cout << "Masukkan Jumlah Stok: ";
                    int stok;
                    if (!(std::cin >> stok)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input stok harus berupa angka!\n";
                        continue;
                    }

                    bukuMgr.tambah(judul, penulis, stok);
                    std::cout << "Sukses menambahkan buku '" << judul << "'.\n";
                }
                else if (pilih == "2") {
                    std::cout << "\n--- DAFTAR KATALOG BUKU ---\n";
                    const auto& daftar = bukuMgr.tampilkanSemua();
                    if (daftar.empty()) {
                        std::cout << "[Katalog buku kosong]\n";
                    } else {
                        std::cout << std::left << std::setw(4) << "ID" << " | "
                                  << std::setw(25) << "Judul Buku" << " | "
                                  << std::setw(18) << "Penulis" << " | Stok\n";
                        std::cout << "-------------------------------------------------------\n";
                        for (const auto& b : daftar) {
                            std::cout << std::left << std::setw(4) << b.idBuku << " | "
                                      << std::setw(25) << b.judul << " | "
                                      << std::setw(18) << b.penulis << " | "
                                      << b.stok << " eks\n";
                        }
                    }
                }
                else if (pilih == "3") {
                    std::cout << "Masukkan ID Buku yang akan diedit: ";
                    int idBuku;
                    if (!(std::cin >> idBuku)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input tidak valid!\n";
                        continue;
                    }

                    Buku* b = bukuMgr.dapatkanBuku(idBuku);
                    if (!b) {
                        std::cout << "Error: Buku tidak ditemukan!\n";
                        continue;
                    }

                    std::cout << "Data Lama -> Judul: " << b->judul << " | Penulis: " << b->penulis << " | Stok: " << b->stok << "\n";
                    std::cout << "Masukkan Judul Baru   : ";
                    std::string judul;
                    std::getline(std::cin >> std::ws, judul);

                    std::cout << "Masukkan Penulis Baru : ";
                    std::string penulis;
                    std::getline(std::cin, penulis);

                    std::cout << "Masukkan Stok Baru    : ";
                    int stok;
                    if (!(std::cin >> stok)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input stok harus berupa angka!\n";
                        continue;
                    }

                    if (bukuMgr.ubah(idBuku, judul, penulis, stok)) {
                        std::cout << "Sukses memperbarui data buku.\n";
                    } else {
                        std::cout << "Gagal memperbarui buku.\n";
                    }
                }
                else if (pilih == "4") {
                    std::cout << "Masukkan ID Buku yang akan dihapus: ";
                    int idBuku;
                    if (!(std::cin >> idBuku)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input ID harus berupa angka!\n";
                        continue;
                    }

                    if (bukuMgr.hapus(idBuku)) {
                        std::cout << "Sukses menghapus buku dari katalog.\n";
                    } else {
                        std::cout << "Error: Buku tidak ditemukan!\n";
                    }
                }
                else if (pilih == "5") {
                    break;
                }
            }
        }

        // ----------------------------------------------------
        // MENU 2: MANAJEMEN ANGGOTA (CRUD)
        // ----------------------------------------------------
        else if (menu == "2") {
            while (true) {
                std::cout << "\n--- MANAJEMEN ANGGOTA ---\n";
                std::cout << "1. Daftarkan Anggota Baru (Create)\n";
                std::cout << "2. Tampilkan Daftar Anggota (Read)\n";
                std::cout << "3. Ubah Profil Anggota (Update)\n";
                std::cout << "4. Hapus Anggota (Delete)\n";
                std::cout << "5. Kembali ke Menu Utama\n";
                std::cout << "Pilih Sub-Menu (1-5): ";

                std::string pilih;
                std::getline(std::cin >> std::ws, pilih);

                if (pilih == "1") {
                    std::cout << "Masukkan Nama Anggota: ";
                    std::string nama;
                    std::getline(std::cin >> std::ws, nama);

                    std::cout << "Masukkan Email       : ";
                    std::string email;
                    std::getline(std::cin, email);

                    if (anggotaMgr.tambah(nama, email)) {
                        std::cout << "Sukses mendaftarkan anggota '" << nama << "'.\n";
                    } else {
                        std::cout << "Gagal! Email anggota sudah terdaftar.\n";
                    }
                }
                else if (pilih == "2") {
                    std::cout << "\n--- DAFTAR ANGGOTA PERPUSTAKAAN ---\n";
                    const auto& daftar = anggotaMgr.tampilkanSemua();
                    if (daftar.empty()) {
                        std::cout << "[Belum ada anggota terdaftar]\n";
                    } else {
                        std::cout << std::left << std::setw(4) << "ID" << " | "
                                  << std::setw(25) << "Nama Anggota" << " | Email\n";
                        std::cout << "-------------------------------------------------------\n";
                        for (const auto& a : daftar) {
                            std::cout << std::left << std::setw(4) << a.idAnggota << " | "
                                      << std::setw(25) << a.nama << " | "
                                      << a.email << "\n";
                        }
                    }
                }
                else if (pilih == "3") {
                    std::cout << "Masukkan ID Anggota yang akan diedit: ";
                    int idAnggota;
                    if (!(std::cin >> idAnggota)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input tidak valid!\n";
                        continue;
                    }

                    Anggota* a = anggotaMgr.dapatkanAnggota(idAnggota);
                    if (!a) {
                        std::cout << "Error: Anggota tidak ditemukan!\n";
                        continue;
                    }

                    std::cout << "Data Lama -> Nama: " << a->nama << " | Email: " << a->email << "\n";
                    std::cout << "Masukkan Nama Baru : ";
                    std::string nama;
                    std::getline(std::cin >> std::ws, nama);

                    std::cout << "Masukkan Email Baru: ";
                    std::string email;
                    std::getline(std::cin, email);

                    if (anggotaMgr.ubah(idAnggota, nama, email)) {
                        std::cout << "Sukses memperbarui data anggota.\n";
                    } else {
                        std::cout << "Gagal memperbarui data anggota.\n";
                    }
                }
                else if (pilih == "4") {
                    std::cout << "Masukkan ID Anggota yang akan dihapus: ";
                    int idAnggota;
                    if (!(std::cin >> idAnggota)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Error: Input ID harus berupa angka!\n";
                        continue;
                    }

                    if (anggotaMgr.hapus(idAnggota)) {
                        std::cout << "Sukses menghapus anggota.\n";
                    } else {
                        std::cout << "Error: Anggota tidak ditemukan!\n";
                    }
                }
                else if (pilih == "5") {
                    break;
                }
            }
        }

        // ----------------------------------------------------
        // MENU 3: TRANSAKSI PEMINJAMAN
        // ----------------------------------------------------
        else if (menu == "3") {
            std::cout << "\n--- TRANSAKSI PEMINJAMAN BUKU ---\n";
            std::cout << "Masukkan ID Buku yang dipinjam : ";
            int idBuku;
            if (!(std::cin >> idBuku)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Input ID harus berupa angka!\n";
                continue;
            }

            std::cout << "Masukkan ID Anggota Peminjam   : ";
            int idAnggota;
            if (!(std::cin >> idAnggota)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Input ID harus berupa angka!\n";
                continue;
            }

            auto [sukses, pesan] = pinjamMgr.pinjam(idBuku, idAnggota);
            std::cout << pesan << "\n";
        }

        // ----------------------------------------------------
        // MENU 4: TRANSAKSI PENGEMBALIAN
        // ----------------------------------------------------
        else if (menu == "4") {
            std::cout << "\n--- TRANSAKSI PENGEMBALIAN BUKU ---\n";
            std::cout << "Masukkan ID Transaksi Peminjaman: ";
            int idPinjam;
            if (!(std::cin >> idPinjam)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error: Input ID harus berupa angka!\n";
                continue;
            }

            auto [sukses, pesan] = pinjamMgr.kembalikan(idPinjam);
            std::cout << pesan << "\n";
        }

        // ----------------------------------------------------
        // MENU 5: LOG RIWAYAT PEMINJAMAN (JOIN)
        // ----------------------------------------------------
        else if (menu == "5") {
            std::cout << "\n--- LOG RIWAYAT PEMINJAMAN BUKU (JOIN DATA) ---\n";
            auto daftar = pinjamMgr.tampilkanSemua();
            if (daftar.empty()) {
                std::cout << "[Belum ada catatan peminjaman]\n";
            } else {
                std::cout << std::left << std::setw(4) << "ID" << " | "
                          << std::setw(22) << "Judul Buku" << " | "
                          << std::setw(16) << "Peminjam" << " | "
                          << std::setw(12) << "Tanggal" << " | Status\n";
                std::cout << "-------------------------------------------------------------------\n";
                for (const auto& log : daftar) {
                    std::cout << std::left << std::setw(4) << log.idPinjam << " | "
                              << std::setw(22) << log.judulBuku << " | "
                              << std::setw(16) << log.namaAnggota << " | "
                              << std::setw(12) << log.tanggalPinjam << " | "
                              << log.status << "\n";
                }
            }
        }

        // ----------------------------------------------------
        // MENU 6: KELUAR
        // ----------------------------------------------------
        else if (menu == "6") {
            std::cout << "\nAplikasi ditutup. Terima kasih!\n";
            break;
        }
        else {
            std::cout << "Pilihan menu utama tidak valid!\n";
        }
    }

    return 0;
}
