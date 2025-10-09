/*
 * Problem URL : https://codeforces.com/contest/2021/problem/C1
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
typedef long long ll;
int t,n,m,q,a[200005],b,c[200005];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	c[0]=1;
	while(t--){
		cin>>n>>m>>q;
		bool f=1;
		for(int i=1;i<=n;i++) cin>>b,a[b]=i,c[i]=0;
		for(int j=1;j<=m;j++){
			cin>>b;
			c[a[b]]=1;
			if(!c[a[b]-1]) f=0;
		}
		if(f) cout<<"YA\n";
		else cout<<"TIDAK\n";
	}
	return 0;
}