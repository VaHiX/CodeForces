/*
 * Problem URL : https://codeforces.com/contest/872/problem/A
 * Submit Date : 2025-09-04
 */


#include <iostream>
using namespace std;
int n, m, a, x=9, y=9, v[15];
int main() {
	cin>>n>>m;
	while(n--) {cin>>a; x=min(x, a); v[a]++;}
	while(m--) {cin>>a; y=min(y, a); v[a]++;}
	for(int i=1; i<=9; i++) if(v[i]==2) {cout<<i; return 0;}
	cout<<min(x,y)<<max(x,y);
	return 0;} 