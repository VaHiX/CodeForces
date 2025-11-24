// Problem: CF 1742 B - Increasing
// https://codeforces.com/contest/1742/problem/B

/*
B. Increasing
Algorithm: Check if array elements can be rearranged to form a strictly increasing sequence.
Approach: Use a set to track unique elements. If any duplicate element is found, it's impossible to make strictly increasing array.
Time Complexity: O(n log n) due to set operations (insert and count)
Space Complexity: O(n) for storing elements in the set

Input:
- Number of test cases t
- For each test case:
  - Array length n
  - n integers

Output:
- YES if elements can be rearranged to strictly increasing order, NO otherwise
*/
#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Set to store unique elements
    long ans(true);   // Flag to track if all elements are unique
    while (n--) {
      long x;
      scanf("%ld", &x);
      if (s.count(x)) { // If element already exists in set
        ans = false;    // Not possible to make strictly increasing
      }
      s.insert(x);      // Insert element into set
    }
    puts(ans ? "YES" : "NO"); // Output result
  }
}


// https://github.com/VaHiX/codeForces/