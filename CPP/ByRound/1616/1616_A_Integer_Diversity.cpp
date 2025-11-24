// Problem: CF 1616 A - Integer Diversity
// https://codeforces.com/contest/1616/problem/A

/*
Algorithm: Integer Diversity
Approach:
- For each number in the array, we decide whether to negate it or not.
- We use a set to keep track of unique values.
- When we encounter a number that's already in the set, we insert its negation instead.
- This ensures we maximize the number of distinct elements by avoiding duplicates.

Time Complexity: O(n log n) per test case due to set operations (insert and count).
Space Complexity: O(n) for storing elements in the set.

Problem: Given an array of integers, determine the maximum number of distinct values 
         achievable by negating any subset of numbers.
*/

#include <cstdio>
#include <set>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s; // Set to store unique values
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (s.count(x)) { // If x is already present in set
        s.insert(-x);   // Insert negation of x to avoid duplication
      } else {
        s.insert(x);    // Insert x as it's unique so far
      }
    }
    printf("%ld\n", s.size()); // Output number of distinct elements
  }
}


// https://github.com/VaHiX/codeForces/