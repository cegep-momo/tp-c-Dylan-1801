#ifndef LOGACTIVITY_H
#define LOGACTIVITY_H

#include <string>

// fonction générique de log d'activité
void logActivity(const std::string& line);

// fonctions spécifiques de log pour les différentes actions
void logAddBook(const std::string& title, const std::string& author, const std::string& isbn);
void logDeleteBook(const std::string& isbn);
void logBorrow(const std::string& isbn, const std::string& userId, const std::string& userName);
void logReturn(const std::string& isbn);
void logAddUser(const std::string& userId, const std::string& userName);

#endif
