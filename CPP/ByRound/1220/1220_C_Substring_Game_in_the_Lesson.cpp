/*
 * Problem URL : https://codeforces.com/contest/1220/problem/C
 * Submit Date : 2025-08-27
 */

#include<bits/stdc++.h>
using namespace std;

string s;
int main(){
	ios::sync_with_stdio(false);
	cin >> s;
	char mi='z'+1;
	for(auto c:s){
		if(c<=mi) cout << "Mike\n";
		else cout << "Ann\n";
		mi=min(mi,c);
	}
}