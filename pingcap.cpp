#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define maxl 10000

struct nod;
struct link;

struct link{
nod* pos;  //该单词末端字母在字典树中对应位置
link* next,*pre;
};    //链表顺序存储不重复单词

struct nod{
nod *fa,*start,*next; //fa代表父亲节点
link *pos;     //字典树中该单词在链表中对应位置
long long num; //字典树中每个单词出现次数统计
char v;
}; //字典树查重

char str[maxl];
int len;
link *s,*t;  //定义s,t为链表超级头，超级尾
nod *p;      //定义字典树超级头

void getout(nod *k)
{
    if (k==p) return;
    getout(k->fa);
    printf("%c",k->v);
}  //递归输出答案

void add(nod* now)
{
    link *L=t->pre,*R=t,*k=new link;
    now->pos=k;
    k->pre=L;
    k->next=R;
    L->next=k;
    R->pre=k;
    k->pos=now;

} //在链表尾部插入第一次出现的单词

void del(nod *now)
{
    link* k=now->pos,*L=k->pre,*R=k->next;
    L->next=R;
    R->pre=L;
    delete k;

} //双向链表中删除重复的单词

void Init_f(nod *f,nod *now,char v)
{
        f->fa=now;
        f->v=v;
        f->num=0;
        f->start=NULL;
        f->next=NULL;
} //字典树新开节点初始化

void deal(nod* now,int k)
{
    nod *f=now->start;


    if (k==len)
    {
        now->num++;
        if (now->num==1) add(now); //第一次出现加入链表
        if (now->num==2) del(now);//第二次出现从链表中删除
        return;
    }

    while (f!=NULL && f->next!=NULL)
    {
        if (f->v==str[k]) break;
        f=f->next;
    } //字典树子节点链表存储

    if (f==NULL)
    {
        now->start=f=new nod;
        Init_f(f,now,str[k]);
        deal(f,k+1);
        return;
    } //新开节点

    if (f->v==str[k])
    {
        deal(f,k+1);
        return;
    }//已经存在的节点

    f->next=new nod;
    f=f->next;
    Init_f(f,now,str[k]);
    deal(f,k+1);
    //新开节点
}

void Initial()
{
    s=new link;
    t=new link;
    s->next=t;
    t->pre=s;
    p=new nod;
    p->num=0;
    p->start=NULL;
} //超级头超级尾初始化

int main()
{
    Initial();
    while (scanf("%s",&str)!=EOF)
    {
        len=strlen(str);
        deal(p,0);
    }//读入单词
    if (s->next!=t)
    {
        link* ans=s->next;
        getout(ans->pos);
        printf("\n");//按顺序第一个不重复单词
    } else
    {
        printf("No answer\n");//无解的可能
    }
}
