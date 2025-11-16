// Problem: CF 1438 B - Valerii Against Everyone
// https://codeforces.com/contest/1438/problem/B

/*
Problem: Valerii Against Everyone
Purpose: Determine if there exist two non-intersecting subarrays in array a = [2^b[0], 2^b[1], ..., 2^b[n-1]] 
         such that their sums are equal. This is equivalent to checking if there are duplicate elements in b,
         because each element in a is a distinct power of 2, and the sum of any subset of powers of 2 
         is unique unless there are repeated powers.
Algorithm: Use a set to track seen values in array b. If a value is encountered again, then it's possible 
           to form two equal sums with subarrays (this relies on the fact that 2^x == 2^y iff x == y).
Time Complexity: O(n) per test case, where n is the length of input array.
Space Complexity: O(n) for storing elements in the set.

Input:
- t test cases
- For each test case:
  - n length of array b
  - Array b of n integers (0 <= b[i] <= 1e9)

Output:
- YES if two non-intersecting subarrays have equal sums, NO otherwise.
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Set to store seen values of b
    bool ans(false); // Flag to indicate if duplicate found
    for (long p = 0; p < n; p++) {
      long b;
      scanf("%ld", &b);
      if (s.count(b)) { // If current value was seen before, there's a duplicate
        ans = true;
      }
      s.insert(b); // Insert current value into set
    }
    puts(ans ? "YES" : "NO");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/