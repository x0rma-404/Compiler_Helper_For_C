import sys
import shutil
import subprocess
import os
print()
RED     = "\033[91m"
GREEN   = "\033[92m"
YELLOW  = "\033[93m"
BLUE    = "\033[94m"
MAGENTA = "\033[95m"
CYAN    = "\033[96m"
BOLD    = "\033[1m"
RESET   = "\033[0m"

def ok(msg):
    print(f"{BLUE}[{GREEN}+{BLUE}]{RESET} {MAGENTA}{msg}{RESET}")

def xeta(msg):
    print(f"{BLUE}[{RED}!{BLUE}]{RESET} {RED}{msg}{RESET}")

def xeberdar(msg):
    print(f"{BLUE}[{YELLOW}~{BLUE}]{RESET} {MAGENTA}{msg}{RESET}")

def baslig(msg):
    print(f"\n{CYAN}{BOLD}--- {msg} ---{RESET}")

def check_dependencies():
    if not shutil.which("g++"):
        xeta("g++ tapılmadı! Yüklə: https://mingw-w64.org")
        sys.exit(1)
    else:
        ok("g++ tapıldı")

    if not shutil.which("pkg-config"):
        xeberdar("pkg-config tapılmadı, bəzi kitabxanalar yoxlanılmayacaq")

def check_library(lib, flag):
    if "pkg-config" in flag:
        if not shutil.which("pkg-config"):
            return True
        result = subprocess.run(
            ["pkg-config", "--exists", lib],
            capture_output=True
        )
        return result.returncode == 0

    test_code = f"""
#include <{lib}.h>
int main() {{ return 0; }}
"""
    with open("__test__.c", "w") as f:
        f.write(test_code)

    result = subprocess.run(
        ["g++", "__test__.c", flag.split()[0], "-o", "__test__"],
        capture_output=True
    )

    for f in ["__test__.c", "__test__", "__test__.exe"]:
        if os.path.exists(f):
            os.remove(f)

    return result.returncode == 0

flags = {
    "math":              "-lm",
    "pthread":           "-lpthread",
    "dl":                "-ldl",
    "rt":                "-lrt",
    "util":              "-lutil",
    "c":                 "-lc",
    "stdc++":            "-lstdc++",
    "atomic":            "-latomic",

    "curl":              "-lcurl",
    "ssl":               "-lssl -lcrypto",
    "openssl":           "-lssl -lcrypto",
    "ssh2":              "-lssh2",
    "microhttpd":        "-lmicrohttpd",
    "nsl":               "-lnsl",
    "socket":            "-lsocket",
    "websockets":        "-lwebsockets",
    "zmq":               "-lzmq",
    "nanomsg":           "-lnanomsg",
    "uv":                "-luv",

    "sqlite3":           "-lsqlite3",
    "pq":                "-lpq",
    "mysqlclient":       "-lmysqlclient",
    "mariadb":           "-lmariadb",
    "mongoc":            "-lmongoc-1.0 -lbson-1.0",
    "redis":             "-lhiredis",
    "leveldb":           "-lleveldb",
    "lmdb":              "-llmdb",
    "rocksdb":           "-lrocksdb",

    "SDL2":              "-lSDL2",
    "SDL2_image":        "-lSDL2_image",
    "SDL2_mixer":        "-lSDL2_mixer",
    "SDL2_ttf":          "-lSDL2_ttf",
    "opengl":            "-lGL -lGLU -lglut",
    "GL":                "-lGL",
    "GLU":               "-lGLU",
    "glut":              "-lglut",
    "glfw3":             "-lglfw3",
    "glew":              "-lGLEW",
    "vulkan":            "-lvulkan",
    "X11":               "-lX11",
    "Xext":              "-lXext",
    "xcb":               "-lxcb",
    "cairo":             "-lcairo",
    "pango":             "`pkg-config --libs pango`",
    "gtk3":              "`pkg-config --cflags --libs gtk+-3.0`",
    "gtk4":              "`pkg-config --cflags --libs gtk4`",
    "glib":              "`pkg-config --cflags --libs glib-2.0`",
    "qt5":               "`pkg-config --cflags --libs Qt5Core Qt5Widgets`",

    "alsa":              "-lasound",
    "portaudio":         "-lportaudio",
    "ao":                "-lao",
    "sndfile":           "-lsndfile",
    "mpg123":            "-lmpg123",
    "vorbis":            "-lvorbis -logg",
    "opus":              "-lopus",

    "libpng":            "-lpng",
    "png":               "-lpng",
    "libjpeg":           "-ljpeg",
    "jpeg":              "-ljpeg",
    "tiff":              "-ltiff",
    "webp":              "-lwebp",
    "opencv":            "`pkg-config --cflags --libs opencv4`",
    "Magick++":          "`Magick++-config --cppflags --libs`",

    "zlib":              "-lz",
    "bz2":               "-lbz2",
    "lzma":              "-llzma",
    "zstd":              "-lzstd",
    "lz4":               "-llz4",
    "snappy":            "-lsnappy",
    "archive":           "-larchive",

    "xml2":              "`xml2-config --cflags --libs`",
    "json-c":            "-ljson-c",
    "jansson":           "-ljansson",
    "yaml":              "-lyaml",
    "toml":              "-ltoml",
    "pcre":              "-lpcre",
    "pcre2":             "-lpcre2-8",
    "readline":          "-lreadline",
    "ncurses":           "-lncurses",
    "panel":             "-lpanel -lncurses",

    "gcrypt":            "-lgcrypt",
    "gpgme":             "-lgpgme",
    "argon2":            "-largon2",
    "sodium":            "-lsodium",
    "gnutls":            "-lgnutls",

    "gsl":               "-lgsl -lgslcblas -lm",
    "fftw3":             "-lfftw3",
    "blas":              "-lblas",
    "lapack":            "-llapack -lblas",
    "gmp":               "-lgmp",
    "mpfr":              "-lmpfr",

    "uuid":              "-luuid",
    "cap":               "-lcap",
    "acl":               "-lacl",
    "fuse":              "-lfuse",
    "iconv":             "-liconv",
    "intl":              "-lintl",
    "dbus":              "`pkg-config --cflags --libs dbus-1`",
    "systemd":           "-lsystemd",
    "udev":              "-ludev",
    "bluetooth":         "-lbluetooth",
    "gio":               "`pkg-config --cflags --libs gio-2.0`",

    "boost_system":      "-lboost_system",
    "boost_filesystem":  "-lboost_filesystem",
    "boost_thread":      "-lboost_thread",
    "boost_regex":       "-lboost_regex",
    "boost_serialization": "-lboost_serialization",
    "boost_program_options": "-lboost_program_options",
}

def main():
    check_dependencies()

    if len(sys.argv) < 2:
        xeberdar("İstifadə: aa.py <fayl.c>")
        sys.exit(1)

    fd_name = sys.argv[1]
    exe_name = fd_name[:-2] + ".exe"
    out = f'g++ {fd_name} -o {exe_name} '

    baslig("Kitabxana yoxlanması")

    fd = open(fd_name, 'r')
    for i in fd:
        if i[0] != '#':
            break
        lib = i[9:].split('.')[0].strip()
        if lib in flags:
            flag = flags[lib]
            if check_library(lib, flag):
                ok(f"{lib} tapıldı")
                out += flag + " "
            else:
                xeta(f"{lib} yüklü deyil! Yüklə: pacman -S mingw-w64-x86_64-{lib}")
    fd.close()

    baslig("Komut")
    print(f"{YELLOW}{out}{RESET}")

    baslig("Kompilasiya")
    result = subprocess.run(out, shell=True, stdout=sys.stdout, stderr=sys.stderr)

    if result.returncode == 0:
        ok("Kompilasiya uğurlu oldu!")

        baslig("Proqram çıxışı")
        subprocess.run(exe_name, shell=True, stdout=sys.stdout, stderr=sys.stderr, stdin=sys.stdin)
    else:
        xeta("Kompilasiya uğursuz oldu!")

main()