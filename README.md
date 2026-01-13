# 📚 LibraSys - Library Management System

Console-based **Library Management System** written in **C++** with file-based persistence.  
Perfect for learning OOP, file I/O, date handling, basic authentication, and simple CRUD operations in C++.

## ✨ Features

### Admin Capabilities
- Add / Remove members
- Add / Remove books
- Issue books to members
- Collect returned books
- View all members
- Search books
- Automatic due date checking & fine calculation (₹50/day overdue)

### Member Capabilities
- View all available books
- Check personal issued books + dues / overdue status

### General
- Persistent storage using plain text files
- Username + password login for both admin & members
- 30-day automatic due date calculation
- First-run admin setup wizard
- Clean, colorful console interface

## 🛠️ Tech Stack

- **Language**: C++ (C++11 or later)
- **Libraries**: Standard Library only (no external dependencies)
- **Storage**: Plain text files (.txt)
- **Date handling**: `<chrono>`, `<ctime>`

## 📁 Project Structure
All source files are in the src directory:
All header files are in the header directory:

- `main.cpp`                    – Program entry point
- `Library.h` / `Library.cpp`   – Core library logic & menus
- `Admin.h`   / `Admin.cpp`     – Admin user & menu
- `Member.h`  / `Member.cpp`    – Member user & menu
- `User.h`    / `User.cpp`      – Base user class (username/password)
- `Book.h`    / `Book.cpp`      – Book entity
- `IssuedBook.h` / `IssuedBook.cpp` – Issued book record
- `Date.h`    / `Date.cpp`      – Date utilities & due date logic
- `global.h`  / `global.cpp`    – Helper functions (first-run check, etc.)

Data files (automatically created when the program runs):

- `admin_info.txt`
- `members.txt`
- `books.txt`
- `issued_books.txt`


### ALL FILES IN HEADERS AND SRC SHOULD BE IN THE SAME FOLDER FOR WORKING / YOU MAY GIVE THEIR PATHS IF NOT
### 1. Clone the repository
### 2. Place all the files in one folder
### 3. You may either run by command by giving paths of all .cpp files or by writing .cpp files in main.cpp and then simply run


🎮 How to Use

Main Menu
1 → Admin Login
2 → Member Login
3 → Exit

Admin Menu (after login)
Add/remove books & members
Issue & collect books
View members, search books, check dues

Member Menu
View all books
Check my issued books & fines


⚙️ Data Files (auto-created)
FileContentadmin_info.txtAdmin username:passwordmembers.txtAll members (username:password)books.txtBook inventoryissued_books.txtCurrently issued books

📌 Important Notes

First run requires admin setup → restart after creating admin
Passwords are stored in plain text (for educational purposes only)
Fine = 50 units per overdue day
Due period = 30 days from issue date
No input sanitization for special characters yet (keep usernames simple)

🔮 Future Improvements (ideas welcome!)

Feel free to use, modify, and learn from this project!


Happy coding! 🚀
