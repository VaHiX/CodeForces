// Problem: CF 892 B - Wrath
// https://codeforces.com/contest/892/problem/B

/*
 * Problem: B. Wrath
 * Algorithm: Greedy + Interval Merging
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 *
 * The problem models a scenario where each person kills others in front of them
 * based on their claw length. We simulate this process greedily by tracking the
 * furthest index that has been killed so far. A person survives if they are not
 * within the range of any previous killer.
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[n - 1 - p]);  // Read input in reverse order
  }
  long count(0), dead(-1);  // count: number of survivors, dead: furthest killed index
  for (long p = 0; p < n; p++) {
    count += (p > dead);  // Increment count if current person is alive
    dead = (dead > p + a[p]) ? dead : (p + a[p]);  // Update furthest killed index
  }
  printf("%ld\n", count);
  return 0;
}


// https://github.com/VaHiX/CodeForces/