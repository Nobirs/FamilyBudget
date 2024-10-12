#include "CategoryRepository.h"

CategoryRepository::CategoryRepository() {
    conn = mysql_init(nullptr);
    if (conn == nullptr) {
        cerr << "mysql_init() failed\n";
        return;
    }

    if (mysql_real_connect(conn, "localhost", "alex", "0811Hades", "family_budget", 0, nullptr, 0) == nullptr) {
        cerr << "mysql_real_connect() failed\n";
        mysql_close(conn);
        return;
    }
}

CategoryRepository::CategoryRepository(MYSQL *connection) : conn(connection) {}


bool CategoryRepository::addCategory(const Category &category) {
    string query = "INSERT INTO categories (name, description, family_id) VALUES ('" + 
                        category.getName() + "', '" + category.getDescription() + "', " + 
                        std::to_string(category.getFamilyId()) + ")";

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (addCategory): " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
}

bool CategoryRepository::updateCategory(int categoryId, const Category &category) {
    string query = "UPDATE categories SET "
                    "name = '" + category.getName() + "', "
                    "description = '" + category.getDescription() + "', "
                    "family_id = " + (category.getFamilyId() ? std::to_string(category.getFamilyId()) : "NULL") + " "
                    "WHERE id = " + std::to_string(categoryId);

    // Выполняем SQL-запрос
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return false;
    }
    return true;
}

bool CategoryRepository::deleteCategory(int categoryId) {
    string query = "DELETE FROM categories WHERE id = " + std::to_string(categoryId);

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (deleteCategory): " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
}

vector<Category> CategoryRepository::getAllCategories() {
    vector<Category> categories;
    string query = "SELECT id, name, description FROM categories";

    if(mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (getAllCategories): " << mysql_error(conn) << std::endl;
        return categories;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if(result == NULL) {
        cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
        return categories;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        string name = row[1];
        string description = row[2];

        Category category = Category::createCategory(id, name, description, 0);
        categories.push_back(category);
    }

    mysql_free_result(result);
    return categories;
}

vector<Category> CategoryRepository::getCategoriesByFamilyId(int familyId) {
    vector<Category> categories;
    string query = "SELECT id, name, description FROM categories WHERE family_id = " + std::to_string(familyId);

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (getCategoriesByFamilyId): " << mysql_error(conn) << std::endl;
        return categories;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == nullptr) {
        cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
        return categories;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        string name = row[1];
        string description = row[2];

        Category category = Category::createCategory(id, name, description, familyId);
        categories.push_back(category);
    }

    mysql_free_result(result);
    return categories;
}

Category CategoryRepository::getCategoryByCategoryIdFamilyId(int categoryId, int familyId) {
    Category category;
    string query = "SELECT id, name, description FROM categories WHERE family_id = " + std::to_string(familyId) + " AND id = " + std::to_string(categoryId);

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (getCategoryByCategoryIdFamilyId): " << mysql_error(conn) << std::endl;
        return category;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == nullptr) {
        cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
        return category;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        string name = row[1];
        string description = row[2];
        Category existingCategory = Category::createCategory(id, name, description, familyId);
        return existingCategory;
    }
    return category;
}

Category CategoryRepository::getCategoryByNameFamilyId(const string &name, int familyId) {
    Category category;
    string query = "SELECT id, name, description FROM categories WHERE family_id = " + std::to_string(familyId) + " AND name = '" + name + "'";

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (getCategoryByNameFamilyId): " << mysql_error(conn) << std::endl;
        return category;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == nullptr) {
        cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
        return category;
    }

    MYSQL_ROW row;
    if ((row = mysql_fetch_row(result))) {
        int id = std::stoi(row[0]);
        string name = row[1];
        string description = row[2];

        Category existingCategory = Category::createCategory(id, name, description, familyId);
        return existingCategory;
    }
    return category;
}

void CategoryRepository::clearCategoryTable() {
    if (conn) {
        const char* disable_fk_checks = "SET FOREIGN_KEY_CHECKS = 0;";
        const char* truncate_table = "TRUNCATE TABLE categories;";
        const char* enable_fk_checks = "SET FOREIGN_KEY_CHECKS = 1;";

        if (mysql_query(conn, disable_fk_checks)) { cerr << "Error disabling foreign key checks: " << mysql_error(conn) << std::endl; }

        if (mysql_query(conn, truncate_table)) { cerr << "Error truncating categories table: " << mysql_error(conn) << std::endl; }
        else { std::clog << "Categories table cleared successfully." << std::endl; }

        if (mysql_query(conn, enable_fk_checks)) { cerr << "Error enabling foreign key checks: " << mysql_error(conn) << std::endl; }
    
    } else {
        cerr << "MySQL connection is not established." << std::endl;
    }
}