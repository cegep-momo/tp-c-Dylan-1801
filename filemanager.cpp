#include <fstream>
#include <iostream>
#include <filesystem>
#include <sstream>
#include "filemanager.h"
#include "book.h"
#include "user.h"

using namespace std;
namespace fs = std::filesystem;


#ifdef DATA_DIR
static const fs::path kDataDir = fs::path(DATA_DIR);
#else

#warning "DATA_DIR not defined by CMake; falling back to ./data"
static const fs::path kDataDir = fs::path("./data");
#endif

static const fs::path kBooksPath = kDataDir / "books.txt";
static const fs::path kUsersPath = kDataDir / "users.txt";


// Constructor
FileManager::FileManager(const string& booksFile, const string& usersFile)
    : booksFileName(booksFile), usersFileName(usersFile) {}

// Save all library data
bool FileManager::saveLibraryData(Library& library) {
    return saveBooksToFile(library) && saveUsersToFile(library);
}

// Load all library data
bool FileManager::loadLibraryData(Library& library) {
    bool ok = true;
    ok = loadBooksFromFile(library) && ok;
    ok = loadUsersFromFile(library) && ok;
    return ok;
}
// Save books to file
bool FileManager::saveBooksToFile(Library& library) {
    fs::create_directories(kDataDir);
    ofstream out(kBooksPath, ios::trunc);
    if (!out) {
        cerr << "Erreur: Impossible d'ouvrir " << kBooksPath << " en écriture.\n";
        return false;
    }
    for (Book* b : library.getAllBooks()) {
        out << b->toFileFormat() << '\n';
    }
    return true;
}
// Load books from file
bool FileManager::loadBooksFromFile(Library& library) {
    if (!fs::exists(kBooksPath)) return true;
    ifstream in(kBooksPath);
    if (!in) {
        cerr << "Erreur: Impossible d'ouvrir " << kBooksPath << " en lecture.\n";
        return false;
    }
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        Book b;
        b.fromFileFormat(line);
        library.addBook(b);
    }
    return true;
}

// Save users to file
bool FileManager::saveUsersToFile(Library& library) {
    fs::create_directories(kDataDir);
    ofstream out(kUsersPath, ios::trunc);
    if (!out) {
        cerr << "Erreur: Impossible d'ouvrir " << kUsersPath << " en écriture.\n";
        return false;
    }
    for (User* u : library.getAllUsers()) {
        out << u->toFileFormat() << '\n';
    }
    return true;
}

// Load users from file
bool FileManager::loadUsersFromFile(Library& library) {
    if (!fs::exists(kUsersPath)) return true;
    ifstream in(kUsersPath);
    if (!in) {
        cerr << "Erreur: impossible d'ouvrir " << kUsersPath << " en lecture.\n";
        return false;
    }
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        User u;
        u.fromFileFormat(line);
        library.addUser(u);
    }
    return true;
}

// Check if file exists
bool FileManager::fileExists(const string& filename) {
    return fs::exists(kDataDir / filename);
}
// Create backup
void FileManager::createBackup() {
    fs::create_directories(kDataDir);
    if (fs::exists(kBooksPath)) {
        fs::copy_file(kBooksPath, kBooksPath.string() + ".backup",
                      fs::copy_options::overwrite_existing);
    }
    if (fs::exists(kUsersPath)) {
        fs::copy_file(kUsersPath, kUsersPath.string() + ".backup",
                      fs::copy_options::overwrite_existing);
    }
    cout << "Les fichiers de sauvegarde ont été créés dans " << kDataDir << "\n";
}
