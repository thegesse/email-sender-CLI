# CLI Email Sender (C + Supabase)

A lightweight, modular command-line interface (CLI) application built in vanilla C to manage an automated email queue. The system connects securely to a remote Supabase (PostgreSQL) backend via `libpq` to fetch pending messages, process emails, and log statuses.

---

## Project Architecture

The project is structured modularly to separate database connectivity, query execution, and core business logic (email handling).

```text
email-sender-CLI/
├── .env                           # Secret configuration profiles (ignored by Git)
├── main.c                         # Application entry point & orchestrator
├── main.o                         # Compiled object file for main
├── email_sender                   # Final compiled executable binary
├── Makefile                       # GNU Make build automation configuration
├── CMakeLists.txt                 # CMake build definition file
├── README.md                      # Project documentation
│
├── database-connection/           # Database Module
│   ├── connection.h               # Connection interface declarations
│   └── connection.c               # Core libpq database lifecycle management
│
├── email/                         # Email Engine Module
│   # (Handles SMTP logic / email transmission structures)
│
└── queries/                       # Data Access Layer
    # (Handles SQL parsing, fetching queues, and state mutations)
```

### Component Breakdown

- **database-connection/**: Handles the raw state of your connection (`PGconn*`). It securely extracts your `DATABASE_URL` from the environment.

- **queries/**: Isolates your raw SQL string logic from `main.c`. Any complex `SELECT` or `UPDATE` logic lives here.

- **email/**: Contains the protocol wrapper or service execution code responsible for parsing and passing payload fields to an outgoing mail server.

- **main.c**: The execution controller that initializes the DB connection, commands the queries module to scan for work, and passes entries to the email engine.

---

## Prerequisites & Installation

This project relies directly on the native C PostgreSQL Client (`libpq`). Ensure it is mapped on your local system before compiling.

### For Fedora Systems:

```bash
sudo dnf install postgresql16-devel
```

### For Ubuntu / Debian Systems:

```bash
sudo apt-get install libpq-dev
```

---

## Environment Setup

Create a `.env` file in the root directory to store your credentials:

```plaintext
DATABASE_URL="postgres://postgres.your_id:your_password@aws-0-your-region.pooler.supabase.com:5432/postgres?sslmode=require"
```

---

## Building and Running

Since you have a Makefile ready, you no longer need to write lengthy, manual `gcc` commands.

### 1. Build the Project

Simply run `make` in your terminal to compile the source code into the final executable (`email_sender`):

```bash
make
```

### 2. Run the Application

Inject your environment configuration variables and execute the generated binary file:

```bash
export $(cat .env | xargs) && ./email_sender
```

### 3. Clean Build Files

To strip out compiled `.o` object files and binaries for a fresh setup:

```bash
make clean
```
