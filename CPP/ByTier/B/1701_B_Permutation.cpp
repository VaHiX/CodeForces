// Problem: CF 1701 B - Permutation
// https://codeforces.com/contest/1701/problem/B

/*
Code Purpose:
This code finds a permutation of length n and a value d such that the number of indices i where p[i] * d = p[i+1] is maximized.
The algorithm uses a greedy approach with a set to efficiently find and remove elements in order to form the longest chain possible.

Algorithms/Techniques:
- Greedy algorithm
- Set data structure for efficient lookup and removal
- Chain building by repeatedly multiplying by d

Time Complexity: O(n * log n)
Space Complexity: O(n)

The time complexity arises from inserting all elements into the set (O(n log n)), and for each element,
we may traverse a chain of length up to log n. The space complexity is due to storing the set of elements.
*/

#include <cstdio>
#include <set>
int main() {
  const long d = 2; // Fixed value of d = 2 for optimal chain building
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::set<long> s;
    for (long p = 1; p <= n; p++) {
      s.insert(p); // Insert all numbers from 1 to n into the set
    }
    printf("%ld\n", d);
    while (s.size()) {
      long cur = *s.begin(); // Get the smallest element in the set
      for (long p = cur; p <= n; p *= d) { // Build a chain starting from 'cur'
        if (!s.count(p)) { // If p is not in the set, break the chain
          break;
        }
        printf("%ld ", p); // Print the current element in the chain
        s.erase(p); // Remove the element from the set
      }
    }
    puts(""); // Print a newline after each test case
  }
}


// https://github.com/VaHiX/CodeForces/