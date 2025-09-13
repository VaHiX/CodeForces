/*
 * Problem URL : https://codeforces.com/contest/1975/problem/H
 * Submit Date : 2025-09-11
 */

#include <bits/stdc++.h>

using namespace std;

template<typename Tp>
void chmin (Tp &x, const Tp &y) { x = min (x, y); }
template<typename Tp>
void chmax (Tp &x, const Tp &y) { x = max (x, y); }

using dbl = double;
using ll = long long;
using ldb = long double;

void init () {}

constexpr int MAX_N = 1e6 + 20;
constexpr int SIGMA = 26;
int n, cnt[SIGMA];
char s[MAX_N], sans[MAX_N];

int idcnt, nxt[MAX_N], val[MAX_N], btm[MAX_N];

void solve () {
    scanf ("%d%s", &n, s + 1);
    fill (cnt, cnt + SIGMA, 0);
    for (int i = 1; i <= n; ++i) {
        ++cnt[s[i] - 'a'];
    }
    fill (nxt, nxt + n + 1, 0);
    fill (val + 1, val + n + 1, -2);
    idcnt = n;
    val[0] = -1;
    for (int i = 1, j = 0; i <= n; ++i) {
        while (!cnt[j]) ++j;
        s[i] = j + 'a';
        val[i] = j;
        --cnt[j];
    }
    int p = n;
    iota (btm, btm + n + 1, 0);
    for (int i = 0, j = 0; i < n; ++i) {
        if (p == n) {
            while (p > i + 1 && val[p] == val[p - 1]) --p;
            j = p;
        } else {
            ++p;
        }
        nxt[btm[p]] = i;
        btm[p] = btm[i];
        val[p] = idcnt += j == p || val[i - 1] != val[i];
    }
    for (int i = 1; ; ++i) {
        sans[i] = s[p];
        if (!p) break;
        p = nxt[p];
    }
    printf ("%s\n", sans + 1);
}

int main () {
    int t = 1; init ();
    scanf ("%d", &t);
    while (t--) solve ();
    return 0;
}