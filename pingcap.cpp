#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define maxl 10000

struct nod;
struct link;

struct link{
nod* pos;  //�õ���ĩ����ĸ���ֵ����ж�Ӧλ��
link* next,*pre;
};    //����˳��洢���ظ�����

struct nod{
nod *fa,*start,*next; //fa�����׽ڵ�
link *pos;     //�ֵ����иõ����������ж�Ӧλ��
long long num; //�ֵ�����ÿ�����ʳ��ִ���ͳ��
char v;
}; //�ֵ�������

char str[maxl];
int len;
link *s,*t;  //����s,tΪ������ͷ������β
nod *p;      //�����ֵ�������ͷ

void getout(nod *k)
{
    if (k==p) return;
    getout(k->fa);
    printf("%c",k->v);
}  //�ݹ������

void add(nod* now)
{
    link *L=t->pre,*R=t,*k=new link;
    now->pos=k;
    k->pre=L;
    k->next=R;
    L->next=k;
    R->pre=k;
    k->pos=now;

} //������β�������һ�γ��ֵĵ���

void del(nod *now)
{
    link* k=now->pos,*L=k->pre,*R=k->next;
    L->next=R;
    R->pre=L;
    delete k;

} //˫��������ɾ���ظ��ĵ���

void Init_f(nod *f,nod *now,char v)
{
        f->fa=now;
        f->v=v;
        f->num=0;
        f->start=NULL;
        f->next=NULL;
} //�ֵ����¿��ڵ��ʼ��

void deal(nod* now,int k)
{
    nod *f=now->start;


    if (k==len)
    {
        now->num++;
        if (now->num==1) add(now); //��һ�γ��ּ�������
        if (now->num==2) del(now);//�ڶ��γ��ִ�������ɾ��
        return;
    }

    while (f!=NULL && f->next!=NULL)
    {
        if (f->v==str[k]) break;
        f=f->next;
    } //�ֵ����ӽڵ�����洢

    if (f==NULL)
    {
        now->start=f=new nod;
        Init_f(f,now,str[k]);
        deal(f,k+1);
        return;
    } //�¿��ڵ�

    if (f->v==str[k])
    {
        deal(f,k+1);
        return;
    }//�Ѿ����ڵĽڵ�

    f->next=new nod;
    f=f->next;
    Init_f(f,now,str[k]);
    deal(f,k+1);
    //�¿��ڵ�
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
} //����ͷ����β��ʼ��

int main()
{
    Initial();
    while (scanf("%s",&str)!=EOF)
    {
        len=strlen(str);
        deal(p,0);
    }//���뵥��
    if (s->next!=t)
    {
        link* ans=s->next;
        getout(ans->pos);
        printf("\n");//��˳���һ�����ظ�����
    } else
    {
        printf("No answer\n");//�޽�Ŀ���
    }
}
