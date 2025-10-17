/*
 * Problem URL : https://codeforces.com/contest/1621/problem/I
 * Submit Date : 2025-09-11
 */

#include <stdio.h>
#include <string.h>
#include<bits/stdc++.h>
 
#define N	100000
#define M	10
 
int min(int a, int b) { return a < b ? a : b; }
 
void op(int *aa, int n) {
	static int bb[N + 1], qq[N + 1], ll[N + 1], kk[N + 1], ll_[N], kk_[N];
	int n_, h, i, j;
 
	for (i = 0, j = 0; j < n; i++, j++) {
		int q, r, l, k;
 
		while (i > 0 && bb[i - qq[i] + 1] > aa[j])
			i %= qq[i];
		bb[i + 1] = aa[j];
		q = i == 0 || bb[i - qq[i] + 1] < aa[j] ? i + 1 : qq[i];
		if ((r = (i + 1) % q) == 0)
			l = q, k = (i + 1) / q;
		else
			l = ll[r], k = kk[r];
		qq[i + 1] = q, ll[i + 1] = l, kk[i + 1] = k;
		ll_[j] = l, kk_[j] = k;
	}
	for (i = n - 1; i >= 0; i--)
		ll_[i] = i + 1 == n || ll_[i + 1] == 1 ? ll_[i] : ll_[i] * kk_[i];
	for (i = 0, n_ = 0; i < n && n_ < n; i++)
		for (h = i - ll_[i] + 1; h <= i && n_ < n; h++)
			bb[n_++] = aa[h];
	memcpy(aa, bb, n * sizeof *bb);
}
 
int main() {
	static int aa[M][N];
	int n, m, q, i;
 
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", &aa[0][i]);
	for (m = 2; m <= M; m++) {
		int updated;
 
		for (i = 0; i < n; i++)
			aa[m - 1][i] = aa[m - 2][i];
		op(aa[m - 1], n);
		updated = 0;
		for (i = 0; i < n; i++)
			if (aa[m - 1][i] != aa[m - 2][i]) {
				updated = 1;
				break;
			}
		if (!updated)
			break;
	}
	scanf("%d", &q);
	while (q--) {
		int h;
 
		scanf("%d%d", &h, &i), i--;
		printf("%d\n", aa[min(h, m - 1)][i]);
	}
	return 0;
}