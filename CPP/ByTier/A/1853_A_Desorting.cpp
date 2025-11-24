// Problem: CF 1853 A - Desorting
// https://codeforces.com/contest/1853/problem/A

/*
Problem: Desorting
Algorithm/Techniques: Greedy approach to determine minimum operations to make array not sorted.
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1) - only using a constant amount of extra space.

The idea is to find the minimum number of operations needed to make the array not sorted,
by identifying where a descent occurs and calculating how many operations are required
to make a particular element smaller than its previous one. If the array is already not sorted,
0 operations are needed.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool sorted(true);              // Assume array is sorted initially
    long minnum(1e9 + 7);           // Initialize minimum operations needed to a large number
    long prev;                      // Store previous element
    scanf("%ld", &prev);            // Read first element
    for (long p = 1; p < n; p++) {  // Loop through remaining elements
      long x;
      scanf("%ld", &x);             // Read current element
      if (prev <= x) {              // If current element is >= previous, it's still sorted
        long num = 1 + (x - prev) / 2;  // Calculate min operations to make a descent
        minnum = (num < minnum) ? num : minnum;  // Update minimum
      } else {
        sorted = false;             // If current element is smaller, it's not sorted
      }
      prev = x;                     // Update previous for next iteration
    }
    printf("%ld\n", sorted ? minnum : 0);  // Output result: if sorted, return min operations; otherwise 0
  }
}


// https://github.com/VaHiX/codeForces/