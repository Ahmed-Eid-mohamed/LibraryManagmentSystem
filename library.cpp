#include "library.h"

mt19937 gen(random_device{}());

string library::InputValidator::ReadString()
{
    string input;
    while (true) {
        getline(cin, input);

        // Check if the input is valid
        bool isValid = true;
        for (char ch : input) {
            if (!isalpha(ch) && ch != ' ') {
                isValid = false;
                break;
            }
        }

        if (isValid && !input.empty()) {
            return input; // Valid input, return it
        }
        cout << "Invalid input, please re-enter again (only letters and spaces) : ";
    }
}

int library::InputValidator::ReadInteger()
{
    string input;
    int number;
    while (getline(cin, input)) {
        stringstream ss(input);
        if (ss >> number && ss.eof() && number > 0 && number < 1000000) 
            return number;
        cout << "Invalid input, please re-enter again : ";
    }
    return -1; // should never reach here
}

library::book::book() : book("", 0, 0, 0, {})
{
}
library::book::book(const string &bookName, int bookId, int borrowedCount, int totalCopies, const set<string>& borrowersList) : bookName(bookName), bookId(bookId), borrowedCount(borrowedCount), totalCopies(totalCopies), borrowersList(borrowersList)
{
}
void library::book::loadBookInfo()
{
    cout << "Enter book name : ";
    bookName = library::InputValidator::ReadString();
    cout << "Enter book quantity : ";
    totalCopies = library::InputValidator::ReadInteger();
}
void library::book::displayBookInfo() const
{
    cout << "Name ( " << bookName << " ) , Id ( " << bookId << " ) , Total Copies ( " << totalCopies << " ) , Borrowed Count ( " << borrowedCount << " )." << endl;
}
bool library::book::borrow(const string& userName)
{
    auto userIt = borrowersList.find(userName);
    if (userIt != borrowersList.end()){
        cout << "This user already borrowed this book." << endl;
        return false;
    }
    else if (borrowedCount == totalCopies){
        cout << "All copies of this book are already borrowed!" << endl;
        return false;
    }
    else {
        borrowersList.insert(userName);
        borrowedCount++;
        return true;
    }
}
bool library::book::returnBorrowedBook(const string& userName)
{
    auto userIt = borrowersList.find(userName);
    if (userIt != borrowersList.end()){
        borrowersList.erase(userIt);
        borrowedCount--;
        return true;
    }
    else {
        cout << userName << "does not borrowed this book ( " << bookName << " )." << endl;
        return false;
    }
}
void library::book::displayBorrowers() const
{
    if (borrowersList.empty()){
        cout << "No one borrowed this book." << endl;
    }
    else {
        for (auto& borrower : borrowersList)
            cout << borrower << endl;
    }
}
int library::book::getId() const
{
    return bookId;
}
int library::book::getTotalCopies() const
{
    return totalCopies;
}
int library::book::getBorrowedCount() const
{
    return borrowedCount;
}
const string& library::book::getName() const
{
    return bookName;
}
const set<string>& library::book::getBorrowers() const
{
    return borrowersList;
}
void library::book::setId(int newId)
{
    bookId = newId;
}
void library::book::setTotalCopies(int newCopies)
{
    totalCopies = newCopies;
}
void library::book::setBorrowedCount(int newCount)
{
    borrowedCount = newCount;
}

library::user::user() : user("", 0, {})
{
}
library::user::user(const string& userName, int userId, const set<string>& booksBorrowedList) : userName(userName), userId(userId), booksBorrowedList(booksBorrowedList)
{
}
void library::user::loadUserInfo()
{
    cout << "Enter user name : ";
    userName = library::InputValidator::ReadString();
}
void library::user::displayUserInfo() const
{
    cout << "User ( " << userName << " ) , Id ( " << userId << " ), Borrowed Books : ";
    if (booksBorrowedList.empty())
        cout << "No books borrowed.";
    bool check = false;
    for (auto& Book : booksBorrowedList)
    {
        if (check)
            cout << ", ";
        cout << Book;
        check = true;
    }
    cout << endl;
}
void library::user::borrowBook(const string& bookName)
{
    booksBorrowedList.insert(bookName);
}
void library::user::returnBorrowedBook(const string& bookName)
{
    auto bookIt = booksBorrowedList.find(bookName);
    if (bookIt == booksBorrowedList.end()){
        cout << "User " << userName << " did not borrow " << bookName << "!" << endl;
    }
    else {
        booksBorrowedList.erase(bookIt);
    }
}
const set<string>& library::user::getBooksBorrowedList() const
{
    return booksBorrowedList;
}
int library::user::getId() const
{
    return userId;
}
const string& library::user::getName() const
{
    return userName;
}
void library::user::setId(int newId)
{
    userId = newId;
}

library::library() : totalBooks(0), totalUsers(0)
{
}
int library::generateUniqueId() const
{
    uniform_int_distribution<> distr(1, 1000000);
    int randomNumber = distr(gen);
    return randomNumber;
}
void library::run()
{
    loadLibraryData();
    int choice;
    cout << "Library Menu: " << endl;
    cout << "1) add book" << endl
         << "2) search book by prefix" << endl
         << "3) print who borrowed book by name" << endl
         << "4) print library by id" << endl
         << "5) print library by name" << endl
         << "6) add user" << endl
         << "7) user borrow book" << endl
         << "8) user return book" << endl
         << "9) print users" << endl
         << "10) Exit" << endl;
    while (1)
    {
        cout << "Enter your menu choice [1:10] : ";
        choice = library::InputValidator::ReadInteger();
        if (choice == 1)
        {
            addBook();
        }
        else if (choice == 2)
        {
            cout << "Enter book name prefix : ";
            const string &bookName = library::InputValidator::ReadString();
            searchBookByPrefix(bookName);
        }
        else if (choice == 3)
        {
            cout << "Enter book name : ";
            const string &bookName = library::InputValidator::ReadString();
            displayBorrowersByBook(bookName);
        }
        else if (choice == 4)
        {
            displayLibraryById();
        }
        else if (choice == 5)
        {
            displayLibraryByName();
        }
        else if (choice == 6)
        {
            addUser();
        }
        else if (choice == 7)
        {
            cout << "Enter user name : ";
            const string &userName = library::InputValidator::ReadString();
            cout << "Enter book name : ";
            const string &bookName = library::InputValidator::ReadString();
            borrowBookForUser(userName, bookName);
        }
        else if (choice == 8)
        {
            cout << "Enter user name : ";
            const string &userName = library::InputValidator::ReadString();
            cout << "Enter book name : ";
            const string &bookName = library::InputValidator::ReadString();
            returnBookForUser(userName, bookName);
        }
        else if (choice == 9)
        {
            displayUsers();
        }
        else if (choice == 10)
        {
            saveLibraryData();
            break;
        }
        else
        {
            cout << "Enter a valid choice!." << endl;
        }
    }
}
void library::addBook()
{
    book book1;
    book1.loadBookInfo();
    const string& bookName = book1.getName();
    auto bookIndexIt = bookIndexes.find(bookName);
    if (bookIndexIt != bookIndexes.end())
    {
        int bookIndex = bookIndexIt->second;
        book& updateBook = booksList[bookIndex];
        int newCopies = updateBook.getTotalCopies() + book1.getTotalCopies();
        updateBook.setTotalCopies(newCopies);
    }
    else
    {
        do
        {
            int bookId = generateUniqueId();
            if (userBookIds.find(bookId) == userBookIds.end())
            {
                userBookIds.insert(bookId);
                book1.setId(bookId);
                break;
            }
        } while (true); // loop until find unique id
        booksList.push_back(book1);
        bookIndexes[book1.getName()] = totalBooks;
        totalBooks++;
    }
}
void library::addUser()
{
    user user1;
    user1.loadUserInfo();
    do
    {
        int userId = generateUniqueId();
        if (userBookIds.find(userId) == userBookIds.end())
        {
            userBookIds.insert(userId);
            user1.setId(userId);
            break;
        }
    } while (true); // loop untill find unique id
    usersList.push_back(user1);
    userIndexes[user1.getName()] = totalUsers;
    totalUsers++;
}
void library::searchBookByPrefix(const string& prefix) const
{
    int matchCount;
    bool isFound = false;
    for (auto &book : booksList)
    {
        matchCount = 0;
        const string& bookName = book.getName();
        for (int i = 0; i < min(prefix.size(), bookName.size()); i++)
        {
            if (bookName[i] == prefix[i])
            matchCount++;
        }
        if (matchCount == prefix.size())
        {
            cout << bookName << endl;
            isFound = true;
        }
    }
    if (isFound == false)
        cout << "No book found with the given prefix." << endl;
}
void library::displayBorrowersByBook(const string& bookName) const
{
    auto bookIndexIt = bookIndexes.find(bookName);
    if (bookIndexIt == bookIndexes.end())
        cout << "This book does not exist in the library!." << endl;
    else {
        int bookIndex = bookIndexIt->second;
        booksList[bookIndex].displayBorrowers();
    }
}
bool library::compareById(book& bookA, book& bookB)
{
    return bookA.getId() < bookB.getId();
}
bool library::compareByName(book& bookA, book& bookB)
{
    return bookA.getName() < bookB.getName();
}
void library::displayLibraryById()
{
    sort(booksList.begin(), booksList.end(), compareById);
    displayBooks();
    updateIndexes();
}
void library::displayLibraryByName()
{
    sort(booksList.begin(), booksList.end(), compareByName);
    displayBooks();
    updateIndexes();
}
void library::borrowBookForUser(const string& userName, const string& bookName)
{
    auto userIndexIt = userIndexes.find(userName);
    if (userIndexIt == userIndexes.end()){
        cout << "The user is not on the system." << endl;
        return;
    }
    auto bookIndexIt = bookIndexes.find(bookName);
    if (bookIndexIt == bookIndexes.end()){
        cout << "This book does not belong to the library." << endl;
        return;
    }

    int userIndex = userIndexIt->second;
    int bookIndex = bookIndexIt->second;

    bool checkSuccess = booksList[bookIndex].borrow(userName);
    if (checkSuccess == true){
        usersList[userIndex].borrowBook(bookName);
    }
}
void library::returnBookForUser(const string& userName, const string& bookName)
{
    auto userIndexIt = userIndexes.find(userName);
    if (userIndexIt == userIndexes.end()){
        cout << "The user is not on the system." << endl;
        return;
    }
    auto bookIndexIt = bookIndexes.find(bookName);
    if (bookIndexIt == bookIndexes.end()){
        cout << "The book does not belonge to the library." << endl;
        return;
    }

    int userIndex = userIndexIt->second;
    int bookIndex = bookIndexIt->second;

    bool checkSuccess = booksList[bookIndex].returnBorrowedBook(userName);
    if (checkSuccess == true){
        usersList[userIndex].returnBorrowedBook(bookName);
    }
}
void library::displayUsers() const
{
    for (int i = 0; i < totalUsers; i++)
    {
        usersList[i].displayUserInfo();
    }
    if (totalUsers == 0)
        cout << "No users yet." << endl;
}
void library::displayBooks() const
{
    for (int i = 0; i < totalBooks; i++)
    {
        booksList[i].displayBookInfo();
    }
    if (totalBooks == 0)
        cout << "No books yet." << endl;
}
int library::getTotalBooks() const
{
    return totalBooks;
}
int library::getTotalUsers() const
{
    return totalUsers;
}
void library::updateIndexes()
{
    for (int i = 0; i < totalBooks; i++)
        bookIndexes[booksList[i].getName()] = i;
}
void library::loadLibraryData()
{
    loadUserData();
    loadBookData();
}
void library::loadUserData()
{
    fstream usersFile("Users.txt", ios::in | ios::out | ios::app);
    string userName;
    string booksBorrowed;
    string line;
    int userId;
    while (getline(usersFile, line))
    {
        istringstream userInfo(line);
        userInfo >> userName >> userId >> booksBorrowed;

        userName = formatFromStorage(userName);
        
        set<string> booksBorrowedList;
        if (booksBorrowed != "noBooks") // No books borrowed
        {
            booksBorrowed = formatFromStorage2(booksBorrowed);
            string book;
            istringstream books(booksBorrowed);
            while (books >> book)
            {
                book = formatFromStorage(book);
                booksBorrowedList.insert(book);
            }
        }
        user user1(userName, userId, booksBorrowedList);
        userBookIds.insert(userId);
        userIndexes[userName] = totalUsers;
        usersList.push_back(user1);
        totalUsers++;
    }
    usersFile.close();
}
void library::loadBookData()
{
    fstream booksFile("Books.txt", ios::in | ios::out | ios::app);
    string bookName;
    string line;
    string borrowers;
    int bookId;
    int totalCopies;
    int borrowedCount;
    while (getline(booksFile, line))
    {
        istringstream bookInfo(line);
        bookInfo >> bookName >> bookId >> totalCopies >> borrowedCount >> borrowers;
        bookName = formatFromStorage(bookName);
        set<string> borrowersList;
        if (borrowers != "noBorrowers")
        {
            borrowers = formatFromStorage2(borrowers);
            string user;
            istringstream users(borrowers);
            while (users >> user)
            {
                user = formatFromStorage(user);
                borrowersList.insert(user);
            }
        }
        book book1(bookName, bookId, totalCopies, borrowedCount, borrowersList);
        userBookIds.insert(bookId);
        bookIndexes[bookName] = totalBooks;
        booksList.push_back(book1);
        totalBooks++;
    }
    booksFile.close();
}
void library::saveLibraryData()
{
    saveUserData();
    saveBookData();
}
void library::saveUserData()
{
    string newData = "";
    for (int i = 0; i < totalUsers; i++)
    {
        string userId = to_string(usersList[i].getId());
        string userName = usersList[i].getName();
        string booksBorrowed = "";
        userName = formatForStorage(userName);
        bool check = false;
        for (auto book : usersList[i].getBooksBorrowedList())
        {
            check = true;
            book = formatForStorage(book);
            booksBorrowed += book + " ";
        }
        if (check == true)
            booksBorrowed.pop_back(); // remove last space
        else
            booksBorrowed = "noBooks";
        booksBorrowed = formatForStorage2(booksBorrowed);
        newData += userName + " " + userId + " " + booksBorrowed + "\n";
    }
    ofstream usersFile("Users.txt", ios::trunc);
    usersFile << newData;
    usersFile.close();
}
void library::saveBookData()
{
    string newData = "";
    for (int i = 0; i < totalBooks; i++)
    {
        string bookId = to_string(booksList[i].getId());
        string totalCopies = to_string(booksList[i].getTotalCopies());
        string borrowedcount = to_string(booksList[i].getBorrowedCount());
        string bookName = booksList[i].getName();
        string borrowers = "";
        bookName = formatForStorage(bookName);
        bool check = false;
        for (auto user : booksList[i].getBorrowers())
        {
            check = true;
            user = formatForStorage(user);
            borrowers += user + " ";
        }
        if (check == true)
            borrowers.pop_back(); // remove last space
        else
            borrowers = "noBorrowers";
        borrowers = formatForStorage2(borrowers);
        newData += bookName + " " + bookId + " " + totalCopies + " " + borrowedcount + " " + borrowers + "\n";
    }
    ofstream booksFile("Books.txt", ios::trunc);
    booksFile << newData;
    booksFile.close();
}
string library::formatForStorage(const string& input) const
{
    string formatted = input;
    replace(formatted.begin(), formatted.end(), ' ', '-');
    return formatted;
}
string library::formatForStorage2(const string& input) const
{
    string formatted = input;
    replace(formatted.begin(), formatted.end(), ' ', '_');
    return formatted;
}
string library::formatFromStorage(const string& input) const
{
    string formatted = input;
    replace(formatted.begin(), formatted.end(), '-', ' ');
    return formatted;
}
string library::formatFromStorage2(const string& input) const
{
    string formatted = input;
    replace(formatted.begin(), formatted.end(), '_', ' ');
    return formatted;
}