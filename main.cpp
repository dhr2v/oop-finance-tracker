#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>

using namespace std;

// Transaction Class
class Transaction {
private:
  string type;        // "Income" or "Expense"
  string description;
  double amount;
  string category;
  string date;

public:
  Transaction(string t, string desc, double amt, string cat, string dt) {
    type = t;
    description = desc;
    amount = amt;
    category = cat;
    date = dt;
  }

  void display() {
    cout << left << setw(12) << date << setw(10) << type 
         << setw(20) << description << setw(15) << category 
         << right << setw(10) << fixed << setprecision(2);
    
    if (type == "Income") {
      cout << "+$" << amount << "\n";
    } else {
      cout << "-$" << amount << "\n";
    }
  }

  string getType() { return type; }
  double getAmount() { return amount; }
  string getCategory() { return category; }
  string getDescription() { return description; }
  string getDate() { return date; }
};

// Budget Class
class Budget {
private:
  string category;
  double limit;
  double spent;

public:
  Budget(string cat, double lim) {
    category = cat;
    limit = lim;
    spent = 0;
  }

  void updateSpent(double amount) {
    spent = amount;
  }

  void display() {
    cout << "Category: " << category << "\n";
    cout << "Budget: $" << fixed << setprecision(2) << limit << "\n";
    cout << "Spent:  $" << spent << "\n";
    cout << "Remaining: $" << (limit - spent) << "\n";
    
    double percent = (spent / limit) * 100.0;
    cout << "Usage: " << setprecision(1) << percent << "%\n";

    if (spent > limit) {
      cout << "WARNING: Budget exceeded!\n";
    } else if (percent > 80) {
      cout << "ALERT: Approaching budget limit!\n";
    }
  }

  string getCategory() { return category; }
  double getLimit() { return limit; }
};

// Main Finance Tracker Class
class FinanceTracker {
private:
  double balance;
  vector<Transaction> transactions;
  vector<Budget> budgets;

  void displayMenu() {
    cout << "\n===== PERSONAL FINANCE TRACKER =====\n";
    cout << "1. Add Income\n";
    cout << "2. Add Expense\n";
    cout << "3. View All Transactions\n";
    cout << "4. View Balance\n";
    cout << "5. Set Budget\n";
    cout << "6. Check Budget Status\n";
    cout << "7. Monthly Report\n";
    cout << "8. Exit\n";
    cout << "====================================\n";
    cout << "Choice: ";
  }

  void addTransaction() {
    int type;
    cout << "\n1. Income\n2. Expense\nSelect type: ";
    cin >> type;
    cin.ignore();

    string description, category, date;
    double amount;

    cout << "Description: ";
    getline(cin, description);
    cout << "Amount: $";
    cin >> amount;
    cin.ignore();
    cout << "Category: ";
    getline(cin, category);
    cout << "Date (DD/MM/YYYY): ";
    getline(cin, date);

    if (type == 1) {
      Transaction trans("Income", description, amount, category, date);
      transactions.push_back(trans);
      balance += amount;
    } else {
      Transaction trans("Expense", description, amount, category, date);
      transactions.push_back(trans);
      balance -= amount;
    }

    saveToFile();
    cout << "\nTransaction added successfully!\n";
  }

  void viewTransactions() {
    if (transactions.empty()) {
      cout << "\nNo transactions found.\n";
      return;
    }

    cout << "\n===== ALL TRANSACTIONS =====\n";
    cout << left << setw(12) << "Date" << setw(10) << "Type" 
         << setw(20) << "Description" << setw(15) << "Category" 
         << right << setw(10) << "Amount" << "\n";
    cout << string(67, '-') << "\n";

    for (int i = 0; i < transactions.size(); i++) {
      transactions[i].display();
    }
  }

  void viewBalance() {
    cout << "\n===== ACCOUNT SUMMARY =====\n";
    cout << "Current Balance: $" << fixed << setprecision(2) 
         << balance << "\n";

    double totalIncome = 0, totalExpense = 0;
    for (int i = 0; i < transactions.size(); i++) {
      if (transactions[i].getType() == "Income") {
        totalIncome += transactions[i].getAmount();
      } else {
        totalExpense += transactions[i].getAmount();
      }
    }

    cout << "\nTotal Income:  $" << totalIncome << "\n";
    cout << "Total Expense: $" << totalExpense << "\n";
    cout << "Net Savings:   $" << (totalIncome - totalExpense) << "\n";
  }

  void addBudget() {
    string category;
    double limit;

    cin.ignore();
    cout << "\nCategory: ";
    getline(cin, category);
    cout << "Monthly Limit: $";
    cin >> limit;

    Budget budget(category, limit);
    budgets.push_back(budget);
    saveToFile();
    cout << "\nBudget set successfully!\n";
  }

  void checkBudgets() {
    if (budgets.empty()) {
      cout << "\nNo budgets set.\n";
      return;
    }

    cout << "\n===== BUDGET STATUS =====\n";
    
    for (int i = 0; i < budgets.size(); i++) {
      double spent = 0;
      for (int j = 0; j < transactions.size(); j++) {
        if (transactions[j].getType() == "Expense" && 
            transactions[j].getCategory() == budgets[i].getCategory()) {
          spent += transactions[j].getAmount();
        }
      }
      budgets[i].updateSpent(spent);
      budgets[i].display();
      cout << "\n";
    }
  }

  void viewMonthlyReport() {
    if (transactions.empty()) {
      cout << "\nNo transactions to report.\n";
      return;
    }

    map<string, double> incomeByCategory;
    map<string, double> expenseByCategory;

    for (int i = 0; i < transactions.size(); i++) {
      if (transactions[i].getType() == "Income") {
        incomeByCategory[transactions[i].getCategory()] += 
          transactions[i].getAmount();
      } else {
        expenseByCategory[transactions[i].getCategory()] += 
          transactions[i].getAmount();
      }
    }

    cout << "\n===== MONTHLY REPORT =====\n";
    
    cout << "\nINCOME BY CATEGORY:\n";
    cout << left << setw(20) << "Category" << right << setw(12) 
         << "Amount" << "\n";
    cout << string(32, '-') << "\n";
    
    for (map<string, double>::iterator it = incomeByCategory.begin();
         it != incomeByCategory.end(); ++it) {
      cout << left << setw(20) << it->first << right << setw(12) 
           << fixed << setprecision(2) << "$" << it->second << "\n";
    }

    cout << "\nEXPENSES BY CATEGORY:\n";
    cout << left << setw(20) << "Category" << right << setw(12) 
         << "Amount" << "\n";
    cout << string(32, '-') << "\n";
    
    for (map<string, double>::iterator it = expenseByCategory.begin();
         it != expenseByCategory.end(); ++it) {
      cout << left << setw(20) << it->first << right << setw(12) 
           << fixed << setprecision(2) << "$" << it->second << "\n";
    }
  }

  void saveToFile() {
    ofstream file("finance_data.txt");
    if (!file) {
      cout << "Error saving data!\n";
      return;
    }

    file << balance << "\n";
    file << transactions.size() << "\n";

    for (int i = 0; i < transactions.size(); i++) {
      file << transactions[i].getType() << "|" 
           << transactions[i].getDescription() << "|" 
           << transactions[i].getAmount() << "|" 
           << transactions[i].getCategory() << "|" 
           << transactions[i].getDate() << "\n";
    }

    file << budgets.size() << "\n";
    for (int i = 0; i < budgets.size(); i++) {
      file << budgets[i].getCategory() << "|" 
           << budgets[i].getLimit() << "\n";
    }

    file.close();
  }

  void loadFromFile() {
    ifstream file("finance_data.txt");
    if (!file) {
      cout << "No previous data found. Starting fresh!\n";
      return;
    }

    file >> balance;

    int transCount;
    file >> transCount;
    file.ignore();

    for (int i = 0; i < transCount; i++) {
      string line;
      getline(file, line);
      
      // Parse the line
      string type, desc, cat, date;
      double amount;
      
      int pos1 = line.find('|');
      type = line.substr(0, pos1);
      
      int pos2 = line.find('|', pos1 + 1);
      desc = line.substr(pos1 + 1, pos2 - pos1 - 1);
      
      int pos3 = line.find('|', pos2 + 1);
      amount = stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
      
      int pos4 = line.find('|', pos3 + 1);
      cat = line.substr(pos3 + 1, pos4 - pos3 - 1);
      
      date = line.substr(pos4 + 1);

      Transaction trans(type, desc, amount, cat, date);
      transactions.push_back(trans);
    }

    int budgetCount;
    file >> budgetCount;
    file.ignore();

    for (int i = 0; i < budgetCount; i++) {
      string line;
      getline(file, line);
      
      int pos = line.find('|');
      string cat = line.substr(0, pos);
      double limit = stod(line.substr(pos + 1));

      Budget budget(cat, limit);
      budgets.push_back(budget);
    }

    file.close();
    cout << "Data loaded successfully!\n";
  }

public:
  FinanceTracker() {
    balance = 0;
  }

  void run() {
    loadFromFile();
    
    int choice;
    do {
      displayMenu();
      cin >> choice;

      switch (choice) {
      case 1:
      case 2:
        addTransaction();
        break;
      case 3:
        viewTransactions();
        break;
      case 4:
        viewBalance();
        break;
      case 5:
        addBudget();
        break;
      case 6:
        checkBudgets();
        break;
      case 7:
        viewMonthlyReport();
        break;
      case 8:
        cout << "\nSaving and exiting...\n";
        saveToFile();
        break;
      default:
        cout << "\nInvalid choice!\n";
      }
    } while (choice != 8);
  }
};

int main() {
  FinanceTracker tracker;
  tracker.run();
  return 0;
}