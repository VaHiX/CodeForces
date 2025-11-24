// Problem: CF 1635 C - Differential Sorting
// https://codeforces.com/contest/1635/problem/C

/*
 * Problem: C. Differential Sorting
 * 
 * Purpose: Given an array of integers, determine if it can be made non-decreasing 
 *          using at most n operations. Each operation selects three indices x < y < z 
 *          and replaces a[x] with a[y] - a[z]. The result must be non-decreasing.
 * 
 * Algorithms/Techniques: 
 *   - Greedy approach based on the properties of the array
 *   - Key insight: If the last two elements are in correct order, we can adjust 
 *     earlier elements by using the last two elements as references.
 * 
 * Time Complexity: O(n) per test case, where n is the size of the array.
 * Space Complexity: O(n) for storing the array.
 * 
 * Approach:
 *   1. If last two elements are not in non-decreasing order, Impossible.
 *   2. If last element is negative, check if array is already sorted.
 *      - If yes, no operations needed.
 *      - If no, Impossible.
 *   3. Otherwise, perform n-2 operations to make the array non-decreasing by 
 *      subtracting the last element from all preceding elements using the last 
 *      two elements as reference.
 */

#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<ll> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
    }
    // If last two elements are not in non-decreasing order, impossible to sort
    if (a[n - 2] > a[n - 1]) {
      puts("-1");
    } 
    // If last element is negative, we check if array is already sorted
    else if (a[n - 1] < 0) {
      bool sorted(true);
      for (long p = 1; p < n; p++) {
        if (a[p - 1] > a[p]) {
          sorted = false;
          break;
        }
      }
      puts(sorted ? "0" : "-1");
    } 
    // Else, we can perform operations to sort the array
    else {
      printf("%ld\n", n - 2);
      for (long p = 1; p < n - 1; p++) {
        // Operation: replace a[p] with a[n-1] - a[n] (using 1-indexed)
        printf("%ld %ld %ld\n", p, n - 1, n);
      }
    }
  }
}


// https://github.com/VaHiX/CodeForces/