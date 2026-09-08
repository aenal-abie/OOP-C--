# Pertemuan 11: CRUD - Create & Read (Tambah & Lihat Data) di C++

Modul ini memandu cara mengimplementasikan operasi **Create** (membuat/menambah data baru) dan **Read** (membaca/menampilkan data) berbasis pemrograman berorientasi objek di C++ menggunakan persistence layer `JSONStorage` yang telah kita bangun pada pertemuan sebelumnya.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Pola Desain Model & Repository (Manager)
Dalam pengembangan aplikasi modern berbasis OOP, kita memisahkan tanggung jawab komponen:
- **Class Model (Entity)**: Representasi cetak biru dari objek data dunia nyata (misalnya kelas `Mahasiswa` dengan atribut `nim`, `nama`, dan `jurusan`). Model bertanggung jawab mengonversi dirinya menjadi format serialisasi (`toJson`) dan merekonstruksi objek dari format serialisasi (`fromJson`).
- **Class Repository / Manager**: Bertanggung jawab memuat (*load*), menyimpan (*save*), menambah (*create*), dan menyajikan (*read*) koleksi objek model tersebut dari/ke media penyimpanan.

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah mengimplementasikan menu tambah dan tampilkan data mahasiswa menggunakan struktur OOP terpisah:
1. **Class `Mahasiswa`**: Sebagai model entitas mahasiswa. Memiliki metode `toJson()` (mengonversi objek menjadi object JSON) dan fungsi statis `fromJson()` (mengonversi JSON menjadi instance objek kembali).
2. **Class `MahasiswaManager`**:
   - Memiliki objek `JSONStorage` menuju berkas `mahasiswa.json`.
   - Metode `tambah(nim, nama, jurusan)`: Melakukan validasi keunikan NIM, instansiasi objek `Mahasiswa` baru, memasukkannya ke dalam vektor memori, dan memicu penyimpanan berkas.
   - Metode `tampilkanSemua()`: Mengembalikan daftar seluruh objek `Mahasiswa` yang aktif.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-11
cd pertemuan-11

# Kompilasi dengan direktori include header json
g++ -std=c++17 -I../include main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan metode pencarian `cariByNama(const std::string& keyword)` pada kelas `MahasiswaManager` yang menyaring dan mengembalikan daftar mahasiswa yang namanya mengandung substring pencarian tersebut.
2. Tambahkan validasi pada proses input mahasiswa baru agar panjang karakter NIM harus tepat 11 karakter angka.
