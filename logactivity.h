#ifndef LOGACTIVITY_H
#define LOGACTIVITY_H

#include <string>

// Appends a single log line with an ISO-like timestamp to data/activity.log.
// The function will create the data/ folder if needed.
void logActivity(const std::string& line);

// Convenience helpers:
void logAddBook(const std::string& title, const std::string& author, const std::string& isbn);
void logDeleteBook(const std::string& isbn);
void logBorrow(const std::string& isbn, const std::string& userId, const std::string& userName);
void logReturn(const std::string& isbn);
void logAddUser(const std::string& userId, const std::string& userName);

#endif
