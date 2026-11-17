#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
const std::string NULL_OUT = " >nul 2>&1";
#else
const std::string NULL_OUT = " >/dev/null 2>&1";
#endif

const std::string HISTORY_FILE = "compile_history.txt";

// ---------- Rengler ----------
namespace Color {
const std::string RED = "\033[91m", GREEN = "\033[92m", YELLOW = "\033[93m",
                  BLUE = "\033[94m", MAGENTA = "\033[95m", CYAN = "\033[96m",
                  BOLD = "\033[1m", RESET = "\033[0m";
}

// ---------- Mesaj funksiyalari ----------
void ok(const std::string& msg) {
    std::cout << Color::BLUE << "[" << Color::GREEN << "+" << Color::BLUE << "]"
              << Color::RESET << " " << Color::MAGENTA << msg << Color::RESET << "\n";
}
void xeta(const std::string& msg) {
    std::cout << Color::BLUE << "[" << Color::RED << "!" << Color::BLUE << "]"
              << Color::RESET << " " << Color::RED << msg << Color::RESET << "\n";
}
void xeberdar(const std::string& msg) {
    std::cout << Color::BLUE << "[" << Color::YELLOW << "~" << Color::BLUE << "]"
              << Color::RESET << " " << Color::MAGENTA << msg << Color::RESET << "\n";
}
void baslig(const std::string& msg) {
    std::cout << "\n" << Color::CYAN << Color::BOLD << "--- " << msg << " ---"
              << Color::RESET << "\n";
}

// ---------- Yardimci funksiyalar ----------
bool commandExists(const std::string& name) {
#ifdef _WIN32
    std::string cmd = "where " + name + NULL_OUT;
#else
    std::string cmd = "command -v " + name + NULL_OUT;
#endif
    return std::system(cmd.c_str()) == 0;
}

std::string trim(const std::string& s) {
    size_t b = s.find_first_not_of(" \t\r\n");
    if (b == std::string::npos) return "";
    size_t e = s.find_last_not_of(" \t\r\n");
    return s.substr(b, e - b + 1);
}

std::vector<std::string> split(const std::string& s, char sep) {
    std::vector<std::string> parts;
    std::string item;
    std::istringstream stream(s);
    while (std::getline(stream, item, sep)) parts.push_back(item);
    return parts;
}

std::string currentTime() {
    std::time_t t = std::time(nullptr);
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&t));
    return buf;
}

// "#include <math.h>" -> "math"; include deyilse bos setir qaytarir
std::string extractLibName(const std::string& line) {
    std::string s = trim(line);
    if (s.empty() || s[0] != '#') return "";
    s = trim(s.substr(1));
    if (s.compare(0, 7, "include") != 0) return "";
    s = trim(s.substr(7));
    if (s.empty() || (s[0] != '<' && s[0] != '"')) return "";
    char closing = (s[0] == '<') ? '>' : '"';
    size_t end = s.find(closing, 1);
    if (end == std::string::npos) return "";
    std::string header = s.substr(1, end - 1);
    size_t dot = header.find('.');
    return dot == std::string::npos ? header : header.substr(0, dot);
}

// "test.cpp" -> "test"
std::string stripExtension(const std::string& name) {
    size_t dot = name.rfind('.');
    size_t slash = name.find_last_of("/\\");
    if (dot == std::string::npos || (slash != std::string::npos && dot < slash))
        return name;
    return name.substr(0, dot);
}

// ---------- Kitabxana bazasi ----------
class FlagDatabase {
    std::map<std::string, std::string> flags;

public:
    FlagDatabase() {
        flags = {
            {"math", "-lm"}, {"pthread", "-lpthread"}, {"dl", "-ldl"}, {"rt", "-lrt"},
            {"util", "-lutil"}, {"c", "-lc"}, {"stdc++", "-lstdc++"}, {"atomic", "-latomic"},

            {"curl", "-lcurl"}, {"ssl", "-lssl -lcrypto"}, {"openssl", "-lssl -lcrypto"},
            {"ssh2", "-lssh2"}, {"microhttpd", "-lmicrohttpd"}, {"nsl", "-lnsl"},
            {"socket", "-lsocket"}, {"websockets", "-lwebsockets"}, {"zmq", "-lzmq"},
            {"nanomsg", "-lnanomsg"}, {"uv", "-luv"},

            {"sqlite3", "-lsqlite3"}, {"pq", "-lpq"}, {"mysqlclient", "-lmysqlclient"},
            {"mariadb", "-lmariadb"}, {"mongoc", "-lmongoc-1.0 -lbson-1.0"},
            {"redis", "-lhiredis"}, {"leveldb", "-lleveldb"}, {"lmdb", "-llmdb"},
            {"rocksdb", "-lrocksdb"},

            {"SDL2", "-lSDL2"}, {"SDL2_image", "-lSDL2_image"}, {"SDL2_mixer", "-lSDL2_mixer"},
            {"SDL2_ttf", "-lSDL2_ttf"}, {"opengl", "-lGL -lGLU -lglut"}, {"GL", "-lGL"},
            {"GLU", "-lGLU"}, {"glut", "-lglut"}, {"glfw3", "-lglfw3"}, {"glew", "-lGLEW"},
            {"vulkan", "-lvulkan"}, {"X11", "-lX11"}, {"Xext", "-lXext"}, {"xcb", "-lxcb"},
            {"cairo", "-lcairo"}, {"pango", "`pkg-config --libs pango`"},
            {"gtk3", "`pkg-config --cflags --libs gtk+-3.0`"},
            {"gtk4", "`pkg-config --cflags --libs gtk4`"},
            {"glib", "`pkg-config --cflags --libs glib-2.0`"},
            {"qt5", "`pkg-config --cflags --libs Qt5Core Qt5Widgets`"},

            {"alsa", "-lasound"}, {"portaudio", "-lportaudio"}, {"ao", "-lao"},
            {"sndfile", "-lsndfile"}, {"mpg123", "-lmpg123"}, {"vorbis", "-lvorbis -logg"},
            {"opus", "-lopus"},

            {"libpng", "-lpng"}, {"png", "-lpng"}, {"libjpeg", "-ljpeg"}, {"jpeg", "-ljpeg"},
            {"tiff", "-ltiff"}, {"webp", "-lwebp"},
            {"opencv", "`pkg-config --cflags --libs opencv4`"},
            {"Magick++", "`Magick++-config --cppflags --libs`"},

            {"zlib", "-lz"}, {"bz2", "-lbz2"}, {"lzma", "-llzma"}, {"zstd", "-lzstd"},
            {"lz4", "-llz4"}, {"snappy", "-lsnappy"}, {"archive", "-larchive"},

            {"xml2", "`xml2-config --cflags --libs`"}, {"json-c", "-ljson-c"},
            {"jansson", "-ljansson"}, {"yaml", "-lyaml"}, {"toml", "-ltoml"},
            {"pcre", "-lpcre"}, {"pcre2", "-lpcre2-8"}, {"readline", "-lreadline"},
            {"ncurses", "-lncurses"}, {"panel", "-lpanel -lncurses"},

            {"gcrypt", "-lgcrypt"}, {"gpgme", "-lgpgme"}, {"argon2", "-largon2"},
            {"sodium", "-lsodium"}, {"gnutls", "-lgnutls"},

            {"gsl", "-lgsl -lgslcblas -lm"}, {"fftw3", "-lfftw3"}, {"blas", "-lblas"},
            {"lapack", "-llapack -lblas"}, {"gmp", "-lgmp"}, {"mpfr", "-lmpfr"},

            {"uuid", "-luuid"}, {"cap", "-lcap"}, {"acl", "-lacl"}, {"fuse", "-lfuse"},
            {"iconv", "-liconv"}, {"intl", "-lintl"},
            {"dbus", "`pkg-config --cflags --libs dbus-1`"}, {"systemd", "-lsystemd"},
            {"udev", "-ludev"}, {"bluetooth", "-lbluetooth"},
            {"gio", "`pkg-config --cflags --libs gio-2.0`"},

            {"boost_system", "-lboost_system"}, {"boost_filesystem", "-lboost_filesystem"},
            {"boost_thread", "-lboost_thread"}, {"boost_regex", "-lboost_regex"},
            {"boost_serialization", "-lboost_serialization"},
            {"boost_program_options", "-lboost_program_options"},
        };
    }

    // nullptr qaytarir, tapilmasa
    const std::string* find(const std::string& lib) const {
        auto it = flags.find(lib);
        return it == flags.end() ? nullptr : &it->second;
    }
};

// ---------- Kitabxana yoxlayici ----------
class LibraryChecker {
    bool hasPkgConfig;

public:
    explicit LibraryChecker(bool pkgConfig) : hasPkgConfig(pkgConfig) {}

    bool check(const std::string& lib, const std::string& flag) const {
        if (flag.find("pkg-config") != std::string::npos) {
            if (!hasPkgConfig) return true;  // yoxlaya bilmirik, kecirik
            return std::system(("pkg-config --exists " + lib + NULL_OUT).c_str()) == 0;
        }

        const std::string src = "__test__.cpp", exe = "__test__";
        {
            std::ofstream f(src);
            f << "#include <" << lib << ".h>\nint main() { return 0; }\n";
        }
        int code = std::system(("g++ " + src + " " + flag + " -o " + exe + NULL_OUT).c_str());

        std::remove(src.c_str());
        std::remove(exe.c_str());
        std::remove((exe + ".exe").c_str());
        return code == 0;
    }
};

// ---------- Kompilyator ----------
class Compiler {
    std::string source, exeName, command;

public:
    explicit Compiler(const std::string& src) : source(src) {
#ifdef _WIN32
        exeName = stripExtension(src) + ".exe";
#else
        exeName = stripExtension(src);
#endif
        command = "g++ " + source + " -o " + exeName + " ";
    }

    const std::string& getCommand() const { return command; }
    void addFlag(const std::string& flag) { command += flag + " "; }

    bool compile() const { return std::system(command.c_str()) == 0; }

    void run() const {
#ifdef _WIN32
        std::system(exeName.c_str());
#else
        std::system(("./" + exeName).c_str());
#endif
    }
};

// ---------- Bir kompilyasiya qeydi ----------
class CompileRecord {
    std::string file;
    std::string command;
    bool success;
    std::string time;

public:
    CompileRecord(const std::string& f, const std::string& cmd, bool ok_, const std::string& t)
        : file(f), command(cmd), success(ok_), time(t) {}

    const std::string& getFile() const { return file; }
    const std::string& getCommand() const { return command; }
    bool isSuccess() const { return success; }
    const std::string& getTime() const { return time; }

    // fayla yazmaq ucun bir setir: fayl <TAB> komut <TAB> 1/0 <TAB> vaxt
    std::string toLine() const {
        return file + "\t" + command + "\t" + (success ? "1" : "0") + "\t" + time;
    }

    static CompileRecord fromLine(const std::string& line) {
        std::vector<std::string> p = split(line, '\t');
        if (p.size() != 4) throw std::runtime_error("Xarab setir: " + line);
        return CompileRecord(p[0], p[1], p[2] == "1", p[3]);
    }
};

// ---------- Tarixce (vector + stack + fayl I/O) ----------
class HistoryManager {
    std::vector<CompileRecord> records;
    std::stack<CompileRecord> removed;  // silinenleri saxlayir (redo ucun)
    std::string path;

public:
    explicit HistoryManager(const std::string& filePath) : path(filePath) {}

    // Proqram acilanda faylden oxu
    void load() {
        std::ifstream in(path);
        if (!in) return;  // fayl hele yoxdur, problem deyil
        std::string line;
        int bad = 0;
        while (std::getline(in, line)) {
            if (trim(line).empty()) continue;
            try {
                records.push_back(CompileRecord::fromLine(line));
            } catch (const std::runtime_error&) {
                ++bad;
            }
        }
        if (bad > 0) xeberdar(std::to_string(bad) + " xarab setir kecildi");
    }

    void save() const {
        std::ofstream out(path);
        if (!out) throw std::runtime_error("Tarixce fayli yazila bilmedi: " + path);
        for (const CompileRecord& r : records) out << r.toLine() << "\n";
    }

    void add(const CompileRecord& r) { records.push_back(r); }

    // Axtarisda ucuncu terefden gelen netice: pointer, tapilmasa nullptr
    const CompileRecord* findByFile(const std::string& part) const {
        for (size_t i = records.size(); i > 0; --i)
            if (records[i - 1].getFile().find(part) != std::string::npos)
                return &records[i - 1];
        return nullptr;
    }

    bool removeLast() {
        if (records.empty()) return false;
        removed.push(records.back());
        records.pop_back();
        return true;
    }

    bool restoreLast() {
        if (removed.empty()) return false;
        records.push_back(removed.top());
        removed.pop();
        return true;
    }

    size_t size() const { return records.size(); }
    size_t removedCount() const { return removed.size(); }

    void show() const {
        baslig("Tarixce (" + std::to_string(records.size()) + " qeyd)");
        if (records.empty()) {
            xeberdar("Tarixce bosdur");
            return;
        }
        for (size_t i = 0; i < records.size(); ++i) {
            const CompileRecord& r = records[i];
            std::cout << " " << (i + 1) << ". " << r.getTime() << "  " << r.getFile() << "  ";
            std::cout << (r.isSuccess() ? Color::GREEN + "OK" : Color::RED + "XETA")
                      << Color::RESET << "\n";
        }
    }
};

// ---------- Bir fayli emal et ----------
// Fayl acila bilmezse istisna atir. runAfter=true olarsa, ugurlu kompilyasiyadan sonra isledir.
CompileRecord processFile(const std::string& path, bool runAfter,
                          const FlagDatabase& db, const LibraryChecker& checker) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Fayl acila bilmedi: " + path);

    Compiler compiler(path);

    baslig("Kitabxana yoxlanmasi");
    std::string line;
    while (std::getline(file, line)) {
        if (trim(line).empty()) continue;
        if (trim(line)[0] != '#') break;  // include hissesi bitdi

        std::string lib = extractLibName(line);
        if (lib.empty()) continue;

        const std::string* flag = db.find(lib);
        if (!flag) continue;  // standart basliq (iostream, vector ve s.)

        if (checker.check(lib, *flag)) {
            ok(lib + " tapildi");
            compiler.addFlag(*flag);
        } else {
            xeta(lib + " yuklu deyil! Yukle: pacman -S mingw-w64-x86_64-" + lib);
        }
    }
    file.close();

    baslig("Komut");
    std::cout << Color::YELLOW << compiler.getCommand() << Color::RESET << "\n";

    baslig("Kompilasiya");
    bool success = compiler.compile();
    if (success) {
        ok("Kompilasiya ugurlu oldu!");
        if (runAfter) {
            baslig("Proqram cixisi");
            std::cout.flush();
            compiler.run();
        }
    } else {
        xeta("Kompilasiya ugursuz oldu!");
    }
    return CompileRecord(path, compiler.getCommand(), success, currentTime());
}

// ---------- Menyu ----------
const char* MENU_ITEMS[] = {
    "Fayli kompilyasiya et ve isle",
    "Novbeye fayl elave et",
    "Novbedekileri kompilyasiya et (toplu)",
    "Tarixceni goster",
    "Tarixcede fayl axtar",
    "Son qeydi sil (undo)",
    "Silineni geri qaytar (redo)",
    "Cixis"};
const int MENU_SIZE = sizeof(MENU_ITEMS) / sizeof(MENU_ITEMS[0]);

void printMenu(size_t queueSize, size_t historySize) {
    baslig("MENYU");
    for (int i = 0; i < MENU_SIZE; ++i)
        std::cout << " " << (i + 1) << ". " << MENU_ITEMS[i] << "\n";
    std::cout << Color::YELLOW << " [novbede: " << queueSize << ", tarixce: " << historySize
              << "]" << Color::RESET << "\n";
}

std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::cout.flush();
    std::string s;
    std::getline(std::cin, s);
    return trim(s);
}

// Reqem deyilse std::invalid_argument atir
int readChoice() {
    std::string s = readLine("Secim: ");
    size_t pos = 0;
    int n = std::stoi(s, &pos);  // reqem deyilse istisna atir
    if (pos != s.size()) throw std::invalid_argument("Secim reqem olmalidir");
    return n;
}

void runMenu(HistoryManager& history, const FlagDatabase& db, const LibraryChecker& checker) {
    std::queue<std::string> batchQueue;  // toplu kompilyasiya novbesi
    bool running = true;

    while (running) {
        printMenu(batchQueue.size(), history.size());
        try {
            int choice = readChoice();
            switch (choice) {
                case 1: {
                    std::string path = readLine("Fayl adi: ");
                    history.add(processFile(path, true, db, checker));
                    history.save();
                    break;
                }
                case 2: {
                    std::string path = readLine("Novbeye elave edilecek fayl: ");
                    if (path.empty()) throw std::invalid_argument("Fayl adi bosdur");
                    batchQueue.push(path);
                    ok(path + " novbeye elave olundu");
                    break;
                }
                case 3: {
                    if (batchQueue.empty()) {
                        xeberdar("Novbe bosdur");
                        break;
                    }
                    while (!batchQueue.empty()) {
                        std::string path = batchQueue.front();
                        batchQueue.pop();
                        try {
                            history.add(processFile(path, false, db, checker));
                        } catch (const std::runtime_error& e) {
                            xeta(e.what());  // bir fayl xeta verse, digerleri davam etsin
                        }
                    }
                    history.save();
                    break;
                }
                case 4:
                    history.show();
                    break;
                case 5: {
                    std::string part = readLine("Axtaris sozu: ");
                    const CompileRecord* r = history.findByFile(part);
                    if (r == nullptr)
                        xeberdar("Tapilmadi");
                    else
                        ok(r->getFile() + "  " + r->getTime() + "  " + (r->isSuccess() ? "OK" : "XETA"));
                    break;
                }
                case 6:
                    if (history.removeLast()) {
                        history.save();
                        ok("Son qeyd silindi (geri qaytarmaq olar)");
                    } else {
                        xeberdar("Silinecek qeyd yoxdur");
                    }
                    break;
                case 7:
                    if (history.restoreLast()) {
                        history.save();
                        ok("Qeyd geri qaytarildi");
                    } else {
                        xeberdar("Geri qaytarilacaq qeyd yoxdur");
                    }
                    break;
                case 8:
                    running = false;
                    break;
                default:
                    xeta("1-" + std::to_string(MENU_SIZE) + " araliginda secin");
            }
        } catch (const std::logic_error&) {  // invalid_argument, out_of_range
            if (!std::cin) break;            // giris bitdi (Ctrl+D)
            xeta("Yanlis giris! Reqem daxil edin.");
        } catch (const std::exception& e) {
            xeta(e.what());
        }
    }
}

// ---------- Esas ----------
void enableColors() {
#ifdef _WIN32
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(h, &mode)) SetConsoleMode(h, mode | 0x0004);  // VT processing
#endif
}

int main(int argc, char* argv[]) {
    enableColors();
    std::cout << "\n";

    if (!commandExists("g++")) {
        xeta("g++ tapilmadi! Yukle: https://mingw-w64.org");
        return 1;
    }
    ok("g++ tapildi");

    bool hasPkgConfig = commandExists("pkg-config");
    if (!hasPkgConfig)
        xeberdar("pkg-config tapilmadi, bezi kitabxanalar yoxlanilmayacaq");

    FlagDatabase db;
    LibraryChecker checker(hasPkgConfig);
    HistoryManager history(HISTORY_FILE);
    history.load();

    try {
        if (argc >= 2) {
            // Tek fayl rejimi (kohne davranis)
            history.add(processFile(argv[1], true, db, checker));
            history.save();
        } else {
            runMenu(history, db, checker);
            ok("Gorusmek uzre!");
        }
    } catch (const std::exception& e) {
        xeta(e.what());
        return 1;
    }
    return 0;
}
