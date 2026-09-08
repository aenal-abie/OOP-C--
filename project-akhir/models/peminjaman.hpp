#ifndef PEMINJAMAN_HPP
#define PEMINJAMAN_HPP

#include <string>
#include <vector>
#include <ctime>
#include <sstream>
#include <iomanip>
#include "../config/storage.hpp"
#include "buku.hpp"
#include "anggota.hpp"

class Peminjaman {
public:
    int idPinjam;
    int idBuku;
    int idAnggota;
    std::string tanggalPinjam;
    std::string status;

    Peminjaman(int id, int idBuku, int idAnggota, std::string tgl, std::string status = "PINJAM")
        : idPinjam(id), idBuku(idBuku), idAnggota(idAnggota), tanggalPinjam(tgl), status(status) {}

    json toJson() const {
        return {
            {"id_pinjam", this->idPinjam},
            {"id_buku", this->idBuku},
            {"id_anggota", this->idAnggota},
            {"tanggal_pinjam", this->tanggalPinjam},
            {"status", this->status}
        };
    }

    static Peminjaman fromJson(const json& data) {
        return Peminjaman(
            data.value("id_pinjam", 0),
            data.value("id_buku", 0),
            data.value("id_anggota", 0),
            data.value("tanggal_pinjam", ""),
            data.value("status", "PINJAM")
        );
    }
};

struct LogPeminjaman {
    int idPinjam;
    std::string judulBuku;
    std::string namaAnggota;
    std::string tanggalPinjam;
    std::string status;
};

class PeminjamanManager {
private:
    std::string filepath;
    BukuManager& bukuManager;
    AnggotaManager& anggotaManager;
    std::vector<Peminjaman> peminjamanList;

    static std::string getTanggalHariIni() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        std::ostringstream oss;
        oss << (now->tm_year + 1900) << '-'
            << std::setfill('0') << std::setw(2) << (now->tm_mon + 1) << '-'
            << std::setfill('0') << std::setw(2) << now->tm_mday;
        return oss.str();
    }

public:
    PeminjamanManager(BukuManager& bMgr, AnggotaManager& aMgr, const std::string& path = "data/peminjaman.json")
        : filepath(path), bukuManager(bMgr), anggotaManager(aMgr) {
        this->loadAll();
    }

    void loadAll() {
        json raw = JSONStorage::loadData(this->filepath, json::array());
        this->peminjamanList.clear();
        for (const auto& d : raw) {
            this->peminjamanList.push_back(Peminjaman::fromJson(d));
        }
    }

    void saveAll() {
        json data = json::array();
        for (const auto& p : this->peminjamanList) {
            data.push_back(p.toJson());
        }
        JSONStorage::saveData(this->filepath, data);
    }

    std::pair<bool, std::string> pinjam(int idBuku, int idAnggota) {
        // 1. Validasi eksistensi & stok
        Buku* buku = this->bukuManager.dapatkanBuku(idBuku);
        Anggota* anggota = this->anggotaManager.dapatkanAnggota(idAnggota);

        if (!buku) {
            return {false, "Error: Buku tidak ditemukan."};
        }
        if (!anggota) {
            return {false, "Error: Anggota tidak ditemukan."};
        }
        if (buku->stok <= 0) {
            return {false, "Error: Stok buku '" + buku->judul + "' sedang kosong."};
        }

        // 2. Proses peminjaman
        buku->stok -= 1;
        this->bukuManager.saveAll();

        int nextId = 1;
        for (const auto& p : this->peminjamanList) {
            if (p.idPinjam >= nextId) {
                nextId = p.idPinjam + 1;
            }
        }

        std::string tgl = getTanggalHariIni();
        this->peminjamanList.emplace_back(nextId, idBuku, idAnggota, tgl, "PINJAM");
        this->saveAll();

        return {true, "Sukses! Buku '" + buku->judul + "' berhasil dipinjam oleh " + anggota->nama + "."};
    }

    std::pair<bool, std::string> kembalikan(int idPinjam) {
        // Cari data peminjaman
        Peminjaman* transaksi = nullptr;
        for (auto& p : this->peminjamanList) {
            if (p.idPinjam == idPinjam) {
                transaksi = &p;
                break;
            }
        }

        if (!transaksi) {
            return {false, "Error: Transaksi peminjaman tidak ditemukan."};
        }
        if (transaksi->status == "KEMBALI") {
            return {false, "Error: Buku sudah dikembalikan sebelumnya."};
        }

        // Proses pengembalian
        Buku* buku = this->bukuManager.dapatkanBuku(transaksi->idBuku);
        if (buku) {
            buku->stok += 1;
            this->bukuManager.saveAll();
        }

        transaksi->status = "KEMBALI";
        this->saveAll();

        return {true, "Sukses! Buku berhasil dikembalikan."};
    }

    // Mendapatkan data list log yang sudah di-JOIN dengan data Buku & Anggota
    std::vector<LogPeminjaman> tampilkanSemua() {
        std::vector<LogPeminjaman> gabungan;
        for (const auto& p : this->peminjamanList) {
            Buku* b = this->bukuManager.dapatkanBuku(p.idBuku);
            Anggota* a = this->anggotaManager.dapatkanAnggota(p.idAnggota);

            std::string judul = b ? b->judul : "[Buku Dihapus]";
            std::string nama = a ? a->nama : "[Anggota Dihapus]";

            gabungan.push_back(LogPeminjaman{
                p.idPinjam,
                judul,
                nama,
                p.tanggalPinjam,
                p.status
            });
        }
        return gabungan;
    }
};

#endif // PEMINJAMAN_HPP
