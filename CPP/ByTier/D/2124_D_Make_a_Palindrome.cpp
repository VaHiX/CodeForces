/*
 * Problem URL : https://codeforces.com/problemset/problem/2124/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
void work(){
	int n,k;
	cin>>n>>k;
	vector<int>a(n);
	for (int i=0; i<n; i++) cin>>a[i];
	auto b=a;
	sort(b.begin(),b.end()); 
	int x=b[k-1],cnt=0;
	vector<int>c,d;
	for (int i=0; i<n; i++){
		if (a[i]<x){
			c.push_back(a[i]);
			d.push_back(cnt);
			cnt=0;
		}
		else if (a[i]==x) cnt++;
	}
	d.push_back(cnt);
	for (int i=0; i<c.size(); i++)
	if (c[i]!=c[c.size()-i-1]){
		cout<<"no"<<endl;
		return;
	}
	int sum=0;
	for (int i=0; i<d.size(); i++)
	sum+=min(d[i],d[d.size()-i-1]);
	if (sum+c.size()<k-1) cout<<"no"<<endl;
	else cout<<"yes"<<endl;
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T=1;
	cin>>T;
	while (T--) work();
	return 0;
}
/*

*/