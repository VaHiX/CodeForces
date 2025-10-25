// Problem: CF 1603 A - Di-visible Confusion
// https://codeforces.com/contest/1603/problem/A

/*
 * Problem: A. Di-visible Confusion
 * Algorithms/Techniques: Simulation with greedy approach
 *
 * Time Complexity: O(n^2) in worst case per test case, but average much lower due to early termination.
 * Space Complexity: O(n) for storing the sequence.
 *
 * Description:
 * YouKn0wWho has an integer sequence. He performs operations until the sequence becomes empty:
 * select index i such that a[i] is NOT divisible by (i + 1), and erase it.
 * Determine whether it's possible to erase the entire sequence.
 */

#include <stdio.h>
#include <iosfwd>

using namespace std;
int t, n, a[100001], flag;
signed main() {
  scanf("%d", &t);
  while (t--) {
    scanf("%d", &n);
    flag = 0;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
      int k = 0;
      // Check how many consecutive positions starting from current can divide a[i]
      while (a[i] % (i + 1 - k) == 0 && k <= i - 1)
        k++;
      // If all positions up to i can divide a[i], then it's impossible to remove
      if (k == i)
        flag = 1;
    }
    if (flag)
      puts("NO");
    else
      puts("YES");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/