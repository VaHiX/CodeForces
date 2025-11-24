// Problem: CF 1613 B - Absent Remainder
// https://codeforces.com/contest/1613/problem/B

/*
Code Purpose:
This code solves the problem of finding floor(n/2) pairs of integers from a given sequence such that:
- Each pair consists of two distinct elements from the sequence.
- The remainder of the first element divided by the second does not appear in the sequence.
The algorithm works by sorting the array and then pairing each element (except the smallest) with the smallest element.
This strategy ensures that the remainder will be less than the smallest element, and hence not present in the sorted array.

Algorithms/Techniques:
- Sorting the array to simplify pairing logic.
- Greedy pairing strategy where each element (except the smallest) is paired with the smallest element.
- Using the property that for any x > y, x % y < y, which helps in ensuring that the remainder is not in the sorted array.

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array.
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
    sort(a.begin(), a.end());  // Sort the array to simplify pairing
    for (long p = 1; p <= n / 2; p++) {
      printf("%ld %ld\n", a[p], a[0]);  // Pair each element with the smallest element
    }
  }
}


// https://github.com/VaHiX/CodeForces/