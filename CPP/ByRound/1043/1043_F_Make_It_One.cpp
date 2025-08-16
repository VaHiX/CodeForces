/*
 * Problem URL : https://codeforces.com/problemset/problem/1043/F
 * Submit Date : 2025-08-13
 */

#include <bits/stdc++.h>
using namespace std;

#define N 300030

int runs, p[N], phi[N], mu[N];
void ppm() {
	phi[1] = 1, mu[1] = 1;
	for (int i = 2; i < N; i ++) {
		if (!phi[i]) p[++runs] = i, phi[i] = i - 1, mu[i] = -1;
		for (int j = 1; j <= runs && i * p[j] < N; j ++) {
			int k = i * p[j];
			phi[k] = phi[i] * (p[j] - 1);
			if (i % p[j] == 0) {
				phi[k] = phi[i] * p[j]; break;
			}
			mu[k] = -mu[i];
		}
	}
}

int n, a[N], b[N];
long long f[N], g[N];

int main() {
	ppm();
	cin>>n;
	int d = 0;
	for (int i = 1; i <= n; i ++) {
		scanf("%d", &a[i]);
		d = __gcd(d, a[i]);
		b[a[i]] ++;
	}
	if (d > 1) {
		puts("-1");
		return 0;
	}
	for (int i = 1; i < N; i ++) for (int j = i; j < N; j += i) f[i] += b[j];
	int cnt = 0;
	for (int i = 1; i < N; i ++) g[i] = mu[i];
	while (1) {
		cnt ++;
		for (int i = 1; i < N; i ++) {
			g[i] *= f[i] --;
		}
		long long ans = 0;
		for (int i = 1; i < N; i ++) ans += g[i];
		if (ans) {
			cout<<cnt;
			break;
		}
	}
}
