// Problem: CF 1627 B - Not Sitting
// https://codeforces.com/contest/1627/problem/B

/*
B. Not Sitting
Algorithm: Precompute all possible maximum distances Rahul can achieve for each k from 0 to n*m-1.
Time Complexity: O(1) per test case (since we precompute all values and store them in a vector)
Space Complexity: O(n * m) for storing the computed distances

The problem involves a grid of seats where two players, Rahul and Tina,
play a game with strategic choices. For each k (number of painted seats),
we determine the best possible distance between Rahul and Tina when both 
play optimally.

Key idea:
- We compute all possible distances from each cell to the four corners.
- The maximum distance from any cell to the corners gives us potential
  worst-case distances for that cell as a candidate position for Rahul.
- Sort these values to get results efficiently.

*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m;
    scanf("%ld %ld", &n, &m);
    std::vector<long> v;
    for (long row = 1; row <= n; row++) {
      for (long col = 1; col <= m; col++) {
        long da = (row - 1) + (col - 1);                      // Distance to top-left corner
        long db = (row - 1) + (m - col);                      // Distance to top-right corner
        long dc = (n - row) + (col - 1);                      // Distance to bottom-left corner
        long dd = (n - row) + (m - col);                      // Distance to bottom-right corner
        long mx = (da > db ? da : db);                        // Max of first two distances
        mx = (mx > dc ? mx : dc);                             // Max with third distance
        mx = (mx > dd ? mx : dd);                             // Max with fourth distance
        v.push_back(mx);                                      // Store the maximum distance for this cell
      }
    }
    sort(v.begin(), v.end());                               // Sort to get final result
    for (long p = 0; p < v.size(); p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/