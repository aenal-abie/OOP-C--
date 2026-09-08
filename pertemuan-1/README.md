# Pertemuan 1: Review Pemrograman C++ Dasar

Materi ini me-review dasar-dasar pemrograman menggunakan C++ sebelum masuk ke konsep Pemrograman Berorientasi Objek (OOP). Fokus utama adalah pemahaman sintaks dasar, variabel, tipe data, struktur kontrol (kondisional & perulangan), fungsi, serta cara melakukan kompilasi dan eksekusi program C++.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Struktur Masukan dan Keluaran (Input & Output)
- Di C++, pustaka standar `<iostream>` menyediakan objek `std::cin` untuk menerima masukan dari papan ketik (keyboard) dan `std::cout` untuk mencetak keluaran ke layar terminal.
- Operator `>>` (stream extraction) digunakan bersama `cin`, sedangkan operator `<<` (stream insertion) digunakan bersama `cout`.
- Untuk membaca teks string yang mengandung spasi (misalnya nama lengkap), gunakan fungsi `std::getline(std::cin, variabel)`.
- Manipulator `std::endl` atau karakter `'\n'` digunakan untuk berpindah baris.

```cpp
#include <iostream>
#include <string>

int main() {
    std::string nama;
    std::cout << "Masukkan nama Anda: ";
    std::getline(std::cin, nama);
    std::cout << "Halo, " << nama << "!" << std::endl;
    return 0;
}
```

### 2. Tipe Data & Casting
C++ adalah bahasa bertipe statis (*statically typed*), sehingga setiap variabel harus dideklarasikan tipe datanya secara eksplisit:
- `std::string` (teks / untaian karakter)
- `int` (bilangan bulat, e.g., 10, -5)
- `double` / `float` (bilangan desimal / pecahan presisi ganda)
- `bool` (`true` atau `false`)
- `char` (karakter tunggal, e.g., 'A')

Untuk melakukan konversi antar tipe data secara aman dan eksplisit (*type casting*), C++ menyediakan `static_cast<tipe_tujuan>(nilai)`.
```cpp
int totalNilai = 275;
int jumlahMatkul = 3;
double rataRata = static_cast<double>(totalNilai) / jumlahMatkul;
```

### 3. Operator di C++
Operator digunakan untuk memanipulasi nilai variabel:
- **Operator Aritmatika**:
  - Penjumlahan (`+`), Pengurangan (`-`), Perkalian (`*`), Pembagian (`/`), Modulo / Sisa Bagi (`%`).
- **Operator Perbandingan / Relasional**:
  - Sama dengan (`==`), Tidak sama dengan (`!=`), Lebih kecil (`<`), Lebih besar (`>`), Kurang dari sama dengan (`<=`), Lebih dari sama dengan (`>=`).
- **Operator Logika**:
  - Logika Dan (`&&`), Logika Atau (`||`), Negasi / Bukan (`!`).
- **Operator Penugasan**:
  - Pengisian (`=`), Tambah dan isi (`+=`), Kurang dan isi (`-=`), Kali dan isi (`*=`), dll.

### 4. Percabangan (`if`, `else if`, `else`)
Mengevaluasi ekspresi boolean untuk menentukan alur eksekusi instruksi program.
```cpp
int nilai = 80;
if (nilai >= 75) {
    std::cout << "Lulus" << std::endl;
} else {
    std::cout << "Tidak Lulus" << std::endl;
}
```

### 5. Fungsi di C++
Fungsi membungkus sekumpulan instruksi menjadi satu unit yang dapat digunakan berulang kali:
```cpp
double hitungDiskon(double harga, double persentase) {
    return harga * (persentase / 100.0);
}
```

---

## 💻 Tugas Praktikum

Tugas praktikum kali ini adalah membuat program **Kalkulator Nilai Akhir Mahasiswa** berbasis teks (CLI) interaktif. Program akan meminta masukan:
- Nama Mahasiswa
- Nilai Tugas (bobot 30%)
- Nilai UTS (bobot 30%)
- Nilai UAS (bobot 40%)

Program akan menghitung Nilai Akhir dengan rumus:
$$\text{Nilai Akhir} = (\text{Tugas} \times 0.3) + (\text{UTS} \times 0.3) + (\text{UAS} \times 0.4)$$

Serta mengonversi Nilai Akhir menjadi Nilai Huruf:
- $\ge 80$: **A**
- $\ge 70$: **B**
- $\ge 60$: **C**
- $\ge 50$: **D**
- $< 50$: **E**

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

Buka terminal pada direktori `pertemuan-1`, kemudian kompilasi kode program C++ menggunakan compiler `g++`:
```bash
# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan Program
./main
```

---

## 📝 Latihan Mandiri
1. Modifikasi program pada `main.cpp` agar dapat memproses input nilai untuk lebih dari satu mahasiswa menggunakan perulangan (`while` atau `do-while`) dengan opsi konfirmasi pengguna (misal: *"Apakah ingin menghitung nilai mahasiswa lain? (y/n)"*).
2. Tambahkan validasi masukan menggunakan `std::cin.fail()` untuk menangani kasus ketika pengguna secara sengaja atau tidak sengaja memasukkan karakter alfabet/simbol pada input nilai angka.
