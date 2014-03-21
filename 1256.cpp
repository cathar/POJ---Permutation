方法一：// 1256 全排列去重复.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <iostream>
using namespace std;
char str[14];
int len;
typedef struct node{
    char a;
    float seq;
}node;
node alphs[52],input[14];
int compare(const void *a,const void *b)
{
    node *x,*y;
    x = (node *) a;
    y = (node *) b;
    if(x->seq-y->seq >0) //需要注意的是，对于float类型来讲，如果差返回为正小数，则还是被当作看待，所以需要额外加判断
        return 1;
    else
        return 0;
}
void prtPerm();
int find_i_1(node curPerm[])
{
    int j;
    for(j=len-1;j>0;j--)
    {
        if(curPerm[j-1].seq<curPerm[j].seq) 
            return j-1;
    }
    return -1;
}
int find_h(node curPerm[],int i)
{
    int j;
    for(j=len-1;j>=0;j--)
    {
        if(curPerm[j].seq>curPerm[i].seq)
            return j;
    }
    return -1;
}
void swap(node *i,node *j)
{
    node *tmp;
    tmp = (node *) malloc(sizeof(node *));
    tmp->a=i->a;
    tmp->seq=i->seq;
    i->a=j->a;
    i->seq=j->seq;
    j->a=tmp->a;
    j->seq=tmp->seq;
}
int _tmain(int argc, _TCHAR* argv[])
{
    int n;
    cin>>n;
    char * lower ="abcdefghijklmnopqrstuvwxyz";
    while(n--)
    {
        memset(str,0,sizeof(str));
        memset(input,0,sizeof(input));
        cin>>str;
        len = strlen(str);
        for (int i = 0;i <26; i++)
        {
            alphs[i].a = lower[i];
            alphs[i].seq = alphs[i].a;
            //cout<<alphs[i].a<<' '<<alphs[i].seq<<endl;
        }
        for (int i = 26;i < 52; i++)
        {
            alphs[i].a = lower[i-26] - 32;
            alphs[i].seq = lower[i-26] - 0.5;
            // cout<<alphs[i].a<<' '<<alphs[i].seq<<endl; // 建立好了AaBbCc的顺序索引值数组
        }
        for (int i=0;i<len;i++)
        {
            input[i].a = str[i]; 
            if (str[i]>='a' && str[i]<='z')
                input[i].seq = alphs[str[i]-97].seq;
            else if (str[i]>='A' && str[i]<='Z')
                input[i].seq = alphs[str[i]-65+26].seq; //将输入的字符数组转化为node类型，并赋予value用于排序
            //cout<<input[i].seq<<endl;
        }
        qsort(input,len,sizeof(node),compare); //将input按照题目要求排好顺序
        for (int i=0;i<len;i++)
        {
            cout<<input[i].a;
        }
        cout<<endl;
        prtPerm();
    }
    return 0;
}
void prtPerm() //注意，需要排除重复的输出，但由于采用的是字典序，所以并没有重复的可能
{
    int j,h;
    j=find_i_1(input);
    h=find_h(input,j);
    while(j!=-1 && h!=-1)
    {
        swap(&input[j],&input[h]);
        if(j!=-1 && len-1-(j+1) >=1){ qsort(&input[j+1],len-1-j,sizeof(node),compare);}
               for (int i=0;i<len;i++)
        {
            cout<<input[i].a;
        } 
        cout<<endl;
        j=find_i_1(input);
        h=find_h(input,j);
    }
}
————————————————————————————————————————————————————————————————————
方法二、 // 1256 STL 全排列.cpp : 定义控制台应用程序的入口点。
#include "stdafx.h"
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 13
char a[MAXN + 1];
int len;
char flag[MAXN];
char s[MAXN + 1];
bool cmp(char a, char b) {
    return tolower(a) == tolower(b) ? a < b : tolower(a) < tolower(b); //这个写的非常好！！！
}
void solve(int n) {
    if (n == len) {
    puts(s);
    return;
    }
    for (int i = 0; i < len; i++) {
        if (! flag[i]) {
            flag[i] = 1; //cout<<"cur n "<<n<<" cur i "<<i<<endl;
            s[n] = a[i]; //s[]记录的是要输出的排列；回溯后，s[n]的前面就能够取到后面的a[i]，因为有i++
            solve(n + 1); //只要没到n=len 就一直递归下去
            flag[i] = 0;//cout<<"back i "<<i<<endl; 显示的是需要回溯的i，即第 i 个字符可用
                     
        while (i + 1 < len && a[i + 1] == a[i]) i++; //这里i++ 是为了避免重复，直接使得for循环结束，或者找到第一个有不同的字符位置aabccc中找到b
        }
    } // cout<<"end of for"<<endl;
}
int main() {
    int CASE;
    scanf("%d", &CASE);
    while (CASE--) {
        scanf("%s", a);
        len = strlen(a);
        sort(a, a + len, cmp);
        memset(flag, 0, sizeof(flag));
        s[len] = 0;
        solve(0);
       }
    return 0;
}
