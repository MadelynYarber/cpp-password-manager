# C++ Password Manager 
This project implements a secure, menu-driven password manager in C++ using a custom templated hash table. Passwords are stored using one-way encryption (`crypt()`), and the system supports account management, file I/O, and more.

---
## Features
- Add/remove user accounts
- Secure password change (with verification)
- Find/check user existence
- Dump internal hash table
- Save/load data to file
- Templated hash table with prime-based rehashing

---
## Key Files
- **hashtable.hpp**: Templated hash table
- **passserver.cpp**: Account management
- **proj5.cpp**: CLI

---
## Build & Run

```bash
make
./proj5
