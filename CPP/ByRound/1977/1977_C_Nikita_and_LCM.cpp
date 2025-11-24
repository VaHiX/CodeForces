// Problem: CF 1977 C - Nikita and LCM
// https://codeforces.com/contest/1977/problem/C

/*
Purpose: This code finds the length of the longest special subsequence in an array.
A subsequence is special if its LCM (Least Common Multiple) is not present in the array.
The approach uses the observation that if all elements divide the maximum element, 
we only need to check valid divisors of the max element to find a valid special subsequence.

Algorithms/Techniques:
- Use of set and map for efficient lookups and counting
- Iteration over divisors of maximum element
- LCM computation using GCD
- Sorting to simplify divisibility checks

Time Complexity: O(n * sqrt(max_element) + n log n)
Space Complexity: O(n + sqrt(max_element))

*/
#include <ext/pb_ds/detail/type_utils.hpp>
#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

using namespace std;
using namespace __gnu_pbds;
#define F first
#define S second
#define PB push_back
#define FAST_IO                                                                \
  ios_base::sync_with_stdio(0);                                                \
  cin.tie(0);
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;

// Calculates GCD using Euclidean algorithm
int __gcd(int a, int b) {
  if (a > b)
    swap(a, b);
  if (a == 0)
    return b;
  return __gcd(a, b - ((b / a) * a));
}

// Calculates LCM using GCD
ll __lcm(int a, int b) { return (ll(a) * b) / __gcd(a, b); }

void solve(int tc) {
  int n;
  cin >> n;
  vector<int> v(n);
  for (auto &i : v)
    cin >> i;
  if (n == 1) {
    cout << "0\n";
    return;
  }
  sort(v.begin(), v.end());
  set<int> s;
  map<int, int> m;
  for (int i = n - 2; i >= 0; i--) {
    // If any element doesn't divide the maximum element, we can use all elements
    if (v[n - 1] % v[i]) {
      cout << n << "\n";
      return;
    }
  }
  for (auto &i : v) {
    s.insert(i);
    m[i]++;
  }
  set<int> div;
  // Find all divisors of the maximum element
  for (int i = 2; i * i <= v[n - 1]; i++) {
    if (!(v[n - 1] % i)) {
      div.insert(i);
      div.insert(v[n - 1] / i);
    }
  }
  int ans = 0;
  // For each divisor, check if it's not in the array
  for (auto &i : div) {
    if (s.find(i) == s.end()) {
      int lcm = 1;
      int cans = 0;
      // Count how many elements in the array divide this divisor
      for (auto &j : s) {
        if (!(i % j)) {
          cans += m[j];
          lcm = __lcm(lcm, j);
        }
        // If LCM equals the divisor, update answer
        if (lcm == i)
          ans = max(ans, cans);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  FAST_IO
  int t = 1;
  cin >> t;
  for (int tc = 1; tc <= t; tc++)
    solve(tc);
  return 0;
}


// https://github.com/VaHiX/CodeForces/