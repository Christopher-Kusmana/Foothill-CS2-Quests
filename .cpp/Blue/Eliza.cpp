// Student ID: 20527001
// Eliza.cpp
// 2a.Lab-05-Eliza
//
//
#include <iostream>
#include <sstream>
using namespace std;
//aeiou
string rotate_vowels(string& s){
    for(size_t i = 0; i < s.length(); i++){
        if(s[i] == 'a'){
            s[i] = 'e';
        } else if(s[i] == 'e'){
            s[i] = 'i';
        } else if(s[i] == 'i'){
            s[i] = 'o';
        } else if(s[i] == 'o'){
            s[i] = 'u';
        } else if(s[i] == 'u'){ 
            s[i] = 'a';
        }
    }
    return s;
}


string lispify(string s){
    for(size_t i=0; i < s.length(); i++){
        if(s[i] == 's'){
            s[i] = 't';
            s.insert(s.begin() + i+1, 'h');
        }
    }
    return s;
}

// Enter the user-interaction loop as described earlier
void enter() {
    cout << "What?\n";
    while(true) {
        string user_input;
        getline(cin , user_input);
        // checks if there is !
        bool excl = false;
        for(size_t i = 0; i < user_input.length(); i++){
            if(user_input[i] == '!'){
                excl = true;
            }
        }
        if(user_input == ""){
            cout << "What?\n";
           
        } 
        cout << "    " << user_input << "\n\n";
        if(excl){
            cout << "OMG! You don't say!! " << user_input << "!!!!!\n";
        } else if(user_input.find("why") <= user_input.length() || user_input.find("what") <= user_input.length())   {
                cout << "I'm sorry, I don't like questions that contain what or why.\n";
        } else if(user_input.find("s") <= user_input.length()){
            cout << "Interethting. When did you thtop thtopping your thibilanth?\n";
            cout << lispify(user_input) << "! Sheesh! Now what?\n";
        } else if(user_input.find("bye") <= user_input.length() || user_input.find("quit") <= user_input.length() || user_input.find("Bye") <= user_input.length() || user_input.find("Quit") <= user_input.length()){
            cout << "Ok Bye. Nice being a force of change in your life.\n";
            break;
        } else {
            int choose = rand() % 10;
            if(choose <= 7){
                cout << rotate_vowels(user_input) << "?\n";
                
            } 
            if(choose >= 8){
                cout << "Huh? Why do you say: " << user_input << "?\n";
            }
        }
    }
}


