// Problem: CF 1324 B - Yet Another Palindrome Problem
// https://codeforces.com/contest/1324/problem/B

/*
B. Yet Another Palindrome Problem

Algorithm: 
The key insight is to check if there exists a subsequence of length at least 3 that forms a palindrome.
A palindrome of length at least 3 can be formed in two primary ways:
1. By having a repeated element (like "a b a" where the first and last are same).
2. By having a middle element with identical elements on both sides.

However, since we're looking for any subsequence (not necessarily contiguous), 
the optimal approach is to iterate through the array from left to right,
keeping track of elements already seen in a set.
When we encounter an element that was previously seen,
it means we've found at least two identical elements.
If we also have elements between them, we can form a subsequence like (x, y, x), 
which is a palindrome of length at least 3.

Time Complexity: O(n) average case for each test case due to the set operations.
Space Complexity: O(n) for storing the elements in the set.

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
      scanf("%ld", &a[p]); // Read array elements
    }
    std::set<long> s; // Set to store previously seen elements
    bool res(false); // Flag to track if palindrome subsequence found
    for (long p = 0; p + 1 < n; p++) {
      if (s.count(a[p + 1])) { // If the next element was already seen
        res = true;
        break;
      }
      s.insert(a[p]); // Insert current element into set
    }
    puts(res ? "YES" : "NO"); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/