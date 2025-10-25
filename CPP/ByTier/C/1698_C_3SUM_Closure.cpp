// Problem: CF 1698 C - 3SUM Closure
// https://codeforces.com/contest/1698/problem/C

/*
C. 3SUM Closure

Algorithm:
- For each test case, we check if the array is 3SUM-closed.
- We first process the input to separate zeros and non-zeros.
- We track counts of positive, negative, and zero elements.
- If there are more than 2 positives or negatives, it's impossible to be 3SUM-closed.
- We add at most two zeros to account for potential sums that could be zero.
- Then we check all combinations of three distinct elements to see if their sum exists in the array.

Time Complexity: O(n^3) where n is the size of the array (for checking all triplets).
Space Complexity: O(n) for storing vector and set.

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
    std::vector<long> v;          // Vector to store non-zero elements, later extended with zeros
    std::set<long> s;             // Set for fast lookup of elements
    long pos(0), neg(0), z(0);    // Counters for positive, negative, and zero elements
    bool possible(true);
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (!x) {
        ++z;
        continue;
      }
      v.push_back(x);          // Add non-zero element to vector
      s.insert(x);             // Insert element into set for fast lookup
      pos += (x > 0);          // Increment positive counter if x > 0
      neg += (x < 0);          // Increment negative counter if x < 0
      if (pos > 2 || neg > 2) {   // Early termination if more than 2 positives/negatives
        possible = false;
      }
    }
    if (z) {
      v.push_back(0);          // Add one zero to vector if any exist
      s.insert(0);
    }
    if (z > 1) {
      v.push_back(0);          // Add second zero if more than one exists
      s.insert(0);
    }
    for (long p = 0; possible && p < v.size(); p++) {         // Triplet check loop
      for (long q = p + 1; possible && q < v.size(); q++) {
        for (long r = q + 1; possible && r < v.size(); r++) {
          if (!s.count(v[p] + v[q] + v[r])) {   // If sum is not in set
            possible = false;
          }
        }
      }
    }
    puts(possible ? "YES" : "NO");   // Output result
  }
}


// https://github.com/VaHiX/codeForces/