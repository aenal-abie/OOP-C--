# Pertemuan 10: Membuat Class Storage Wrapper (Abstraksi Penyimpanan) di C++

Materi ini mengajarkan cara merancang arsitektur aplikasi yang rapi dengan mengemas (*wrapping*) fungsi pembacaan dan penulisan berkas JSON ke dalam sebuah Class khusus bernama **`JSONStorage`**. Konsep ini serupa dengan pembuatan Class Database Wrapper pada arsitektur perangkat lunak berbasis OOP.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Mengapa Perlu Abstraksi Penyimpanan (*Storage Wrapper*)?
Jika kita menulis logika `std::ifstream`, `std::ofstream`, dan parsing JSON berulang-ulang di seluruh file program, kode kita akan menjadi kotor (*boilerplate*) dan sulit dikelola jika suatu saat arsitektur penyimpanan berubah. Dengan membungkusnya dalam sebuah Class:
- Memusatkan seluruh logika I/O file di satu tempat saja (*Single Responsibility Principle*).
- Menawarkan enkapsulasi yang lebih baik.
- Mempermudah penggantian media penyimpanan di kemudian hari (misalnya migrasi ke SQLite) tanpa perlu mengubah kode logika bisnis aplikasi.

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah membuat kelas **`JSONStorage`** dengan spesifikasi:
- Atribut instansi `filepath` untuk menentukan berkas JSON mana yang akan diakses.
- Metode `loadData(const json& defaultValue)`: Membaca berkas JSON yang terkait dan mengembalikan datanya. Jika berkas belum ada di disk, otomatis buat berkas baru dengan isi `defaultValue`.
- Metode `saveData(const json& data)`: Menyimpan data terstruktur (array/object JSON) kembali ke berkas dengan format indentasi yang rapi, serta otomatis membuat direktori induk jika belum tersedia menggunakan fitur C++17 `<filesystem>`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

Di dalam berkas tersebut, Class `JSONStorage` diuji untuk melakukan pembacaan dan pembaruan pengaturan aplikasi (`settings.json`) secara terenkapsulasi.

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-10
cd pertemuan-10

# Kompilasi dengan menyertakan header json
g++ -std=c++17 -I../include main.cpp -o main

# Jalankan program
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan metode `backup()` pada kelas `JSONStorage` yang menyalin isi file JSON saat ini ke file baru dengan ekstensi `.bak` sebagai cadangan keamanan data.
2. Implementasikan penanganan kesalahan (*Exception Handling*) menggunakan blok `try-catch` di dalam metode `loadData` untuk mendeteksi berkas yang korup/rusak dan mengembalikan nilai default yang aman.
