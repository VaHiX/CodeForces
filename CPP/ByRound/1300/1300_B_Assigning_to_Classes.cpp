// Problem: CF 1300 B - Assigning to Classes
// https://codeforces.com/contest/1300/problem/B

/*
 * Problem: Assigning to Classes
 * 
 * Purpose: Given 2n students with skill levels, partition them into two classes,
 *          each with an odd number of students, such that the absolute difference
 *          between the medians of the two classes is minimized.
 * 
 * Algorithm: 
 *   - Sort the array of skill levels.
 *   - To minimize the difference between the medians of two odd-sized classes,
 *     we can consider splitting the sorted array into two parts such that one
 *     part has n students and the other has n students, and we take the median
 *     of each part.
 *   - The optimal split minimizes |median1 - median2|, which occurs when we split
 *     the sorted array at positions n-1 and n, and take the difference between
 *     a[n] and a[n-1].
 * 
 * Time Complexity: O(n log n) per test case due to sorting.
 * Space Complexity: O(n) for storing the array of skill levels.
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
    std::vector<long> a(2 * n);
    for (long p = 0; p < 2 * n; p++) {
      scanf("%ld", &a[p]);
    }
    sort(a.begin(), a.end());  // Sort the array to facilitate median calculation
    printf("%ld\n", a[n] - a[n - 1]);  // Difference between adjacent elements in sorted array gives minimal difference
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/