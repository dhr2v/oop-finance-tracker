# Personal Finance Tracker

A command-line application for managing personal finances with transaction tracking, budget management, and monthly reporting capabilities.

## Overview

Personal Finance Tracker is a C++ application designed to help you manage your income, expenses, and budgets effectively. Track all your financial transactions, set spending limits for different categories, and generate comprehensive monthly reports to understand your spending patterns.

## Features

- **Transaction Management**: Record income and expense transactions with detailed descriptions and categories
- **Balance Tracking**: View your current account balance and net savings at a glance
- **Budget Management**: Set monthly budget limits for different spending categories
- **Budget Monitoring**: Track spending against budgets with visual alerts when approaching limits
- **Monthly Reports**: Generate category-wise breakdowns of income and expenses
- **Data Persistence**: Automatic saving and loading of financial data between sessions

## Getting Started

### Prerequisites

- C++ compiler (C++11 or later)
- Windows, macOS, or Linux system

### Building the Project

Compile the program using your C++ compiler:

```bash
g++ -std=c++11 main.cpp -o finance_tracker
```

Or with clang:

```bash
clang++ -std=c++11 main.cpp -o finance_tracker
```

### Running the Application

```bash
./finance_tracker
```

Or on Windows:

```bash
finance_tracker.exe
```

## Usage

Upon running the application, you'll see the main menu with the following options:

1. **Add Income** - Record an income transaction
2. **Add Expense** - Record an expense transaction
3. **View All Transactions** - Display all recorded transactions in a table format
4. **View Balance** - Check your current balance and financial summary
5. **Set Budget** - Create a new budget for a spending category
6. **Check Budget Status** - Review spending against set budgets
7. **Monthly Report** - View income and expenses categorized and summarized
8. **Exit** - Close the application and save all data

### Example Workflow

1. Start the application
2. Add an income transaction (salary, bonus, etc.)
3. Add expense transactions (groceries, utilities, entertainment, etc.)
4. Set monthly budgets for categories where you want spending limits
5. Check your budget status to ensure you're staying within limits
6. Generate a monthly report to analyze your spending patterns

## Data Storage

All financial data is automatically saved to `finance_data.txt` in the application directory. This file is created automatically and contains:

- Current account balance
- All transaction records
- Budget configurations

The application loads this data automatically on startup, so your financial history persists between sessions.

## Program Structure

### Classes

- **Transaction**: Represents a single income or expense transaction with type, description, amount, category, and date
- **Budget**: Manages budget limits for spending categories and tracks spending against those limits
- **FinanceTracker**: Main controller class that manages transactions, budgets, and user interactions

## Technical Details

- Built with standard C++ libraries (iostream, vector, string, fstream, iomanip, map)
- Uses object-oriented design principles with encapsulation and data persistence
- Implements file I/O for data storage and retrieval
- Provides formatted console output with proper alignment and precision

## Limitations and Future Enhancements

Current limitations:

- Console-based interface only
- Single file-based storage (no database)
- No data encryption or security features

---

## Contributors

- **Dhruv Anand** - Developer and Maintainer
- **Ojas Wane** - Contributor & Tester
- **Suryansh Verma** - Contributor & Tester

---
