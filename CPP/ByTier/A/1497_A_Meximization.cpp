// Problem: CF 1497 A - Meximization
// https://codeforces.com/contest/1497/problem/A

/*
 * Code purpose: Reorder an array to maximize the sum of MEX values on all prefixes.
 * Algorithms/Techniques: Greedy approach - place 0 first, then consecutive integers in order,
 *                        followed by duplicates and remaining elements.
 * Time complexity: O(n log n) due to set operations (insertion and iteration).
 * Space complexity: O(n) for storing the set and vector.
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
    std::set<long> s;           // Set to track unique elements
    std::vector<long> v;        // Vector to store duplicates
    for (long p = 0; p < n; p++) {  // Read all elements
      long a;
      scanf("%ld", &a);
      if (s.count(a)) {         // If element already exists in set
        v.push_back(a);         // Add to duplicates vector
      } else {
        s.insert(a);            // Insert new element into set
      }
    }
    for (std::set<long>::iterator it = s.begin(); it != s.end(); it++) {  // Print unique elements in sorted order
      printf("%ld ", *it);
    }
    for (long p = 0; p < v.size(); p++) {  // Print duplicates
      printf("%ld ", v[p]);
    }
    puts("");                   // Newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/