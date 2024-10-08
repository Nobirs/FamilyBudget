#include <iostream>
#include <string>
#include <memory>
#include <map>

#include "User.h"
#include "UserRepository.h"
#include "UserEditStrategies.h"
#include "Transaction.h"
#include "TransactionRepository.h"
#include "TransactionEditStrategies.h"
#include "Category.h"
#include "CategoryRepository.h"
#include "CategoryEditStrategies.h"

using std::map;
using std::string;
using std::unique_ptr;
using std::make_unique;


class FamilyAdmin {
private:
    User user;
    UserRepository userRep;
    CategoryRepository categoryRep;
    TransactionRepository transactionRep;
    map<string, unique_ptr<IEditStrategy>> userStrategies;
    map<string, unique_ptr<CEditStrategy>> categoryStrategies;
    map<string, unique_ptr<TEditStrategy>> transactionStrategies;
public:
    FamilyAdmin(const User &user);

    // Управление пользователями
    void addFamilyMember(User& user);
    void removeFamilyMember(int userId);
    void editUserInfo(int userId, const map<string, string>& changes);

    // Управление транзакциями
    vector<Transaction> getFamilyTransactions();
    void editTransactionInfo(int transactionId, const map<string, string>& changes);
    void deleteTransaction(int transactionId);

    // Управление категориями
    void addCategory(Category& category);
    void removeCategory(int categoryId);
    void editCategory(int categoryId, const map<string, string>& changes);

    // Отчеты и статистика
    void generateReport();

    // Управление бюджетом
    void setBudgetLimit(int userId, double limit);
    //void adjustCategoryLimit(int categoryId, double limit);

    // Управление системой
    //void configureSettings();
    void updateUserInDatabase(const User& updatedUser);
    void updateCategoryInDatabase(const Category& updatedCategory);
    void updateTransactionInDatabase(const Transaction& updatedTransaction);
};
