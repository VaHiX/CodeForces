/*
 * Problem URL : https://codeforces.com/contest/2014/problem/H
 * Submit Date : 2025-09-12
 */

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int T,n,m;
unsigned long long s[N],v[1000005];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	mt19937 rnd(time(0));
	srand(time(0));
	cin>>T;
	for(int i=0;i<=1000000;i++)
		v[i]=rnd();
	while(T--){
		cin>>n>>m;
		for(int i=1,x;i<=n;i++)
			cin>>x,s[i]=s[i-1]^v[x];
		for(int l,r,i=1;i<=m;i++){
			cin>>l>>r;
			if(s[r]==s[l-1])
				puts("YES");
			else
				puts("NO");
		}
	}
	return 0;
}