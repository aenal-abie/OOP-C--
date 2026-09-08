# Pertemuan 8: Project UTS - Sistem POS (Point of Sale) Kasir Mini

Pertemuan 8 adalah **Ujian Tengah Semester (UTS)** praktikum. Mahasiswa diminta membangun aplikasi kasir toko (**Point of Sale / POS**) mandiri menggunakan paradigma pemrograman berorientasi objek (OOP) murni di C++ tanpa menggunakan database. Seluruh data disimpan dalam struktur vektor objek (`std::vector`) di memori.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum (Soal UTS)](#-tugas-praktikum-soal-uts)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Apa itu Sistem POS?
Sistem POS (*Point of Sale*) mengelola katalog produk, melacak keranjang belanja pelanggan, menghitung total harga transaksi beserta diskon, serta mencetak struk belanja virtual ke terminal.

### 2. Tantangan Desain Tanpa Database
Tanpa database, kita harus mendesain class-class yang bertindak sebagai:
- **`Produk`**: Menyimpan detail produk (ID, Nama, Harga).
- **`ItemKeranjang`**: Menyimpan objek `Produk` beserta kuantitas belanja (`qty`).
- **`Keranjang`**: Mengelola daftar `ItemKeranjang`, menghitung diskon (misalnya diskon 10% jika belanja di atas Rp 100.000), memproses pembayaran uang tunai, dan mencetak struk penjualan rapi ke terminal.

---

## 💻 Tugas Praktikum (Soal UTS)

Membangun aplikasi POS Kasir Mini berbasis CLI interaktif dengan ketentuan:
1. **Class `Produk`**: atribut `idProduk`, `nama`, `harga`.
2. **Class `Keranjang`**:
   - Metode `tambahItem(const Produk& produk, int qty)`: menambahkan produk ke dalam keranjang belanja (jika produk sudah ada, tambahkan kuantitasnya).
   - Metode `hitungTotal()`: menjumlahkan total harga belanja.
   - Metode `cetakStruk(double bayar)`: menampilkan data struk belanja rapi menggunakan `<iomanip>`, menghitung diskon 10% jika total harga > Rp 100.000, serta menghitung kembalian uang tunai.
3. **Loop Menu Interaktif**:
   - Menu 1: Lihat Katalog Produk
   - Menu 2: Tambah Produk ke Keranjang Belanja
   - Menu 3: Lihat Isi Keranjang Belanja
   - Menu 4: Bayar & Cetak Struk Belanja
   - Menu 5: Keluar

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-8
cd pertemuan-8

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan validasi pada proses pembayaran agar jika uang tunai yang diinput oleh kasir kurang dari total belanja yang harus dibayar, transaksi tidak diselesaikan dan program menampilkan peringatan.
2. Tambahkan fitur cetak nomor struk transaksi otomatis menggunakan generator acak (*random number generator*) atau nomor urut *counter*.
