// Problem: CF 1294 B - Collecting Packages
// https://codeforces.com/contest/1294/problem/B

/*
B. Collecting Packages
Algorithm: Greedy + Sorting
Time Complexity: O(n log n + S) where n is the number of packages and S is the total length of the path
Space Complexity: O(n + S) for storing package coordinates and path string

The problem asks to find the lexicographically smallest path to collect all packages,
starting from (0, 0), using only 'R' (right) and 'U' (up) moves.
To minimize the number of moves and ensure lexicographical minimality:
1. Sort the packages in lexicographical order.
2. Visit them in this sorted order.
3. For each package, move right as needed, then up.
4. If at any point moving up leads to a lower y-coordinate than current, it's impossible.
*/

#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <utility>

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<std::pair<long, long>> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld %ld", &a[p].first, &a[p].second);
    }
    sort(a.begin(), a.end()); // Sort packages in lexicographical order
    bool possible(true);
    std::string path;
    long x(0), y(0);
    for (long p = 0; p < n; p++) {
      while (x < a[p].first) { // Move right until reaching the required x-coordinate
        ++x;
        path += 'R';
      }
      if (a[p].second < y) { // If required y is less than current y, impossible
        possible = false;
        break;
      }
      while (y < a[p].second) { // Move up until reaching the required y-coordinate
        ++y;
        path += 'U';
      }
    }
    if (possible) {
      puts("YES");
      printf("%s\n", path.c_str());
    } else {
      puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/