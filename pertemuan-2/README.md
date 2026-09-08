# Pertemuan 2: Class & Object

Selamat datang di materi praktikum Pertemuan 2. Pada pertemuan ini, kita mulai mempelajari inti dari Pemrograman Berorientasi Objek (OOP) di C++, yaitu bagaimana membuat cetak biru (**Class**) dan menginstansiasinya menjadi perwujudan nyata (**Object**).

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Definisi Class & Object
- **Class**: Struktur atau cetak biru (*blueprint*) yang mendefinisikan atribut (variabel/data) dan perilaku (fungsi/metode) dari suatu entitas.
- **Object**: Wujud nyata (*instance*) yang dialokasikan di memori berdasarkan cetak biru Class tersebut.

### 2. Deklarasi Class di C++
Di C++, pembuatan class menggunakan kata kunci `class` dan diakhiri dengan titik koma (`;`). 

Secara default, anggota class di C++ bersifat `private`. Agar atribut dan metode dapat diakses dari luar class, kita menggunakan penentu akses (*access specifier*) `public:`.

```cpp
#include <iostream>
#include <string>

class Mobil {
public:
    // Atribut (Member Variables)
    std::string merk;
    std::string warna;

    // Constructor untuk inisialisasi objek
    Mobil(std::string m, std::string w) {
        merk = m;
        warna = w;
    }

    // Metode (Member Function)
    void jalan() {
        std::cout << "Mobil " << merk << " berwarna " << warna << " sedang melaju!" << std::endl;
    }
};
```

> [!NOTE]
> **Perbedaan `class` dan `struct` di C++:**
> Pada dasarnya `struct` dan `class` memiliki kemampuan yang hampir identik di C++. Perbedaan utamanya adalah: secara default anggota `class` bersifat `private`, sedangkan anggota `struct` bersifat `public`.

### 3. Cara Membuat Object (Instansiasi)
Di C++, objek dapat dibuat secara langsung di memori stack tanpa kata kunci `new`:
```cpp
Mobil mobilSaya("Toyota", "Merah");
mobilSaya.jalan(); // Output: Mobil Toyota berwarna Merah sedang melaju!
```

### 4. Pointer `this` di C++
Jika di Python kita menggunakan parameter `self` secara eksplisit pada setiap method, di C++ terdapat pointer implisit bernama `this` yang menunjuk ke instance objek saat ini.

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah membuat kelas **`Mahasiswa`** dan kelas **`Mobil`**:
1. **Class `Mahasiswa`**: memiliki atribut `nama` dan `nim`, serta memiliki metode `belajar()`.
2. **Class `Mobil`**: memiliki atribut `merk` dan `warna`, serta memiliki metode `jalan()`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

File tersebut mendemonstrasikan proses deklarasi class, instansiasi objek-objek ke dalam memori, pengisian nilai atribut, pemanggilan metode, serta inspeksi nilai atribut objek.

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-2
cd pertemuan-2

# Kompilasi kode C++
g++ -std=c++17 main.cpp -o main

# Jalankan program hasil kompilasi
./main
```

---

## 📝 Latihan Mandiri
1. Buatlah kelas baru bernama `Buku` yang memiliki atribut `judul` dan `penulis`, serta metode `baca()`. Instansiasikan dua objek buku yang berbeda di program utama.
2. Jelaskan persamaan dan perbedaan antara pointer `this` di C++ dengan parameter `self` di Python.
