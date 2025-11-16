// Problem: CF 1105 A - Salem and Sticks 
// https://codeforces.com/contest/1105/problem/A

/*
A. Salem and Sticks 
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Salem gave you n sticks with integer positive lengths a_1, a_2, ..., a_n.
For every stick, you can change its length to any other positive integer length (that is, either shrink or stretch it). The cost of changing the stick's length from a to b is |a - b|, where |x| means the absolute value of x.
A stick length a_i is called 
almost good
 for some integer t if |a_i - t| <= 1.
Salem asks you to change the lengths of some sticks (possibly all or none), such that all sticks' lengths are almost good for some positive integer t and the total cost of changing is minimum possible. The value of t is not fixed in advance and you can choose it as any positive integer. 
As an answer, print the value of t and the minimum cost. If there are multiple optimal choices for t, print any of them.

Algorithm: Sorting + Brute Force
Time Complexity: O(n log n + n * R) where R is the range of stick lengths (100 in constraints)
Space Complexity: O(n)

The solution works as follows:
- Sort the array to easily find median(s).
- Consider t values around the median to reduce search space.
- For each candidate t, compute the total cost of modifying sticks such that all are within [t-1, t+1].
- The range for t is limited to median ± 1 to ensure minimum cost.
*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);
  // Read input stick lengths
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  // Sort the array to find median easily
  sort(a.begin(), a.end());
  // Compute median (average of two middle elements for even n, single middle for odd)
  long median = (a[(n - 1) / 2] + a[n / 2]) / 2;
  // Initialize variables to track minimum cost and its corresponding t
  long mid(0), minCost(1e10);
  // Check candidate t values around median (median-1, median, median+1)
  for (long t = median - 1; t <= median + 1; t++) {
    if (t <= 0) {
      continue;
    }
    long cost(0);
    // Calculate total cost for this t
    for (long p = 0; p < n; p++) {
      // If stick is shorter than t-1, we must increase it to t-1
      if (a[p] < t - 1) {
        cost += t - 1 - a[p];
      } 
      // If stick is longer than t+1, we must decrease it to t+1
      else if (a[p] > t + 1) {
        cost += a[p] - t - 1;
      }
    }
    // Update minimum cost and corresponding t if we found better solution
    if (cost < minCost) {
      minCost = cost;
      mid = t;
    }
  }
  printf("%ld %ld\n", mid, minCost);
  return 0;
}


// https://github.com/VaHiX/codeForces/