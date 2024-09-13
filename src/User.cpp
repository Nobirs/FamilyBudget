#include "User.h"


User::User(){
    username = "default";
    passwordHash = "default";
    role = UserRole::USER;
}

string User::hashPassword(const string &password) const {
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

User User::createUser(const string &username, const string &passwordHash, UserRole role){
    User user;
    user.username = username;
    user.passwordHash = passwordHash;
    user.role = role;
    return user;

}

User::User(const string &username, const string &password, UserRole role)
    : username(username), role(role) {
        this->passwordHash = hashPassword(password);
}

const string &User::getUsername() const {
    return username;
}

bool User::authenticate(const string &inputPassword) const {
    return passwordHash == hashPassword(inputPassword);
}

const string &User::getPasswordHash() const {
    return this->passwordHash;
}

UserRole User::getRole() const {
    return role;
}

void User::changePassword(const string &newPassword) {
    this->passwordHash = hashPassword(newPassword);
}


