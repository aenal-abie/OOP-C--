#include <iostream>
#include <string>

// === 1. CLASS INDUK (BASE CLASS) ===

class Pegawai {
protected:
    std::string nama;
    double gajiPokok;

public:
    Pegawai(std::string nama, double gajiPokok)
        : nama(nama), gajiPokok(gajiPokok) {}

    virtual ~Pegawai() = default;

    virtual std::string getJabatan() const {
        return "Pegawai";
    }

    virtual double hitungGaji() const {
        // Default: hanya gaji pokok
        return this->gajiPokok;
    }

    virtual void tampilkanInfo() const {
        std::cout << "Nama Pegawai : " << this->nama << "\n";
        std::cout << "Jabatan      : " << this->getJabatan() << "\n";
        std::cout << "Gaji Pokok   : Rp " << static_cast<long long>(this->gajiPokok) << "\n";
        std::cout << "Total Gaji   : Rp " << static_cast<long long>(this->hitungGaji()) << "\n";
        std::cout << "---------------------------------------------\n";
    }
};


// === 2. CLASS ANAK (DERIVED CLASS) ===

class Dosen : public Pegawai {
private:
    double tunjanganSks;

public:
    Dosen(std::string nama, double gajiPokok, double tunjanganSks)
        : Pegawai(nama, gajiPokok), tunjanganSks(tunjanganSks) {}

    std::string getJabatan() const override {
        return "Dosen";
    }

    double hitungGaji() const override {
        // Method Overriding: gaji pokok + tunjangan SKS
        return this->gajiPokok + this->tunjanganSks;
    }
};


class Staff : public Pegawai {
private:
    double lembur;

public:
    Staff(std::string nama, double gajiPokok, double lembur)
        : Pegawai(nama, gajiPokok), lembur(lembur) {}

    std::string getJabatan() const override {
        return "Staff";
    }

    double hitungGaji() const override {
        // Method Overriding: gaji pokok + uang lembur
        return this->gajiPokok + this->lembur;
    }
};


// === 3. PROGRAM UTAMA ===

int main() {
    std::cout << "==================================================\n";
    std::cout << "        SISTEM PAYROLL PEGAWAI (INHERITANCE)      \n";
    std::cout << "==================================================\n";

    // Instansiasi objek subclass
    Dosen dosen("Dr. Salwa Salsabila", 5000000, 1500000);
    Staff staff("Ahmad Fauzi", 3000000, 600000);

    std::cout << "\n--- Slip Informasi Slip Gaji Dosen ---\n";
    dosen.tampilkanInfo();

    std::cout << "\n--- Slip Informasi Slip Gaji Staff ---\n";
    staff.tampilkanInfo();

    std::cout << "==================================================\n";

    return 0;
}
