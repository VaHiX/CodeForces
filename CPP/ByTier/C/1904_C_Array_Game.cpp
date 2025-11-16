// Problem: CF 1904 C - Array Game
// https://codeforces.com/contest/1904/problem/C

/*
Algorithm: Array Game
Approach:
This problem involves minimizing the smallest element in an array by repeatedly taking two elements, computing their absolute difference, and appending that difference back to the array. The key insight is that after a few operations, all elements will eventually become multiples of the GCD of the original array. This allows us to optimize the solution significantly.

Time Complexity: O(n log n) per test case due to sorting and iterating through elements.
Space Complexity: O(n) for storing the array.

Techniques Used:
- Sorting the array to facilitate computation.
- Using GCD-based optimization for large k values.
- Efficiently checking differences and computing minimums.

*/
#include <bits/std_abs.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#if defined(RSPC_TRACE_HINT)
#define TRACE(...)                                                             \
  do {                                                                         \
    __VA_ARGS__;                                                               \
  } while (0)
#else
#define TRACE(...) (void)0
#endif
#define TLN(...) TRACE(__VA_ARGS__; cerr << endl)
#define TA(VEC, ...)                                                           \
  TRACE(cerr << #VEC << "= ";                                                  \
        for_each((VEC).begin(), (VEC).end(), [&](auto _) { __VA_ARGS__; }))
#define TI(HEAD, TAIL, ...)                                                    \
  TRACE(cerr << "[" #HEAD "," #TAIL ") = ";                                    \
        for_each((HEAD), (TAIL), [&](auto _) { __VA_ARGS__; }))
#define TV(EXPR) TRACE(cerr << #EXPR " = " << (EXPR) << ' ')
using namespace std;
#define self_todo_placeholder
int main() {
#if defined(RSPC_TRACE_BTIME)
  TRACE(cerr << "build time: " RSPC_TRACE_BTIME "\n");
#else
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
#endif
  int tt;
  cin >> tt;
  while (tt--) {
    int n, K;
    cin >> n >> K;
    TLN(TV(n); TV(K));
    if (K > 2) {
      int64_t t;
      for (int i = 0; i < n; ++i)
        cin >> t;
      cout << "0\n"; // If K > 2, the minimum value can always be made 0
      continue;
    }
    vector<int64_t> a;
    a.reserve(n);
    copy_n(std::istream_iterator<int64_t>(std::cin), n, std::back_inserter(a));
    sort(a.begin(), a.end());
    int64_t ans = a.front(); // Initially assume minimum element is the smallest
    for (int i = 1; i < n; ++i)
      ans = min(ans, a[i] - a[i - 1]); // Find GCD of differences
    if (1 == K || 0 == ans) { // If only one operation or GCD is already 0
      cout << ans << endl;
      continue;
    }
    for (const auto &x : a) {
      for (int i = 1, j = 0; i < n; ++i) {
        while (j + 1 < i && a[i] - a[j] > x)
          ++j;
        ans = min(ans, abs((a[i] - a[j]) - x));
        if (j)
          ans = min(ans, abs((a[i] - a[j - 1]) - x));
      }
    }
    cout << ans << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/