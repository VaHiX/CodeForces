// Problem: CF 680 B - Bear and Finding Criminals
// https://codeforces.com/contest/680/problem/B

/*
 * Problem: Bear and Finding Criminals
 * Purpose: Determine how many criminals Limak will catch after using the BCD.
 *          The BCD tells him how many criminals exist at each distance from his city.
 *          A criminal is caught if Limak is certain it's in a city.
 *
 * Algorithm:
 * 1. Read the number of cities (n) and Limak's city (a).
 * 2. Read the criminal distribution across cities.
 * 3. Start with the criminal in Limak's city (v[a]).
 * 4. For each distance d from Limak's city:
 *    - If there is exactly one city at distance d, add that city’s criminal count.
 *    - If there are two cities at distance d, and both have the same number of criminals,
 *      add twice that number to the catch count.
 * 5. Output total criminals caught.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
#include <cstdio>
#include <vector>
int main() {
  int n, a;
  scanf("%d %d\n", &n, &a);
  std::vector<int> v(n + 1);
  for (int p = 1; p <= n; p++) {
    scanf("%d ", &v[p]);
  }
  int ans(v[a]);  // Start with criminal in Limak's city
  for (int p = 1; p <= n; p++) {
    if (a - p < 1 && a + p > n) {
      break;  // No more cities to check
    } else if (a - p >= 1 && a + p <= n && v[a - p] == v[a + p]) {
      // Both cities at distance p have same number of criminals
      ans += 2 * v[a - p];
    } else if (a - p >= 1 && a + p > n) {
      // Only left city exists
      ans += v[a - p];
    } else if (a - p < 1 && a + p <= n) {
      // Only right city exists
      ans += v[a + p];
    }
  }
  printf("%d\n", ans);
  return 0;
}


// https://github.com/VaHiX/CodeForces/