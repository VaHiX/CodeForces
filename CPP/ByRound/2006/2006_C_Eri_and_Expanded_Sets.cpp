/*
 * Problem URL : https://codeforces.com/contest/2006/problem/C
 * Submit Date : 2025-09-13
 */

#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
const int N = 4e5 + 5, B = 45;
int t, n, a[N], b[N], cn;
i64 ans;
struct node
{
    int v, c;
}c[B];
void solve() 
{
    cin >> n; ans = n; cn = 0;
    for(int i = 1; i <= n; i++) cin >> a[i], b[i] = abs(a[i] - a[i - 1]);
    for(int i = 2; i <= n; i++) 
    {
        for(int j = 1; j <= cn; j++) c[j].v = __gcd(c[j].v, b[i]);
        c[++cn] = {b[i], 1}; int m = cn; cn = 1;
        for(int j = 2; j <= m; j++) 
        {
            if(c[j].v == c[cn].v) c[cn].c += c[j].c;
            else c[++cn] = c[j];
        }
        for(int j = 1; j <= cn; j++) if(c[j].v == 0 || (c[j].v & (c[j].v - 1)) == 0) ans += c[j].c;

    }
    cout << ans << '\n';
}
int main()
{
    ios :: sync_with_stdio(false); cin.tie(nullptr), cout.tie(nullptr);
    cin >> t;
    while(t--) solve();
    return 0;
}