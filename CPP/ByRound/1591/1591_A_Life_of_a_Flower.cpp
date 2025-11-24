// Problem: CF 1591 A - Life of a Flower
// https://codeforces.com/contest/1591/problem/A

/*
 * Problem: A. Life of a Flower
 * Algorithm/Techniques: Simulation
 * Time Complexity: O(n) where n is the number of days
 * Space Complexity: O(1)
 *
 * The flower starts at 1 cm height.
 * - If watered on day i, it grows by 1 cm (or 5 cm if also watered on day i-1).
 * - If not watered on day i and was not watered on day i-1, the flower dies (return -1).
 * - If not watered on day i but was watered on day i-1, no growth occurs.
 */
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long prev(0), res(1); // 'res' initializes to 1 cm (initial height), 'prev' tracks previous day's water status
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (res < 0) {
        continue; // If flower already died, skip further processing
      }
      if (x) { // If today is watered
        res += prev ? 5 : 1; // Add 5 if previous day was also watered, else add 1
      } else if (p && !prev) {
        res = -1; // Flower dies if not watered today but wasn't watered yesterday
      }
      prev = x; // Update previous day's status
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/