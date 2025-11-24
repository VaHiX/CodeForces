// Problem: CF 1061 B - Views Matter
// https://codeforces.com/contest/1061/problem/B

/*
B. Views Matter
Algorithms/Techniques: Sorting, Greedy
Time Complexity: O(n log n)
Space Complexity: O(1)

The problem asks us to remove the maximum number of blocks such that 
the top and side views remain unchanged. This means:
- Top view: we must keep at least one block in each stack.
- Side view: we must maintain the same maximum height in each column.

We sort the stacks and then greedily determine how many blocks can be removed
while preserving both views.
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
const int maxn = 100005;
int a[maxn];

int main() {
  int n, s, f = 1;           // n: number of stacks, s: height limit, f: counter for side view
  long long sum = 0;         // total number of blocks
  scanf("%d%d", &n, &s);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);      // read block counts for each stack
    sum += a[i];             // accumulate total blocks
  }
  sort(a, a + n);            // sort stacks in ascending order
  for (int i = 1; i < n; i++) {
    if (a[i] > f)          // if current stack height exceeds the counter
      f++;                 // increment counter to maintain decreasing side view
  }
  printf("%lld\n", sum - (a[n - 1] + n - f)); // compute max removable blocks
}


// https://github.com/VaHiX/codeForces/