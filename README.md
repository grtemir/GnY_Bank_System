# GnY Banking System

A modular, CLI-based banking application written in pure C. Built to handle account operations, balance updates, and transaction logs without relying on external database engines or third-party cryptography libraries.

---

## What It Does

* **SHA-256 Authentication:** Passwords are never stored in plain text. Hashing is handled directly by an in-house SHA-256 implementation.
* **Safe File Writes (`temp.txt`):** Balance modifications and transfers don't write directly to the live database file. Instead, updates pass through a temporary staging file before replacing the original, preventing corrupted records if an operation fails mid-way[cite: 8].
* **Audit Logging:** Every critical action (sign-ups, authentication attempts, deposits, transfers) gets written to `logs.txt` with a system timestamp.
* **Clean Terminal I/O:** String buffers are capped (`%29s`) to prevent overflows, and input streams are flushed to keep menus from looping infinitely on bad inputs.

---

## Data Flow: How Balances Update Safely

```text
[User Transfer / Withdraw]
            │
            ▼
   Read "accounts.txt" ──► Match target account ID
                                   │
                           Recalculate balance
                                   │
                                   ▼
                            Write to "temp.txt"
                                   │
       Delete "accounts.txt" ◄─────┴── fclose() both files
                 │
                 ▼
       Rename "temp.txt" ──► "accounts.txt" (Atomic swap)

```


## File Structure
```
├── CMakeLists.txt        # Build instructions
├── main.c                # Program entry point
├── headers.h             # Struct definitions and core function prototypes
├── admin_info.h          # Admin credentials & SHA-256 hash configuration
├── account_function.c    # User registration, login, transfers, and logging
├── admin_functions.c     # Admin panel, account batch adding, and log viewing
├── function.c            # Menus and input handling
└── hash.c / hash.h       # Standalone SHA-256 hashing engine

```
## File Format Of "accounts.txt"

```text
ID:NAME:SHA256_PASSWORD_HASH:BALANCE
1001:John:ef92b778bafe771e89245b89ecbc08a44a4e166c06659911881f383d4473e94f:1500.50
```

## File Format Of "logs.txt"

```text
[2026-09-03 14:15:00] ID: 1001 -- Action: LOGIN_SUCCESS
[2026-09-03 14:16:30] ID: 1001 -- Action: TRANSFER_SEND -- Amount: 250.00
```

## Built And Run

```text
# Configure and build
cmake -B build
cmake --build build

# Run (Linux / macOS)
./build/untitled

# Run (Windows)
.\build\untitled.exe
```
## Admin Infos
```text
Admin ID: Admin123
Admin Password: 11223344
```