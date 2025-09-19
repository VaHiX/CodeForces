/*
 * Problem URL : https://codeforces.com/contest/2018/problem/F3
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
#define For(i, a, b) for(int i = (a), en = (b); i <= en; ++i)
#define Rof(i, a, b) for(int i = (a), en = (b); i >= en; --i)
#define Tra(u, i) for(int i = hd[u]; ~i; i = e[i].net)
#define cst const
#define LL long long
#define DD double
#define LD long double
#define pb push_back
#define mp make_pair
#define fir first
#define sec second
#define inf 0x3f3f3f3f
#define Inf 0x3f3f3f3f3f3f3f3f
#define eps 1e-12
using namespace std;

template <class T>
void read(T& x) {
    char ch;
    bool ok;
    for(ok = 0, ch = getchar(); !isdigit(ch); ch = getchar()) if(ch == '-') ok = 1;
    for(x = 0; isdigit(ch); x = x * 10 + ch - '0', ch = getchar());
    if(ok) x = -x;
}

#define maxn 3000
int T, n, P;
int f[maxn + 5], g[maxn + 5][maxn + 5], as[maxn + 5], fac[maxn + 5], ifac[maxn + 5];

int fp(int x, int y) {
    int res = 1;
    while(y) {
        if(y & 1) res = 1ll * res * x % P;
        x = 1ll * x * x % P;
        y >>= 1;
    }
    return res;
}

void mian() {
    read(n); read(P);
    fac[0] = 1;
    For(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % P;
    ifac[n] = fp(fac[n], P - 2);
    Rof(i, n - 1, 0) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % P;

    // For(i, 1, n) {
        // g[i][i - 1] = 1;
        // For(j, i, n) g[i][j] = 1ll * g[i][j - 1] * j % P;
    // }
    int sum = 0, sum_as[2] = { 0, 0 };
    Rof(len, n, 1) {
        if(len != n) f[len] = (1ll * (n - len) * f[len + 1] % P + 1ll * fac[n - len - 1] * sum % P) % P;
        else f[len] = 1;
        sum = (sum + 1ll * ifac[n - len] * f[len] % P) % P;
        as[len] = 1ll * f[len] * fac[n - len + len / 2] % P * ifac[n - len] % P * fac[n - len / 2] % P * ifac[n - len] % P;
        as[len] = (as[len] - sum_as[1] + P) % P;
        sum_as[0] = (sum_as[0] + as[len]) % P;
        sum_as[1] = (1ll * sum_as[1] + as[len] + sum_as[0]) % P;
    }

    as[0] = 1;
    For(i, 1, n) as[0] = 1ll * as[0] * n % P;
    For(i, 1, n) as[0] = (as[0] - as[i] + P) % P;
    For(i, 0, n) printf("%d ", as[i]);
    puts("");
}

int main() {
    // freopen("in.txt", "r", stdin);
    read(T);
    while(T--) {
        mian();
    }
}
