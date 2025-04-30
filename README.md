# 💸 Expense Splitter App (C++ Console)

This is a C++ console application that helps users manage shared expenses between friends and within groups. It supports user login/signup with secure password hashing (using SHA-256 via [PicoSHA2](https://github.com/okdshin/PicoSHA2)), friend management, group creation, activity logging, and spending history.

---

## 🚀 Features

- 🔐 **User Authentication**
  - Signup with password strength validation
  - Login with password verification using SHA-256 hashing

- 🧑‍🤝‍🧑 **Friend Management**
  - Add friends
  - View friends list

- 👥 **Group Management**
  - Create groups with friends
  - Add friends to groups

- 🧾 **Expense Tracking**
  - Log shared activities with individual friends or entire groups
  - Automatically splits the bill equally
  - Displays personal activity and spending history

---

## 🛠️ Tech Stack

- **Language**: C++
- **Hashing Library**: [PicoSHA2](https://github.com/okdshin/PicoSHA2) - single header SHA-256 library
- **OOP Concepts**: Classes, encapsulation, and file I/O (user persistence may require extension)

---

## 🗂️ File Structure

```text
project-root/
├── main.cpp         # Entry point: menu, I/O, control flow
├── classes.h        # Declarations: User, Group, Activity classes
├── picosha2.h       # SHA-256 hashing header (PicoSHA2)
└── README.md        # This file