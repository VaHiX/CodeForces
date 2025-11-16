// Problem: CF 977 C - Less or Equal
// https://codeforces.com/contest/977/problem/C

/*
Algorithm: Sorting + Binary Search Concept
Purpose: Find any number x such that exactly k elements in the sorted array are less than or equal to x.
Time Complexity: O(n log n) due to sorting.
Space Complexity: O(1) if we ignore the space used by input array, otherwise O(n) for the vector.

Approach:
1. Sort the array.
2. Handle edge cases:
   - If k == 0, the answer is 1 if the smallest element is greater than 1, otherwise -1.
   - If k == n, the answer is the last (largest) element.
3. If k is between 1 and n-1:
   - Check if a[k-1] == a[k]. If they are equal, it means there's no unique value that satisfies the condition, so return -1.
   - Otherwise, return a[k-1] as it's the largest value such that exactly k elements are <= x.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n, k;
  scanf("%ld %ld", &n, &k);
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  sort(a.begin(), a.end());
  if (k == 0) {
    puts((a[0] == 1) ? "-1" : "1");  // If minimum element is 1, no valid x exists for k=0
  } else if (k == n) {
    printf("%ld\n", a.back());  // All elements are <= x, so x can be the maximum element
  } else if (a[k - 1] == a[k]) {
    puts("-1");  // If the k-th and (k+1)-th elements are equal, we can't uniquely determine x
  } else {
    printf("%ld\n", a[k - 1]);  // Return the k-th smallest element which satisfies the condition
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/