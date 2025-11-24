// Problem: CF 1712 C - Sort Zero
// https://codeforces.com/contest/1712/problem/C

/*
C. Sort Zero
Purpose: Given an array of positive integers, find the minimum number of operations to sort it in non-decreasing order,
         where each operation sets all occurrences of a chosen value to 0.
Algorithm:
    - First pass: Identify elements that are greater than any element after them (right-to-left scan),
      these are candidates for operations.
    - Second pass: Process elements from right to left, and if any element exists in the set of candidates,
      flag that we've seen a candidate, and all previous elements become part of the solution.
    - The number of unique candidates is the answer.

Time Complexity: O(n log n)
Space Complexity: O(n)

Input Format:
    - Multiple test cases
    - For each test case:
        - n: size of array
        - Array of n positive integers (1 <= a[i] <= n)

Output Format:
    - Minimum number of operations to sort the array

*/
#include <cstdio>
#include <set>
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
    std::set<long> s;
    long cur(a.back()); // Initialize current max from the end
    for (long p = n - 2; p >= 0; p--) {
      if (a[p] > cur) {
        s.insert(a[p]); // Insert elements that are greater than current max
      } else {
        cur = a[p]; // Update current max
      }
    }
    bool flag(false);
    for (long p = n - 1; p >= 0; p--) {
      if (flag) {
        s.insert(a[p]); // Insert all elements after a candidate was found
      } else if (s.count(a[p])) { // If this element is a candidate
        flag = true; // Mark that we've entered the flag state
      }
    }
    printf("%ld\n", s.size()); // Print count of unique candidates = operations needed
  }
}


// https://github.com/VaHiX/codeForces/