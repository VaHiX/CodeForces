// Problem: CF 1941 B - Rudolf and 121
// https://codeforces.com/contest/1941/problem/B

/*
B. Rudolf and 121

Problem Description:
Given an array of integers, determine if it's possible to reduce all elements to zero using a specific operation.
The operation at index i (2 <= i <= n-1) modifies three consecutive elements as follows:
a[i-1] -= 1
a[i] -= 2  
a[i+1] -= 1

This is essentially a simulation of applying operations from left to right, where each operation effectively "removes" one unit from the current element and redistributes it to adjacent elements with specific weights.

Approach:
- Process array from left to right.
- For each position p (from 0 to n-3), if a[p] is positive, apply the operation on index p+1 (since it's not valid for first or last few indices).
- This transforms the problem into checking if we can reduce all elements to zero using a greedy simulation.
- After processing, check if final two elements are both zero.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithm used:
- Greedy simulation with linear traversal
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
    bool valid(true);
    for (long p = 0; valid && p + 2 < n; p++) {
      if (a[p] < 0) {   // If a[p] is negative, it's impossible to reduce further
        valid = false;
      }
      a[p + 1] -= 2 * a[p];  // Apply operation: subtract 2*a[p] from next element
      a[p + 2] -= a[p];      // Apply operation: subtract a[p] from element after next
    }
    valid = valid && !a[n - 2] && !a[n - 1];  // Check final two elements are zero
    puts(valid ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/