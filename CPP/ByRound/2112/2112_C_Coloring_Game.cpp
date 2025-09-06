/*
 * Problem URL : https://codeforces.com/problemset/problem/2112/C
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
      cin >> arr[i];
    ll cnt = 0;
    for (int i = 2; i < n; i++) {
      int val = max(arr[i], (arr[n - 1] - arr[i]));
      int left = 0, right = i - 1;
      while (right > left) {
        if (arr[left] + arr[right] > val) {
          cnt += (right - left);
          right -= 1;
        } else
          left += 1;
      }
    }
    cout << cnt << endl;
  }
}