# Pertemuan 13: Relasi Objek & Penyimpanan Berkas Terdistribusi di C++

Pada pertemuan penutup materi sebelum project akhir, kita akan membahas cara merelasikan dua berkas data yang berbeda menggunakan prinsip asosiasi OOP di C++. Ini adalah alternatif / substitusi dari operasi SQL `JOIN` pada database relasional yang dieksekusi langsung di memori program (*In-Memory Relational Join*).

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Mensimulasikan Primary Key & Foreign Key Tanpa Database
Dalam arsitektur penyimpanan berbasis berkas JSON terdistribusi:
- Berkas `mahasiswa.json` menyimpan data entitas primer mahasiswa dengan kunci utama (**Primary Key**: `nim`).
- Berkas `nilai.json` menyimpan data akademik dengan kunci tamu (**Foreign Key**: `nim`).

### 2. Melakukan Operasi JOIN di Memori (*In-Memory JOIN*)
Di C++, kita memadukan data dengan memuat kedua berkas ke struktur memori (vektor objek), lalu melakukan pencocokan relasi melalui query filter:
```cpp
// Mencocokkan nilai dengan data mahasiswa berdasarkan Foreign Key (nim)
const Mahasiswa* mhs = mhsMgr.dapatkanMahasiswa(nim);
std::vector<Nilai> khs = nilaiMgr.dapatkanKhs(nim);

if (mhs != nullptr) {
    std::cout << "Nama: " << mhs->nama << "\n";
    for (const auto& n : khs) {
        std::cout << "Matkul: " << n.matakuliah << " | Nilai: " << n.hitungAkhir() << "\n";
    }
}
```

---

## 💻 Tugas Praktikum

Membangun aplikasi **Kartu Hasil Studi (KHS)** berbasis relasi OOP di C++ dengan ketentuan:
1. **Data Mahasiswa**: dibaca dan disimpan ke `mahasiswa.json` (NIM, Nama, Jurusan).
2. **Data Nilai**: dibaca dan disimpan ke `nilai.json` (NIM, Mata Kuliah, Nilai Tugas, Nilai UTS, Nilai UAS).
3. **Logika Bisnis**: menghitung Nilai Akhir (Tugas 20% + UTS 30% + UAS 50%) dan mengonversi menjadi nilai huruf (A, B, C, D, E).
4. **Relational Read (JOIN)**: Menampilkan nama dan jurusan mahasiswa pada laporan cetak KHS dengan mencocokkan relasi NIM.
5. **Validasi Foreign Key**: Nilai mata kuliah hanya dapat diinput jika NIM mahasiswa yang bersangkutan sudah terdaftar.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-13
cd pertemuan-13

# Kompilasi
g++ -std=c++17 -I../include main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan metode `dapatkanIpk(const std::string& nim)` untuk menghitung nilai Indeks Prestasi (IPK) rata-rata mahasiswa berdasarkan bobot huruf mata kuliah (A=4, B=3, C=2, D=1, E=0).
2. Tambahkan fitur validasi agar satu mahasiswa tidak dapat memiliki dua entri nilai untuk mata kuliah yang sama.
