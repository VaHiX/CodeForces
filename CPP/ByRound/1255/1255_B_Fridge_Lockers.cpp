/*
 * Problem URL : https://codeforces.com/contest/1255/problem/B
 * Submit Date : 2025-08-27
 */

#include<bits/stdc++.h>
using namespace std;
int work(){
	int n,m,sum=0,x;scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)scanf("%d",&x),sum+=x;
	if(n<3||m<n)return puts("-1"),0;
	printf("%d\n",sum*2);
	for(int i=1;i<=n;i++)printf("%d %d\n",i,i%n+1);
	return 0;
}
int main(){
	int t;scanf("%d",&t);
	while(t--)work();
	return 0;
}