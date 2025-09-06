/*
 * Problem URL : https://codeforces.com/contest/1588/problem/A
 * Submit Date : 2025-08-31
 */

#include <bits/stdc++.h>
using namespace std;
 
int main() {
	int T;
	for (cin>>T;T--;) {
		int n,a[109],b[109],Ans=1;
		cin>>n;
		for (int i=1;i<=n;i++) cin>>a[i];
		for (int i=1;i<=n;i++) cin>>b[i];
		sort(a+1,a+1+n),sort(b+1,b+1+n);
		for (int i=1;i<=n;i++) if (a[i]!=b[i] && a[i]!=b[i]-1) Ans=0;
		puts(Ans? "Yes":"No");
	}
	return 0;
}