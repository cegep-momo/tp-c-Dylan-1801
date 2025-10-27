#include <iostream>
#include <algorithm>

#include "library.h"

#include "logactivity.h"


using namespace std;

// Constructor
Library::Library() {}

// Add book to library
void Library::addBook(const Book& book) {
    books.push_back(make_unique<Book>(book));
    logAddBook(book.getTitle(), book.getAuthor(), book.getISBN());
}

// Remove book from library
bool Library::removeBook(const string& isbn) {
    auto it = find_if(books.begin(), books.end(),
        [&isbn](const unique_ptr<Book>& book) {
            return book->getISBN() == isbn;
        });
    
    if (it != books.end()) {
        std::string removedIsbn = (*it)->getISBN();
        books.erase(it);
        logDeleteBook(removedIsbn);  
        return true;
    }
    return false;
}

// Find book by ISBN
Book* Library::findBookByISBN(const string& isbn) {
    auto it = find_if(books.begin(), books.end(),
        [&isbn](const unique_ptr<Book>& book) {
            return book->getISBN() == isbn;
        });
    
    return (it != books.end()) ? it->get() : nullptr;
}

// Search books by title (case-insensitive partial match)
vector<Book*> Library::searchBooksByTitle(const string& title) {
    vector<Book*> results;
    string lowerTitle = title;
    transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);
    
    for (auto& book : books) {
        string bookTitle = book->getTitle();
        transform(bookTitle.begin(), bookTitle.end(), bookTitle.begin(), ::tolower);
        
        if (bookTitle.find(lowerTitle) != string::npos) {
            results.push_back(book.get());
        }
    }
    std::sort(results.begin(), results.end(), [](const Book* a, const Book* b){
    if (a->getTitle() == b->getTitle()) return a->getAuthor() < b->getAuthor();
    return a->getTitle() < b->getTitle();
});

    return results;
}

// Search books by author (case-insensitive partial match)
vector<Book*> Library::searchBooksByAuthor(const string& author) {
    vector<Book*> results;
    string lowerAuthor = author;
    transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);
    
    for (auto& book : books) {
        string bookAuthor = book->getAuthor();
        transform(bookAuthor.begin(), bookAuthor.end(), bookAuthor.begin(), ::tolower);
        
        if (bookAuthor.find(lowerAuthor) != string::npos) {
            results.push_back(book.get());
        }
    }
    std::sort(results.begin(), results.end(), [](const Book* a, const Book* b){
    if (a->getTitle() == b->getTitle()) return a->getAuthor() < b->getAuthor();
    return a->getTitle() < b->getTitle();
});

    return results;
}

// Get all available books
vector<Book*> Library::getAvailableBooks() {
    vector<Book*> available;
    for (auto& book : books) {
        if (book->getAvailability()) {
            available.push_back(book.get());
        }
    }
    return available;
}

// Get all books
vector<Book*> Library::getAllBooks() {
    vector<Book*> allBooks;
    for (auto& book : books) {
        allBooks.push_back(book.get());
    }
    return allBooks;
}

// Add user to library
void Library::addUser(const User& user) {
    users.push_back(make_unique<User>(user));
    logAddUser(user.getUserId(), user.getName());
}

// Find user by ID
User* Library::findUserById(const string& userId) {
    auto it = find_if(users.begin(), users.end(),
        [&userId](const unique_ptr<User>& user) {
            return user->getUserId() == userId;
        });
    
    return (it != users.end()) ? it->get() : nullptr;
}

// Get all users
vector<User*> Library::getAllUsers() {
    vector<User*> allUsers;
    for (auto& user : users) {
        allUsers.push_back(user.get());
    }
    return allUsers;
}

// Check out book
bool Library::checkOutBook(const string& isbn, const string& userId) {
    Book* book = findBookByISBN(isbn);
    User* user = findUserById(userId);
    
    if (book && user && book->getAvailability()) {
        book->checkOut(user->getName());
        user->borrowBook(isbn);
        logBorrow(isbn, user->getUserId(), user->getName());
        return true;
    }
    return false;
}

// Return book
bool Library::returnBook(const string& isbn) {
    Book* book = findBookByISBN(isbn);
    
    if (book && !book->getAvailability()) {
        // Find the user who borrowed this book
        for (auto& user : users) {
            if (user->hasBorrowedBook(isbn)) {
                user->returnBook(isbn);
                break;
            }
        }
        book->returnBook();
        logReturn(isbn);   
        return true;
    }
    return false;
}

// Display all books
void Library::displayAllBooks() {
    if (books.empty()) {
        cout << "Aucun livre dans la bibliothèque.\n";
        return;
    }

    // Construire les pointeurs vers les livres
    std::vector<const Book*> v;
    v.reserve(books.size());
    for (const auto& uptr : books) v.push_back(uptr.get());

    // Tri: titre asc + auteur asc
    std::sort(v.begin(), v.end(), [](const Book* a, const Book* b){
        if (a->getTitle() == b->getTitle()) return a->getAuthor() < b->getAuthor();
        return a->getTitle() < b->getTitle();
    });

    cout << "\n=== TOUS LES LIVRES (triés par titre, puis auteur) ===\n";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << v[i]->toString() << "\n";
        cout << "-------------------------\n";
    }
}


// Display available books
void Library::displayAvailableBooks() {
    // Collecter les livres disponibles
    std::vector<const Book*> v;
    v.reserve(books.size());
    for (const auto& uptr : books) {
        if (uptr->getAvailability()) v.push_back(uptr.get());
    }

    if (v.empty()) {
        cout << "Aucun livre disponible pour emprunt.\n";
        return;
    }

    // Tri: titre asc + auteur asc
    std::sort(v.begin(), v.end(), [](const Book* a, const Book* b){
        if (a->getTitle() == b->getTitle()) return a->getAuthor() < b->getAuthor();
        return a->getTitle() < b->getTitle();
    });

    cout << "\n=== LIVRES DISPONIBLES (triés par titre, puis auteur) ===\n";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << "\nLivre " << (i + 1) << " :\n";
        cout << v[i]->toString() << "\n";
        cout << "---------------------------\n";
    }
}


// Display all users
void Library::displayAllUsers() {
    if (users.empty()) {
        cout << "Aucun utilisateur enregistré.\n";
        return;
    }
    
    cout << "\n=== TOUS LES UTILISATEURS ===\n";
    for (size_t i = 0; i < users.size(); ++i) {
        cout << "\nUtilisateur " << (i + 1) << " :\n";
        cout << users[i]->toString() << "\n";
        cout << "------------------------------\n";
    }
}

// Statistics
int Library::getTotalBooks() const { return books.size(); }
int Library::getAvailableBookCount() const {
    return count_if(books.begin(), books.end(),
        [](const unique_ptr<Book>& book) {
            return book->getAvailability();
        });
}
int Library::getCheckedOutBookCount() const { return getTotalBooks() - getAvailableBookCount(); }

#include <cctype>
#include <sstream>

// fonctions utilitaires pour normaliser les chaînes
static std::string trim(const std::string& s) {
    size_t start = 0, end = s.size();
    while (start < end && std::isspace((unsigned char)s[start])) ++start;
    while (end > start && std::isspace((unsigned char)s[end - 1])) --end;
    return s.substr(start, end - start);
}

static std::string toLower(const std::string& s) {
    std::string res = s;
    std::transform(res.begin(), res.end(), res.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return res;
}

static std::string normalizeISBN(const std::string& isbn) {
    std::string res;
    for (char c : isbn)
        if (std::isdigit((unsigned char)c) || c == 'X' || c == 'x')
            res.push_back(c);
    return res;
}

// Vérifie si un livre existe déjà par ISBN ou par Titre + Auteur
bool Library::hasDuplicate(const std::string& title,
                           const std::string& author,
                           const std::string& isbn) const {
    std::string tNorm = toLower(trim(title));
    std::string aNorm = toLower(trim(author));
    std::string iNorm = normalizeISBN(isbn);

    for (const auto& b : books) {
        const std::string bt = toLower(trim(b->getTitle()));
        const std::string ba = toLower(trim(b->getAuthor()));
        const std::string bi = normalizeISBN(b->getISBN());

        // Doublon si meme ISBN, ou si même Titre + Auteur
        if (bi == iNorm || (bt == tNorm && ba == aNorm)) {
            return true;
        }
    }
    return false;
}
