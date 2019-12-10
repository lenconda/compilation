//
//  main.cpp
//  project2
//
//  Created by 彭瀚林 on 2019/12/10.
//  Copyright © 2019 penghanlin. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

struct grammar {
    char Vn[20];
    char Vt[20];
    char S;
    string P[20];
};

int m = 0, n = 0;

char get_bc(FILE* fpi) {
    char ch;
    do {
        ch = fgetc(fpi);
    } while (ch == ' ');
    return ch;
}

void scan_p(FILE* fpi, struct grammar *gp) {
    char ch;
    string str;
    if (feof(fpi))
        return;
    ch = get_bc(fpi);
    if (ch >= 'A' && ch <= 'Z') {
        str += ch;
        gp->Vn[m] = ch;
        m++;
        ch = get_bc(fpi);
        if (ch == '-') {
            str += ch;
            ch = get_bc(fpi);
            if (ch == '>') {
                str += ch;
                while (1) {
                    ch = get_bc(fpi);
                    if (ch == '\n' || ch == ';')
                        break;
                    str += ch;
                    if (ch >= 'a' && ch <= 'z') {
                        int num;
                        for (num = 0; num < n; num++) {
                            if (gp->Vt[num] == ch)
                                break;
                        }
                        if (num == n) {
                            gp->Vt[n] = ch;
                            n++;
                        }
                    }
                }
            }
        }
        gp->P[m - 1] += str;
    }
}


string strsplit(string strTok, unsigned long pos) {
    string str;
    size_t position;
    position = strTok.find("|", pos);
    if (position != string::npos) {
        str = strTok.substr(pos, position - pos);
    } else {
        str = strTok.substr(pos, strTok.size() - pos);
    }
    return str;
}

char get_word(char *p) {
    char ch, word[] = {'A', 'B', 'C', 'D', 'E', 'F',
        'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
        'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z'};
    int w,x;
    for (w = 0; w < 26; w++) {
        ch = word[w];
        for (x = 0; x < m; x++) {
            if (ch == p[x]) {
                break;
            }
        }
        if (x == m) break;
    }
    return ch;
}

bool check_word(char ch, string Vn) {
    int i;
    bool flag = true;
    for (i = 0; i < Vn.size(); i++) {
        if (ch == Vn[i])
            flag = false;
    }
    return flag;
}

void simplify(struct grammar *gp) {
    string str;
    int sVn[20];
    sVn[0] = 0;
    str.insert(0, 1, gp->Vn[0]);
    bool flag[20];
    flag[0] = false;
    char ch;
    int i, j, k, l, o;
    for (i = 0; i < str.size(); i++) {
        for (j = 3; j < gp->P[sVn[i]].size(); j++) {
            for (k = 0; k < m;k++) {
                if (gp->P[sVn[i]][j] < 'A' || gp->P[sVn[i]][j] > 'Z')
                    break;
                if (gp->P[sVn[i]][j] == gp->Vn[k]) {
                    flag[k] = false;
                    if (check_word(gp->Vn[k], str)) {
                        int e = (int)str.size();
                        sVn[e] = k;
                        str.insert(str.size(), 1, gp->Vn[k]);
                    }
                    break;
                }
            }
        }
    }
    for (l = 0; l < m; l++) {
        char ch;
        if (flag[l]) {
            gp->Vn[l] = ' ';
            for (o = l + 1; o < m; o++) {
                ch = gp->Vn[o - 1];
                gp->Vn[o - 1] = gp->Vn[o];
                gp->Vn[o] = ch;
                gp->P[o - 1].clear();
                gp->P[o - 1].swap(gp->P[o]);
            }
            m--;
        }
    }
}

void remove_left_recursion(struct grammar *gp) {
    int i, j, num_i, num_j;
    unsigned long ipos, jpos;
    char ch_i, ch_j;
    for (i = 1; i < m + 1; i++) {
        bool repeat = true;
        num_i = 0;
        ipos = 3;
        string str_i[20], restr_i[20], ex = "a";
        ch_i = gp->Vn[i - 1];
        
        while (ipos != gp->P[i - 1].size() + 1) {
            str_i[num_i] = strsplit(gp->P[i - 1], ipos);
            restr_i[num_i] = str_i[num_i];
            ipos = ipos + str_i[num_i].size() + 1;
            num_i++;
        }
        
        for (j = 1; j <= i - 1; j++) {
            if (!repeat) {
                num_i = 0;
                ipos = 3;
                
                while (ipos != gp->P[i - 1].size() + 1) {
                    str_i[num_i] = strsplit(gp->P[i - 1], ipos);
                    restr_i[num_i] = str_i[num_i];
                    ipos = ipos + str_i[num_i].size() + 1;
                    num_i++;
                }
            }
            repeat = true;
            string str_j[20];
            int l;
            jpos = 3;
            num_j = 0;
            ch_j = gp->Vn[j - 1];

            while (jpos != gp->P[j - 1].size() + 1) {
                str_j[num_j] = strsplit(gp->P[j - 1], jpos);
                jpos = jpos + str_j[num_j].size() + 1;
                num_j++;
            }
            for (l = 0; l < num_i; l++) {
                string change;
                ex[0] = ch_j;
                size_t pos = restr_i[l].find(ex);
                if (pos == string::npos) { continue; }
                else if (pos == 0) {
                    repeat = false;
                    string s = str_i[l].substr(1, str_i[l].size() - 1);
                    str_i[l].swap(change);
                    int link = 0;
                    while (1) {
                        if (link == num_j) break;
                        str_j[link] += s;
                        if (link == num_j - 1) str_i[l] += str_j[link];
                        else str_i[l] = str_i[l] + str_j[link] + "|";
                        link++;
                    }
                } else if (pos == str_i[l].size() - 1) {
                    repeat = false;
                    string s = str_i[l].substr(0, str_i[l].size() - 1);
                    str_i[l].swap(change);
                    int link = 0;
                    while (1) {
                        if (link == num_j) break;
                        str_j[link] = s + str_j[link];
                        if (link == num_j - 1) str_i[l] += str_j[link];
                        else str_i[l] = str_i[l] + str_j[link] + "|";
                        link++;
                    }
                } else {
                    repeat = false;//
                    string s1 = str_i[l].substr(0, pos - 1);
                    string s2 = str_i[l].substr(pos + 1, str_i[l].size() - pos - 1);
                    str_i[l].swap(change);
                    int link = 0;
                    while (1) {
                        if (link == num_j) break;
                        str_j[link] = s1 + str_j[link] + s2;
                        if (link == num_j - 1) str_i[l] += str_j[link];
                        else str_i[l] = str_i[l] + str_j[link] + "|";
                        link++;
                    }
                }
            }
            string stri = "->";
            stri.insert(0, 1, ch_i);
            int index = 0;
            while (1) {
                if (index == num_i) break;
                if (index == num_i - 1) stri = stri + str_i[index];
                else stri = stri + str_i[index] + "|";
                index++;
            }
            gp->P[i - 1] = stri;
        }

        string splitstr[30], resplitstr[30];
        int s = 0, ps = 3, h = 0;
        while (1) {
            splitstr[s] = strsplit(gp->P[i - 1], ps);
            resplitstr[s] = splitstr[s];
            ps = (int)(ps + splitstr[s].size() + 1);
            if (ps == gp->P[i - 1].size() + 1) break;
            s++;
        }
        string Pi = "->", Pichange = "->";
        Pi = ch_i + Pi;
        int link = 0, flag = -1;
        bool flagpos[30];
        char newWord;
        for (; link <= s; link++) {
            size_t posi;
            posi = resplitstr[link].find(ch_i);
            if (posi == 0) {
                flag++;
                if (flag == 0) {
                    newWord = get_word(gp->Vn);
                    gp->Vn[m] = newWord;
                    Pichange = newWord + Pichange;
                    m++;
                    splitstr[link] = splitstr[link].substr(1) + newWord;
                    flagpos[link] = false;
                    gp->P[m - 1] = Pichange + splitstr[link] + "|";
                }
                if (flag > 0) {
                    splitstr[link] = splitstr[link].substr(1) + newWord;
                    flagpos[link] = false;
                    gp->P[m - 1] = gp->P[m - 1] + splitstr[link] + "|";
                }
            }
        }
        if (flag > -1) {
            gp->P[i - 1] = "->";
            gp->P[i - 1].insert(0, 1, ch_i);
            for (; h <= s; h++) {
                if (flagpos[h]) {
                    splitstr[h] += newWord;
                    gp->P[i - 1] = gp->P[i - 1] + splitstr[h] + "|";
                }
            }
            gp->P[m - 1] += "@";
            gp->P[i - 1].erase(gp->P[i - 1].size() - 1, 1);
        }
    }
    simplify(gp);
}

void str_sort(string *str, int num) {
    int i, j;
    for (i = 0; i < num; i++) {
        for (j = i + 1; j < num; j++) {
            if (str[i] > str[j])
                str[i].swap(str[j]);
        }
    }
}

void remove_left_gene(struct grammar *gp) {
    int rule_a, i, j, k, l, matchnum, oldmatchnum, resize, size;
    char ch, newWord;
    for (rule_a = 0; rule_a < m; rule_a++) {
        int bre = -1;
        int oldpo = 0;
        int num = 0, ps = 3;
        string str[30], restr[30];
        while (ps != gp->P[rule_a].size() + 1) {
            str[num] = strsplit(gp->P[rule_a], ps);
            restr[num] = str[num];
            ps = (int)(ps + str[num].size() + 1);
            num++;
        }
        str_sort(str, num);
        str_sort(restr, num);
        int ca_i;
        string Pa = "->";
        Pa.insert(0, 1, gp->Vn[rule_a]);
        for (ca_i = 0; ca_i < num; ca_i++) {
            if (ca_i == num - 1)
                Pa += str[ca_i];
            else
                Pa += str[ca_i] + "|";
        }
        gp->P[rule_a] = Pa;
        int ipo = 0;
        for (i = 0; i < num; i++,i += ipo) {
            ipo = 0;
            size = 0;
            resize = 0;
            oldmatchnum = 0;
            int i_s = (int)(str[i].size());
            for (j = 0; j < i_s; j++) {
                matchnum = 0;
                ch = str[i][j];
                int kf = num;
                for (k = i + 1; k < num && k < kf; k++) {
                    if (str[k][j] == ch) {
                        matchnum++;
                    } else {
                        break;
                    }
                }
                if (j == 0) {
                    if (matchnum == 0) break;
                    else {
                        oldmatchnum = matchnum;
                        kf = i + 1 + oldmatchnum;
                    }
                } else {
                    if (oldmatchnum != matchnum) break;
                }
            }

            if (matchnum != oldmatchnum || j == i_s) {
                bre ++;
                string match, repstr, can, newP;
                match = str[i].substr(0, j);
                newWord = get_word(gp->Vn);
                gp->Vn[m] = newWord;
                m++;
                newP = "->";
                newP.insert(0, 1, newWord);
                repstr = match + newWord;
                int renum = num;
                if (bre > 0) {
                    size = resize = 0;
                    renum = 0;
                    ps = 3;
                    while (ps != gp->P[rule_a].size() + 1) {
                        restr[renum] = strsplit(gp->P[rule_a], ps);
                        ps = (int)(ps + restr[renum].size() + 1);
                        renum++;
                    }
                }

                for (l = 0; l <= i - oldpo + oldmatchnum; l++) {
                    if (l >= i - oldpo) {
                        size += restr[l].size();
                        can = restr[l].substr(j);
                        if (can == "")
                            can = "@";
                        if (l == i - oldpo + oldmatchnum)
                            newP += can;
                        else
                            newP = newP + can + "|";
                        gp->P[m - 1] = newP;
                    } else {
                        resize += restr[l].size();
                        resize++;
                    }
                }
                gp->P[rule_a].replace(resize + 3, size + oldmatchnum, repstr);
                if (i + 1 + oldmatchnum > num) { break; }
                else
                    oldpo = ipo = oldmatchnum;
            }
        }
    }
}

int main() {
    FILE* fpin;
    FILE* fpout;
    char input[30], output[30];
    cout << "Enter input file path: ";
    for (;;) {
        cin >> input;
        if ((fpin = fopen(input, "r")) == NULL) {
            cout << "No such file or directory!" << endl;
            exit(0);
        } else
            break;
    }
    cout << "Enter output file path: ";
    cin >> output;
    struct grammar g, *gp;
    gp = &g;

    char ch;
    do {
        ch = get_bc(fpin);
    } while (ch <= 'A' || ch >= 'Z');
    gp->S = ch;
    fseek(fpin, -1L, 1);

    while (!feof(fpin)) {
        scan_p(fpin,gp);
    }
    fclose(fpin);
    fpin = NULL;
    remove_left_recursion(gp);
    remove_left_gene(gp);
    if ((fpout = fopen(output, "w")) == NULL) {
        cout << "File can not open!" << endl;
        exit(0);
    }
    int i;
    for (i = 0; i < m; i++) {
        fputs(gp->P[i].data(), fpout);
        fputs("\n", fpout);
    }
    fclose(fpout);
    fpout = NULL;
}
