//
//  main.cpp
//  project3
//
//  Created by 彭瀚林 on 2019/12/10.
//  Copyright © 2019 penghanlin. All rights reserved.
//

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

#define NULL 0
#define MAXSIZE 30

typedef struct GrammarSymbol {
    char ch;
    int po;
    string val;
    int type;
} W;

char pre[6][6] = {
        { '>', '<', '<', '>', '<','>' },
        { '>', '>', '<', '>', '<', '>' },
        { '<', '<', '<', '=', '<', '1' },
        { '>', '>', '2', '>', '2', '>' },
        { '>', '>', '2', '>', '2', '>' },
        { '<', '<', '<', '3', '<', '=' }
};
char get_char(FILE* fp) {
    char ch;
    ch = fgetc(fp);
    return ch;
}

char get_bc(FILE* fp) {
    char ch;
    do {
        ch = get_char(fp);
    } while (ch == ' ' || ch == '\t' || ch == '\n');
    return ch;
}

void concat(char ch, char token[]) {
//    char str[2];
    int len = (int)strlen(token);
    token[len] = ch;
    token[len + 1] = '\0';
}

int is_letter(char ch) {
    int flag = 0;
    if (ch >= 'a' && ch <= 'z')
        flag = 1;
    return flag;
}

int is_number(char ch) {
    int flag = 0;
    if (ch >= '0' && ch <= '9')
        flag = 1;
    return flag;
}

int reverse(char strToken[]) {
    int code = 0, i;
    char keyWord[6][6] = {"if", "then", "else", "while", "do"};
    for (i = 0; i < 5; i++) {
        if (strcmp(strToken, keyWord[i]) == 0) {
            code = i + 1;
            break;
        }
    }
    return code;
}

int search_op(char ch) {
    int code = 0, i;
    char OP[10] = {'+', '*', '(', ')', '-', '/', '<', '>', '=', ';'};
    for (i = 0; i < 10; i++) {
        if (ch == OP[i]) {
            code = i + 1;
            break;
        }
    }
    return code;
}

char retract(FILE* fp, char ch) {
    ch = ' ';
    fseek(fp, -1L, 1);
    return ch;
}

int scan(FILE* fp, W* E, int num) {
    W w;
    char ch;
    char token[10];
    token[0] = '\0';
    ch = get_bc(fp);
    if (feof(fp))
        return 0;
    if (ch == ';') {
        printf(";");
        return 0;
    }
    if (is_letter(ch)) {
        while (is_letter(ch) || is_number(ch)) {
            concat(ch, token);
            ch = get_char(fp);
        }
        ch = retract(fp, ch);
        if (reverse(token)) {
            cout << "<" << token << ", ->" << endl;
        } else {
            cout << token;
            w.ch = 'i';
            w.po = 4;
            w.val = token;
            w.type = 0;
            E[num] = w;
        }
    } else if (ch >= '1' && ch <= '9') {
        while (is_number(ch)) {
            concat(ch, token);
            ch = get_char(fp);
        }
        ch = retract(fp, ch);
        cout << token;
        w.ch = 'i';
        w.po = 4;
        w.val = token;
        w.type = 1;
        E[num] = w;
    } else if (ch == '0') {
        ch = get_char(fp);
        if (ch >= '1' && ch <= '7') {
            while (ch >= '0' && ch <= '7') {
                concat(ch, token);
                ch = get_char(fp);
            }
            ch = retract(fp, ch);
            cout << "<2, " << token << ">" << endl;
        } else if (ch == 'x') {
            ch = get_char(fp);
            while (is_number(ch) || (ch >= 'a' && ch <= 'f')) {
                concat(ch, token);
                ch = get_char(fp);
            }
            ch = retract(fp, ch);
            cout << "<3, " << token << ">";
        } else {
            ch = retract(fp, ch);
            cout << "0";
            w.ch = 'i';
            w.po = 4;
            w.val = "0";
            w.type = 0;
            E[num] = w;
        }
    } else if (search_op(ch) != 0) {
        cout << ch;
        int po = search_op(ch) - 1;
        w.ch = ch;
        w.po = po;
        E[num] = w;
    } else {
        cout << "Error: Input: error input" << endl;
    }
    return 1;
}

bool check_vt(char ch) {
    bool flag = false;
    int i;
    char Vt[6] = {'+', '*', '(', ')', 'i', '#'};
    for (i = 0; i < 6; i++) {
        if (ch == Vt[i]) {
            flag = true;
        }
    }
    return flag;
}


W statute(W* S, int s, int e) {
    W N;
    if (S[s].ch == 'i' && s == e) {
        N.ch = 'F';
        N.val = S[s].val;
        N.type = S[s].type;
    } else if (S[s].ch == '(' && !(check_vt(S[s + 1].ch)) && S[e].ch == ')') {
        if (S[s + 1].type == 1) {
            N.ch = 'F';
            N.val = S[s + 1].val;
            N.type = S[s + 1].type;
        } else {
            N.ch = 'F';
            N.val = '('+ S[s + 1].val + ')';
            N.type = S[s + 1].type;
        }
    } else if (!(check_vt(S[s].ch)) && S[s + 1].ch == '+' && !(check_vt(S[e].ch))) {
        N.ch = 'E';
        if (S[s].type == 1 && S[e].type == 1) {
            N.type = 1;
            int v = atoi(S[s].val.data()) + atoi(S[e].val.data());
            char l[30];
            sprintf(l, "%d", v);
            N.val = l;
        } else {
            N.type = 0;
            N.val = S[s].val + S[s + 1].ch + S[e].val;
        }
    } else if ((s != e) && !(check_vt(S[s].ch)) && S[s + 1].ch == '*' && !(check_vt(S[e].ch))) {
        N.ch = 'T';
        if (S[s].type == 1 && S[e].type == 1) {
            N.type = 1;
            int v = atoi(S[s].val.data()) * atoi(S[e].val.data());
            char l[30];
            sprintf(l, "%d", v);
            N.val = l;
        } else {
            N.type = 0;
            N.val = S[s].val + S[s + 1].ch + S[e].val;
        }
    } else if(S[s].ch == 'T' && s == e){
        N.ch = 'E';
        N.val = S[s].val;
        N.type = S[s].type;
    } else {
        N.ch = '#';
    }
    N.po = 4;
    return N;
}

void error(char errnum) {
    string message;
    switch (errnum) {
        case '1':
            message = "Syntax: Illegal token '('";
            break;
        case '2':
            message = "Grammar: Missing operator";
            break;
        case '3':
            message = "Syntax: Illegal token ')'";
            break;
        case '4':
            message = "Grammar: Missing expression";
            break;
        default:
            break;
    }
    cout << "Error: " << message << endl;
}

int syntax(W* E, int num) {
    W S[MAXSIZE];
    int k = 1, i = 0, j;
    W border, A, Q;
    border.ch = '#';
    border.po = 5;
    E[num] = border;
    S[k] = border;
    do {
        A = E[i++];
        if (check_vt(S[k].ch))
            j = k;
        else
            j = k - 1;
        while (pre[S[j].po][A.po] == '>') {
            do {
                Q = S[j];
                if (check_vt(S[j - 1].ch))
                    j = j - 1;
                else
                    j = j - 2;
            } while (pre[S[j].po][Q.po] != '<');
            W N = statute(S, j + 1, k);
            if (N.ch == '#') {
                error('4');
                return 0;
            }
            k = j + 1;
            S[k] = N;
        }
        if (pre[S[j].po][A.po] == '<' || pre[S[j].po][A.po] == '=') {
            k++;
            S[k] = A;
        } else {
            error(pre[S[j].po][A.po]);
            return 0;
        }
    } while (A.ch != '#');
    if (A.ch == '#') {
        cout << "Success, result: " << S[k - 1].val.data() << endl;
        return 0;
    }
    return 0;
}

int main() {
    FILE* fpin;
    char input[30];
    cout << "Enter the expression file: ";
    for (;;) {
        cin >> input;
        if ((fpin = fopen(input, "r")) == NULL) {
            cout << "Error: No such file or directory" << endl;
            exit(0);
        } else
            break;
    }
    int n = 0;
    cout << "Result: " << endl;
    cout << endl;
    while (!feof(fpin)) {
        int num = 0;
        W E[MAXSIZE];
        get_bc(fpin);
        if (!feof(fpin)) {
            n++;
            fseek(fpin, -1L, 1);
            printf("(%d)", n);
        }
        else {
            break;
        }
        while (1) {
            int flag = scan(fpin, E,num);
            if (flag == 0)
                break;
            num++;
        }
        cout << endl;
        cout << "Outputs: " << endl;
        syntax(E,num);
        cout << endl;
    }
    fclose(fpin);
    fpin = NULL;
}
