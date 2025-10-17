// Problem: CF 2005 B2 - The Strict Teacher (Hard Version)
// https://codeforces.com/contest/2005/problem/B2

/*
B2. The Strict Teacher (Hard Version)
Purpose: Given a line of n cells with m teachers positioned at various cells,
         determine the minimum number of moves required for the teachers to catch
         David, who starts at a given cell and moves optimally to avoid capture.
         Teachers act optimally to minimize the catching time.

Algorithms/Techniques:
- Binary search using upper_bound on sorted teacher positions
- Greedy optimal strategy for both David and the teachers
- Preprocessing of teacher positions to enable quick queries

Time Complexity: O(m * log m + q * log m)
Space Complexity: O(m)

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, q;
    scanf("%ld %ld %ld", &n, &m, &q);
    std::vector<long> b(m);
    for (long p = 0; p < m; p++) {
      scanf("%ld", &b[p]); // Read positions of teachers
    }
    sort(b.begin(), b.end()); // Sort teacher positions for binary search
    
    while (q--) {
      long a;
      scanf("%ld", &a); // Read David's position
      
      // Find the first teacher with position > a using upper_bound
      long pos = std::upper_bound(b.begin(), b.end(), a) - b.begin();
      
      long res(0);
      
      // If David is to the left of all teachers (pos == 0)
      if (!pos) {
        res = b[0] - 1; // Distance from first teacher to start
      } 
      // If David is to the right of all teachers (pos == m)
      else if (pos == m) {
        res = n - b.back(); // Distance from last teacher to end
      } 
      // David is between two teachers
      else {
        // Compute the maximum distance needed to catch in the gap
        res = (b[pos] - b[pos - 1]) / 2;
      }
      
      printf("%ld\n", res);
    }
  }
}


// https://github.com/VaHiX/codeForces/