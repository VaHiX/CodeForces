// Problem: CF 2077 A - Breach of Faith
// https://codeforces.com/contest/2077/problem/A

/*
 * Problem: Breach of Faith
 * Task: Recover a sequence 'a' of 2n+1 elements given a shuffled sequence 'b' of 2n elements,
 *       where the first element equals alternating sum of the rest.
 * 
 * Algorithm:
 * - Sort the input array 'b'
 * - Use greedy assignment to restore 'a':
 *   - Assign smaller values to odd positions (0, 2, 4, ...) in result array
 *   - Assign larger values starting from middle to even positions
 *   - Calculate final value based on alternating sum constraint
 *
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing input and output arrays.
 */

#include <algorithm>
#include <iostream>

using namespace std;
const int N = 4e5 + 5;
int t, n, a[N], id;
long long ans[N];

void solve() {
  cin >> n;
  for (int i = 0; i < (n << 1); ++i) // Read 2*n elements into array 'a'
    cin >> a[i];
  sort(a, a + (n << 1)); // Sort the array
  long long res = 0;
  for (int i = 0; i < n - 1; ++i)
    res -= (ans[i << 1 | 1] = a[i]); // Assign small elements to odd indices of result
  for (int i = 0; i < n + 1; ++i)
    res += (ans[i << 1] = a[n + i - 1]); // Assign larger elements to even indices
  ans[(n << 1) - 1] = res; // Final element is computed as alternating sum
  for (int i = 0; i <= (n << 1); ++i)
    cout << ans[i] << ' '; // Output the recovered sequence
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--)
    solve(), cout << "\n";
  return 0;
}


// https://github.com/VaHiX/codeForces/