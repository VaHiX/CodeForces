// Problem: CF 1174 A - Ehab Fails to Be Thanos
// https://codeforces.com/contest/1174/problem/A

/*
Purpose: 
This code determines whether an array of 2n elements can be reordered such that the sum of the first n elements is not equal to the sum of the last n elements.
It uses a greedy approach by sorting the array and checking if all elements are the same.
If all elements are the same, no valid reordering exists; otherwise, the sorted array itself works.

Algorithms/Techniques:
- Sorting
- Greedy approach

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array

*/
#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  n *= 2; // Total number of elements
  std::vector<long> a(n);
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]); // Read all elements
  }
  sort(a.begin(), a.end()); // Sort the array to check for uniformity
  if (a[0] == a.back()) { // If all elements are the same
    puts("-1"); // No valid reordering possible
  } else {
    for (long p = 0; p < n; p++) {
      printf("%ld ", a[p]); // Print sorted array (valid reordering)
    };
    puts(""); // New line
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/