#ifndef ANGGOTA_HPP
#define ANGGOTA_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "../config/storage.hpp"

class Anggota {
public:
    int idAnggota;
    std::string nama;
    std::string email;

    Anggota(int id, std::string nama, std::string email)
        : idAnggota(id), nama(nama), email(email) {}

    json toJson() const {
        return {
            {"id_anggota", this->idAnggota},
            {"nama", this->nama},
            {"email", this->email}
        };
    }

    static Anggota fromJson(const json& data) {
        return Anggota(
            data.value("id_anggota", 0),
            data.value("nama", ""),
            data.value("email", "")
        );
    }
};

class AnggotaManager {
private:
    std::string filepath;
    std::vector<Anggota> anggotaList;

    static std::string toLower(std::string s) {
        std::transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    explicit AnggotaManager(const std::string& path = "data/anggota.json")
        : filepath(path) {
        this->loadAll();
        // Data Sampel Awal (Seeding) jika kosong
        if (this->anggotaList.empty()) {
            this->tambah("Budi Santoso", "budi@example.com");
            this->tambah("Dewi Lestari", "dewi@example.com");
        }
    }

    void loadAll() {
        json raw = JSONStorage::loadData(this->filepath, json::array());
        this->anggotaList.clear();
        for (const auto& d : raw) {
            this->anggotaList.push_back(Anggota::fromJson(d));
        }
    }

    void saveAll() {
        json data = json::array();
        for (const auto& a : this->anggotaList) {
            data.push_back(a.toJson());
        }
        JSONStorage::saveData(this->filepath, data);
    }

    bool tambah(const std::string& nama, const std::string& email) {
        // Cek duplikasi email
        std::string lowerEmail = toLower(email);
        for (const auto& a : this->anggotaList) {
            if (toLower(a.email) == lowerEmail) {
                return false;
            }
        }

        int nextId = 1;
        for (const auto& a : this->anggotaList) {
            if (a.idAnggota >= nextId) {
                nextId = a.idAnggota + 1;
            }
        }

        this->anggotaList.emplace_back(nextId, nama, email);
        this->saveAll();
        return true;
    }

    const std::vector<Anggota>& tampilkanSemua() const {
        return this->anggotaList;
    }

    Anggota* dapatkanAnggota(int idAnggota) {
        for (auto& a : this->anggotaList) {
            if (a.idAnggota == idAnggota) {
                return &a;
            }
        }
        return nullptr;
    }

    bool ubah(int idAnggota, const std::string& nama, const std::string& email) {
        Anggota* a = this->dapatkanAnggota(idAnggota);
        if (a) {
            a->nama = nama;
            a->email = email;
            this->saveAll();
            return true;
        }
        return false;
    }

    bool hapus(int idAnggota) {
        auto it = std::find_if(this->anggotaList.begin(), this->anggotaList.end(),
                               [idAnggota](const Anggota& a) { return a.idAnggota == idAnggota; });
        if (it != this->anggotaList.end()) {
            this->anggotaList.erase(it);
            this->saveAll();
            return true;
        }
        return false;
    }
};

#endif // ANGGOTA_HPP
