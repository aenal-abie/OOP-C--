# Project Akhir: Sistem Manajemen Portal Perpustakaan (OOP C++)

Project Akhir ini merupakan integrasi menyeluruh dari seluruh materi pemrograman berorientasi objek (OOP) di C++ yang telah dipelajari dari Pertemuan 1 hingga Pertemuan 13. Aplikasi ini mengelola siklus katalog buku, keanggotaan, serta transaksi peminjaman dan pengembalian buku dengan persistensi berkas JSON.

## 📋 Fitur Utama
1. **Manajemen Katalog Buku (CRUD)**
   - Tambah Buku baru dengan ID otomatis (*auto-increment*) dan inisialisasi stok.
   - Tampilkan seluruh katalog buku dalam format tabel rapi.
   - Perbarui informasi buku (Judul, Penulis, Stok).
   - Hapus buku dari katalog.
2. **Manajemen Anggota (CRUD)**
   - Registrasi anggota baru dengan validasi keunikan email (*unique constraint*).
   - Tampilkan daftar anggota terdaftar.
   - Ubah profil anggota (Nama dan Email).
   - Hapus data anggota.
3. **Transaksi Peminjaman**
   - Validasi ketersediaan stok buku dan verifikasi identitas anggota.
   - Pengurangan stok buku otomatis saat transaksi berhasil.
   - Pencatatan log transaksi peminjaman lengkap dengan stempel tanggal sistem.
4. **Transaksi Pengembalian**
   - Validasi status transaksi pinjam.
   - Pengembalian stok buku secara otomatis ke katalog.
   - Pembaruan status transaksi menjadi `"KEMBALI"`.
5. **Log Riwayat Transaksi (In-Memory JOIN)**
   - Menggabungkan data dari `peminjaman.json`, `buku.json`, dan `anggota.json` secara dinamis di memori program tanpa RDBMS SQL.

---

## 🏗️ Struktur Arsitektur Direktori

```
project-akhir/
├── Makefile                # Skrip build otomatis
├── config/
│   └── storage.hpp         # Abstraksi persistensi JSONStorage
├── data/                   # Direktori penyimpanan berkas persisten JSON
│   ├── anggota.json
│   ├── buku.json
│   └── peminjaman.json
├── models/
│   ├── anggota.hpp         # Entity Anggota & AnggotaManager
│   ├── buku.hpp            # Entity Buku & BukuManager
│   └── peminjaman.hpp      # Entity Peminjaman & PeminjamanManager (JOIN logic)
├── main.cpp                # Dashboard CLI utama
└── README.md               # Dokumentasi proyek
```

---

## 🚀 Panduan Kompilasi & Eksekusi

### Menggunakan Makefile:
```bash
# Masuk ke direktori project-akhir
cd project-akhir

# Kompilasi
make

# Jalankan program
./main
```

### Menggunakan g++ langsung:
```bash
# Masuk ke direktori project-akhir
cd project-akhir

# Kompilasi dengan menyertakan header direktori
g++ -std=c++17 -I../include -I. main.cpp -o main

# Jalankan program
./main
```
