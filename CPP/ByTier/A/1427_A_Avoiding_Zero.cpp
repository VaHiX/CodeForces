// Problem: CF 1427 A - Avoiding Zero
// https://codeforces.com/contest/1427/problem/A

/*
Code Purpose:
This program solves the "Avoiding Zero" problem where we need to rearrange an array such that all prefix sums are non-zero.
The approach is based on sorting the array and then traversing it in a specific direction depending on the total sum.
If the total sum is zero, it's impossible to avoid zero prefix sums, and "NO" is printed; otherwise, a valid arrangement is printed.

Algorithms/Techniques:
1. Sort the input array.
2. Check if the total sum is zero. If yes, output "NO".
3. Otherwise, output the elements in a specific order:
   - If the sum is positive, traverse from the largest to smallest element.
   - If the sum is negative, traverse from the smallest to largest element.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array
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
    long total(0); // Calculate total sum of array elements
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      total += a[p]; // Accumulate sum
    }
    if (total == 0) { // If total sum is zero, impossible to avoid zero prefix sums
      puts("NO");
      continue;
    }
    puts("YES");
    sort(a.begin(), a.end()); // Sort the array to determine traversal order
    long start(0), stop(n), step = 1;
    if (total > 0) { // If sum is positive, we want to start from the largest element
      start = n - 1;
      stop = -1;
      step = -1;
    }
    for (long p = start; p != stop; p += step) { // Traverse according to direction
      printf("%ld ", a[p]);
    }
    puts(""); // Print newline after each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/