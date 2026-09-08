#include <iostream>
#include <string>
#include <iomanip>
#include <limits>

// Menghitung nilai akhir berdasarkan pembobotan
double hitungNilaiAkhir(double tugas, double uts, double uas) {
    return (tugas * 0.3) + (uts * 0.3) + (uas * 0.4);
}

// Mengonversi nilai akhir angka menjadi predikat nilai huruf
std::string konversiNilaiHuruf(double nilaiAkhir) {
    if (nilaiAkhir >= 80.0) {
        return "A";
    } else if (nilaiAkhir >= 70.0) {
        return "B";
    } else if (nilaiAkhir >= 60.0) {
        return "C";
    } else if (nilaiAkhir >= 50.0) {
        return "D";
    } else {
        return "E";
    }
}

int main() {
    std::cout << "=============================================\n";
    std::cout << "    PROGRAM HITUNG NILAI AKHIR MAHASISWA     \n";
    std::cout << "=============================================\n";

    std::string nama;
    std::cout << "Masukkan Nama Mahasiswa: ";
    std::getline(std::cin, nama);

    double tugas = 0.0, uts = 0.0, uas = 0.0;

    std::cout << "Masukkan Nilai Tugas (0-100): ";
    if (!(std::cin >> tugas)) {
        std::cout << "\nError: Mohon masukkan angka yang valid untuk nilai tugas!\n";
        return 1;
    }

    std::cout << "Masukkan Nilai UTS (0-100)  : ";
    if (!(std::cin >> uts)) {
        std::cout << "\nError: Mohon masukkan angka yang valid untuk nilai UTS!\n";
        return 1;
    }

    std::cout << "Masukkan Nilai UAS (0-100)  : ";
    if (!(std::cin >> uas)) {
        std::cout << "\nError: Mohon masukkan angka yang valid untuk nilai UAS!\n";
        return 1;
    }

    // Validasi batas rentang nilai (0 - 100)
    if (tugas < 0 || tugas > 100 || uts < 0 || uts > 100 || uas < 0 || uas > 100) {
        std::cout << "\nError: Nilai harus berada dalam rentang 0 hingga 100!\n";
        return 1;
    }

    double nilaiAkhir = hitungNilaiAkhir(tugas, uts, uas);
    std::string nilaiHuruf = konversiNilaiHuruf(nilaiAkhir);

    std::cout << "\n=============================================\n";
    std::cout << "               HASIL PENILAIAN               \n";
    std::cout << "=============================================\n";
    std::cout << "Nama Mahasiswa : " << nama << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Nilai Tugas    : " << tugas << "\n";
    std::cout << "Nilai UTS      : " << uts << "\n";
    std::cout << "Nilai UAS      : " << uas << "\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Nilai Akhir    : " << nilaiAkhir << "\n";
    std::cout << "Nilai Huruf    : " << nilaiHuruf << "\n";
    std::cout << "=============================================\n";

    return 0;
}
