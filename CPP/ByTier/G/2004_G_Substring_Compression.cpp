/*
 * Problem URL : https://codeforces.com/contest/2004/problem/G
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;
const int N=200005;
int n,k;
char s[N];
int L[N][10], R[N][10];
int res[N];
void calc(int m){
	int l = max(1, m-k+1);
	int r = min(n, m+k-1);
	for(int d=0;d<=9;++d){
		for(int x=0;x<=9;++x){
			L[m+1][x] = 1e9;
			R[m][x] = 1e9;
		}
		L[m+1][d] = 0;
		R[m][d] = 0;
		for(int i=m;i>=l && i>=m-k+1;--i){
			L[i][0] = L[i+1][s[i]-'0'];
			for(int p=1;p<=9;++p)
				L[i][p] = p + min(L[i+1][0], L[i+1][p]);
		}
		for(int i=m+1;i<=r && i<=m+k-1;++i){
			R[i][0] = 1e9;
			for(int p=1;p<=9;++p){
				R[i][0] = min(R[i][0], p + R[i-1][p]);
				R[i][p] = R[i-1][p] + p;
				if(s[i]-'0'==p)
					R[i][p] = min(R[i][p], R[i-1][0]);
			}
		}
		for(int i=max(l,m-k+1);i<=m;++i)
			if(i+k-1<=r)
				res[i] = min(res[i], L[i][0] + R[i+k-1][0]);
	}
}
int main() {
	scanf("%d%d%s",&n,&k,s+1);
	for(int i=0;i<N;++i)
		res[i] = 1e9;
	for(int i=k;i<n;i+=k)
		calc(i);
	calc(n);
	for(int i=1;i<=n-k+1;++i)
		printf("%d ", res[i]);
	return 0;
}