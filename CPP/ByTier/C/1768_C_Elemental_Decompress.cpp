// Problem: CF 1768 C - Elemental Decompress
// https://codeforces.com/contest/1768/problem/C

/*
 * Problem: Elemental Decompress
 * Purpose: Given an array a of n integers, find two permutations p and q such that
 *          max(p[i], q[i]) = a[i] for all i. If no such permutations exist, output "NO".
 *
 * Algorithm:
 * - Group indices by their values in array a.
 * - For each value from n down to 1:
 *   - If value appears more than twice, impossible -> NO
 *   - If value appears exactly twice, assign both indices to p and q with the value.
 *   - If value appears exactly once, assign the same value to both p and q at that index.
 *   - If value appears zero times, use the largest remaining value from earlier groups
 *     to assign to p and q.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

#define N 200010
int a[N], b[N], t[N], t_n;
std::vector<int> vec[N];

void _() {
  int n, i;
  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    vec[i].clear();  // Clear the vector for current test case
  for (i = 1; i <= n; i++) {
    scanf("%d", a + i);
    vec[a[i]].push_back(i);  // Group indices by value
  }
  t_n = 0;
  for (i = n; i >= 1; i--) {
    if (vec[i].size() > 2)  // If value occurs more than twice, impossible
      return puts("NO"), void();
    if (vec[i].size() == 2) {  // If value occurs exactly twice
      a[vec[i][0]] = b[vec[i][1]] = i;  // Assign to p and q appropriately
      t[++t_n] = i;  // Store this value for potential later use
    } else if (vec[i].size() == 1) {  // If value occurs exactly once
      a[vec[i][0]] = b[vec[i][0]] = i;  // Assign same value to both p and q
    } else {  // If value occurs zero times (we use a stored value)
      if (!t_n)  // If no available value to use, impossible
        return puts("NO"), void();
      b[vec[t[t_n]][0]] = a[vec[t[t_n]][1]] = i;  // Use stored value for assignment
      t_n--;
    }
  }
  puts("YES");
  for (i = 1; i <= n; i++)
    printf("%d ", a[i]);  // Print permutation p
  puts("");
  for (i = 1; i <= n; i++)
    printf("%d ", b[i]);  // Print permutation q
  puts("");
}

int main() {
  int T = 1;
  scanf("%d", &T);
  while (T--)
    _();
  return 0;
}


// https://github.com/VaHiX/CodeForces/