#include "Category.h"

Category Category::createCategory(int id, const string &name, const string &description, int familyId){
    Category category;
    category.id = id;
    category.name = name;
    category.description = description;
    category.familyId = familyId;
    return category;
}

Category::Category() {
    this->id = 1;
    this->name = "GENERAL";
    this->description = "General category for all products";
    this->familyId = 1;
}

Category::Category(const string &name, const string &description, int familyId)
    : name(name), description(description), familyId(familyId) {}

int Category::getId() const { return id; }

const string &Category::getName() const { return name; }
void Category::setName(const string &name) { this->name = name; }

const string &Category::getDescription() const { return description; }
void Category::setDescription(const string &description) { this->description = description; }

int Category::getFamilyId() const { return familyId; }
void Category::setFamilyId(int familyId) { this->familyId = familyId; }
