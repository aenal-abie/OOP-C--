# Pertemuan 12: CRUD - Update & Delete (Ubah & Hapus Data) di C++

Modul ini melengkapi siklus **CRUD** dengan mengimplementasikan metode pembaruan data (**Update**) dan penghapusan data (**Delete**) pada data mahasiswa yang disimpan di dalam berkas JSON menggunakan arsitektur pemrograman berorientasi objek di C++.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Operasi Pembaruan Data (*Update*) di C++
Untuk mengedit data pada berkas persisten:
1. Memuat seluruh data list objek dari berkas ke memori (`std::vector<Mahasiswa>`).
2. Mencari pointer/referensi objek yang akan diubah berdasarkan *kunci pencarian* (NIM).
3. Mengubah nilai atribut objek tersebut di memori.
4. Menyimpan kembali seluruh vektor objek tersebut ke berkas JSON menggunakan method `saveAll()`.

### 2. Operasi Penghapusan Data (*Delete*) di C++
Untuk menghapus data pada `std::vector` di C++:
1. Mencari posisi iterator elemen yang akan dihapus (misal menggunakan perulangan atau algoritma `std::find_if`).
2. Menghapus elemen dari vektor menggunakan `mahasiswaList.erase(iterator)`.
3. Menyimpan kembali daftar objek yang tersisa ke berkas JSON.

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah memperluas kelas `MahasiswaManager` agar memiliki kemampuan memodifikasi dan menghapus data mahasiswa:
1. **Method `ubah(nim, namaBaru, jurusanBaru)`**: Mencari mahasiswa berdasarkan NIM. Jika ditemukan, perbarui nama dan jurusannya lalu simpan perubahan.
2. **Method `hapus(nim)`**: Mencari mahasiswa berdasarkan NIM. Jika ditemukan, hapus objek tersebut dari vektor memori lalu simpan perubahan.
3. **Menu Loop Interaktif**: Menambahkan opsi menu **Ubah Mahasiswa** dan **Hapus Mahasiswa** dengan konfirmasi persetujuan di terminal.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-12
cd pertemuan-12

# Kompilasi
g++ -std=c++17 -I../include main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan pencatatan riwayat perubahan (*log timestamp*) sederhana setiap kali data mahasiswa diubah atau dihapus.
2. Buat fungsi ekspor data mahasiswa ke format tabel teks `.txt` agar siap dicetak.
