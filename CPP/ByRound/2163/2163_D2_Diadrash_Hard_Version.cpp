// Problem: CF 2163 D2 - Diadrash (Hard Version)
// https://codeforces.com/contest/2163/problem/D2

/*
Algorithm: Binary search on MEX value
Time Complexity: O(q * log n * log n) - The binary search is performed on the MEX value (at most n), 
and for each step, we do a linear scan through ranges to find the boundary. 
Space Complexity: O(n) - For storing L and R arrays of size n+1
*/
#include <assert.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
int cnt = 0;
int ask(int l, int r) {
  cnt++;
  assert(cnt <= 30);
  cout << "? " << l << ' ' << r << endl;
  cin >> l;
  return l;
}
void solve() {
  cnt = 0;
  int n, q;
  cin >> n >> q;
  vector<int> L(n + 1, -2), R(n + 1, 2e9);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    L[l] = max(L[l], r);
    R[r] = min(R[r], l);
  }
  int k = ask(n / 2 + 1, n);
  int mx = 0;
  if (k) {
    int bstr = 1e9, bstl = 1e9;
    for (int i = n / 2 + 1; i <= n; i++) {
      if (R[i] <= bstl) {
        bstl = R[i];
        bstr = i;
      }
    }
    if (bstr == 1e9) {
      cout << "0\n";
      return;
    }
    mx = 0;
    int l = n / 2 + 1, r = n;
    while (l <= r) {
      int mid = (l + r) / 2;
      int bstr = 1e9, bstl = 1e9;
      for (int i = mid; i <= n; i++) {
        if (R[i] <= bstl) {
          bstl = R[i];
          bstr = i;
        }
      }
      if (bstr == 1e9) {
        r = mid - 1;
        continue;
      }
      int a = ask(bstl, bstr);
      mx = max(mx, a);
      int b = ask(1, bstr);
      if (a != b) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
  } else {
    int bstr = -1, bstl = -1;
    for (int i = n / 2; i >= 1; i--) {
      if (L[i] >= bstr) {
        bstl = i;
        bstr = L[i];
      }
    }
    if (bstl == -1) {
      cout << "0\n";
      return;
    }
    mx = 0;
    int l = 1, r = n / 2;
    while (l <= r) {
      int mid = (l + r) / 2;
      bstl = -1, bstr = -1;
      for (int i = mid; i >= 1; i--) {
        if (L[i] >= bstr) {
          bstl = i;
          bstr = L[i];
        }
      }
      if (bstl == -1) {
        l = mid + 1;
        continue;
      }
      int a = ask(bstl, bstr);
      mx = max(mx, a);
      int b = ask(bstl, n);
      if (a != b) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
  }
  cout << "! " << mx << endl;
}
int32_t main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/