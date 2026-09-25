# Vehicle / Transport Management System

A C-based modular console application designed to manage vehicles, drivers, trips, and summary reports with persistent binary file storage.

---

## 📌 Project Overview
The **Vehicle/Transport Management System** simplifies transport record management for small organizations, schools, or businesses. It replaces traditional paper registers and spreadsheet logs with an efficient, interactive terminal application built in C.

---

## 👥 Team Members & Responsibilities

| Member Name | Student ID | Primary File | Assigned Modules & Responsibilities |
| :--- | :--- | :--- | :--- |
| **Muhib Haider** | 26k-0592 | `member1_vehicle.c` | **Vehicle Module & UI Interface**: Main console loop, primary menu navigation, and Vehicle CRUD operations (Add, View, Search, Update, Delete, Check Availability). |
| **Muhammad Sarim** | 26k-0627 | `member2_driver.c` | **Driver Module & Input Validation**: Driver CRUD operations (Add, View, Search, Update, Delete, Assign Driver) and reusable safe input helper functions. |
| **Mustafa** | 26k-0628 | `member3_trip.c` | **Trip Management, Files & Reports**: Trip management (Create, View History), binary file handling (`vehicles.dat`, `drivers.dat`, `trips.dat`), and overall transport status summaries. |

---

## 🛠️ Key Features

* **Vehicle Management**: Add, search, update, delete, and check availability status of vehicles.
* **Driver Management**: Manage driver records and assign drivers to available vehicles.
* **Trip Management**: Record trip details (source, destination, date, status) and maintain trip history.
* **File Persistence**: Automatically load and save all records to binary files (`.dat`) upon startup and exit.
* **Summary Reports**: Generate instant overall system summaries.
* **Robust Input Validation**: Safe integer and text input handling to prevent console crashes or infinite loops.

---

## ⚙️ Exposed Functions Breakdown

### 1. Vehicle Module (`member1_vehicle.c`)
- `void vehicle_menu()`
- `void add_vehicle()`
- `void display_vehicles()`
- `int check_vehicle_exists(int id)`

### 2. Driver Module (`member2_driver.c`)
- `void driver_menu()`
- `void add_driver()`
- `void display_drivers()`
- `int get_valid_int(const char *prompt)` *(Reusable Helper)*

### 3. Trip & File Persistence Module (`member3_trip.c`)
- `void trip_menu()`
- `void create_trip()`
- `void view_trip_history()`
- `void save_all_data()` / `void load_all_data()`
- `void generate_summary_report()`

---

## 💻 Tech Stack & Tools

* **Programming Language**: C
* **Compiler**: GCC / Clang
* **Target OS**: Windows

---

## 🚀 How to Build and Run

1. **Clone the repository**:
   ```bash
   git clone <YOUR_REPOSITORY_LINK>
   cd <REPOSITORY_FOLDER>
