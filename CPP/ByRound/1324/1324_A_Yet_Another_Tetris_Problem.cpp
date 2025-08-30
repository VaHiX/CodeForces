/*
 * Problem URL : https://codeforces.com/contest/1324/problem/A
 * Submit Date : 2025-08-27
 */

#include <stdio.h>
int m, n, a, cnt[2];
int main() {
	for(scanf("%d", &m); m--; cnt[0]=cnt[1]=0) {
		scanf("%d", &n);
		for(int i=0; i<n; i++) scanf("%d", &a), cnt[a&1]++;
		puts(!cnt[0] || !cnt[1] ? "YES" : "NO");
	}
}