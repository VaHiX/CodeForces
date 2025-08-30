/*
 * Problem URL : https://codeforces.com/contest/1281/problem/B
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
using namespace std;
 
int main(){
	int t;
	cin>>t;
	while(t--){
		string a,b;
		cin>>a>>b;
		for(int i=0; i<a.size(); i++){
			int x=i;
			for(int j= a.size()-1; j>i; j--)
				if(a[j] < a[x])
					x=j;
			if(x==i)
				continue;
			swap(a[x], a[i]);
			break;
		}
		cout<< ((a<b) ? a: "---") <<'\n';
 
	}
}