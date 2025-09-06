/*
 * Problem URL : https://codeforces.com/contest/896/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
#define LL long long
int n,q;
LL k,f[55]={75};
string str="What are you doing at the end of the world? Are you busy? Will you save us?";//75
string fi="What are you doing while sending \"",se="\"? Are you busy? Will you send \"",ed="\"?";//34 32 2
char calc(int n,LL k)
{
	if(n<53&&k>f[n])return '.';
	if(n==0)return str[k-1];
	if(k<=34)return fi[k-1];
	if(n>=54||k<=f[n-1]+34)return calc(n-1,k-34);
	if(k<=f[n-1]+66)return se[k-f[n-1]-35];
	if(k>=f[n]-1)return ed[1-(f[n]-k)];
	return calc(n-1,k-f[n-1]-66);
}
int main()
{
	for(int i=1;i<55;i++)f[i]=f[i-1]*2+68;
	for(cin>>q;q--;){cin>>n>>k;putchar(calc(n,k));}
	return 0;
}