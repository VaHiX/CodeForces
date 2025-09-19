/*
 * Problem URL : https://codeforces.com/contest/2022/problem/E2
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, M = 1e9 + 7;
int t, n, m, k, q, p[N], x, y, z, dsu[N], sz[N], val[N], ok, cmps;

void mrg(int a, int b, int c){
    while (a != dsu[a]) c ^= val[a], a = dsu[a];
    while (b != dsu[b]) c ^= val[b], b = dsu[b];
    if (a == b) { if (c) ok = 0;  return; }
    if (sz[a] > sz[b]) swap(a, b);
    dsu[a] = b, sz[b] += sz[a], val[a] = c, cmps--;
}

int main(){  ios::sync_with_stdio(0),cout.tie(0),cin.tie(0);
    for (p[0] = x = 1; x < N; x++) p[x] = p[x - 1] * (1LL << 30) % M;
    cin >> t;  while (t--){
        cin >> n >> m >> k >> q;  ok = 1, cmps = n + m - 1;
        for (x = 1; x <= n + m; x++) dsu[x] = x, sz[x] = 1, val[x] = 0;
        while (k--) cin >> x >> y >> z, mrg(x, y + n, z); cout << ok * p[cmps] << "\n";
        while (q--) cin >> x >> y >> z, mrg(x, y + n, z), cout << ok * p[cmps] << "\n";
    }
}