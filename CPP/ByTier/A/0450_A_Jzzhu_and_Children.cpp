// Problem: CF 450 A - Jzzhu and Children
// https://codeforces.com/contest/450/problem/A

/*
 * Problem: Jzzhu and Children
 * Purpose: Determine the last child to go home based on candy distribution process.
 * Algorithm: Simulate the distribution by calculating how many rounds each child needs,
 *            then find the child requiring the maximum number of rounds.
 *
 * Time Complexity: O(n), where n is the number of children.
 * Space Complexity: O(1), only using a constant amount of extra space.
 */

#include <cstdio>
int main() {
  int n, m;
  scanf("%d %d\n", &n, &m);
  int currentMax(0), lastChild(0);
  for (int p = 1; p <= n; p++) {
    int need;
    scanf("%d", &need);
    // Calculate number of rounds needed for this child
    int temp = (need / m) + ((need % m) > 0);
    // If this child requires more rounds than previously seen,
    // update the max rounds and record this child as the last one
    if (temp >= currentMax) {
      currentMax = temp;
      lastChild = p;
    }
  }
  printf("%d\n", lastChild);
  return 0;
}


// https://github.com/VaHiX/CodeForces/