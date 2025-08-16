/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/A
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
int T,n;
set<int> s;
int main(){
	cin.tie(0)->sync_with_stdio(0);
	for(cin>>T;T--;){
		cin>>n;
		s.clear();
		for(int x;n--;){
			cin>>x;
			if(x>=0) s.insert(x);
		}
		cout<<(s.size()>1||s.size()==1&&!*s.begin()?"NO\n":"YES\n");
	}
	return 0;
}