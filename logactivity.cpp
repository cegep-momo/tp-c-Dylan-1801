#include "logactivity.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>
#include <filesystem>

#ifndef DATA_DIR
#define DATA_DIR "data" // secours si CMake ne définit pas DATA_DIR
#endif

static std::string nowTimestamp() {
    using clock = std::chrono::system_clock;
    auto t = clock::to_time_t(clock::now());
    std::tm local{};
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    localtime_r(&t, &local);
#endif
    char buf[32];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &local);
    return std::string(buf);
}

void logActivity(const std::string& line) {
    try {
        std::filesystem::path dataDir = std::filesystem::path(DATA_DIR);
        std::filesystem::create_directories(dataDir);
        std::filesystem::path logPath = dataDir / "activity.log";
        std::ofstream out(logPath, std::ios::app);
        if (!out) {
            std::cerr << "Impossible d’ouvrir " << logPath << "\n";
            return;
        }
        out << "[" << nowTimestamp() << "] " << line << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Erreur log: " << e.what() << "\n";
    }
}

void logAddBook(const std::string& title, const std::string& author, const std::string& isbn) {
    logActivity("ADD_BOOK|isbn=" + isbn + "|title=" + title + "|author=" + author);
}
void logDeleteBook(const std::string& isbn) {
    logActivity("DEL_BOOK|isbn=" + isbn);
}
void logBorrow(const std::string& isbn, const std::string& userId, const std::string& userName) {
    logActivity("BORROW|isbn=" + isbn + "|userId=" + userId + "|user=" + userName);
}
void logReturn(const std::string& isbn) {
    logActivity("RETURN|isbn=" + isbn);
}
void logAddUser(const std::string& userId, const std::string& userName) {
    logActivity("ADD_USER|id=" + userId + "|name=" + userName);
}