/*
 * Problem URL : https://codeforces.com/problemset/problem/2097/A
 * Submit Date : 2025-08-20
 */

#include <bits/stdc++.h>
#include <iostream>
#define ll long long
#define ull unsigned long long
using namespace std;
ll arr[1000007];
ll t, n, ans;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> arr[i];
    }
    sort(arr + 1, arr + n + 1);
    ans = 0;
    for (int i = 2; i <= n; i++) {
      if (arr[i] == arr[i - 1]) {
        ans++;
        if (ans == 2)
          break;
        if (arr[i + 1] >= arr[i] + 2)
          ans = 0;
        i++;
        continue;
      }
      if (arr[i] >= arr[i - 1] + 2)
        ans = 0;
    }
    if (ans == 2)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
}
