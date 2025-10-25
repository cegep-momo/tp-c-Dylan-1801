#include <sstream>
#include "book.h"

Book::Book() : title(""), author(""), isbn(""), isAvailable(true), borrowerName("") {}

Book::Book(const string& t, const string& a, const string& i)
    : title(t), author(a), isbn(i), isAvailable(true), borrowerName("") {}

string Book::getTitle() const { return title; }
string Book::getAuthor() const { return author; }
string Book::getISBN() const { return isbn; }
bool   Book::getAvailability() const { return isAvailable; }
string Book::getBorrowerName() const { return borrowerName; }

void Book::setTitle(const string& v){ title=v; }
void Book::setAuthor(const string& v){ author=v; }
void Book::setISBN(const string& v){ isbn=v; }
void Book::setAvailability(bool v){ isAvailable=v; }
void Book::setBorrowerName(const string& v){ borrowerName=v; }

void Book::checkOut(const string& borrower){
    isAvailable = false;
    borrowerName = borrower;
}

void Book::returnBook(){
    isAvailable = true;
    borrowerName.clear();
}
// Représentation textuelle du livre
string Book::toString() const{
    ostringstream os;
    os << "Titre: "  << title
       << " | Auteur: " << author
       << " | ISBN: "   << isbn
       << " | État: "   << (isAvailable ? "Disponible"
                                        : ("Emprunté par " + borrowerName));
    return os.str();
}

string Book::toFileFormat() const {
    // title|author|isbn|isAvailable|borrowerName
    ostringstream os;
    os << title << '|' << author << '|' << isbn << '|' << (isAvailable?1:0) << '|' << borrowerName;
    return os.str();
}
// format pour le book:
void Book::fromFileFormat(const string& line){
    string av;
    stringstream ss(line);
    getline(ss, title,  '|');
    getline(ss, author, '|');
    getline(ss, isbn,   '|');
    getline(ss, av,     '|');
    isAvailable = (av == "1");
    getline(ss, borrowerName, '|');
    if (isAvailable) borrowerName.clear();
}