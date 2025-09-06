/*
 * Problem URL : https://codeforces.com/contest/1053/problem/A
 * Submit Date : 2025-09-02
 */

#include<iostream>
#include<stdio.h>
#include<ctype.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=0; char ch=getchar();
	while(!isdigit(ch)) f|=(ch==45),ch=getchar();
	while(isdigit(ch)) x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
	return f?-x:x;
}
int n,m,k;
signed main(){
	n=read(),m=read(),k=read();
	if((n*m*2)%k) return puts("NO")&0;
	puts("YES");
	int x=n*2,y=m;
	for(int i=2;i*i<=k;++i){
		while(k%i==0){
			k/=i;
			if(x%i==0) x/=i;
			else y/=i;
		}
	}
	if(x%k==0) x/=k;
	else y/=k;
	if(x>n) x/=2,y*=2;
	printf("0 0\n%lld 0\n0 %lld",x,y);
	return 0;
}
