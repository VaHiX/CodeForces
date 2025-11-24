// Problem: CF 2046 A - Swap Columns and Find a Path
// https://codeforces.com/contest/2046/problem/A

/*
 * Problem: Maximum Path Sum After Column Swaps
 * 
 * Algorithm/Technique: Greedy with Column Swapping
 * 
 * Description:
 * We are given a 2-row matrix of size n columns. We can swap any two columns,
 * then select a path from (1,1) to (2,n) moving only down or right.
 * Goal is to maximize the sum of values along the path.
 * 
 * Approach:
 * Since we can reorder columns freely, for each column we can choose the
 * maximum value between the two rows. Then we add the second largest value
 * among all pairs (from the same column) to the total sum. This ensures
 * that we get the maximum possible contribution per column in the path.
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing vectors
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    std::vector<long> b(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &b[p]);
    }
    long add(-1e9), total(0);
    for (long p = 0; p < n; p++) {
      // Add the maximum of a[p] and b[p] to the total
      total += (a[p] > b[p] ? a[p] : b[p]);
      // Find the minimum of a[p] and b[p] to keep track of second best
      long second = (a[p] < b[p] ? a[p] : b[p]);
      add = (add > second ? add : second);
    }
    total += add;  // Add the best second element across all columns
    printf("%ld\n", total);
  }
}


// https://github.com/VaHiX/codeForces/