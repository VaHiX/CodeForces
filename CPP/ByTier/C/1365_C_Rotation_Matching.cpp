/*
 * Problem URL : https://codeforces.com/contest/1365/problem/C
 * Submit Date : 2025-08-27
 */

#include <stdio.h>
int t, n, x, a[200020], b[200020], cnt[200020], ans;
int main() {
	scanf("%d", &n);
	for(int i=0; i<n; i++) scanf("%d", a+i);
	for(int i=0; i<n; i++) scanf("%d", &x), b[x]=i;
	for(int i=0; i<n; i++) cnt[(n+b[a[i]]-i)%n]++;
	for(int i=0; i<n; i++) if (cnt[i]>ans) ans=cnt[i];
	printf("%d", ans);
}
