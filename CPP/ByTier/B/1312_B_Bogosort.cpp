// Problem: CF 1312 B - Bogosort
// https://codeforces.com/contest/1312/problem/B

/*
Purpose: This code solves the problem of shuffling an array to make it "good". 
         An array is good if for every pair of indices i < j, the condition 
         j - a[j] != i - a[i] holds. The approach is to sort the array in 
         descending order, which ensures that the transformed values j - a[j] 
         are all unique, thus satisfying the good array condition.

Algorithms/Techniques: Sorting in descending order to avoid conflicts in the 
                       transformed values j - a[j].

Time Complexity: O(n log n) per test case due to sorting.
Space Complexity: O(n) for storing the array elements.

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
    sort(a.rbegin(), a.rend());  // Sort in descending order to ensure good array property
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/