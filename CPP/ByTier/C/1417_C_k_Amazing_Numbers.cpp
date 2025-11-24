// Problem: CF 1417 C - k-Amazing Numbers
// https://codeforces.com/contest/1417/problem/C

/*
C. k-Amazing Numbers
Purpose: For each k from 1 to n, compute the minimum number that appears in ALL subsegments of length k.
Algorithm: 
  - For each number a in the array, store its positions in a map.
  - For each possible k (from 1 to n), check all numbers that appear in at least one subsegment of length k.
  - For a given number a, compute the minimum gap between its occurrences.
  - The k-amazing number for a is the minimum such gap across all numbers.
Time Complexity: O(n^2) average per test case, but due to constraints and optimizations,
Space Complexity: O(n)
*/
#include <cstdio>
#include <map>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::map<long, std::vector<long>> pos; // Store positions of each number
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      pos[x].push_back(p); // Record position of each occurrence
    }
    long idx(n + 1); // Track minimum gap found so far
    std::vector<long> res(n + 1, -1); // Result array initialized with -1
    for (long a = 1; a <= n; a++) {
      if (!pos.count(a)) {
        continue; // Skip numbers not present in the array
      }
      std::vector<long> cur = pos[a];
      cur.push_back(n); // Append n to handle last segment properly
      long prev(-1), mx(0); // prev tracks previous position, mx tracks max gap
      for (long p = 0; p < cur.size(); p++) {
        long dist = cur[p] - prev;
        mx = (mx > dist) ? mx : dist; // Update maximum distance
        prev = cur[p];
      }
      for (long p = mx; p < idx; p++) {
        res[p] = a; // Assign number to result for gaps up to mx
      }
      idx = (idx < mx) ? idx : mx; // Update minimal gap found so far
    }
    for (long p = 1; p <= n; p++) {
      printf("%ld ", res[p]);
    }
    puts("");
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/