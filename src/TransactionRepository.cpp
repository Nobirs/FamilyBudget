#include "TransactionRepository.h"

TransactionRepository::TransactionRepository() {
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "mysql_init() failed\n";
        return;
    }

    if(mysql_real_connect(conn, "localhost", "alex", "0811Hades", "family_budget", 0, nullptr, 0) == nullptr) {
        cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return;
    }
}

TransactionRepository::TransactionRepository(MYSQL *connection): conn(connection) {}

bool TransactionRepository::addTransaction(const Transaction &transaction) {
    string type = transaction.getType() == TransactionType::INCOME ? "INCOME" : "EXPENSE";
    string query = "INSERT INTO transactions (description, amount, type, user_id, family_id, category_id) VALUES ('" + 
                        transaction.getDescription() + "', " + std::to_string(transaction.getAmount()) + ", '" + type + "', '" +
                        std::to_string(transaction.getUserId()) + "', '" + std::to_string(transaction.getFamilyId()) + "', '" + std::to_string(transaction.getCategoryId()) + "')";

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (addTransaction): " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
}

bool TransactionRepository::updateTransaction(int transactionId, const Transaction &transaction) {
    string formattedDate = formatDate(transaction.getDate());
    string query = "UPDATE transactions SET "
                    "description = '" + transaction.getDescription() + "', "
                    "amount = '" + std::to_string(transaction.getAmount()) + "', "
                    "date = '" + formattedDate + "', "
                    "type = " + transaction.getTypeStr() + ", "
                    "user_id = '" + std::to_string(transaction.getUserId()) + "', "
                    "family_id = " + (transaction.getFamilyId() ? std::to_string(transaction.getFamilyId()) : "NULL") + " "
                    "categoryId = " + std::to_string(transaction.getCategoryId()) + ", "
                    "WHERE id = " + std::to_string(transactionId);

    // Выполняем SQL-запрос
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool TransactionRepository::deleteTransaction(int transactionId) {
    string query = "DELETE FROM transactions WHERE id = " + std::to_string(transactionId);

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (deleteTransaction): " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
}

Transaction TransactionRepository::getTransactionById(int transactionId) {
    string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE id = " + std::to_string(transactionId);
    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (getTransactionById): " << mysql_error(conn) << std::endl;
        Transaction defaultTransaction;
        return defaultTransaction;
    }
    MYSQL_RES *result = mysql_store_result(conn);

    MYSQL_ROW row = mysql_fetch_row(result);
    int id = std::stoi(row[0]);
    string description = row[1];
    double amount = std::stod(row[2]);
    // Преобразование строки в time_t (date)
    tm tmReg = {};
    strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
    time_t date = std::mktime(&tmReg);

    TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
    int userId = std::stoi(row[5]);
    int categoryId = std::stoi(row[6]);
    int familyId = std::stoi(row[7]);

    Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
    return transaction;
}

vector<Transaction> TransactionRepository::getTransactionsByUserId(int userId) {
    string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE user_id = " + std::to_string(userId);
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);

    vector<Transaction> transactions;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        string description = row[1];
        double amount = std::stod(row[2]);
        // Преобразование строки в time_t (date)
        tm tmReg = {};
        strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t date = std::mktime(&tmReg);

        TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
        int userId = std::stoi(row[5]);
        int categoryId = std::stoi(row[6]);
        int familyId = std::stoi(row[7]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionsByFamilyId(int familyId) {
    std::string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE family_id = " + std::to_string(familyId);
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);

    vector<Transaction> transactions;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string description = row[1];
        double amount = std::stod(row[2]);
        // Преобразование строки в time_t (date)
        std::tm tmReg = {};
        strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t date = std::mktime(&tmReg);

        TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
        int userId = std::stoi(row[5]);
        int categoryId = std::stoi(row[6]);
        int familyId = std::stoi(row[7]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByCategoryId(int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE category_id = " + std::to_string(categoryId);
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);

    vector<Transaction> transactions;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string description = row[1];
        double amount = std::stod(row[2]);
        // Преобразование строки в time_t (date)
        std::tm tmReg = {};
        strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t date = std::mktime(&tmReg);

        TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
        int userId = std::stoi(row[5]);
        int categoryId = std::stoi(row[6]);
        int familyId = std::stoi(row[7]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByUserIdCategoryId(int userId, int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE user_id = " + std::to_string(userId) + "AND category_id = " + std::to_string(categoryId);
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);

    vector<Transaction> transactions;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string description = row[1];
        double amount = std::stod(row[2]);
        // Преобразование строки в time_t (date)
        std::tm tmReg = {};
        strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t date = std::mktime(&tmReg);

        TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
        int userId = std::stoi(row[5]);
        int categoryId = std::stoi(row[6]);
        int familyId = std::stoi(row[7]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByFamilyIdCategoryId(int familyId, int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, user_id, category_id, family_id FROM transactions WHERE family_id = " + std::to_string(familyId) + "AND category_id = " + std::to_string(categoryId);
    mysql_query(conn, query.c_str());
    MYSQL_RES *result = mysql_store_result(conn);

    vector<Transaction> transactions;
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        std::string description = row[1];
        double amount = std::stod(row[2]);
        // Преобразование строки в time_t (date)
        std::tm tmReg = {};
        strptime(row[3], "%Y-%m-%d %H:%M:%S", &tmReg);
        time_t date = std::mktime(&tmReg);

        TransactionType type = (std::string(row[4]) == "INCOME") ? TransactionType::INCOME : TransactionType::EXPENSE;
        int userId = std::stoi(row[5]);
        int categoryId = std::stoi(row[6]);
        int familyId = std::stoi(row[7]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, userId, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

void TransactionRepository::clearTransactionTable() {
    if (conn) {
        const char* disable_fk_checks = "SET FOREIGN_KEY_CHECKS = 0;";
        const char* truncate_table = "TRUNCATE TABLE transactions;";
        const char* enable_fk_checks = "SET FOREIGN_KEY_CHECKS = 1;";

        if (mysql_query(conn, disable_fk_checks)) { cerr << "Error disabling foreign key checks: " << mysql_error(conn) << std::endl; }

        if (mysql_query(conn, truncate_table)) { cerr << "Error truncating transactions table: " << mysql_error(conn) << std::endl; }
        else { cout << "Transactions table cleared successfully." << std::endl; }

        if (mysql_query(conn, enable_fk_checks)) { cerr << "Error enabling foreign key checks: " << mysql_error(conn) << std::endl; }
    
    } else {
        cerr << "MySQL connection is not established." << std::endl;
    }
}