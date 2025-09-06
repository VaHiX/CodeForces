/*
 * Problem URL : https://codeforces.com/contest/983/problem/A
 * Submit Date : 2025-09-04
 */

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
void solve(){
	ll p,q,b;
	scanf("%lld%lld%lld",&p,&q,&b);
	ll g=__gcd(p,q);
	q/=g;
	while(q!=1&&b!=1){
		b=__gcd(q,b);
		q/=b;
	}
	if(q==1) puts("Finite");
	else puts("Infinite");
}
int main(){
	int n;
	scanf("%d",&n);
	while(n--) solve();
	return 0;
}
  		 		   		 	 	   		 	       	