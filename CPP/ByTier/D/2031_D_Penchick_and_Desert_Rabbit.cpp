// Problem: CF 2031 D - Penchick and Desert Rabbit
// https://codeforces.com/contest/2031/problem/D

/*
Problem: D. Penchick and Desert Rabbit

Task: For each tree i, determine the maximum height among all trees the rabbit can reach starting from tree i,
given the jumping rules:
- Can jump backward to a taller tree (j < i and a[j] > a[i])
- Can jump forward to a shorter tree (j > i and a[j] < a[i])

Approach:
1. Precompute for each position i, the maximum height from 1 to i (mx[i]).
2. Precompute for each position i, the minimum height from i to n (mn[i]).
3. For each position i from n down to 1:
   - If mx[i] <= mn[i+1], then i can reach all trees with heights <= mx[i]
     so f[i] = mx[i]
   - Else, f[i] = f[i+1], meaning the best height is carried over
4. Output f[i] for each i

Time Complexity: O(n) per test case
Space Complexity: O(n) 

Algorithms/Techniques:
- Preprocessing with prefix max and suffix min arrays
- Dynamic Programming (forward pass)
*/

#include <algorithm>
#include <iostream>

using namespace std;
int t, n, a[500005], mx[500005], mn[500005], f[500005];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    mx[1] = a[1], mn[n] = a[n];
    for (int i = 2; i <= n; i++)
      mx[i] = max(mx[i - 1], a[i]); // prefix maximum
    for (int i = n - 1; i >= 1; i--)
      mn[i] = min(mn[i + 1], a[i]); // suffix minimum
    f[n] = mx[n];
    for (int i = n - 1; i >= 1; i--) {
      if (mx[i] <= mn[i + 1]) // can reach all elements up to current max
        f[i] = mx[i];
      else
        f[i] = f[i + 1]; // carry forward the best result from right
    }
    for (int i = 1; i <= n; i++)
      cout << f[i] << " ";
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/