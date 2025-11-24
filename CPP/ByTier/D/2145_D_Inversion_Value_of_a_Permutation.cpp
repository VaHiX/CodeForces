// Problem: CF 2145 D - Inversion Value of a Permutation
// https://codeforces.com/contest/2145/problem/D

/*
D. Inversion Value of a Permutation
Algorithms/Techniques: Dynamic Programming, Greedy Construction

Time Complexity: O(n^3) per test case
Space Complexity: O(n^2) for the DP table f[32][500]

This code constructs a permutation of length n with inversion value exactly k.
It uses dynamic programming to determine whether a valid configuration exists,
and then greedily builds the permutation by selecting segments that contribute
the required number of inversions.

The inversion value is defined as the number of subsegments of the permutation
that contain at least one inversion (a pair i<j such that p[i]>p[j]).

The approach precomputes the DP table f[i][k] = whether it's possible to form
a permutation of length i with k inversions. Then, during construction,
it greedily selects the largest segment that fits within remaining constraints,
and appends those elements in reverse order to satisfy inversion count.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int n, k, f[32][500];
std::vector<int> ans;
void Main() {
  scanf("%d%d", &n, &k), k = n * (n + 1) / 2 - k, ans.clear();
  if (!f[n][k])
    return puts("0"), void(); // If no valid permutation exists, output 0
  for (int now = n, j = 1; now;) {
    for (int i = 1; i <= now; i++)
      if (k - i * (i + 1) / 2 >= 0 && f[now - i][k - i * (i + 1) / 2]) {
        now -= i;
        for (int v = j + i - 1; v >= j; v--) // Append elements in reverse to construct inversion
          ans.push_back(v);
        j += i, k -= i * (i + 1) / 2; // Update remaining length and inversion count
        break;
      }
  }
  std::reverse(ans.begin(), ans.end()); // Reverse final list to get correct order
  for (int i : ans)
    printf("%d ", i);
  puts("");
}
int main() {
  f[0][0] = 1; // Base case: empty permutation with 0 inversions is valid
  for (int i = 0; i < 30; i++)
    for (int k = 0; k < 500; k++)
      if (f[i][k])
        for (int j = 1; i + j <= 30 && k + i * (i + 1) / 2 < 500; j++)
          f[i + j][k + j * (j + 1) / 2] = 1; // Fill DP table by considering adding a segment of size j
  int t;
  scanf("%d", &t);
  while (t--)
    Main();
}


// https://github.com/VaHiX/CodeForces/