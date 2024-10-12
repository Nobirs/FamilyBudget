#ifndef CATEGORYREPOSITORY_H
#define CATEGORYREPOSITORY_H

#include <vector>
#include <iostream>
#include "Category.h"
#include <mysql/mysql.h>

using std::string;
using std::vector;
using std::cout;
using std::cerr;


class CategoryRepository {
private:
    MYSQL *conn;  // MySQL connection object

public:
    CategoryRepository();
    CategoryRepository(MYSQL *connection);

    bool addCategory(const Category &category); 
    bool updateCategory(int categoryId, const Category &category);
    bool deleteCategory(int categoryId);
    vector<Category> getAllCategories();
    vector<Category> getCategoriesByFamilyId(int familyId);
    Category getCategoryByCategoryIdFamilyId(int categoryId, int familyId);
    Category getCategoryByNameFamilyId(const string &name, int familyId);
    void clearCategoryTable();
};

#endif // CATEGORYREPOSITORY_H
