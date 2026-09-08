# 🚀 Pemrograman Berorientasi Objek (OOP) Menggunakan C++

Repositori ini memuat seluruh materi perkuliahan, kode sumber praktikum, latihan mandiri, dan proyek akhir untuk mata kuliah **Pemrograman Berorientasi Objek (OOP)** menggunakan bahasa pemrograman **C++ (C++17)**.

Materi ini diadaptasi secara komprehensif dari silabus OOP, menyajikan transisi konsep dari pemrograman prosedural menuju pemrograman berorientasi objek modern hingga persistensi data berbasis berkas JSON.

---

## 📚 Daftar Modul Pertemuan

| Pertemuan | Topik Materi | Kode Sumber | Dokumentasi |
| :---: | :--- | :---: | :---: |
| **01** | Review Pemrograman C++ Dasar (I/O, Variabel, Tipe Data, Percabangan, Fungsi) | [`main.cpp`](pertemuan-1/main.cpp) | [Modul 1](pertemuan-1/README.md) |
| **02** | Konsep OOP: Class, Object, Member Variables & Functions | [`main.cpp`](pertemuan-2/main.cpp) | [Modul 2](pertemuan-2/README.md) |
| **03** | Constructor, Member Initializer List & Destructor | [`main.cpp`](pertemuan-3/main.cpp) | [Modul 3](pertemuan-3/README.md) |
| **04** | Enkapsulasi & Access Specifiers (`private`, `public`, Getter/Setter) | [`main.cpp`](pertemuan-4/main.cpp) | [Modul 4](pertemuan-4/README.md) |
| **05** | Pewarisan (Inheritance), Base Initialization & Method Overriding | [`main.cpp`](pertemuan-5/main.cpp) | [Modul 5](pertemuan-5/README.md) |
| **06** | Polimorfisme Dinamis, Virtual Functions & Pure Virtual (Abstract Class) | [`main.cpp`](pertemuan-6/main.cpp) | [Modul 6](pertemuan-6/README.md) |
| **07** | Review OOP & Relasi Antar Objek (Asosiasi & Agregasi dengan Pointer) | [`main.cpp`](pertemuan-7/main.cpp) | [Modul 7](pertemuan-7/README.md) |
| **08** | **UTS**: Proyek Sistem POS (Point of Sale) Kasir Toko Mini | [`main.cpp`](pertemuan-8/main.cpp) | [Modul 8](pertemuan-8/README.md) |
| **09** | Pengenalan File Storage Persisten (JSON Serialisasi & Deserialisasi) | [`main.cpp`](pertemuan-9/main.cpp) | [Modul 9](pertemuan-9/README.md) |
| **10** | Arsitektur Storage Wrapper (Class `JSONStorage` Reusable) | [`main.cpp`](pertemuan-10/main.cpp) | [Modul 10](pertemuan-10/README.md) |
| **11** | CRUD: Create & Read (Pola Model-Repository `MahasiswaManager`) | [`main.cpp`](pertemuan-11/main.cpp) | [Modul 11](pertemuan-11/README.md) |
| **12** | CRUD: Update & Delete (Pencarian & Penghapusan Elemen Vector) | [`main.cpp`](pertemuan-12/main.cpp) | [Modul 12](pertemuan-12/README.md) |
| **13** | Relasi Data Terdistribusi & Operasi In-Memory JOIN (KHS Mahasiswa) | [`main.cpp`](pertemuan-13/main.cpp) | [Modul 13](pertemuan-13/README.md) |
| **PROYEK** | **Project Akhir**: Portal Sistem Informasi Manajemen Perpustakaan | [`project-akhir/`](project-akhir/) | [Modul Proyek](project-akhir/README.md) |

Silabus terperinci dapat dibaca pada berkas [`materi.txt`](materi.txt).

---

## 🛠️ Persyaratan Lingkungan & Compiler

1. **Compiler C++**:
   - Mendukung standar **C++17** ke atas (e.g., `g++` versi $\ge 7$ atau `clang++`).
   - Periksa versi compiler di terminal:
     ```bash
     g++ --version
     ```
2. **Pustaka JSON**:
   - Menggunakan pustaka header-only **`nlohmann/json`** yang sudah disediakan di folder [`include/`](include/). Tidak memerlukan instalasi paket eksternal tambahan.

---

## 🚀 Panduan Kompilasi & Eksekusi Umum

Setiap pertemuan memiliki program mandiri. Anda dapat mengompilasi dan menjalankannya dengan mudah:

### Untuk Pertemuan 1 - 8 (Standar I/O):
```bash
cd pertemuan-1
g++ -std=c++17 main.cpp -o main
./main
```

### Untuk Pertemuan 9 - 13 (Memerlukan Pustaka JSON):
Sertakan direktori header `include` menggunakan argumen `-I../include`:
```bash
cd pertemuan-9
g++ -std=c++17 -I../include main.cpp -o main
./main
```

### Untuk Project Akhir:
Disediakan `Makefile` agar kompilasi dapat dilakukan dalam satu perintah:
```bash
cd project-akhir
make
./main
```
Atau kompilasi manual:
```bash
cd project-akhir
g++ -std=c++17 -I../include -I. main.cpp -o main
./main
```

---

## 📂 Struktur Repositori

```
OOP C++/
├── include/
│   └── nlohmann/
│       └── json.hpp          # Header-only JSON library untuk persistensi
├── materi.txt                 # Silabus 16 minggu mata kuliah
├── README.md                  # Panduan umum repositori
├── pertemuan-1/ s.d. 13/      # Modul materi, praktikum, dan solusi C++
│   ├── README.md
│   └── main.cpp
└── project-akhir/             # Proyek akhir aplikasi perpustakaan terpadu
    ├── Makefile
    ├── README.md
    ├── config/
    ├── models/
    ├── data/
    └── main.cpp
```
