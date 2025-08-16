/*
 * Problem URL : https://codeforces.com/problemset/problem/1203/C
 * Submit Date : 2025-08-16
 */

#include <bits/stdc++.h>
using namespace std;
int64_t n,i,x,g,r=1;
int main(){
	ios_base::sync_with_stdio(0);cin.tie(0);
	for(cin>>n;n--;)cin>>x,g=__gcd(g,x);
	for(i=2,x=0;i*i<=g;i++){
		for(;g%i==0;)g/=i,x++;
		r*=x+1;
		x=0;
	}
	g>1?r*=2:0;
	cout<<r;
}