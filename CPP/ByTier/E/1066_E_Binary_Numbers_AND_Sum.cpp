/*
 * Problem URL : https://codeforces.com/contest/1066/problem/E
 * Submit Date : 2025-09-01
 */

#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 200005
using namespace std;
const int p=998244353;
int n,m,ans,pw[N],s[N];
char s1[N],s2[N];
int main(){
	scanf("%d%d%s%s",&n,&m,s1+1,s2+1);
	for (int i=pw[0]=1;i<=m;i++) pw[i]=pw[i-1]*2%p;
	for (int i=1;i<=m;i++) s[i]=s[i-1]+s2[i]-48;
	for (int i=max(1,n-m+1);i<=n;i++)
		ans=1ll*(ans+1ll*pw[n-i]*s[i+m-n]*(s1[i]-48))%p;
	return printf("%d\n",ans),0;
}

