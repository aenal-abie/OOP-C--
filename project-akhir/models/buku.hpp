#ifndef BUKU_HPP
#define BUKU_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "../config/storage.hpp"

class Buku {
public:
    int idBuku;
    std::string judul;
    std::string penulis;
    int stok;

    Buku(int id, std::string judul, std::string penulis, int stok)
        : idBuku(id), judul(judul), penulis(penulis), stok(stok) {}

    json toJson() const {
        return {
            {"id_buku", this->idBuku},
            {"judul", this->judul},
            {"penulis", this->penulis},
            {"stok", this->stok}
        };
    }

    static Buku fromJson(const json& data) {
        return Buku(
            data.value("id_buku", 0),
            data.value("judul", ""),
            data.value("penulis", ""),
            data.value("stok", 0)
        );
    }
};

class BukuManager {
private:
    std::string filepath;
    std::vector<Buku> bukuList;

public:
    explicit BukuManager(const std::string& path = "data/buku.json")
        : filepath(path) {
        this->loadAll();
        // Data Sampel Awal (Seeding) jika kosong
        if (this->bukuList.empty()) {
            this->tambah("Clean Code", "Robert C. Martin", 3);
            this->tambah("C++ OOP Mastery", "Salwa Salsabila", 5);
        }
    }

    void loadAll() {
        json raw = JSONStorage::loadData(this->filepath, json::array());
        this->bukuList.clear();
        for (const auto& d : raw) {
            this->bukuList.push_back(Buku::fromJson(d));
        }
    }

    void saveAll() {
        json data = json::array();
        for (const auto& b : this->bukuList) {
            data.push_back(b.toJson());
        }
        JSONStorage::saveData(this->filepath, data);
    }

    bool tambah(const std::string& judul, const std::string& penulis, int stok) {
        int nextId = 1;
        for (const auto& b : this->bukuList) {
            if (b.idBuku >= nextId) {
                nextId = b.idBuku + 1;
            }
        }

        this->bukuList.emplace_back(nextId, judul, penulis, stok);
        this->saveAll();
        return true;
    }

    const std::vector<Buku>& tampilkanSemua() const {
        return this->bukuList;
    }

    Buku* dapatkanBuku(int idBuku) {
        for (auto& b : this->bukuList) {
            if (b.idBuku == idBuku) {
                return &b;
            }
        }
        return nullptr;
    }

    bool ubah(int idBuku, const std::string& judul, const std::string& penulis, int stok) {
        Buku* b = this->dapatkanBuku(idBuku);
        if (b) {
            b->judul = judul;
            b->penulis = penulis;
            b->stok = stok;
            this->saveAll();
            return true;
        }
        return false;
    }

    bool hapus(int idBuku) {
        auto it = std::find_if(this->bukuList.begin(), this->bukuList.end(),
                               [idBuku](const Buku& b) { return b.idBuku == idBuku; });
        if (it != this->bukuList.end()) {
            this->bukuList.erase(it);
            this->saveAll();
            return true;
        }
        return false;
    }
};

#endif // BUKU_HPP
