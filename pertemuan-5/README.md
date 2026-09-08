# Pertemuan 5: Pewarisan (Inheritance)

Materi ini membahas konsep **Pewarisan** (Inheritance) di C++. Pewarisan memungkinkan sebuah kelas baru (kelas anak / *subclass* / *derived class*) untuk mewarisi atribut dan metode dari kelas yang sudah ada (kelas induk / *superclass* / *base class*), meminimalkan duplikasi kode (*code reuse*).

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Deklarasi Pewarisan di C++
Di C++, kelas anak mewarisi kelas induk menggunakan simbol titik dua (`:`) diikuti oleh mode pewarisan (umumnya `public`):
```cpp
class Induk {
public:
    void sapa() {
        std::cout << "Halo dari Induk!\n";
    }
};

class Anak : public Induk {
    // Mewarisi semua anggota public & protected dari Induk
};
```

### 2. Mengakses Constructor Induk
Jika kelas anak memiliki constructor sendiri, constructor kelas induk harus dipanggil pada **Member Initializer List**:
```cpp
class Pegawai {
protected:
    std::string nama;
    double gajiPokok;

public:
    Pegawai(std::string n, double g) : nama(n), gajiPokok(g) {}
};

class Dosen : public Pegawai {
private:
    double tunjanganSks;

public:
    // Memanggil constructor Pegawai(n, g)
    Dosen(std::string n, double g, double t) 
        : Pegawai(n, g), tunjanganSks(t) {}
};
```

### 3. Method Overriding di C++
Untuk memungkinkan kelas turunan mengubah perilaku metode kelas induk secara dinamis, metode pada kelas induk ditandai dengan kata kunci `virtual`, dan metode di kelas turunan ditandai dengan `override`:
```cpp
virtual double hitungGaji() const {
    return gajiPokok;
}
```

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah mengimplementasikan sistem penggajian pegawai (**Payroll**) menggunakan konsep pewarisan:
1. **Class Induk `Pegawai`**: memiliki atribut `nama` dan `gajiPokok`, serta metode `hitungGaji()` yang mengembalikan nilai `gajiPokok`.
2. **Class Anak `Dosen`**: mewarisi `Pegawai`, menambahkan atribut `tunjanganSks`, dan meng-override metode `hitungGaji()` untuk mengembalikan `gajiPokok + tunjanganSks`.
3. **Class Anak `Staff`**: mewarisi `Pegawai`, menambahkan atribut `lembur`, dan meng-override metode `hitungGaji()` untuk mengembalikan `gajiPokok + lembur`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-5
cd pertemuan-5

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Buat subclass baru bernama `Teknisi` yang mewarisi `Pegawai`, dengan tambahan atribut `tunjanganLapangan`. Override metode `hitungGaji()` agar menyertakan tunjangan lapangan tersebut.
2. Tambahkan metode `tampilkanSlip()` pada kelas induk `Pegawai` yang mencetak slip rincian gaji karyawan, lalu demonstrasikan pemanggilannya pada objek Dosen dan Staff.
