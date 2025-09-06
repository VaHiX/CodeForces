/*
 * Problem URL : https://codeforces.com/contest/1118/problem/E
 * Submit Date : 2025-08-29
 */

#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n,k;cin>>n>>k;
	if(n>1ll*k*(k-1)) return puts("No"),0;
	puts("Yes");int cur=0;
	for(int i=0;i<n;i++) printf("%d %d\n",i%k+1,((cur+=(i%k==0))+i%k)%k+1);
}