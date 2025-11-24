// Problem: CF 1457 B - Repainting Street
// https://codeforces.com/contest/1457/problem/B

/*
B. Repainting Street

Algorithm:
This problem uses a greedy approach combined with a sliding window technique. For each possible target color (from 1 to 100), we check how many groups of k consecutive houses need to be repainted if all houses are to be painted in that color. The key idea is to iterate through the array, and for each group of k houses, if the house colors don't match the target color, we must repaint it. Since we can repaint k houses at once per day, we count the number of such operations required.

Time Complexity:
O(100 * n) where 100 is the number of possible colors (since colors are bounded by 100)
Space Complexity:
O(n + 100) for storing the vector and color visibility array

*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, k;
    scanf("%ld %ld", &n, &k);
    std::vector<long> col(n); // Stores the colors of houses
    std::vector<bool> cv(107, 0); // Tracks which colors are present in the street
    for (long p = 0; p < n; p++) {
      scanf("%ld", &col[p]);
      cv[col[p]] = 1; // Mark color as present
    }
    long res(n + 1); // Initialize result with maximum possible value
    for (long cand = 1; cand <= 100; cand++) {
      if (!cv[cand]) {
        continue; // Skip unused colors
      }
      long idx(0), cnt(0); // idx: current index, cnt: number of operations needed
      while (idx < n) {
        if (col[idx] == cand) {
          ++idx;
          continue; // If the color matches target, move to next house
        }
        ++cnt; // Increment count as we will repaint a block
        idx += k; // Skip k houses since this block can be repainted in one day
      }
      res = (res < cnt) ? res : cnt; // Keep minimum operations across all colors
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/