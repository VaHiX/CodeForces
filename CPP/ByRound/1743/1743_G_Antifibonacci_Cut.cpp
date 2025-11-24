// Problem: CF 1743 G - Antifibonacci Cut
// https://codeforces.com/contest/1743/problem/G

/*
Purpose: This code solves the problem of computing the number of ways to cut a Fibonacci-like string into segments such that none of the segments are Fibonacci strings.
           It uses a dynamic programming approach with bit manipulation for efficient state tracking.

Algorithms/Techniques:
- Dynamic Programming with bitmask states
- Fibonacci string recognition using bitwise operations
- Efficient state transition using bit manipulation

Time Complexity: O(n * m * log m) where n is total length of strings and m is average string length
Space Complexity: O(m) for storing the state vector

Note: The code uses a custom structure SB to maintain the dynamic programming states efficiently using binary operations.
*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
#define M 998244353
int i, j, k, n, m, t;
int su(int a, int b) {
  a += b;
  return (a >= M) ? a - M : a;
}
int pre = 1, res = 1, tmp;
struct SB {
  ll f, g;
  bool add(ll x) {
    // Adjust x to match the pattern of Fibonacci strings
    while ((-g & g) & (x + x)) {
      g -= (-g & g);
      x <<= 2;
    }
    // Check if this is a valid state to continue
    if (g && (-g & g) <= x)
      return 0;
    // Update result
    if (!g)
      res = su(res, M - f);
    g |= x;
    return 1;
  }
};
vector<SB> v1;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) {
    string s;
    cin >> s;
    for (auto i : s) {
      vector<SB> v2;
      i -= '0';
      tmp = res;
      res = su(pre, M - res);
      // Process existing states
      for (auto s : v1) {
        if (!s.add(i + 1))
          continue;
        v2.push_back(s);
      }
      // Add new state
      if (i)
        v2.push_back({tmp, 2});
      pre = su(pre, res);
      swap(v1, v2);
    }
    cout << res << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/