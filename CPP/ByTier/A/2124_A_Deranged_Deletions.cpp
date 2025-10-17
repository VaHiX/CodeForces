// Problem: CF 2124 A - Deranged Deletions
// https://codeforces.com/contest/2124/problem/A

/*
Purpose:
This code determines whether it's possible to delete elements from a given array such that the remaining elements form a derangement. A derangement is an array where no element appears in its sorted position.

Algorithm:
- For each test case, the algorithm checks if there exists a pair of elements (a[p], a[q]) such that a[p] > a[q]. If such a pair exists, then it's possible to delete some elements to form a derangement.
- The solution simply outputs one such valid pair if found, otherwise outputs "NO".

Time Complexity: O(n^2) per test case
Space Complexity: O(n) for storing the array

Techniques:
- Brute-force search for a valid pair (a[p], a[q]) where a[p] > a[q].
- Uses nested loops to find such a pair.
*/

#include <algorithm>
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
    long x(-1), y(-1);
    for (long p = 0; x < 0 && p < n; p++) {
      for (long q = p + 1; x < 0 && q < n; q++) {
        if (a[p] > a[q]) { // Found a valid pair where a[p] > a[q]
          x = a[p];
          y = a[q];
        }
      }
    }
    if (x < 0) {
      puts("NO"); // No such pair found, cannot form derangement
    } else {
      printf("YES\n2\n%ld %ld\n", x, y); // Output valid pair
    }
  }
}


// https://github.com/VaHiX/codeForces/