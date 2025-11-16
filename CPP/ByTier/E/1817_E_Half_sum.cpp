// Problem: CF 1817 E - Half-sum
// https://codeforces.com/contest/1817/problem/E

/*
Purpose: 
This code solves the problem of finding the maximum possible absolute difference between two numbers 
after performing a series of operations on a multiset of integers. In each operation, two elements are 
taken, their average is computed, and inserted back into the multiset. The process continues until 
only two numbers remain. The result is returned modulo 10^9 + 7.

The algorithm uses a bit manipulation technique to represent and compare large numbers, 
allowing handling of fractional parts in the operations.

Time Complexity: O(n log n) due to sorting plus O(n) for bit handling, effectively O(n log n) per test case.
Space Complexity: O(n) for storing the input and auxiliary data structures.

Algorithms/Techniques:
- Sorting to organize elements
- Bit manipulation using BigNumber class for precise comparison
- Greedy approach for choosing optimal cut points
- Modular arithmetic for handling large numbers and modulo operations
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define nl '\n'
using namespace std;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
ll MOD = 1e9 + 7;

struct BigNumber {
  int N;
  vector<bool> bits;
  BigNumber(int N) {
    this->N = N;
    bits.assign(N, false);
  }
  bool operator>(const BigNumber &other) const {
    for (int i = N - 1; i >= 0; i--) {
      if (bits[i] != other.bits[i]) {
        return bits[i] > other.bits[i];
      }
    }
    return false;
  }
};

void addShifted(BigNumber &num, int x, int shift) {
  int carry = 0;
  while (x || carry) {
    int s = num.bits[shift] + (x & 1) + carry;
    num.bits[shift] = s & 1;
    carry = s >> 1;
    x >>= 1;
    shift++;
  }
}

void subtractShifted(BigNumber &num, int x, int shift) {
  int borrow = 0;
  while (x || borrow) {
    int diff = num.bits[shift] - (x & 1) - borrow;
    if (diff < 0) {
      diff += 2;
      borrow = 1;
    } else {
      borrow = 0;
    }
    num.bits[shift] = diff;
    x >>= 1;
    shift++;
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int m = n + 128;
    vi a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    sort(a.begin(), a.end());
    BigNumber res(m);
    BigNumber lc(m);
    int l_idx = 0;
    while (a[l_idx + 1] == a[l_idx] && l_idx + 1 < n - 1) {
      l_idx++;
    }
    addShifted(lc, a[l_idx + 1], l_idx);
    for (int i = l_idx; i < n - 2; i++) {
      addShifted(lc, a[i + 2], i);
    }
    subtractShifted(lc, a[l_idx], n - 2 - l_idx);
    for (int i = 0; i < l_idx; i++) {
      subtractShifted(lc, a[i], n - 3 - i);
    }
    BigNumber rc(m);
    int r_idx = n - 2;
    while (a[r_idx] == a[r_idx + 1] && r_idx > 0) {
      r_idx--;
    }
    addShifted(rc, a[r_idx + 1], r_idx);
    for (int i = r_idx + 2; i < n; i++) {
      addShifted(rc, a[i], i - 2);
    }
    subtractShifted(rc, a[r_idx], n - 2 - r_idx);
    for (int i = 0; i < r_idx; i++) {
      subtractShifted(rc, a[i], n - 3 - i);
    }
    if (lc > rc) {
      res = lc;
    } else {
      res = rc;
    }
    int CUT_SIZE = 5;
    int min_idx = max(1, (n - 2) / 2 - CUT_SIZE);
    int max_idx = min(n - 3, (n - 1) / 2 + CUT_SIZE);
    if (min_idx <= max_idx) {
      BigNumber cut(m);
      addShifted(cut, a[min_idx + 1], min_idx);
      for (int j = min_idx + 2; j < n; j++) {
        addShifted(cut, a[j], j - 2);
      }
      subtractShifted(cut, a[min_idx], n - 2 - min_idx);
      for (int j = 0; j < min_idx; j++) {
        subtractShifted(cut, a[j], n - 3 - j);
      }
      if (cut > res) {
        for (int i = 0; i < m; i++) {
          res.bits[i] = cut.bits[i];
        }
      }
      for (int cut_idx = min_idx + 1; cut_idx <= max_idx; cut_idx++) {
        addShifted(cut, a[cut_idx + 1] - a[cut_idx], cut_idx - 1);
        subtractShifted(cut, a[cut_idx] - a[cut_idx - 1], n - 2 - cut_idx);
        if (cut > res) {
          for (int i = 0; i < m; i++) {
            res.bits[i] = cut.bits[i];
          }
        }
      }
    }
    ll half = (MOD + 1) / 2;
    ll ans = 0;
    ll half_factor = 1;
    for (int i = n - 2; i >= 0; i--) {
      ans = (ans + (res.bits[i] * half_factor) % MOD + MOD) % MOD;
      half_factor = (half_factor * half) % MOD;
    }
    ll two_factor = 2;
    for (int i = n - 1; i < m; i++) {
      ans = (ans + (res.bits[i] * two_factor) % MOD + MOD) % MOD;
      two_factor = (two_factor * 2) % MOD;
    }
    cout << ans << nl;
  }
}


// https://github.com/VaHiX/CodeForces/