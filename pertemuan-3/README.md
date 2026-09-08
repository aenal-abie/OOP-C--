# Pertemuan 3: Constructor & Destructor di C++

Materi ini membahas konsep **Constructor** dan **Destructor** di C++. Constructor adalah metode khusus yang dipanggil secara otomatis saat objek baru pertama kali diinstansiasi dari kelasnya. Di C++, constructor memiliki nama yang persis sama dengan nama kelas dan tidak memiliki tipe kembalian (*return type*).

## 📋 Daftar Isi
1. [Materi Teori](#-materi-teori)
2. [Tugas Praktikum](#-tugas-praktikum)
3. [Panduan Kompilasi](#-panduan-kompilasi)
4. [Latihan Mandiri](#-latihan-mandiri)

---

## 📖 Materi Teori

### 1. Apa itu Constructor?
Constructor digunakan untuk:
- Mengalokasikan dan menginisialisasi memori untuk objek baru.
- Melakukan inisialisasi awal nilai properti/atribut objek.
- Menjalankan logika atau validasi awal ketika objek dibuat.

### 2. Constructor Berparameter & Member Initializer List
Di C++, inisialisasi atribut dapat dilakukan secara efisien menggunakan **Member Initializer List**:
```cpp
class Buku {
public:
    std::string judul;
    std::string penulis;
    int tahun;

    // Constructor dengan Member Initializer List
    Buku(std::string j, std::string p, int t) 
        : judul(j), penulis(p), tahun(t) {
        // Logika tambahan / validasi dapat diletakkan di dalam kurung kurawal
    }
};
```
Saat objek diinstansiasi, argumen dilewatkan ke dalam kelas:
```cpp
Buku bukuBaru("Laskar Pelangi", "Andrea Hirata", 2005);
```

### 3. Apa itu Destructor?
Destructor adalah metode khusus yang dipanggil secara otomatis saat masa hidup (*lifetime*) objek berakhir (misalnya ketika objek keluar dari scope fungsi). Destructor diawali dengan simbol tilde (`~`):
```cpp
~Buku() {
    // Membersihkan resource jika diperlukan
}
```

---

## 💻 Tugas Praktikum

Tugas praktikum pada pertemuan ini adalah membuat kelas **`Buku`** dengan ketentuan:
- Memiliki constructor berparameter untuk mengisi: `judul`, `penulis`, dan `stok`.
- Menambahkan validasi di dalam constructor: jika `stok` yang dimasukkan bernilai negatif (kurang dari 0), otomatis tampilkan pesan peringatan (*Warning*) dan set nilai `stok` menjadi 0.
- Memiliki metode `tampilkanInfo()` untuk mencetak semua properti buku ke terminal.

### **✨ Solusi Implementasi**
Jawaban praktikum ini dapat dilihat dan dijalankan pada file:
👉 **[`main.cpp`](main.cpp)**

---

## 🚀 Panduan Kompilasi & Eksekusi

```bash
# Masuk ke direktori pertemuan-3
cd pertemuan-3

# Kompilasi
g++ -std=c++17 main.cpp -o main

# Jalankan
./main
```

---

## 📝 Latihan Mandiri
1. Tambahkan atribut baru bernama `harga` ke dalam kelas `Buku` dan tambahkan validasi pada constructor agar harga tidak boleh kurang dari 1.000 rupiah. Jika kurang, otomatis set menjadi 1.000 rupiah.
2. Buatlah objek buku baru dengan input yang diambil secara dinamis dari ketikan keyboard pengguna (`std::cin` / `std::getline`) lalu tampilkan informasinya.
