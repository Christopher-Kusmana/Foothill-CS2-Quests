// Pet.cpp
// 2a-Lab-06-Pets
//
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "Pet.h"
using namespace std;
// This is a way to properly initialize (out-of-line) a static variable.
size_t Pet::_population = 0;

Pet::Pet(string name, long id, int num_limbs){
    _name = name;
    _id = id;
    _num_limbs = num_limbs;
    _population++;
}

Pet::~Pet() {
    --_population; 
}
string Pet::get_name() const { 
    return _name; 
}
long Pet::get_id() const {
    return _id; 
}
int Pet::get_num_limbs() const {
    return _num_limbs;
}
bool Pet::set_name(string name) {
    if(name != ""){
        _name = name;
        return true; 
    } else {
        return false; 
    }
 
}
bool Pet::set_id(long id) {
    if(id >= 0){
        _id = id;
        return true;
    }
    else {
        return false;
    } 
    
}
bool Pet::set_num_limbs(int num_limbs) {
    if(num_limbs >= 0){
        _num_limbs = num_limbs;
        return true; 
    }
    else{
        return false;
    }
}
string Pet::to_string() const {
    stringstream id;
    stringstream limbs;
    string pet_id;
    string pet_limbs;
    id << get_id();
    limbs << get_num_limbs();
    id >> pet_id;
    limbs >> pet_limbs;
    string stringification = "(Name: " + get_name() + ", ID: " + pet_id + ", Limb Count: " + pet_limbs + ")";
    return stringification;

}

// Fill in the supplied pets vector with n pets whose
// properties are chosen randomly.
// Don't mess with this method more than necessary.
void Pet::get_n_pets(size_t n, std::vector<Pet>& pets, int name_len) {
pets.resize(n);
long prev_id = 0;
for (size_t i = 0; i < n; i++) {
    long id = prev_id + 1 + rand() % 10;
    pets[i].set_id(id);
    pets[i].set_num_limbs(rand() % 9); // up to arachnids
    string pet_name = make_a_name(name_len);
    pets[i].set_name(pet_name);
    prev_id = id; 
}
}

// ---------------------------------------------------------------------
string Pet::make_a_name(int len) {
    string vowels = "aeiou";
    string consonants = "bcdfghjklmnpqrstvwxyz";
    string name;
    if(len == 0){
        return name;
    }
    char first;
    int chosen = rand() % 2;
    if (chosen == 0) {

        first = consonants[rand() % consonants.length()];
    } else {

        first = vowels[rand() % vowels.length()];
    }
    name += first;

    if(chosen == 0){
        for (int i = 1; i < len; i++) {
        if (i % 2 == 0) { //if even index = consonant

            name += consonants[rand() % consonants.length()];
        } else { //if odd index = vowel

            name += vowels[rand() % vowels.length()];
        }
    }
    } else {
        for (int i = 0; i < len-1; i++) {
        if (i % 2 == 0) { //if even index = consonant

            name += consonants[rand() % consonants.length()];
        } else { //if odd index = vowel

            name += vowels[rand() % vowels.length()];
        }
    }
    }


    return name;
}

// Optional EC points
// Global helpers
bool operator==(const Pet& pet1, const Pet& pet2) {
    return (pet1.get_name() == pet2.get_name() &&
             pet2.get_num_limbs()== pet2.get_num_limbs()
            );
}
bool operator!=(const Pet& pet1, const Pet& pet2) {
    return (!(pet1 == pet2));
}
ostream& operator<<(ostream& os, const Pet& pet) {
    string res = pet.to_string();
    os << res; 
    return os; 
}
