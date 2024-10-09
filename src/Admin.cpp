#include "Admin.h"


FamilyAdmin::FamilyAdmin(const User& user) : user(user) {
    if (user.getRole() != UserRole::ADMIN) {
        throw std::runtime_error("Only users with ADMIN role can be admins!");
    }

    // Инициализация стратегий для пользователя
    userStrategies["username"] = make_unique<IEditUsernameStrategy>();
    userStrategies["password"] = make_unique<IEditPasswordStrategy>();
    userStrategies["email"] = make_unique<IEditEmailStrategy>();
    userStrategies["role"] = make_unique<IEditRoleStrategy>();
    userStrategies["budgetLimit"] = make_unique<IEditBudgetLimitStrategy>();

    // Инициализация стратегий для категории
    categoryStrategies["name"] = make_unique<CEditNameStrategy>();
    categoryStrategies["description"] = make_unique<CEditDescriptionStrategy>();
    categoryStrategies["familyid"] = make_unique<CEditFamilyIdStrategy>();

    // Инициализация стратегий для транзакций
    transactionStrategies["description"] = make_unique<TEditDescriptionStrategy>();
    transactionStrategies["amount"] = make_unique<TEditAmountStrategy>();
    transactionStrategies["date"] = make_unique<TEditDateStrategy>();
    transactionStrategies["type"] = make_unique<TEditTypeStrategy>();
    transactionStrategies["userId"] = make_unique<TEditUserIdStrategy>();
    transactionStrategies["familyId"] = make_unique<TEditFamilyIdStrategy>();
    transactionStrategies["categoryId"] = make_unique<TEditCategoryIdStrategy>();
}

void FamilyAdmin::addFamilyMember(User& user) {
    user.setFamilyId(this->user.getFamilyId());
    userRep.updateUserFamilyId(user.getUsername(), user.getFamilyId());
}

void FamilyAdmin::removeFamilyMember(int userId) {
    User user = userRep.getUserById(userId);
    userRep.updateUserFamilyId(user.getUsername(), NULL);
}

void FamilyAdmin::editUserInfo(int userId, const map<string, string>& changes) {
    User userToEdit = userRep.getUserById(userId);

    // Применяем стратегии для каждого изменения
    for (const auto& [field, value] : changes) {
        if (userStrategies.find(field) != userStrategies.end()) {
            userStrategies[field]->apply(userToEdit, value);
        } else {
            std::cout << "Unknown field: " << field << std::endl;
        }
    }
    userRep.updateUser(userId, userToEdit);
}

vector<Transaction> FamilyAdmin::getFamilyTransactions() {
    return transactionRep.getTransactionsByFamilyId(user.getFamilyId());
}

void FamilyAdmin::editTransactionInfo(int transactionId, const map<string, string>& changes) {
    Transaction transactionToEdit = transactionRep.getTransactionById(transactionId);
    for (const auto& [field, value] : changes) {
        if(transactionStrategies.find(field) != transactionStrategies.end()) {
            transactionStrategies[field]->apply(transactionToEdit, value);
        } else {
            std::cout << "Unknown field: " << field << std::endl;
        }
    }
    transactionRep.updateTransaction(transactionId, transactionToEdit);
}

void FamilyAdmin::deleteTransaction(int transactionId) {
    transactionRep.deleteTransaction(transactionId);
}

void FamilyAdmin::addCategory(Category& category) {
    category.setFamilyId(user.getFamilyId());
    categoryRep.addCategory(category);
}

void FamilyAdmin::removeCategory(int categoryId) {
    categoryRep.deleteCategory(categoryId);
}

void FamilyAdmin::editCategory(int categoryId, const map<string, string>& changes) {
    Category categoryToEdit = categoryRep.getCategoryByCategoryIdFamilyId(categoryId, user.getFamilyId());
    
    // Применяем стратегии для каждого изменения
    for (const auto& [field, value] : changes) {
        if (categoryStrategies.find(field) != categoryStrategies.end()) {
            categoryStrategies[field]->apply(categoryToEdit, value);
        } else {
            std::cout << "Unknown field: " << field << std::endl;
        }
    }
    categoryRep.updateCategory(categoryId, categoryToEdit);
}

void FamilyAdmin::generateReport() {

}

void FamilyAdmin::setBudgetLimit(int userId, double limit) {
    User user = userRep.getUserById(userId);
    userRep.updateBudgetLimit(user.getUsername(), limit);
}
