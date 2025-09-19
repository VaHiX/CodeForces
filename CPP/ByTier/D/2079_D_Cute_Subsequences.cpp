/*
 * Problem URL : https://codeforces.com/contest/2079/problem/D
 * Submit Date : 2025-08-25
 */

#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int nx = 5e5 + 5;

ll n, k, x, sm, ans, a[nx];
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main() {
  cin.tie(NULL)->sync_with_stdio(false);
  cin >> n >> k;
  for (int i = 1; i <= n; i++)
    cin >> a[i];
  for (int i = 1; i < k; i++)
    pq.push(a[i]), sm += a[i];
  for (int i = k; i <= n; i++) {

    ans = max(ans, sm + a[i] + i);
    sm += a[i];
    pq.push(a[i]);
    sm -= pq.top();
    pq.pop();
  }
  cout << ans;
}