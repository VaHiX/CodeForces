/*
 * Problem URL : https://codeforces.com/contest/1016/problem/B
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>
using namespace std;

int cnt[1005],n,m,q;
string s,t;
int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
	cin>>n>>m>>q>>s>>t;
	for (int i=0;i<=n-m;++i) 
            cnt[i+1]=cnt[i]+(s.substr(i,m)==t);
	while (q--){
		int l,r;
		cin>>l>>r;
		if (r-l+1<m) puts("0");
		else printf("%d\n", cnt[r-m+1]-cnt[l-1]);
	}
}