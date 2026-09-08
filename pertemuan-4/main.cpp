#include <iostream>
#include <string>
#include <iomanip>

class RekeningBank {
private:
    std::string nomorRekening;
    std::string pemilik;
    double saldo; // Atribut private

public:
    // Constructor
    RekeningBank(std::string noRek, std::string nama, double saldoAwal)
        : nomorRekening(noRek), pemilik(nama), saldo(saldoAwal >= 0 ? saldoAwal : 0) {}

    // Getter Saldo
    double getSaldo() const {
        return this->saldo;
    }

    std::string getNomorRekening() const {
        return this->nomorRekening;
    }

    std::string getPemilik() const {
        return this->pemilik;
    }

    // Method Setor Uang (dengan validasi nilai positif)
    void setoran(double jumlah) {
        if (jumlah > 0) {
            this->saldo += jumlah;
            std::cout << "[Setoran] Sukses menyetor Rp " << static_cast<long long>(jumlah)
                      << ". Saldo saat ini: Rp " << static_cast<long long>(this->saldo) << "\n";
        } else {
            std::cout << "[Setoran Gagal] Jumlah setoran harus bernilai positif!\n";
        }
    }

    // Method Tarik Uang (dengan validasi saldo mencukupi)
    bool tarikTunai(double jumlah) {
        if (jumlah <= 0) {
            std::cout << "[Penarikan Gagal] Jumlah penarikan harus bernilai positif!\n";
            return false;
        }

        if (jumlah > this->saldo) {
            std::cout << "[Penarikan Gagal] Saldo tidak mencukupi! (Saldo Anda: Rp " 
                      << static_cast<long long>(this->saldo) << ", Penarikan: Rp " 
                      << static_cast<long long>(jumlah) << ")\n";
            return false;
        }

        this->saldo -= jumlah;
        std::cout << "[Penarikan] Sukses menarik Rp " << static_cast<long long>(jumlah)
                  << ". Sisa saldo: Rp " << static_cast<long long>(this->saldo) << "\n";
        return true;
    }
};

int main() {
    std::cout << "==================================================\n";
    std::cout << "        SIMULATOR ATM REKENING BANK (OOP)         \n";
    std::cout << "==================================================\n";

    // Buat Akun Rekening Baru
    RekeningBank rekening("123-456-789", "Salwa Salsabila", 200000);
    std::cout << "Pemilik Rekening : " << rekening.getPemilik() << "\n";
    std::cout << "Nomor Rekening   : " << rekening.getNomorRekening() << "\n";
    std::cout << "Saldo Awal       : Rp " << static_cast<long long>(rekening.getSaldo()) << "\n";
    std::cout << "--------------------------------------------------\n";

    // 1. Coba akses variabel private secara langsung:
    // Baris berikut akan memicu COMPILER ERROR jika tanda komentar dibuka:
    // rekening.saldo = 500000; // error: 'double RekeningBank::saldo' is private within this context

    // 2. Uji Coba Setoran
    rekening.setoran(50000);
    rekening.setoran(-10000); // Kasus error input negatif
    std::cout << "--------------------------------------------------\n";

    // 3. Uji Coba Penarikan
    rekening.tarikTunai(100000); // Berhasil
    rekening.tarikTunai(300000); // Gagal karena saldo kurang
    std::cout << "==================================================\n";

    return 0;
}
