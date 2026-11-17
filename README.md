<div align="center">

![header](https://capsule-render.vercel.app/api?type=waving&color=00F7FF&height=220&section=header&text=Compiler%20Helper%20for%20C%20/%20C++&fontSize=38&fontColor=ffffff&animation=fadeIn&desc=Ağıllı%20Kompilyasiya%20%7C%20Avtomatik%20Flag%20Detection%20%7C%20Tarixçə%20&%20Növbə%20Meneceri&descSize=16&descAlignY=75)

<br/>

[![C++](https://img.shields.io/badge/C++-11%20%2F%2014%20%2F%2017%20%2F%2020-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![Python](https://img.shields.io/badge/Python-3.x-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://python.org)
[![G++](https://img.shields.io/badge/G++-MinGW--w64%20%2F%20GCC-F34B7D?style=for-the-badge&logo=gnu&logoColor=white)](https://mingw-w64.org)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://microsoft.com)
[![License: MIT](https://img.shields.io/badge/License-MIT-22C55E?style=for-the-badge)](LICENSE)

<br/>

**C və C++ layihələrini avtomatik analiz edən, asılılıqları (headers & libraries) yoxlayan, uyğun linker flag-lərini təyin edən, toplu növbə və tarixçə idarəetməsi təqdim edən müasir kompilyasiya köməkçisi.**

</div>

---

## 📌 Layihə Haqqında

**Compiler Helper for C / C++**, C və C++ proqramçılarının tez-tez qarşılaşdığı kitabxana bağlama (`-lm`, `-lpthread`, `-lcurl`, `-lsqlite3`, `-lSDL2`, və s.) xətalarını və vaxt itkisini aradan qaldırmaq üçün hazırlanmışdır. 

Kodunuzdakı `#include` sətirlərini intellektual olaraq oxuyur, sisteminizdə həmin kitabxanaların mövcudluğunu sınaqdan keçirir, tələb olunan kompilyasiya parametrlərini avtomatik formalaşdırır və proqramı dərhal işə salır.

Layihə tam olaraq **Modern C++** ilə yenidən yazılmış, əlavə olaraq **Python** versiyası da təmin edilmişdir.

---

## ✨ Əsas Xüsusiyyətlər

<table>
<tr>
  <td width="50%">
    <h4>🔍 Avtomatik Header & Library Analizi</h4>
    Mənbə kodundakı <code>#include &lt;...&gt;</code> və <code>#include "..."</code> direktivlərini skan edir və tələb olunan kitabxanaları müəyyənləşdirir.
  </td>
  <td width="50%">
    <h4>🏷️ 100+ Kitabxana üçün Flag Bazası</h4>
    Sistem, qrafika, şəbəkə, verilənlər bazası, riyaziyyat, multimedia və şifrələmə kitabxanaları üçün düzgün linker flag-lərini (və ya <code>pkg-config</code>) avtomatik əlavə edir.
  </td>
</tr>
<tr>
  <td>
    <h4>✅ Sistem Asılılıq Sınağı (Pre-check)</h4>
    Kitabxananın OS-də quraşdırılıb-quraşdırılmadığını real mini-kompilyasiya ilə yoxlayır. Əgər yoxdursa, onu necə quraşdırmaq lazım olduğunu göstərir.
  </td>
  <td>
    <h4>📋 Toplu Kompilyasiya Növbəsi (Batch Queue)</h4>
    <code>std::queue</code> ilə çoxsaylı faylları növbəyə əlavə edib tək bir əmrlə ardıcıl şəkildə kompilyasiya edə bilərsiniz.
  </td>
</tr>
<tr>
  <td>
    <h4>📜 Tarixçə & Axtarış Meneceri</h4>
    Bütün kompilyasiya cəhdləri, əmrlər və nəticələr tarixçə faylında (<code>compile_history.txt</code>) saxlanılır. Fayl adına görə sürətli axtarış aparmaq mümkündür.
  </td>
  <td>
    <h4>↩️ Geri Alma / Qaytarma (Undo & Redo)</h4>
    <code>std::stack</code> məlumat strukturu vasitəsilə səhvən silinmiş tarixçə qeydlərini asanlıqla geri qaytarmaq mümkündür.
  </td>
</tr>
<tr>
  <td>
    <h4>💻 İkili İş Rejimi (CLI & İnteraktiv Menyu)</h4>
    Həm birbaşa terminal arqumenti kimi (<code>./comp main.cpp</code>), həm də zəngin ANSI rəngli interaktiv konsol menyusu kimi işləyir.
  </td>
  <td>
    <h4>🌐 Cross-Platform (Windows & Linux)</h4>
    Həm Windows (Virtual Terminal Processing dəstəyi, <code>where</code>, <code>.exe</code>), həm də Linux/macOS mühitləri üçün uyğunlaşdırılmışdır.
  </td>
</tr>
</table>

---

## 🏗️ Struktur və Alqoritmlər (C++ Architecture)

`comp.cpp` kodu yüksək səviyyəli Obyektyönlü Proqramlaşdırma (OOP) prinsipləri və STL məlumat strukturları əsasında qurulmuşdur:

```
Compiler_Helper_For_C/
│
├── comp.cpp                 # Əsas C++ mənbə kodu (CLI + İnteraktiv Menyu + Məlumat Strukturları)
├── comp.py                  # Python alternativi (skript rejimi)
├── compile_history.txt       # Avtomatik formalaşan kompilyasiya loqları (TSV formatında)
└── README.md                # Layihə sənədləşməsi
```

### İstifadə olunan Məlumat Strukturları və Siniflər:

- **`std::map<std::string, std::string>` (`FlagDatabase`)**: 100-dən çox kitabxananın adını onun uyğun flag-i ilə saxlayır və $O(\log N)$ zaman mürəkkəbliyi ilə sürətli axtarış təmin edir.
- **`std::queue<std::string>` (Batch Queue)**: Toplu kompilyasiyada faylların FIFO (First-In, First-Out) prinsipi ilə ardıcıl emalını təmin edir.
- **`std::stack<CompileRecord>` (Undo / Redo Stack)**: Tarixçədən silinən qeydləri LIFO (Last-In, First-Out) strukturu ilə müvəqqəti yaddaşda saxlayaraq Redo imkanı yaradır.
- **`std::vector<CompileRecord>` (`HistoryManager`)**: Dinamik tarixçə qeydlərinin saxlanılması, filtrasiyası və fayla seriyalaşdırılması.
- **`Compiler` & `LibraryChecker`**: Sistem əmrlərinin təhlükəsiz çağırılması (`std::system`) və platformaya uyğun icra edilməsi.
- **Davamlılıq & Error Handling**: `try-catch` blokları, fayl axınları (`ifstream`, `ofstream`), xətalı sətirlərə qarşı dözümlülük və təmiz resurs idarəetməsi.

---

## ⚡ Quraşdırma və Kompilyasiya

### 1. `comp.cpp`-ni kompilyasiya etmək:

Hər hansı müasir C++ kompilyatoru (G++, Clang və ya MSVC) ilə layihəni saniyələr içində qura bilərsiniz:

```bash
# Windows (MinGW-w64 / MSYS2)
g++ -O2 -std=c++17 comp.cpp -o comp.exe

# Linux / macOS
g++ -O2 -std=c++17 comp.cpp -o comp
```

> 💡 **Qeyd**: Layihə heç bir kənar kitabxana tələb etmir (yalnız standart C++ STL).

---

## 🚀 İstifadə Qaydası

### Rejim 1: Birbaşa CLI Arqumenti ilə (Sürətli)

Faylın adını arqument olaraq vermək kifayətdir. Alət kitabxanaları tapacaq, flag-ləri birləşdirəcək, kompilyasiya edəcək və proqramı dərhal işlədəcək:

```bash
# Windows
.\comp.exe main.cpp

# Linux / macOS
./comp main.c
```

**Terminal Çıxışı Nümunəsi:**
```text
[+] g++ tapildi
--- Kitabxana yoxlanmasi ---
[+] math tapildi
[+] curl tapildi
[!] SDL2 yuklu deyil! Yukle: pacman -S mingw-w64-x86_64-SDL2

--- Komut ---
g++ main.cpp -o main.exe -lm -lcurl 

--- Kompilasiya ---
[+] Kompilasiya ugurlu oldu!

--- Proqram cixisi ---
Hesablama tamamlandı! Nəticə: 42
```

---

### Rejim 2: İnteraktiv Terminal Menyu Rejimi

Fayl adı göstərmədən proqramı işə saldıqda interaktiv idarəetmə konsolu açılır:

```bash
.\comp.exe
```

```text
--- MENYU ---
 1. Fayli kompilyasiya et ve isle
 2. Novbeye fayl elave et
 3. Novbedekileri kompilyasiya et (toplu)
 4. Tarixceni goster
 5. Tarixcede fayl axtar
 6. Son qeydi sil (undo)
 7. Silineni geri qaytar (redo)
 8. Cixis
 [novbede: 0, tarixce: 14]
Secim: 
```

#### Menyu Seçimləri:
1. **Faylı kompilyasiya et və işlə**: Fayl adını soruşur, analiz edir, build edir və dərhal icra edir.
2. **Növbəyə fayl əlavə et**: Toplu emal üçün fayl adını növbəyə (`queue`) qoyur.
3. **Növbədəkiləri kompilyasiya et (toplu)**: Növbədəki bütün faylları ard-arda kompilyasiya edir (fayllardan birində xəta olsa belə digərləri dayanmır).
4. **Tarixçəni göstər**: Əvvəlki bütün kompilyasiyaların zamanını, fayl adını və statusunu (`OK` / `XETA`) sıralayır.
5. **Tarixçədə fayl axtar**: Fayl adına görə keçmiş əmrləri axtarır.
6. **Son qeydi sil (undo)**: Tarixçədəki sonuncu sətri ləğv edir.
7. **Silinəni geri qaytar (redo)**: Ləğv olunmuş son qeydi yenidən tarixçəyə bərpa edir.
8. **Çıxış**: Tarixçəni diskə yadda saxlayaraq proqramdan çıxır.

---

### Rejim 3: Python Skripti ilə İstifadə (`comp.py`)

Python mühitində işləmək istəyirsinizsə:

```bash
python comp.py fayl.c
```

---

## 🛠️ Ətraf Mühitin Hazırlanması (G++ & MSYS2)

<details>
<summary><b>🪟 Windows — MSYS2 ilə G++ və Alətlərin Quraşdırılması</b></summary>
<br>

1. **[MSYS2 Rəsmi Saytından](https://www.msys2.org)** quraşdırıcını yükləyin və qurun.
2. MSYS2 UCRT64 və ya MinGW64 terminalını açıb əmrləri daxil edin:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-gdb
pacman -S mingw-w64-x86_64-pkg-config
pacman -S mingw-w64-x86_64-make
```
3. `C:\msys64\mingw64\bin` yolunu Windows **Environment Variables (PATH)**-ə əlavə edin.
4. CMD və ya PowerShell-də yoxlayın:
```bash
g++ --version
```

</details>

<details>
<summary><b>🐧 Linux (Ubuntu / Debian / Fedora)</b></summary>
<br>

```bash
# Ubuntu / Debian
sudo apt update
sudo apt install build-essential pkg-config

# Fedora
sudo dnf groupinstall "Development Tools"
sudo dnf install pkg-config
```

</details>

<details>
<summary><b>📦 Populyar Kitabxanaların Quraşdırılması (MSYS2)</b></summary>
<br>

```bash
pacman -S mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-openssl
pacman -S mingw-w64-x86_64-libpng
pacman -S mingw-w64-x86_64-opencv
pacman -S mingw-w64-x86_64-boost
```

</details>

---

## 📚 Dəstəklənən Kitabxanalar və Flag Cədvəli

<div align="center">

| 🏷️ Kateqoriya | 📦 Aşkarlanan Kitabxanalar | ⚙️ Avtomatik Əlavə Olunan Flag-lər |
|:---|:---|:---|
| ⚙️ **Sistem & Nüvə** | `math`, `pthread`, `dl`, `rt`, `util`, `atomic`, `stdc++` | `-lm`, `-lpthread`, `-ldl`, `-lrt`, `-latomic` |
| 🌐 **Şəbəkə & Protokollar** | `curl`, `ssl`, `openssl`, `ssh2`, `zmq`, `uv`, `nanomsg`, `websockets` | `-lcurl`, `-lssl -lcrypto`, `-lssh2`, `-lzmq`, `-luv` |
| 🗄️ **Verilənlər Bazası** | `sqlite3`, `pq` (PostgreSQL), `mysqlclient`, `mariadb`, `redis`, `leveldb`, `lmdb`, `rocksdb` | `-lsqlite3`, `-lpq`, `-lmysqlclient`, `-lhiredis` |
| 🎮 **Qrafika & GUI** | `SDL2`, `SDL2_image`, `SDL2_mixer`, `OpenGL`, `glfw3`, `glew`, `vulkan`, `cairo`, `gtk3`, `qt5` | `-lSDL2`, `-lGL -lGLU -lglut`, `-lglfw3`, `pkg-config` |
| 🔊 **Audio & Media** | `alsa`, `portaudio`, `sndfile`, `mpg123`, `vorbis`, `opus`, `ao` | `-lasound`, `-lportaudio`, `-lsndfile`, `-lopus` |
| 🖼️ **Şəkil & Vizual** | `png`, `jpeg`, `tiff`, `webp`, `opencv`, `Magick++` | `-lpng`, `-ljpeg`, `-lwebp`, `pkg-config opencv4` |
| 🗜️ **Sıxılma & Arxiv** | `zlib`, `bz2`, `lzma`, `zstd`, `lz4`, `snappy`, `archive` | `-lz`, `-lbz2`, `-lzstd`, `-llz4`, `-larchive` |
| 📝 **Mətn, Parser & Format** | `pcre`, `pcre2`, `readline`, `ncurses`, `xml2`, `json-c`, `jansson`, `yaml`, `toml` | `-lreadline`, `-lncurses`, `-lpcre2-8`, `-ljson-c` |
| 🔐 **Təhlükəsizlik & Kripto** | `sodium`, `argon2`, `gcrypt`, `gnutls`, `gpgme` | `-lsodium`, `-largon2`, `-lgnutls`, `-lgcrypt` |
| 🔢 **Elmi & Riyazi** | `gsl`, `fftw3`, `blas`, `lapack`, `gmp`, `mpfr` | `-lgsl -lgslcblas -lm`, `-lfftw3`, `-llapack` |
| 🚀 **Boost Ekosistemi** | `boost_system`, `boost_filesystem`, `boost_thread`, `boost_regex`, `boost_serialization` | `-lboost_system`, `-lboost_filesystem`, və s. |

</div>

---

## 👥 Müəllif və Təşəkkür

- **Tərtibatçı:** [x0rma-404](https://github.com/x0rma-404)
- **Akademik Rəhbər:** Samir Müəllim üçün xüsusi layihə (C++ Project)
- **İcazə:** [MIT License](LICENSE)

<div align="center">

⭐ **Faydalı oldusa layihəyə ulduz atmağı unutmayın!** ⭐

</div>
