/*
 * Problem URL : https://codeforces.com/contest/2039/problem/E
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
const long long M=998244353;
long long a[1000001],b[1000001];
int main() {
	int t;
	cin>>t;
	while(t--) {
		int n;
		cin>>n;
		a[2]=b[3]=1;
		a[3]=2;
		for(int i=4; i<=n; ++i) {
			b[i]=(a[i-2]+b[i-1]+1+M)%M;
			a[i]=(a[i-1]*(long long)i-b[i]+M)%M;
		}
		cout<<a[n]<<endl;
	}
	return 0;
}