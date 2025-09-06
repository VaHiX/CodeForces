/*
 * Problem URL : https://codeforces.com/contest/2134/problem/F
 * Submit Date : 2025-08-30
 */

#include <stdio.h>

const int N = 800, M = 400, K = 1598, mod = 1e9 + 7;
int c[N + 1][N + 1], f02[M + 1][N + 1], f13[M + 1][N + 1], ans[K + 1];

int add(int x, int y){
	return x + y >= mod ? x + y - mod : x + y;
}

void init1(){
	c[0][0] = 1;
	for (int i = 1; i <= N; i++){
		c[i][0] = 1;
		for (int j = 1; j <= i; j++){
			c[i][j] = add(c[i - 1][j], c[i - 1][j - 1]);
		}
	}
}

void init2(){
	for (int i = 1; i <= M; i++){
		for (int j = 0; j <= N; j++){
			f02[i][j] = f13[i][j] = 0;
		}
	}
	for (int i = 0; i <= K; i++){
		ans[i] = 0;
	}
}

int min(int a, int b){
	return a < b ? a : b;
}

void calc(int f[M + 1][N + 1], int p, int q){
	for (int i = 2; ; i++){
		int x = i / 2, y = i - x, coef = (1ll * c[p - 1][x - 1] * c[q - 1][y - 1] + 1ll * c[p - 1][y - 1] * c[q - 1][x - 1]) % mod;
		if (coef == 0) break;
		for (int j = 0; j < i; j++){
			for (int k = j + 1; k - j - 1 <= p + q - i && k <= M; k++){
				f[k][i - j - 1] = (f[k][i - j - 1] + 1ll * coef * c[i - 1][j] % mod * c[p + q - i][k - j - 1]) % mod;
			}
		}
	}
}

int main(){
	int t;
	scanf("%d", &t);
	init1();
	for (int i = 1; i <= t; i++){
		int c0, c1, c2, c3, c02, c13, n, m;
		scanf("%d %d %d %d", &c0, &c1, &c2, &c3);
		c02 = c0 + c2;
		c13 = c1 + c3;
		n = c02 + c13;
		m = (n - 1) * 2;
		init2();
		calc(f02, c0, c2);
		calc(f13, c1, c3);
		for (int j = 1; j * 2 <= n; j++){
			for (int k = 0; k <= n; k++){
				if (f02[j][k] == 0) continue;
				for (int l = 0; l <= n; l++){
					if (f13[j][l] == 0) continue;
					int x = (j * 2 - 1) + (k + l) * 2;
					ans[x] = (ans[x] + 1ll * f02[j][k] * f13[j][l] * 2) % mod;
				}
			}
		}
		for (int j = 1; j * 2 + 1 <= n; j++){
			for (int k = 0; k <= n; k++){
				if (f02[j][k] == 0 && f02[j + 1][k] == 0) continue;
				for (int l = 0; l <= n; l++){
					if (f13[j][l] == 0 && f13[j + 1][l] == 0) continue;
					int x = j * 2 + (k + l) * 2;
					ans[x] = (ans[x] + 1ll * f02[j][k] * f13[j + 1][l] + 1ll * f02[j + 1][k] * f13[j][l]) % mod;
				}
			}
		}
		for (int j = 0; j <= m; j++){
			printf("%d ", ans[j]);
		}
		printf("\n");
	}
	return 0;
}