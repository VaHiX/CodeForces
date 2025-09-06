/*
 * Problem URL : https://codeforces.com/problemset/problem/1468/A
 * Submit Date : 2025-09-01
 */

#include <bits/stdc++.h>
using namespace std;
const int N = 500010;
int tree[N], q[N], n, a[N] , dp[N] ,ans;
long long k;
void add(int x, int k){
	while (x<=n){
		tree[x]=max(tree[x], k);
		x+=x&-x;
	}
}
 
int find(int x){
	int ans = 0;
	while (x>0){
		ans=max(ans, tree[x]);
		x-=x&-x;
	}
	return ans;
}
 
int main() {
	int t;
    scanf("%d", &t);
    while (t){
    	t--;
    	scanf("%d", &n);
    	ans = 1;
    	for (int i=0; i<n; i++){
    		scanf("%d", &a[i]);
    		tree[i+1]=0;
		}
		int r=0;
		for (int i=0; i<n; i++){
			dp[i]=min(i+1, 2);
			dp[i]=max(find(a[i])+1, dp[i]);
			ans = max(ans, dp[i]);
			while (r>0 && a[q[r-1]]<=a[i]){
				add(a[q[r-1]], dp[q[r-1]]+1);
				r--;
			}
			q[r++]=i;
			add(a[i], dp[i]);
		}
		printf("%d\n", ans);
	}
    return 0;
}