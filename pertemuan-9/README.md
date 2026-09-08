# Pertemuan 9: Pengenalan File Storage (JSON & File I/O) di C++

Selamat datang di paruh kedua praktikum. Mulai Pertemuan 9, kita akan menghubungkan objek OOP kita dengan media penyimpanan persisten (*persistent storage*). Karena kita tidak menggunakan sistem manajemen database relasional (SQL), kita akan menggunakan format pertukaran data yang sangat populer dan terstandarisasi, yaitu **JSON (JavaScript Object Notation)**.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Mengapa Menggunakan Berkas JSON untuk Penyimpanan?
JSON adalah format teks ringan berbasis pasangan kunci-nilai (*key-value*) dan daftar (*array*) yang mudah dibaca manusia dan komputer. Di C++, kita dapat mengelola JSON dengan elegan menggunakan pustaka header-only **`nlohmann/json`** (sudah tersedia pada direktori `include/` di repositori ini).

### 2. Aliran Berkas di C++ (`<fstream>`)
C++ menyediakan kelas stream untuk operasi file:
- `std::ifstream`: Membaca berkas (*Input File Stream*).
- `std::ofstream`: Menulis/membuat berkas (*Output File Stream*).
- `std::filesystem::exists()`: Memeriksa apakah berkas sudah ada di disk.

### 3. Serialization & Deserialization
- **Serialization (Serialisasi)**: Mengonversi struktur objek/data di memori program menjadi format teks JSON dan menyimpannya ke berkas disk.
- **Deserialization (Deserialisasi)**: Membaca teks JSON dari berkas disk dan mem-parsingnya kembali menjadi objek/tipe data di memori C++.

```cpp
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Serialisasi (Menulis ke file)
json data = { {"nim", "123"}, {"nama", "Ahmad"} };
std::ofstream fileKeluar("data.json");
fileKeluar << std::setw(4) << data; // setw(4) untuk format indentasi rapi
fileKeluar.close();

// Deserialisasi (Membaca dari file)
std::ifstream fileMasuk("data.json");
json dataLoaded;
fileMasuk >> dataLoaded;
std::cout << dataLoaded["nama"] << std::endl;
```

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah membuat program sederhana untuk mencatat dan menyimpan daftar nama mahasiswa beserta jurusannya ke sebuah berkas lokal bernama `mahasiswa.json`:
1. Program akan mengecek apakah berkas `mahasiswa.json` sudah ada. Jika ada, baca datanya dan tampilkan di layar.
2. Menyediakan formulir ketik input data mahasiswa baru, lalu tambahkan ke dalam struktur data yang lama.
3. Simpan kembali seluruh daftar data mahasiswa yang baru ke berkas `mahasiswa.json`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

Pada saat mengompilasi program C++ yang menggunakan pustaka `nlohmann/json.hpp`, tambahkan parameter `-I../include` agar compiler mengetahui letak direktori header:

```bash
# Masuk ke direktori pertemuan-9
cd pertemuan-9

# Kompilasi kode C++ menyertakan direktori include
g++ -std=c++17 -I../include main.cpp -o main

# Jalankan program
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan menu opsi "Hapus Semua Data" yang akan mengosongkan isi file `mahasiswa.json` menjadi array kosong `[]` secara permanen setelah mendapat konfirmasi dari pengguna.
2. Pelajari format penyimpanan `.csv`. Tulis analisis perbandingan singkat mengenai kelebihan dan kekurangan menggunakan format JSON dibandingkan CSV untuk penyimpanan data objek berstruktur kompleks pada aplikasi C++.
