#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "bits/stdc++.h"

using namespace std;

class library
{
private:
    class book
    {
    private:
        string bookName;
        int bookId;
        int totalCopies; 
        int borrowedCount;
        set<string> borrowersList;

    public:
        book();
        book(const string &bookName, int bookId, int borrowedCount, int totalCopies, const set<string>& borrowersList);
        void loadBookInfo();
        void displayBookInfo() const;
        bool borrow(const string &userName);
        bool returnBorrowedBook(const string &userName);
        void displayBorrowers() const;
        int getId() const;
        int getTotalCopies() const;
        int getBorrowedCount() const;
        const string& getName() const;
        const set<string>& getBorrowers() const;
        void setId(int newId);
        void setTotalCopies(int newCopies);
        void setBorrowedCount(int newCount);
    };

    class user
    {
    private:
        int userId;
        string userName;
        set<string> booksBorrowedList;

    public:
        user();
        user(const string& userName, int userId, const set<string>& booksBorrowedList);
        void loadUserInfo();
        void displayUserInfo() const;
        void borrowBook(const string& bookName);
        void returnBorrowedBook(const string& bookName);
        const set<string>& getBooksBorrowedList() const;
        int getId() const;
        const string& getName() const;
        void setId(int newId);
    };
    
    class InputValidator{
    public:
        static string ReadString();
        static int ReadInteger();
    };

    int totalBooks;
    int totalUsers;
    set<int> userBookIds;
    vector<user> usersList;
    vector<book> booksList;
    unordered_map<string, int> userIndexes;
    unordered_map<string, int> bookIndexes;
    int generateUniqueId() const;
    void addBook();
    void addUser();
    void searchBookByPrefix(const string& prefix) const; 
    void displayBorrowersByBook(const string& bookName) const;
    static bool compareById(book &bookA, book &bookB);
    static bool compareByName(book &bookA, book &bookB);
    void displayLibraryById();
    void displayLibraryByName();
    void borrowBookForUser(const string& userName, const string& bookName);
    void returnBookForUser(const string& userName, const string& bookName);
    void displayUsers() const;
    void displayBooks() const;
    int getTotalBooks() const;
    int getTotalUsers() const;
    void updateIndexes();
    void loadLibraryData();
    void loadUserData();
    void loadBookData();
    void saveLibraryData();
    void saveUserData();
    void saveBookData();
    string formatForStorage(const string& input) const;
    string formatForStorage2(const string& input) const;
    string formatFromStorage(const string& input) const;
    string formatFromStorage2(const string& input) const;

public:
    library();
    void run();
};

#endif