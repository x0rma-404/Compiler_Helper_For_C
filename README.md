<div align="center">

![header](https://capsule-render.vercel.app/api?type=waving&color=00F7FF&height=200&section=header&text=Compiler%20Helper%20for%20C&fontSize=40&fontColor=ffffff&animation=fadeIn&desc=Auto%20detect%20%7C%20Compile%20%7C%20Run&descSize=18&descAlignY=75)
<br/>

[![Python](https://img.shields.io/badge/Python-3.x-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://python.org)
[![G++](https://img.shields.io/badge/G++-MinGW--w64-F34B7D?style=for-the-badge&logo=gnu&logoColor=white)](https://mingw-w64.org)
[![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)](https://microsoft.com)
[![MIT License](https://img.shields.io/badge/License-MIT-22C55E?style=for-the-badge)](LICENSE)

<br/>

> **C fayllarını avtomatik analiz edib kompilyasiya edən və işlədən Python aləti**

</div>

---

## ✨ Xüsusiyyətlər

<table>
<tr>
<td>🔍 <b>Avtomatik analiz</b></td>
<td>#include sətirlərinə baxır, kitabxanaları tapır</td>
</tr>
<tr>
<td>🏷️ <b>Flag detector</b></td>
<td>100+ kitabxana üçün avtomatik flag əlavə edir</td>
</tr>
<tr>
<td>✅ <b>Dependency check</b></td>
<td>Kitabxananın yüklü olub olmadığını yoxlayır</td>
</tr>
<tr>
<td>⚡ <b>Auto compile & run</b></td>
<td>Kompilyasiya edib proqramı avtomatik işlədir</td>
</tr>
<tr>
<td>🎨 <b>Rəngli terminal</b></td>
<td>Rəngli və oxunaqlı çıxış</td>
</tr>
</table>

---

## 🚀 İstifadə

```bash
python aa.py fayl.c
```

**Nümunə çıxış:**

```
[+] g++ tapıldı

─── Kitabxana yoxlanması ───
[+] math tapıldı
[+] curl tapıldı
[!] SDL2 yüklü deyil! Yüklə: pacman -S mingw-w64-x86_64-SDL2

─── Komut ───
g++ main.c -o main.exe -lm -lcurl

─── Kompilasiya ───
[+] Kompilasiya uğurlu oldu!

─── Proqram çıxışı ───
Salam dünya!
```

---

## 🛠️ Quraşdırma

<details>
<summary><b>🪟 Windows — MSYS2 ilə g++ quraşdırma</b></summary>
<br>

1. **[MSYS2](https://www.msys2.org)** indir və quraşdır
2. MSYS2 terminalında:
```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc
pacman -S mingw-w64-x86_64-pkg-config
```
3. `C:\msys64\mingw64\bin` yolunu Windows **PATH**-ə əlavə et
4. Yoxla:
```bash
g++ --version
```

</details>

<details>
<summary><b>📦 Kitabxana quraşdırma (MSYS2)</b></summary>
<br>

```bash
pacman -S mingw-w64-x86_64-curl
pacman -S mingw-w64-x86_64-SDL2
pacman -S mingw-w64-x86_64-sqlite3
pacman -S mingw-w64-x86_64-openssl
pacman -S mingw-w64-x86_64-libpng
pacman -S mingw-w64-x86_64-opencv
```

</details>

---

## 📚 Dəstəklənən kitabxanalar

<div align="center">

| 🏷️ Kateqoriya | 📦 Kitabxanalar |
|:---:|:---|
| ⚙️ **Sistem** | `math` `pthread` `dl` `rt` `atomic` `stdc++` |
| 🌐 **Şəbəkə** | `curl` `ssl` `zmq` `uv` `websockets` `ssh2` `microhttpd` |
| 🗄️ **Veritabanı** | `sqlite3` `pq` `redis` `leveldb` `lmdb` `rocksdb` `mariadb` |
| 🎮 **Qrafika** | `SDL2` `SDL2_image` `SDL2_mixer` `OpenGL` `glfw3` `vulkan` `cairo` |
| 🔊 **Ses** | `alsa` `portaudio` `opus` `vorbis` `sndfile` `mpg123` |
| 🖼️ **Şəkil** | `libpng` `jpeg` `webp` `opencv` `tiff` `Magick++` |
| 🗜️ **Sıxışdırma** | `zlib` `bz2` `zstd` `lz4` `snappy` `archive` `lzma` |
| 📝 **Mətn / Format** | `pcre` `ncurses` `readline` `xml2` `json-c` `yaml` `jansson` |
| 🔐 **Şifrələmə** | `ssl` `sodium` `gcrypt` `gnutls` `argon2` `gpgme` |
| 🔢 **Riyaziyyat** | `gsl` `fftw3` `blas` `lapack` `gmp` `mpfr` |
| 🖥️ **Sistem / OS** | `uuid` `fuse` `udev` `dbus` `systemd` `bluetooth` |
| 🚀 **Boost** | `boost_system` `boost_filesystem` `boost_thread` `boost_regex` |

</div>

---

## 📊 Statistika

<div align="center">

![GitHub repo size](https://img.shields.io/github/repo-size/x0rma-404/Compiler_Helper_For_C?style=for-the-badge&color=blue)
![GitHub last commit](https://img.shields.io/github/last-commit/x0rma-404/Compiler_Helper_For_C?style=for-the-badge&color=purple)
![GitHub language count](https://img.shields.io/github/languages/count/x0rma-404/Compiler_Helper_For_C?style=for-the-badge&color=orange)

</div>

---

<div align="center">

### 📄 MIT Lisansı altında paylaşılır

<br/>

**⭐ Bəyəndinsə ulduz ver!**

<br/>

<sub>Made with ❤️ by <a href="https://github.com/x0rma-404">x0rma-404</a></sub>

</div>
