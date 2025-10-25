// Problem: CF 1957 A - Stickogon
// https://codeforces.com/contest/1957/problem/A

/*
 * Problem: Stickogon
 * Purpose: Find the maximum number of regular polygons that can be formed
 *          from given sticks, where each polygon uses only sticks of equal length.
 *
 * Algorithm:
 *   - For each stick length, count how many sticks of that length exist.
 *   - To form a regular polygon with k sides, we need exactly k sticks of the same length.
 *   - Thus, for each stick length, compute how many complete polygons (with 3 or more sides) can be formed.
 *   - Sum up all such polygons across all stick lengths.
 *
 * Time Complexity: O(n), where n is the number of sticks.
 * Space Complexity: O(1), since we use a fixed-size vector of size 101.
 */

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::vector<int> v(101); // Count of sticks for each length (1 to 100)
    long n;
    scanf("%ld", &n);
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      ++v[a]; // Increment count of sticks of length 'a'
    }
    long cnt(0);
    for (long p = 0; p <= 100; p++) {
      cnt += v[p] / 3; // Each polygon requires at least 3 sides, so divide by 3 to get number of polygons
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/