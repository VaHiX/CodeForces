// Problem: CF 1762 G - Unequal Adjacent Elements
// https://codeforces.com/contest/1762/problem/G

/*
Algorithm/Technique: Greedy + Counting
Time Complexity: O(n)
Space Complexity: O(n)

This code attempts to find a permutation of indices such that:
1. For every i >= 3, p[i-2] < p[i] (i.e., no three consecutive elements in the permutation are in increasing order)
2. For every i >= 2, a[p[i-1]] != a[p[i]] (no two adjacent elements in the permutation have same value in the original array)

Approach:
- First, we count occurrences of each value in the array.
- If any value occurs more than (n+1)/2 times, it's impossible to construct such permutation.
- Otherwise, we can construct a valid permutation by placing elements in a greedy fashion:
  - Place elements with highest frequency first, ensuring no two of them are adjacent.
  - Fill the remaining positions with other elements.

The algorithm uses a greedy assignment strategy to ensure:
- Consecutive elements in the final permutation have different values in the original array.
- No three consecutive elements in the final permutation form an ascending sequence.
*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
int _, n, a[1 << 20], s[1 << 20], c[1 << 20], u, A[1 << 20];
void O() {
  cin >> n, u = 0;
  for (int i = 1; i <= n; i++)
    s[i] = c[i] = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], s[++c[a[i]]]++, u = max(u, c[a[i]]);
  if (u > (n + 1) / 2) {
    cout << "NO\n";
    return;
  }
  cout << "YES\n";
  for (int i = 1, l = 1, r = 2; i <= n; i++) {
    if (u == (n - l + 2) / 2)
      for (int j = 1; j <= n; j++)
        if (c[j] == u) {
          for (int k = i; k <= n; k++)
            if (a[k] == j)
              A[l] = k, l += 2;
            else
              A[r] = k, r += 2;
          for (int k = 1; k <= n; k++)
            cout << A[k] << ' ';
          cout << '\n';
          return;
        }
    if (a[i] != a[A[l - 1]]) {
      A[l] = i, l += 2;
      if (l > r)
        swap(l, r);
    } else
      A[r] = i, r += 2;
    s[c[a[i]]--]--, u -= !s[u];
  }
}
int main() {
  for (cin >> _; _--;)
    O();
}


// https://github.com/VaHiX/CodeForces/