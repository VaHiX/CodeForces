/*
 * Problem URL : https://codeforces.com/contest/2005/problem/E2
 * Submit Date : 2025-09-13
 */

/*
	www.youtube.com/YugiHackerChannel
	linktr.ee/YugiHacker
*/
#include<bits/stdc++.h>
#define el cout<<"\n"
#define f0(i,n) for(int i=0;i<n;++i)
#define f1(i,n) for(int i=1;i<=n;++i)
#define maxn 1503
using namespace std;
int t;
int a[maxn], b[maxn][maxn];
int dp[maxn][maxn];
int id[maxn * maxn];
void solve()
{
    int l, n, m;
    cin >> l >> n >> m;
    f1 (i, n+1) f1 (j, m+1) f0 (x, 2) dp[i][j] = 1e9;
    f1 (i, l)
    {
        cin >> a[i];
        if (!id[a[i]]) id[a[i]] = i;
    }
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
            cin >> b[i][j];
    for (int i=n; i; i--)
        for (int j=m; j; j--) {
            dp[i][j] = min(dp[i+1][j], dp[i][j+1]);
            if (id[b[i][j]] && dp[i + 1][j + 1] > id[b[i][j]] + 1)
                dp[i][j] = min(dp[i][j], id[b[i][j]]);
        }
    if (dp[1][1] == 1) cout << "T";
    else cout << "N";
    el;

    f1 (i, l) id[a[i]] = 0;
}
main()
{
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> t;
    while (t--) {
        solve();
    }
}
