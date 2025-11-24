// Problem: CF 2089 B2 - Canteen (Hard Version)
// https://codeforces.com/contest/2089/problem/B2

// Problem: B2. Canteen (Hard Version)
// Algorithms/Techniques: Simulation with Stack, Prefix Sum, Binary Search on Answer
// Time Complexity: O(n) per test case
// Space Complexity: O(n)

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
  stack<pair<i64, i64>> S; // Stack to keep track of elements in 'a' and their indices
  i64 Ans = n;
  F(i, 1, 2 * n) { // Simulate up to 2*n rounds to handle wraparound
    i64 I = (i - 1) % n + 1; // Wrap index around
    if (a[I])
      S.push({a[I], i}), a[I] = 0; // Push element from 'a' to stack, mark it as processed
    if (b[I])
      while (!S.empty() && b[I]) { // While there's an element in the stack and b[I] > 0
        i64 x = min(S.top().first, b[I]); // Take minimum of current value from stack and b[I]
        S.top().first -= x, b[I] -= x; // Decrease both by x
        sm[i - S.top().second + 1] += x; // Add x to the result array based on gap between positions
        if (S.top().first == 0)
          S.pop(); // Remove stack element if it becomes zero
      }
  }
  D(i, n, 1) { // Traverse backwards from n to 1
    if (k - sm[i] < 0) {
      cout << i << endl; // If k is not enough for current prefix, return this index
      return;
    } else
      k -= sm[i]; // Deduct the value and proceed
  }
  cout << 0 << endl; // If all elements are used up, answer is 0
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