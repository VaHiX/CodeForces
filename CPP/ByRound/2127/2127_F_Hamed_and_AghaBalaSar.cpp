/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/F
 * Submit Date : 2025-08-14
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int MOD = 1e9+7;
const int MAXN = 200010;
typedef long long LL;
int t, n, m;
int inv[MAXN];
int facto[MAXN<<1], invFacto[MAXN<<1];

int quickPower(int x, int n) {
    int ans = 1;
    while (n) {
        if (n&1) ans = (LL)ans * (LL)x % MOD;
        x = (LL)x * (LL)x % MOD;
        n >>= 1;
    }
    return ans;
}

void init() {
    facto[0] = invFacto[0] = 1;
    for (int i = 1; i < (MAXN<<1); i++) {
        facto[i] = (LL)facto[i-1] * (LL)i % MOD;
    }
    invFacto[(MAXN<<1)-1] = quickPower(facto[(MAXN<<1)-1], MOD-2);
    for (int i = (MAXN<<1)-2; i > 0; i--) {
        invFacto[i] = (LL)invFacto[i+1] * (LL)(i+1) % MOD;
    }

    inv[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        inv[i] = (LL)(MOD - MOD/i) * (LL)inv[MOD%i] % MOD;
    }
}

inline int get_combination(int n, int m) {
    if (m > n || m < 0) return 0;
    return ((LL)facto[n] * (LL)invFacto[m] % MOD) * (LL)invFacto[n-m] % MOD;
}

int get_count(int n, int m, int k) {
    if (m < 0) return 0;
    if (n == 0) return m==0;
    if (n == 1) return m<=k;

    int ans = 0;
    int r = m/(k+1);
    for (int s = 0; s <= r; s++) {
        int tmp = (LL)get_combination(n, s) * (LL)get_combination(m+n-1-(k+1)*s, n-1) % MOD;
        if (s&1) {
            ans -= tmp;
            ans += (ans < 0) ? MOD : 0;
        } else
        {
            ans += tmp;
            ans -= (ans >= MOD) ? MOD : 0;
        }
    }
    return ans;
}

int calc(int n, int m, int k) {
    int t1 = get_count(n-1, m-k, k);
    int t2 = get_count(n-2, m-2*k, k);
    // printf("t1 = %d\n", t1);
    // printf("t2 = %d\n", t2);

    int sum_max, sum_an, sum_other_max, sum_a1, sum_ai;
    int tmp = (LL)t2 * (LL)k % MOD;
    sum_an = (LL)t1 * (LL)k % MOD;
    sum_other_max = (LL)tmp * (LL)(n-1) % MOD;
    sum_max = (sum_an + sum_other_max) % MOD;

    sum_a1 = (LL)t1 * (LL)(m-k) % MOD;
    sum_a1 = (LL)sum_a1 * (LL)inv[n-1] % MOD;

    sum_ai = (LL)t2 * (LL)(m-2*k) % MOD;
    sum_ai = (sum_ai + tmp) % MOD;

    // printf("sum_max = %d\n", sum_max);
    // printf("sum_a1  = %d\n", sum_a1);
    // printf("sum_ai  = %d\n\n", sum_ai);

    int res = ((sum_max - sum_a1 + MOD) % MOD - sum_ai + MOD) % MOD;
    return res;
}

int main() {
    init();
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &m);

        if (m == 0) {
            printf("0\n");
            continue;
        }

        int ans = 0;
        for (int k = 1; k <= m; k++) {
            ans += calc(n, m, k);
            ans -= (ans >= MOD) ? MOD : 0;
        }
        printf("%d\n", ans);
    }
    return 0;
}