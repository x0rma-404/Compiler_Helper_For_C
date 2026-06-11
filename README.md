<div align="center">

# ⚙️ Compiler Helper for C

**C fayllarını avtomatik analiz edib kompilyasiya edən Python aləti**

![Python](https://img.shields.io/badge/Python-3.x-blue?style=for-the-badge&logo=python)
![G++](https://img.shields.io/badge/G++-MinGW-orange?style=for-the-badge&logo=gnu)
![Platform](https://img.shields.io/badge/Platform-Windows-lightblue?style=for-the-badge&logo=windows)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 🚀 Nə edir?

> `#include` sətirlərinə baxır, lazımi flag-ları tapır, kompilyasiya edir və proqramı işlədir — hamısı bir komutla!

```
#include <curl/curl.h>   →   -lcurl
#include <math.h>        →   -lm
#include <SDL2/SDL.h>    →   -lSDL2
```

---

## 📦 İstifadə

```bash
python aa.py fayl.c
```

**Nümunə çıxış:**

```
[+] g++ tapıldı

--- Kitabxana yoxlanması ---
[+] math tapıldı
[+] curl tapıldı
[!] SDL2 yüklü deyil! Yüklə: pacman -S mingw-w64-x86_64-SDL2

--- Komut ---
g++ main.c -o main.exe -lm -lcurl

--- Kompilasiya ---
[+] Kompilasiya uğurlu oldu!

--- Proqram çıxışı ---
Salam dünya!
```

---

## 🛠️ Quraşdırma

### Tələblər
- Python 3.x
- g++ (MinGW-w64 və ya MSYS2)
- pkg-config *(isteğe bağlı)*

### g++ quraşdırma (Windows)

1. **[MSYS2](https://www.msys2.org)** indir və quraşdır
2. MSYS2 terminalında:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
```
3. `C:\msys64\mingw64\bin` yolunu Windows **PATH**-ə əlavə et

### Kitabxana quraşdırma

```bash
pacman -S mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-SDL2
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-openssl
```

---

## 📚 Dəstəklənən kitabxanalar (100+)

| 🏷️ Kateqoriya | 📦 Kitabxanalar |
|:---:|:---|
| ⚙️ Sistem | `math` `pthread` `dl` `rt` `atomic` |
| 🌐 Şəbəkə | `curl` `ssl` `zmq` `uv` `websockets` `ssh2` |
| 🗄️ Veritabanı | `sqlite3` `pq` `redis` `leveldb` `lmdb` `rocksdb` |
| 🎮 Qrafika | `SDL2` `OpenGL` `glfw3` `vulkan` `cairo` `glew` |
| 🔊 Ses | `alsa` `portaudio` `opus` `vorbis` `sndfile` |
| 🖼️ Şəkil | `libpng` `jpeg` `webp` `opencv` `tiff` |
| 🗜️ Sıxışdırma | `zlib` `bz2` `zstd` `lz4` `snappy` |
| 📝 Mətn | `pcre` `ncurses` `readline` `xml2` `json-c` |
| 🔐 Şifrələmə | `ssl` `sodium` `gcrypt` `gnutls` `argon2` |
| 🔢 Riyaziyyat | `gsl` `fftw3` `blas` `lapack` `gmp` |
| 🚀 Boost | `boost_system` `boost_filesystem` `boost_thread` `boost_regex` |

---

## 📄 Lisans

Bu layihə **MIT** lisansı altında paylaşılır.

---

<div align="center">
  <sub>Made with ❤️ by <a href="https://github.com/x0rma-404">x0rma-404</a></sub>
</div>
