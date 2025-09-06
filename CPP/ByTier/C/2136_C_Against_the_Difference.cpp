/*
 * Problem URL : https://codeforces.com/contest/2136/problem/C
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
const int N=2e5+2;
int T,n,a[N],f[N];
vector<int> id[N];
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(cin>>T;T--;){
		cin>>n;
		for(int i=1;i<=n;++i) id[i].clear();
		for(int i=1;i<=n;++i) cin>>a[i];
		for(int i=1;i<=n;++i){
			f[i]=f[i-1];
			id[a[i]].push_back(i);
			if(id[a[i]].size()>=a[i]) f[i]=max(f[i],f[*(id[a[i]].end()-a[i])-1]+a[i]);
		}
		cout<<f[n]<<'\n';
	}
	return 0;
}
