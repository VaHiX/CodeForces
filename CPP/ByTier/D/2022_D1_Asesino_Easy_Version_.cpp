/*
 * Problem URL : https://codeforces.com/contest/2022/problem/D1
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long 
//#define endl '\n'
void solve(){
	int n;cin>>n;
	for(int i=1;i<n;i+=2){
		cout<<"? "<<i<<" "<<i+1<<endl;
		int x1;cin>>x1;
		cout<<"? "<<i+1<<" "<<i<<endl;
		int x2;cin>>x2;
		if(x1!=x2){
			int u;
			if(i==1) u=n;
			else u=1;  
			cout<<"? "<<i<<" "<<u<<endl;
			int y1;cin>>y1;
			cout<<"? "<<u<<" "<<i<<endl;
			int y2;cin>>y2;
			if(y1==y2) cout<<"! "<<i+1<<endl;
			else cout<<"! "<<i<<endl;
			return;
		}
	}
	cout<<"! "<<n<<endl;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}