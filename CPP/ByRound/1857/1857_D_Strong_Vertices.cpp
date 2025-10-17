// Problem: CF 1857 D - Strong Vertices
// https://codeforces.com/contest/1857/problem/D

/*
D. Strong Vertices
Algorithm: 
    - For each vertex u, compute a value (a[u] - b[u]).
    - An edge exists from u to v if (a[u] - b[u]) >= (a[v] - b[v]).
    - A vertex is strong if there is a path to all other vertices.
    - This can be simplified by sorting based on (a[i] - b[i]) in descending order. 
      If multiple vertices have the same value, they form a connected component and are all strong.
    - All vertices with the maximum value of (a[i] - b[i]) are strong ones.

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the pairs

*/
#include <algorithm>
#include <cstdio>
#include <vector>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> v(n); // Store (a[i] - b[i], original index)
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p].first);
      v[p].second = p + 1; // Store 1-based index
    }
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      v[p].first -= x; // Compute a[i] - b[i]
    }
    sort(v.rbegin(), v.rend()); // Sort in descending order of (a[i] - b[i])
    long cnt(0);
    for (long p = 0; p < n; p++) {
      if (v[p].first == v[0].first) { // Count how many have the maximum value
        ++cnt;
      } else {
        break;
      }
    }
    printf("%ld\n", cnt); // Print number of strong vertices
    for (long p = cnt - 1; p >= 0; p--) {
      printf("%ld ", v[p].second); // Print indices in ascending order
    }
    puts(""); // Newline after each test case
  }
}


// https://github.com/VaHiX/codeForces/