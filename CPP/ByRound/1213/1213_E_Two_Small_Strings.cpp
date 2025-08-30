/*
 * Problem URL : https://codeforces.com/contest/1213/problem/E
 * Submit Date : 2025-08-27
 */

#include<bits/stdc++.h>
using namespace std;
int main(){
	int n;
	cin>>n;
	string s,t;
	cin>>s>>t;
	string a;
	a+="abc";
	vector<string>g;
	do{
		string t;
		for(int i=1;i<=n;i++) t+=a;
		g.push_back(t);
		t=string(n,a[0])+string(n,a[1])+string(n,a[2]);
		g.push_back(t);
	}while(next_permutation(a.begin(),a.end()));
	for(auto b:g){
		if(b.find(s)>n*5&&b.find(t)>n*5){
			cout<<"YES"<<endl<<b;
			return 0;
		}
	}
	return 0;
}