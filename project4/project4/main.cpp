//
//  main.cpp
//  project4
//
//  Created by 彭瀚林 on 2019/12/10.
//  Copyright © 2019 penghanlin. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>
char input[200],mech[10];        /*input,´æ·Å×îÏÈÊäÈëµÄ×Ö·û´®£¬ÔÚÊäÈëµÄ¹ý³ÌÖÐ£¬¾Í½øÐÐÁËÔ¤´¦Àí*/
char ech[100][10];
char echattr[100][10];
char nch[10];
char Fplace[10],Eplace[10],Tplace[10],TTplace[10],EEplace[10],E1place[10],E2place[10],idplace[10],Splace[10],Snext[10],Ctrue[10],Cfalse[10],Sbegin[10];
char S1next[10],S2next[10];
char Fcode[50],Ecode[50],Tcode[50],TTcode[50],EEcode[50],E1code[50],E2code[50],idcode[50],Scode[50],Ccode[50];
int temp=1;
int label=0;
int stack;
int nuattr;
int flag=0;
char attr[10];
int number=0;
int now;
void init(char *ch)
{
    char newc[10];
    newc[0]=NULL;
    strcpy(ch,newc);
}
int S();
int SS();
int E();
int C();
int CC();
int T();
int TT();
int EE();
int F();
int scan();
void newtemp(char *ch)
{
    sprintf(attr,"%d",temp);
    strcpy(ch,"t");
    strcat(ch,attr);
    temp++;
}
void newlabel(char *ch)
{
    sprintf(attr,"%d",label);
    strcpy(ch,"L");
    strcat(ch,attr);
    label++;
}

int scan(char *ch)
{
    char *k1="if";
    char *k2="then";
    char *k3="else";
    char *k4="while";
    char *k5="do";
    char *k6="+";
    char *k7="-";
    char *k8="*";
    char *k9="/";
    char *k10=">";
    char *k11="<";
    char *k12="=";
    char *k13="(";
    char *k14=")";
    int judge;
    int i=1,k;
    int answer=0;
    if(strcmp(ch,k1)==0)
    {
        strcpy(attr,ch);
        return 1;
    }
    if(strcmp(ch,k2)==0)
    {
        strcpy(attr,ch);
        return 2;
    }
    if(strcmp(ch,k3)==0)
    {
        strcpy(attr,ch);
        return 3;
    }
    if(strcmp(ch,k4)==0)
    {
        strcpy(attr,ch);
        return 4;
    }
    if(strcmp(ch,k5)==0)
    {
        strcpy(attr,ch);
        return 5;
    }
    else
    {
        if(strcmp(ch,k6)==0)
        {
            strcpy(attr,ch);
            return 6;
        }
        if(strcmp(ch,k7)==0)
        {
            strcpy(attr,ch);
            return 7;
        }
        if(strcmp(ch,k8)==0)
        {
            strcpy(attr,ch);
            return 8;
        }
        if(strcmp(ch,k9)==0)
        {
           strcpy(attr,ch);
           return 9;
        }
        if(strcmp(ch,k10)==0)
        {
            strcpy(attr,ch);
            return 10;
        }
        if(strcmp(ch,k11)==0)
        {
            strcpy(attr,ch);
            return 11;
        }
        if(strcmp(ch,k12)==0)
        {
            strcpy(attr,ch);
            return 12;
        }
        if(strcmp(ch,k13)==0)
        {
            strcpy(attr,ch);
            return 13;
        }
        if(strcmp(ch,k14)==0)
        {
            strcpy(attr,ch);
            return 14;
        }
        else
        {
            if(isdigit(ch[0])==2)                  /* ÒÉ */
            {
                if(strlen(ch)>1)
                {
                    if(strlen(ch)>2)
                    {
                        if(ch[1]=='x')
                        {
                            i=2;
                            judge=1;
                            while(ch[i]!=NULL)
                            {
                                if(isxdigit(ch[i])==0)
                                {
                                    judge=0;
                                }
                                i++;
                            }
                            if(judge==1)
                            {
                                for(i=2;i<strlen(ch);i++)
                                {
                                    if(ch[i]>='0'&&ch[i]<='9')
                                    {
                                        k=ch[i]-'0';
                                    }
                                    else
                                    {
                                        k=ch[i]-'W';
                                    }
                                    answer=answer+k*pow(16,strlen(ch)-i-1);
                                }
                                    nuattr=answer;
                                    return 16;
                            }
                            else
                            {
                                strcpy(attr,ch);
                                return 18;
                            }
                        }
                    }
                    if(ch[0]=='0')
                    {
                        i=1;
                        judge=1;
                        while(ch[i]!=NULL)
                        {
                            if(isxdigit(ch[i])==0)
                            {
                                judge=0;
                            }
                            i++;
                        }
                        if(judge==1)
                        {
                            for(i=0;i<strlen(ch);i++)
                            {
                                k=ch[i]-'0';
                                answer=answer+k*pow(8,strlen(ch)-i-1);
                            }
                            nuattr=answer;
                            return 17;
                        }
                    }
                    else
                    {
                        i=1;
                        judge=1;
                        while(ch[i]!=NULL)
                        {
                            if(isxdigit(ch[i])==0)
                            {
                                judge=0;
                            }
                            i++;
                        }
                        if(judge==1)
                        {
                            for(i=0;i<strlen(ch);i++)
                            {
                                k=ch[i]-'0';
                                answer=answer+k*pow(10,strlen(ch)-i-1);
                            }
                            nuattr=answer;
                            return 15;
                        }
                    }
                }
                if(strlen(ch)==1)
                {
                    for(i=0;i<strlen(ch);i++)
                            {
                                k=ch[i]-'0';
                                answer=answer+k*pow(10,strlen(ch)-i-1);
                            }
                            nuattr=answer;
                            return 15;

                }
            }
            else
            {
                strcpy(attr,ch);
                return 18;
            }
        }
    }
    return 0;
}
int S()
{
    int c,s1,ss,e;
    if(strcmp(ech[now],"if")==0)
    {
        if(label==0)
        {
            newlabel(Snext);
            newlabel(Sbegin);
            printf("\n%s:\n",Sbegin);
        }
        else
        {
            strcpy(Sbegin,Ctrue);
        }

        newlabel(Ctrue);
        strcpy(Cfalse,Snext);



        now++;
        c=C();
        if(c==0)
        {
            return 0;
        }
        if(strcmp(ech[now],"then")==0)
        {
            now++;
            if(strcmp(ech[now],"i")==0||strcmp(ech[now],"if")==0)
            {
                printf("\n%s:\n",Ctrue);
            }
            s1=S();
            if(s1==0)
            {
                return 0;
            }
            ss=SS();
            if(ss==0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    if(strcmp(ech[now],"i")==0)
    {
        strcpy(idplace,echattr[now]);
        now++;
        if(strcmp(ech[now],"=")==0)
        {
            now++;
            e=E();
            strcpy(Scode,Ecode);                                 /*aaaaaaaaaaaaaaa*/
            printf("   %s=%s\n",idplace,Eplace);
            printf("   goto%s",Sbegin);
            if(e==0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
        return 0;
    }
    if(strcmp(ech[now],"while")==0)
    {
        now++;

        if(label==0)
        {
            newlabel(Snext);
            newlabel(Sbegin);
        }
        else
        {
            strcpy(Sbegin,Ctrue);
        }
        newlabel(Ctrue);
        strcpy(Cfalse,Snext);
        strcpy(S1next,Sbegin);

        printf("\n%s:\n",Sbegin);

        c=C();



        if(c==0)
        {
            return 0;
        }
        if(strcmp(ech[now],"do")==0)
        {
            now++;

            if(strcmp(ech[now],"while")!=0)
            {
                printf("\n%s:\n",Ctrue);
            }
            strcpy(Snext,S1next);
            s1=S();



            if(s1==0)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}
int SS()
{
    int s;
    if(strcmp(ech[now],"else")==0)
    {
        now++;
        s=S();
        if(s==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(strcmp(ech[now],"#")==0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int C()
{
    int cc,e;
    e=E();
    strcpy(E1place,Eplace);           /*aaaaaaaaaaaaaa*/
    strcpy(E1code,Ecode);
    if(e==0)
    {
        return 0;
    }
    cc=CC();
    if(cc==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int CC()
{
    int e;
    if(strcmp(ech[now],">")==0)
    {
        now++;
        e=E();
        strcpy(E2place,Eplace);           /*aaaaaaaaaaaaaa*/
        strcpy(E2code,Ecode);
        printf("   if %s>%s goto %s \n   goto %s",E1place,E2place,Ctrue,Cfalse);
        if(e==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(strcmp(ech[now],"<")==0)
    {
        now++;
        e=E();
        strcpy(E2place,Eplace);           /*aaaaaaaaaaaaaa*/
        strcpy(E2code,Ecode);
        printf("   if %s<%s goto %s \n   goto %s",E1place,E2place,Ctrue,Cfalse);
        if(e==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(strcmp(ech[now],"=")==0)
    {
        now++;
        e=E();
        strcpy(E2place,Eplace);           /*aaaaaaaaaaaaaa*/
        strcpy(E2code,Ecode);
        printf("   if %s=%s goto %s \n   goto %s",E1place,E2place,Ctrue,Cfalse);
        if(e==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
int E()
{
    int t,ee;
    t=T();
    strcpy(Eplace,Tplace);                /*aaaaaaaaaaaa*/
    strcpy(Ecode,Tcode);
    if(t==0)
    {
        return 0;
    }
    ee=EE();
    if(ee==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int T()
{
    int f,tt;
    f=F();
    strcpy(Tplace,Fplace);                /*aaaaaaaaaaaa*/
    strcpy(Tcode,Fcode);
    if(f==0)
    {
        return 0;
    }
    tt=TT();
    if(tt==0)
    {
        return 0;
    }
    else
    {
        return 1;
    }

}
int TT()
{
    int f,tt;
    if(strcmp(ech[now],"*")==0)
    {
        strcpy(TTplace,Tplace);
        strcpy(TTcode,Tcode);
        newtemp(Tplace);                            /*aaaaaaaaaaaa*/
        now++;
        f=F();
        strcpy(Tcode,TTcode);                       /*aaaaaaaaaaaa*/
        strcat(Tcode,Fcode);
        printf("   %s=%s*%s\n",Tplace,TTplace,Fplace);
        if(f==0)
        {
            return 0;
        }
        tt=TT();
        if(tt==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    if(strcmp(ech[now],"/")==0)
    {
        strcpy(TTplace,Tplace);
        strcpy(TTcode,Tcode);
        newtemp(Tplace);                            /*aaaaaaaaaaaa*/
        now++;
        f=F();
        strcpy(Tcode,TTcode);                       /*aaaaaaaaaaaa*/
        strcat(Tcode,Fcode);
        printf("   %s=%s/%s\n",Tplace,TTplace,Fplace);
        if(f==0)
        {
            return 0;
        }
        tt=TT();
        if(tt==0)
        {
            return 0;
        }
        else
        {

            return 1;
        }
    }
    else
    {
        return 1;
    }
}
int EE()
{
    int t,ee;
    if(strcmp(ech[now],"+")==0)
    {
        strcpy(EEplace,Eplace);
        strcpy(EEcode,Ecode);
        newtemp(Eplace);                            /*aaaaaaaaaaaa*/
        now++;
        t=T();
        strcpy(Ecode,EEcode);                       /*aaaaaaaaaaaa*/
        strcat(Ecode,Tcode);
        printf("   %s=%s+%s\n",Eplace,EEplace,Tplace);
        if(t==0)
        {
            return 0;
        }
        ee=EE();
        if(ee==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    if(strcmp(ech[now],"-")==0)
    {
        strcpy(EEplace,Eplace);
        strcpy(EEcode,Ecode);
        newtemp(Eplace);                            /*aaaaaaaaaaaa*/
        now++;
        t=T();
        strcpy(Ecode,EEcode);                       /*aaaaaaaaaaaa*/
        strcat(Ecode,Tcode);
        printf("   %s=%s-%s\n",Eplace,EEplace,Tplace);
        if(t==0)
        {
            return 0;
        }
        ee=EE();
        if(ee==0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return 1;
    }
}
int F()
{
    int e=0;
    if(strcmp(ech[now],"(")==0)
    {
        now++;
        e=E();
        strcpy(Fplace,Eplace);                 /*aaaaaaaaaaaa*/
        strcpy(Fcode,Ecode);
        if(e==0)
        {
            return 0;
        }
        if(strcmp(ech[now],")")==0)
        {
            now++;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    if(strcmp(ech[now],"i")==0)
    {
        strcpy(Fplace,echattr[now]);             /*aaaaaaaaaaaa*/
        strcpy(Fcode,"");
        now++;
        return 1;
    }
    if(strcmp(ech[now],"int8")==0)
    {
        strcpy(Fplace,echattr[now]);            /*aaaaaaaaaaaa*/
        strcpy(Fcode,"");
        now++;
        return 1;
    }
    if(strcmp(ech[now],"int10")==0)
    {
        strcpy(Fplace,echattr[now]);            /*aaaaaaaaaaaa*/
        strcpy(Fcode,"");
        now++;
        return 1;
    }
    if(strcmp(ech[now],"int16")==0)
    {
        strcpy(Fplace,echattr[now]);            /*aaaaaaaaaaaa*/
        strcpy(Fcode,"");
        now++;
        return 1;
    }

    else
    {
        return 0;
    }
}

int main()
{
    int i=0,j=0,t;
    char c;
    char c1[2];
    c1[1]='\0';
    printf("Please input the String end with #:\n");    /*ÒÔ#´ú±í½áÊø*/
    do
    {
        c=getchar();
        if(c==' ')
        {
            if(i==0)
            {
                while(c==' ')
                {
                    c=getchar();
                }
                input[i]=c;
                i++;
            }
            else
            {
                while(c==' ')
                {
                    c=getchar();
                }
                input[i]=' ';
                i++;
                input[i]=c;
                i++;
            }
        }
        else
        {
            input[i]=c;
            i++;
        }
    }while(c!='#');                                   /*ÊäÈë×Ö·û´®£¬ÊäÈëµÄ¹ý³ÌÖÐ½øÐÐÔ¤´¦Àí£¬È¥µô¶àÓàµÄ¿Õ¸ñ*/
    i=0;
    while(input[i]!='#')
    {
        c1[0]=input[i];
        if(c1[0]=='+'||c1[0]=='-'||c1[0]=='*'||c1[0]=='/'||c1[0]=='>'||c1[0]=='<'||c1[0]=='='||c1[0]=='('||c1[0]==')')
        {
            if(strlen(mech)!=0)
            {
                t=scan(mech);
                if(t==15)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int10");
                }
                if(t==16)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int16");
                }
                if(t==17)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int8");
                }
                if(t==18)
                {
                    strcpy(echattr[j],attr);
                    strcpy(mech,"i");
                }
                strcpy(ech[j],mech);
                strcpy(echattr[j],attr);
                j++;
                init(mech);
                strcat(mech,c1);
                t=scan(mech);
                if(t==15)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int10");
                }
                if(t==16)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int16");
                }
                if(t==17)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int8");
                }
                if(t==18)
                {
                    strcpy(echattr[j],attr);
                    strcpy(mech,"i");
                }
                strcpy(ech[j],mech);
                strcpy(echattr[j],attr);
                j++;
                init(mech);
            }
            else
            {
                strcat(mech,c1);
                t=scan(mech);
                if(t==15)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int10");
                }
                if(t==16)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int16");
                }
                if(t==17)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int8");
                }
                if(t==18)
                {
                    strcpy(echattr[j],attr);
                    strcpy(mech,"i");
                }
                strcpy(ech[j],mech);
                strcpy(echattr[j],attr);
                j++;
                init(mech);
            }
            i++;
            continue;
        }
        if(c1[0]==' ')
        {
            if(strlen(mech)!=0)
            {
                t=scan(mech);
                if(t==15)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int10");
                }
                if(t==16)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int16");
                }
                if(t==17)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int8");
                }
                if(t==18)
                {
                    strcpy(echattr[j],attr);
                    strcpy(mech,"i");
                }
                strcpy(ech[j],mech);
                strcpy(echattr[j],attr);
                j++;
                init(mech);
            }
        }
        else
        {
            strcat(mech,c1);
        }
        i++;
    }
    if(strlen(mech)!=0)
    {
        t=scan(mech);
                if(t==15)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int10");
                }
                if(t==16)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int16");
                }
                if(t==17)
                {
                    sprintf(attr,"%d",nuattr);
                    strcpy(echattr[j],attr);
                    strcpy(mech,"int8");
                }
                if(t==18)
                {
                    strcpy(echattr[j],attr);
                    strcpy(mech,"i");
                }
                strcpy(ech[j],mech);
                strcpy(echattr[j],attr);
                j++;
    }
    strcpy(ech[j],"#");
    number=j+1;
    now=0;
    j=S();
    printf("\nL0:\t//  S.next");

    if(j==1)
    {
        printf("\ntrue\n");
    }
    else
    {
        printf("\nfalse\n");
    }
    j=0;
//    getch();
    return 0;
}
