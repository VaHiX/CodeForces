// Problem: CF 1625 B - Elementary Particles
// https://codeforces.com/contest/1625/problem/B

/*
B. Elementary Particles

Algorithm:
This problem asks us to find the maximum length of two different subsegments that are "harmonious" — meaning they share at least one position where their elements are equal.

Approach:
- For each element in the array, we keep track of its last seen position.
- When an element is encountered again, we compute the distance from its previous occurrence.
- To find the longest harmonious pair, we look for the minimum distance between two occurrences of the same element.
- The result is calculated as: n - min_distance, but if no such pair exists (min_distance == n+1), we return -1.

Time Complexity: O(n * log n) due to map operations — each insertion and lookup in std::map takes O(log n).
Space Complexity: O(n) for storing positions in the map.

Input Format:
- First line contains number of test cases t.
- For each test case:
  - First line: n (number of elements)
  - Second line: n integers representing particle types

Output Format:
- For each test case, print maximum length of harmonious pair of different subsegments,
  or -1 if no such pair exists.
*/

#include <cstdio>
#include <map>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, long> pos; // Map to store last seen index of each element
    long md(n + 1); // Initialize minimum distance to a large value
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (pos.count(x)) { // If this element was seen before
        md = (md < (p - pos[x]) ? md : (p - pos[x])); // Update min distance
      }
      pos[x] = p; // Store current index of the element
    }
    printf("%ld\n", n - md); // Output result or -1 if needed
  }
}


// https://github.com/VaHiX/codeForces/