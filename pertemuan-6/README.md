# Pertemuan 6: Polimorfisme & Virtual Functions di C++

Materi ini membahas konsep **Polimorfisme** (Polymorphism) di C++. Polimorfisme adalah kemampuan objek-objek dari berbagai kelas turunan yang berbeda untuk merespons antarmuka (*interface* / metode) yang sama dengan cara dan perilakunya masing-masing yang unik pada saat program berjalan (*runtime*).

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Polimorfisme Runtime & Virtual Function
Di C++, agar polimorfisme runtime dapat bekerja, metode pada kelas induk harus dideklarasikan dengan kata kunci **`virtual`**. Compiler akan membangun *Virtual Method Table* (vtable) untuk menghubungkan pemanggilan metode ke implementasi yang sesuai pada kelas turunan.

### 2. Pure Virtual Function & Abstract Base Class (ABC)
Sebuah kelas di C++ menjadi **Abstract Class** jika memiliki setidaknya satu **Pure Virtual Function** (fungsi virtual murni yang diakhiri dengan `= 0`). Kelas abstrak tidak dapat diinstansiasi secara langsung menjadi objek.

```cpp
class Hewan {
public:
    virtual ~Hewan() = default; // Destructor virtual wajib untuk kelas polimorfik

    // Pure virtual function (Wajib di-override oleh kelas anak)
    virtual std::string bersuara() const = 0;

    // Metode konkrit biasa yang otomatis diwariskan
    void tidur() const {
        std::cout << "Hewan sedang tidur pulas... Zzz\n";
    }
};
```

### 3. Mengakses Polimorfisme Melalui Pointer atau Reference
Polimorfisme dinamis di C++ hanya terwujud jika objek diakses melalui **pointer** (`Hewan*`), **reference** (`const Hewan&`), atau *smart pointer* (`std::unique_ptr<Hewan>`). Jika objek disalin langsung (*pass-by-value*), akan terjadi fenomena *Object Slicing*.

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah mendemonstrasikan perilaku polimorfis pada berbagai jenis hewan:
1. **Class Abstrak `Hewan`**: Memiliki pure virtual function `bersuara()` dan metode konkrit `tidur()`.
2. **Subclass `Kucing`**: Meng-override `bersuara()` untuk mengembalikan string `"Meow! Meow! 🐱"`.
3. **Subclass `Anjing`**: Meng-override `bersuara()` untuk mengembalikan string `"Guk! Guk! 🐶"`.
4. **Fungsi Polimorfik**: Membuat fungsi `perdengarkanSuara(const Hewan& hewan)` dan perulangan menggunakan koleksi objek `Hewan`.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-6
cd pertemuan-6

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan subclass baru bernama `Burung` yang mewarisi `Hewan`, dan implementasikan metode `bersuara()` yang menghasilkan suara `"Cuit! Cuit! 🐦"`. Uji objek Burung tersebut di dalam koleksi polimorfik pada program utama.
2. Coba hilangkan kata kunci `virtual` pada deklarasi metode `bersuara()` di kelas induk `Hewan`, lalu amati dan jelaskan apa yang terjadi saat fungsi `perdengarkanSuara` dipanggil.
