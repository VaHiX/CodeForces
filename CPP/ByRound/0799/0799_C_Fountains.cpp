/*
 * Problem URL : https://codeforces.com/contest/799/problem/C
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
#define N 100010
using namespace std;
int C[N],D[N],n,c,d,ans=0,b,p,ret;
char s[5];
void add(int C[],int x,int d){for(;x<=100000;x+=x&-x)C[x]=max(C[x],d);}
int query(int C[],int x){int y=-1e9;for(;x;x-=x&-x)y=max(y,C[x]);return y;}
int main()
{
	scanf("%d%d%d",&n,&c,&d);
	memset(C,128,sizeof(C));
	memset(D,128,sizeof(D));
	for (int i=0;i<n;i++){
		scanf("%d%d%s",&b,&p,s);
		if (s[0]=='C'){
			if(p>c)continue;
			ret=max(query(C,c-p),query(D,d));
			add(C,p,b);
		}else{
			if(p>d)continue;
			ret=max(query(C,c),query(D,d-p));
			add(D,p,b);
		}
		ans=max(ans,ret+b);
	}
	printf("%d",ans);
}
	