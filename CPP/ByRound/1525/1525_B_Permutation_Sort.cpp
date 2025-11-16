// Problem: CF 1525 B - Permutation Sort
// https://codeforces.com/contest/1525/problem/B

/*
B. Permutation Sort
Algorithm: Greedy approach to determine minimum operations to sort a permutation.
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the permutation

The problem requires us to sort a permutation using operations where we can choose any subarray (except the whole array) and rearrange its elements. 
We analyze the given permutation to determine how many operations are needed:
- If already sorted, 0 operations.
- If first element is 1 or last element is n, 1 operation suffices.
- If first element is n and last element is 1, 3 operations are needed.
- Otherwise, 2 operations are sufficient.
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
    long x(0);
    bool sorted(true);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]); // Read each element of the permutation
      if (a[p] < x) {     // Check if current element is less than previous, indicating unsorted
        sorted = false;
      }
      x = a[p]; // Update previous element
    }
    if (a[0] == 1 && a.back() == n && sorted) {
      puts("0"); // Already sorted and starts with 1 and ends with n
    } else if (a[0] == 1 || a.back() == n) {
      puts("1"); // Either start with 1 or end with n, one operation suffices
    } else if (a[0] == n && a.back() == 1) {
      puts("3"); // Special case: starts with n and ends with 1, needs three operations
    } else {
      puts("2"); // Default case: two operations required
    }
  }
}


// https://github.com/VaHiX/codeForces/