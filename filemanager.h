#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>
#include "library.h"

using namespace std;

class FileManager {
private:
    string booksFileName;
    string usersFileName;

public:
    FileManager(const string& booksFile = "books.txt",
                const string& usersFile = "users.txt");

    bool saveLibraryData(Library& library);
    bool loadLibraryData(Library& library);

    bool saveBooksToFile(Library& library);
    bool saveUsersToFile(Library& library);
    bool loadBooksFromFile(Library& library);
    bool loadUsersFromFile(Library& library);

    bool fileExists(const string& filename);
    void createBackup();
};

#endif