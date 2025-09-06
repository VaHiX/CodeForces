/*
 * Problem URL : https://codeforces.com/contest/977/problem/F
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
map <int,int>mp;
int main() {
		ios::sync_with_stdio(false);cin.tie(0);
	int n,i,max=0,v=-1;
	cin>>n;
	vector<int> a(n+1);
	for(i=1;i<=n;i++){
	cin>>a[i];
	int x=mp[a[i]]=mp[a[i]-1]+1;
	if(x>max){
	max=x;
	v=a[i];
	}
	}
		v=v-max+1;
	cout<<max<<"\n";
	for(i=1;i<=n;i++)
	{
		if(a[i]==v){
		cout<<i<<" ";
		v++;}
	}

	return 0;
}