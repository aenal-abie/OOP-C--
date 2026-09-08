# Pertemuan 4: Enkapsulasi (Encapsulation)

Materi ini membahas konsep **Enkapsulasi** (Encapsulation) di C++. Enkapsulasi adalah teknik menyembunyikan detail properti internal suatu objek (*data hiding*) untuk melindunginya dari modifikasi eksternal yang tidak sah, serta menyediakan antarmuka akses terpadu melalui *Getter* dan *Setter*.

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Menyembunyikan Data (*Data Hiding*) Menggunakan Penentu Akses
Berbeda dengan Python yang mengandalkan konvensi penamaan (`_protected` atau `__private` dengan *name mangling*), C++ menerapkan pembatasan akses secara ketat di tingkat compiler (*compile-time enforcement*) menggunakan tiga kata kunci penentu akses:
- **`private:`**: Anggota hanya dapat diakses dari dalam class itu sendiri.
- **`protected:`**: Anggota dapat diakses dari dalam class itu sendiri dan class turunannya (*derived classes*).
- **`public:`**: Anggota dapat diakses secara bebas dari mana saja di luar class.

```cpp
class Akun {
private:
    double saldo; // Atribut private, tidak bisa diakses dari fungsi luar

public:
    Akun(double saldoAwal) : saldo(saldoAwal) {}
};
```
Jika kita mencoba mengakses `akun.saldo` dari luar class, compiler C++ akan memicu error kompilasi:
`error: 'double Akun::saldo' is private within this context`.

### 2. Getter & Setter di C++
Untuk memberikan akses yang aman dan terkontrol terhadap variabel private, kita membuat metode public:
- **Getter**: Mengembalikan nilai atribut (biasanya ditandai dengan kata kunci `const` untuk menjamin tidak ada modifikasi data).
- **Setter**: Memperbarui nilai atribut dengan menyertakan validasi logika bisnis.

```cpp
class Akun {
private:
    double saldo;

public:
    Akun(double s) : saldo(s >= 0 ? s : 0) {}

    // Getter dengan qualifier const
    double getSaldo() const {
        return saldo;
    }

    // Setter dengan validasi
    void setSaldo(double s) {
        if (s >= 0) {
            saldo = s;
        }
    }
};
```

---

## 💻 Tugas Praktikum

Tugas praktikum kali ini adalah membuat kelas **`RekeningBank`** dengan spesifikasi:
- Atribut private: `nomorRekening`, `pemilik`, dan `saldo`.
- Constructor untuk menerima `nomorRekening`, `pemilik`, dan `saldoAwal`.
- Method Getter `getSaldo()` untuk mengecek saldo.
- Method `setoran(double jumlah)` untuk menambah saldo dengan validasi nominal positif.
- Method `tarikTunai(double jumlah)` dengan validasi: pastikan jumlah penarikan bernilai positif dan saldo mencukupi sebelum dikurangi.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-4
cd pertemuan-4

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Modifikasi kelas `RekeningBank` di `main.cpp` agar memiliki batas saldo minimal mengendap (misalnya saldo tidak boleh kurang dari Rp 50.000). Jika penarikan menyebabkan sisa saldo di bawah Rp 50.000, batalkan penarikan tersebut dan tampilkan pesan kesalahan.
2. Tambahkan atribut private baru `pin` bertipe `std::string` dan buat metode `ubahPin(std::string pinLama, std::string pinBaru)` untuk memvalidasi dan mengubah PIN rekening tersebut.
