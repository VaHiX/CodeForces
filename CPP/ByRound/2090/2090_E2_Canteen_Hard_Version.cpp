// Problem: CF 2090 E2 - Canteen (Hard Version)
// https://codeforces.com/contest/2090/problem/E2

/*
E2. Canteen (Hard Version)

Algorithms/Techniques: Simulation with stack-based optimization, prefix sum, greedy approach

Time Complexity: O(n) per test case amortized
Space Complexity: O(n)

The problem simulates a process where we can make exactly k changes to sequence a,
then perform rounds of operations until all elements in a become zero.
Each round involves:
1. Matching min(a[i], b[i]) and reducing both
2. Shifting elements in a (c[i] = a[(i-1)%n])
3. Assigning c back to a

We precompute how much each round contributes to the total reduction in a,
then we greedily find the minimum number of rounds needed using prefix sums.
*/
#include <algorithm>
#include <iostream>
#include <stack>
#include <utility>

#define F(i, f, t) for (int i = (f), _end = (t); i <= _end; i++)
#define D(i, f, t) for (int i = (f), _end = (t); i >= _end; i--)
#define dbg(x) cerr << #x << '=' << x << endl
#define mems(x, y) memset(x, y, sizeof x)
#define memc(x, y) memcpy(x, y, sizeof x)
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using d128 = long double;
const int N = 3e5, M = 5000;
const i64 MOD = 998244353;
using intn = int[N];
using i64n = i64[N];
i64 n, k;
i64n a, b, sm;
void Sol() {
  cin >> n >> k;
  F(i, 1, n) cin >> a[i];
  F(i, 1, n) cin >> b[i];
  F(i, 1, n) sm[i] = 0; // Initialize prefix sum array
  F(i, 1, n) {
    int x = min(a[i], b[i]); // Match initial a and b values
    sm[1] += x;               // Add matched values to round 1
    a[i] -= x, b[i] -= x;     // Reduce a and b by matched amount
  }
  stack<pair<i64, i64>> S;   // Stack to track excess a values with their positions
  i64 Ans = n;               // Initialize answer
  F(i, 1, 2 * n) {           // Simulate up to 2*n rounds (full cycle)
    i64 I = (i - 1) % n + 1; // Get current index (1-based)
    if (a[I])                // If there's remaining a[I] value
      S.push({a[I], i}), a[I] = 0; // Push to stack and clear a[I]
    if (b[I])                // If there's remaining b[I] value
      while (!S.empty() && b[I]) { // While stack is not empty and b[I] > 0
        i64 x = min(S.top().first, b[I]); // Match minimum between stack top and b[I]
        S.top().first -= x, b[I] -= x;    // Reduce both by matched amount
        sm[i - S.top().second + 1] += x;  // Add to prefix sum based on round number
        if (S.top().first == 0)           // If stack top is exhausted
          S.pop();                        // Pop from stack
      }
  }
  D(i, n, 1) {               // Go backwards from n to 1
    if (k - sm[i] < 0) {     // If k becomes negative with this round
      cout << i << endl;     // Output the round number and return
      return;
    } else
      k -= sm[i];            // Deduct the amount for this round from k
  }
  cout << 0 << endl;         // All elements in a are zero, return 0
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--)
    Sol();
  return 0;
}


// https://github.com/VaHiX/codeForces/