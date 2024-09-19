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

bool CategoryRepository::deleteCategory(int categoryId) {
    string query = "DELETE FROM categories WHERE id = " + std::to_string(categoryId);

    if (mysql_query(conn, query.c_str())) {
        cerr << "MySQL query error (deleteCategory): " << mysql_error(conn) << std::endl;
        return false;
    }

    return true;
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

Category CategoryRepository::getCategoryByCategoryIdFamilyId(int categoryId, int familyId) {
    Category category;
    string query = "SELECT id, name, description FROM categories WHERE family_id = " + std::to_string(familyId) + " AND categoryId = " + std::to_string(categoryId);

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


void CategoryRepository::clearCategoryTable() {
    if (conn) {
        const char* query = "DELETE FROM categories";
        
        if (mysql_query(conn, query)) {
            cerr << "Error clearing category table: " << mysql_error(conn) << std::endl;
        } else {
            cout << "Category table cleared successfully." << std::endl;
        }
    } else {
        cerr << "MySQL connection is not established." << std::endl;
    }
}