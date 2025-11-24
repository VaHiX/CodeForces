// Problem: CF 1938 C - Bit Counting Sequence
// https://codeforces.com/contest/1938/problem/C

/*
Purpose: Given a sequence of bit counts for consecutive integers, determine the smallest starting integer x such that the bit counts of x, x+1, ..., x+n-1 match the given sequence.
Algorithm: 
  - Use a sliding window approach with bit manipulation to reconstruct the minimal x.
  - For each difference in bit counts, validate feasibility and maintain a bit pattern.
  - Backtrack from initial bits to compute the minimum valid x.
Time Complexity: O(n * log(max_value)) where n is the length of sequence and max_value is up to 500000.
Space Complexity: O(log(max_value)) for storing bit patterns and related arrays.

*/
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  // bits: tracks bit values at each position during construction
  // init: stores initial bit pattern before adjustments
  vector<int> bits(64, -1), init(64, -1);
  for (int i = 0; i + 1 < n; ++i) {
    int diff = a[i + 1] - a[i];
    if (diff > 1) {
      cout << -1 << '\n';
      return;
    }
    bool ok = 1;
    int ones = 1 - diff; // Count of bits to flip in current step
    for (int j = 0; j < ones; ++j) {
      if (bits[j] < 0) {
        bits[j] = init[j] = 1;
        continue;
      }
      if (bits[j] == 0) {
        cout << "-1\n";
        return;
      }
    }
    if (bits[ones] < 0) {
      bits[ones] = init[ones] = 0;
    } else if (bits[ones] == 1) {
      cout << "-1\n";
      return;
    }
    for (int j = 0; j < ones; ++j) {
      assert(bits[j] == 1);
      bits[j] = 0;
    }
    assert(bits[ones] == 0);
    bits[ones] = 1;
  }
  int cnt = 0, sz = 0;
  long long ans = 0;
  for (int i = 0; i < init.size(); ++i) {
    if (init[i] < 0)
      break;
    ++sz;
    cnt += init[i];
    if (init[i]) {
      ans |= 1LL << i;
    }
  }
  if (a[0] < cnt) {
    cout << "-1\n";
    return;
  }
  for (int i = 0; i < a[0] - cnt; ++i) {
    ans |= 1LL << (sz + i);
  }
  cout << ans << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/