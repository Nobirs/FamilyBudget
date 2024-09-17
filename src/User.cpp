#include "User.h"


User::User(){
    username = "default";
    passwordHash = hashPassword("default");
    role = UserRole::USER;
    email = "default@gmail.com";
    registrationDate = time(nullptr);
    lastLogin = time(nullptr);
    financialRole = "FAMILY_MEMBER";
    budgetLimit = 0.0;
    familyStatus = "CHILD";
}

string User::hashPassword(const string &password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

User User::createUser(const string &username, const string &passwordHash, UserRole role, 
                        const string &email, time_t registrationDate, const string &financialRole, 
                        double budgetLimit, const string& familyStatus, int familyId){
    User user;
    user.username = username;
    user.passwordHash = passwordHash;
    user.role = role;
    user.email = email;
    user.registrationDate = registrationDate;
    user.lastLogin = time(nullptr);
    user.financialRole = financialRole;
    user.budgetLimit = budgetLimit;
    user.familyStatus = familyStatus;
    user.familyId = familyId;
    return user;

}

User::User(const string &username, const string &password, UserRole role, 
                        const string &email, const string &financialRole, 
                        double budgetLimit, const string& familyStatus, int familyId)
                        : username(username), role(role), financialRole(financialRole),
                        budgetLimit(budgetLimit), familyStatus(familyStatus), familyId(familyId) {
        this->passwordHash = hashPassword(password);
        this->setEmail(email);
        this->setRegistrationDate(time(nullptr));
        this->setLastLogin(time(nullptr));
}

const string &User::getUsername() const { return username; }
void User::setUsername(const string &newUsername) { this->username = newUsername; }

const string &User::getEmail() const { return this->email; }
void User::setEmail(const string &newEmail) {
    if(isValidEmail(newEmail)) this->email = newEmail;
    else throw std::runtime_error("Invalid Email");
}

UserRole User::getRole() const { return this->role; }
void User::setRole(UserRole newRole) { this->role = newRole; }

time_t User::getRegistrationDate() const { return this->registrationDate; }
string User::getRegDateStr() const {
    std::tm *tm = std::localtime(&registrationDate);
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void User::setRegistrationDate(time_t regDate) { this->registrationDate = regDate; }

time_t User::getLastLogin() const { return this->lastLogin; }
string User::getLastLoginStr() const {
    std::tm *tm = std::localtime(&lastLogin);
    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
void User::setLastLogin(time_t lastLogin) { this->lastLogin = lastLogin; }

const string &User::getFinancialRole() const { return this->financialRole; }
void User::setFinancialRole(const string &role) { this->financialRole = role; }

double User::getBudgetLimit() const { return this->budgetLimit; }
void User::setBudgetLimit(double limit) {
    if(limit >= 0) this->budgetLimit = limit;
    else throw std::runtime_error("Invalid budget");
}

const string &User::getFamilyStatus() const { return this->familyStatus; }
void User::setFamilyStatus(const string &status) { this->familyStatus = status; }

int User::getFamilyId() const { return familyId; }
void User::setFamilyId(int familyId) { this->familyId = familyId; }

bool User::isAdmin(const User &user) { return user.role == UserRole::ADMIN; }

bool User::isValidEmail(const string &email) {
    const std::regex pattern("^[\\w\\.-]+@[\\w\\.-]+\\.\\w+$");
    return std::regex_match(email, pattern);
}

const string &User::getPasswordHash() const { return this->passwordHash; }

bool User::authenticate(const string &inputPassword) const {
    return passwordHash == hashPassword(inputPassword);
}

void User::changePassword(const string &newPassword) {
    this->passwordHash = hashPassword(newPassword);
}
