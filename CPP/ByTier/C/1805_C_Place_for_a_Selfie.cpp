// Problem: CF 1805 C - Place for a Selfie
// https://codeforces.com/contest/1805/problem/C

/*
 * Problem: C. Place for a Selfie
 * 
 * Purpose: For each parabola y = ax^2 + bx + c, find a line y = kx such that the line does not intersect or touch the parabola.
 * 
 * Algorithm:
 * 1. Store all line slopes k and sort them.
 * 2. For each parabola y = ax^2 + bx + c, compute the discriminant of the equation formed by setting the line equal to the parabola.
 *    This leads to a quadratic in x, and we want to avoid real roots (no intersection or touching).
 * 3. The condition for no intersection / touching is that the discriminant of the resulting quadratic must be negative.
 *    We can simplify this to an inequality involving k and the coefficients of the parabola.
 * 4. Use binary search to find the closest k value to b such that the discriminant is negative.
 *
 * Time Complexity: O(n log n + m log n)
 *   - Sorting: O(n log n)
 *   - For each parabola: O(log n) for binary search
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int tc;
  scanf("%d", &tc);
  while (tc--) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> k(n);
    for (int i = 0; i < n; i++)
      scanf("%d", &k[i]);
    sort(k.begin(), k.end()); // Sort the slopes for binary search
    
    while (m--) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      
      // Calculate discriminant related to intersection of line and parabola
      // We are looking to avoid real roots, so we derive the condition.
      // The intersection points occur when ax^2 + bx + c = kx => ax^2 + (b-k)x + c = 0
      // For no intersection/touching, discriminant must be negative:
      // (b-k)^2 - 4ac < 0 => (b-k)^2 < 4ac
      long long t = 4ll * a * c;
      
      // Binary search for the closest k to b that satisfies condition
      int p = lower_bound(k.begin(), k.end(), b) - k.begin();
      
      // Check if current k[p] satisfies the condition
      if (p < n && 1ll * (b - k[p]) * (b - k[p]) < t) {
        puts("YES");
        printf("%d\n", k[p]);
      } else if (p && 1ll * (b - k[p - 1]) * (b - k[p - 1]) < t) {
        // Check the previous element since lower_bound might overshoot
        puts("YES");
        printf("%d\n", k[p - 1]);
      } else
        puts("NO");
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/