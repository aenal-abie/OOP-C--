# Pertemuan 7: Review OOP & Studi Kasus Relasi Objek

Selamat datang di modul Pertemuan 7. Pada pertemuan ini, kita me-review konsep-konsep dasar OOP dan mulai mengenalkan bagaimana objek-objek saling berinteraksi dan berasosiasi (*Object Association / Aggregation*) untuk memecahkan suatu masalah dunia nyata di C++.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Hubungan Antar Objek (Object Association & Aggregation)
Di dunia nyata, objek tidak berdiri sendiri melainkan saling terhubung:
- **Asosiasi**: Hubungan "menggunakan" atau "mengetahui" antar objek yang independen satu sama lain (misal: Anggota meminjam Buku).
- **Agregasi**: Hubungan "memiliki" (*has-a*) di mana objek bagian (*part*) dapat tetap eksis secara mandiri meskipun objek pemilik (*whole*) dihancurkan (misal: Anggota memiliki kumpulan referensi Buku).

### 2. Memetakan Relasi Objek di C++ Menggunakan Pointer
Di C++, untuk merelasikan objek tanpa membuat duplikat salinannya di memori, kita menggunakan **pointer** atau **reference**. Dengan menyimpan pointer `Buku*`, modifikasi status pada buku (misal: ketersediaan) akan tercermin langsung pada objek aslinya.

```cpp
class Anggota {
private:
    std::string nama;
    std::vector<Buku*> bukuDipinjam; // Agregasi pointer ke objek Buku

public:
    void pinjamBuku(Buku* buku) {
        bukuDipinjam.push_back(buku);
    }
};
```

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah membuat simulator **Sistem Peminjaman Buku Perpustakaan Sederhana** menggunakan relasi objek di C++:
1. **Class `Buku`**: Menyimpan data `judul`, `penulis`, dan status `tersedia` (boolean).
2. **Class `Anggota`**: Menyimpan data `nama`, `nomorAnggota`, dan `std::vector<Buku*> bukuDipinjam`.
3. **Logika Peminjaman**:
   * Metode `pinjamBuku(Buku& buku)` pada kelas `Anggota`: mengubah status buku menjadi tidak tersedia dan memasukkan alamat buku ke dalam daftar `bukuDipinjam`.
   * Metode `kembalikanBuku(Buku& buku)` pada kelas `Anggota`: mengubah status buku menjadi tersedia kembali dan menghapus pointer buku dari daftar `bukuDipinjam`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-7
cd pertemuan-7

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan pengecekan pada method `pinjamBuku(Buku& buku)` agar anggota tidak bisa meminjam buku jika buku tersebut statusnya sedang dipinjam oleh orang lain (`tersedia == false`). Tampilkan pesan peringatan.
2. Tambahkan batasan maksimal peminjaman (misalnya maksimal hanya 3 buku per anggota). Jika anggota mencoba meminjam buku ke-4, tolak peminjaman tersebut.
