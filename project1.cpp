//
//  main.cpp
//  project1
//
//  Created by 彭瀚林 on 2019/10/29.
//  Copyright © 2019 penghanlin. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#define LENGTH 5
char ch = ' ';
string key[5] = {"if", "then", "else", "while", "do"};

int is_key(string c) {
    int i;
    for (i = 0; i < LENGTH; i++) {
        if (key[i].compare(c) == 0) return 1;
    }
    return 0;
}

int is_letter(char c) {
    if (((c <= 'z') && (c >= 'a')) || ((c <= 'Z') && (c >= 'A'))) return 1;
    else return 0;
}

int is_letter_a_f(char c) {
    if (((c <= 'f') && (c >= 'a')) || ((c <= 'F') && (c >= 'A'))) return 1;
    else return 0;
}

int is_number(char c) {
     if (c >= '0' && c <= '9') return 1;
     else return 0;
}

void scan(FILE *fpin) {
    string arr = "";
    while ((ch = fgetc(fpin)) != EOF) {
         arr = "";
         if (ch == ' ' || ch == '\t' || ch == '\n') {}
         else if(is_letter(ch) || ch == '_') {
             arr = arr + ch;
             ch = fgetc(fpin);
             while (is_letter(ch) || is_number(ch)) {
                 if ((ch <= 'Z') && (ch >= 'A')) ch = ch + 32;
                 arr = arr + ch;
                 ch = fgetc(fpin);
             }

             fseek(fpin, -1L, SEEK_CUR);
             if (is_key(arr)) {
                 cout << "<" << arr << ", ->" << endl;
             }
             else {
                 cout << "<" << arr << ", -->" << endl;
             }
         } else if(is_number(ch)) {
             int flag = 0;
             if (ch == '0') {
                 arr = arr + ch;
                 ch = fgetc(fpin);
                 if (ch >= '0' && ch <= '7') {
                     while (ch >= '0' && ch <= '7') {
                         flag = 1;
                         arr = arr + ch;
                         ch = fgetc(fpin);
                     }
                 } else if (ch == 'x' || ch == 'X') {
                     flag = 2;
                     arr = arr + ch;
                     ch = fgetc(fpin);
                     while (is_number(ch) || is_letter_a_f(ch)) {
                         arr = arr + ch;
                         ch = fgetc(fpin);
                     }
                 } else if (ch == ' ' || ch == ',' || ch == ';') {
                     cout << "<" << arr << ", 0>" << endl;
                 }
                 fseek(fpin, -1L, SEEK_CUR);
                 if (flag == 1)
                     cout << "<" << arr <<", octal>" << endl;
                 else if (flag == 2)
                     cout << "<" << arr << ", hexadecimal>" << endl;
                } else {
                    arr = arr + ch;
                    ch = fgetc(fpin);
                    while (is_number(ch)) {
                        arr = arr + ch;
                        ch = fgetc(fpin);
                    }
                    fseek(fpin, -1L, SEEK_CUR);
                    cout << "<" << arr << ", decimal>" << endl;
                }
         } else
             switch (ch) {
                 case '+':
                 case '-':
                 case '*':
                 case '=':
                 case '/':
                     cout << "<" << ch << ", ->" << endl;
                     break;
                 case '(':
                 case ')':
                 case '[':
                 case ']':
                 case ';':
                 case '.':
                 case ',':
                 case '{':
                 case '}':
                     cout << "<" << ch << ", border>" << endl;
                     break;
                 case ':':
                 {
                     ch = fgetc(fpin);
                     if (ch == '=')
                         cout << "<" << ":=" << ", >" << endl;
                     else {
                         cout << "<" << "::" << ", border>" << endl;
                         fseek(fpin, -1L, SEEK_CUR);
                     }
                 }
                     break;
                 case'>':
                 {
                     ch = fgetc(fpin);
                     if (ch == '=')
                         cout << "<" << ">=" << ", >" << endl;
                     if (ch == '>')
                         cout << "<" << ">>" << ", ->" << endl;
                     else {
                         cout << "<" << ">" << ", ->" << endl;
                         fseek(fpin, -1L, SEEK_CUR);
                     }
                 }
                     break;
                 case'<':
                 {
                     ch = fgetc(fpin);
                     if (ch == '=')
                         cout << "<" << "<=" << ", >" << endl;
                     else if (ch == '<')
                         cout << "<" << "<<" << ", control>" << endl;
                     else if (ch == '>')
                         cout << "<" << "<>" << ", ->" << endl;
                     else {
                         cout << "<" << "<" << ", ->" << endl;
                         fseek(fpin, -1L, SEEK_CUR);
                     }
                 }
                     break;
                 default:
                     cout << "<" << ch << ", unknown>" << endl;
             }
    }
}

int main() {
    char in_fn[30];
    FILE *fpin;
    cout << "Enter input file path: ";
    for (;;) {
        cin >> in_fn;
        if ((fpin = fopen(in_fn, "r")) != NULL)
            break;
        else
            cout << "Error - No such file or directory, enter again: ";
    }
    scan(fpin);
    fclose(fpin);
    return 0;
}
