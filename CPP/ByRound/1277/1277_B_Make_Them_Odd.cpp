/*
 * Problem URL : https://codeforces.com/contest/1277/problem/B
 * Submit Date : 2025-08-27
 */

#include <bits/stdc++.h>
using namespace std;
 
main(){
	int n;
	
 
	cin>>n;
	while(n--){
		int a;
		cin>>a;
		set <int> s1;
		for(int i = 0;i<a;i++){
			int aa;
			cin>>aa;
 
			while(aa%2==0){
				s1.insert(aa);
				aa=aa/2;
			}
		}
		cout<<s1.size()<<endl;
	}
}