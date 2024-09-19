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
    string query = "INSERT INTO transactions (description, amount, type, familyId, categoryId) VALUES ('" + 
                        transaction.getDescription() + "', " + std::to_string(transaction.getAmount()) + ", '" + type + "', '" +
                        std::to_string(transaction.getFamilyId()) + "', '" + std::to_string(transaction.getCategoryId()) + "')";

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (addTransaction): " << mysql_error(conn) << std::endl;
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

vector<Transaction> TransactionRepository::getTransactionsByUserId(int userId) {
    std::string query = "SELECT id, description, amount, date, type, category_id, family_id FROM transactions WHERE user_id = " + std::to_string(userId);
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
        int categoryId = std::stoi(row[5]);
        int familyId = std::stoi(row[6]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionsByFamilyId(int familyId) {
    std::string query = "SELECT id, description, amount, date, type, category_id, family_id FROM transactions WHERE family_id = " + std::to_string(familyId);
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
        int categoryId = std::stoi(row[5]);
        int familyId = std::stoi(row[6]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByCategoryId(int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, category_id, family_id FROM transactions WHERE category_id = " + std::to_string(categoryId);
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
        int categoryId = std::stoi(row[5]);
        int familyId = std::stoi(row[6]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByUserIdCategoryId(int userId, int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, category_id, family_id FROM transactions WHERE user_id = " + std::to_string(userId) + "AND category_id = " + std::to_string(categoryId);
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
        int categoryId = std::stoi(row[5]);
        int familyId = std::stoi(row[6]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}

vector<Transaction> TransactionRepository::getTransactionByFamilyIdCategoryId(int familyId, int categoryId) {
    std::string query = "SELECT id, description, amount, date, type, category_id, family_id FROM transactions WHERE family_id = " + std::to_string(familyId) + "AND category_id = " + std::to_string(categoryId);
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
        int categoryId = std::stoi(row[5]);
        int familyId = std::stoi(row[6]);

        Transaction transaction = Transaction::createTransaction(description, amount, date, type, familyId, categoryId);
        transactions.push_back(transaction);
    }

    mysql_free_result(result);
    return transactions;
}