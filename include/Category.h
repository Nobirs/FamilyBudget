#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

using std::string;

class CategoryRepository;

class Category {
protected:
    int id;
    string name;
    string description;
    int familyId; 

    static Category createCategory(int id, const string &name, const string &description, int familyId);

public:
    Category();
    Category(const string &name, const std::string &description, int familyId);

    int getId() const;
    const string &getName() const;
    const string &getDescription() const;
    int getFamilyId() const;

    void setName(const string &name);
    void setDescription(const string &description);
    void setFamilyId(int familyId);

    friend class CategoryRepository;
};

#endif // CATEGORY_H
