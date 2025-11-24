// Problem: CF 1620 B - Triangles on a Rectangle
// https://codeforces.com/contest/1620/problem/B

/*
 * Problem: B. Triangles on a Rectangle
 * Algorithms/Techniques: Greedy approach to find maximum segment length on each side
 * Time Complexity: O(n), where n is the total number of points across all test cases
 * Space Complexity: O(1)
 *
 * Given a rectangle with corners at (0, 0) and (w, h), and lattice points on its sides,
 * we need to find three points forming a triangle such that exactly two belong to the same side,
 * and the area of this triangle is maximized.
 *
 * Strategy:
 *   - For each pair of adjacent sides, compute the maximum possible base length when choosing
 *     two points from one side and one point from an adjacent side.
 *   - This is done by calculating max consecutive differences in points on a side.
 *   - Compare areas formed using the max width/height segments and return the largest doubled area.
 */

#include <cstdio>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll w, h;
    scanf("%lld %lld", &w, &h);
    
    // Process horizontal sides
    ll k(0), left(0), right(0), width(0);
    scanf("%lld", &k);
    scanf("%lld", &left);
    for (ll p = 1; p < k; p++) {
      scanf("%lld", &right);
      width = right - left; // compute max segment in horizontal side
    }
    
    // Re-read and process second horizontal side to find maximum width
    scanf("%lld", &k);
    scanf("%lld", &left);
    for (ll p = 1; p < k; p++) {
      scanf("%lld", &right);
      ll cur = right - left;
      width = (width > cur) ? width : cur; // update max width
    }
    
    ll res = width * h; // area using horizontal side segment and vertical dimension
    
    // Process vertical sides
    ll bottom(0), top(0), height(0);
    scanf("%lld", &k);
    scanf("%lld", &bottom);
    for (ll p = 1; p < k; p++) {
      scanf("%lld", &top);
      height = top - bottom; // compute max segment in vertical side
    }
    
    // Re-read and process second vertical side to find maximum height
    scanf("%lld", &k);
    scanf("%lld", &bottom);
    for (ll p = 1; p < k; p++) {
      scanf("%lld", &top);
      ll cur = top - bottom;
      height = (height > cur) ? height : cur; // update max height
    }
    
    res = (res > height * w) ? res : (height * w); // compare with area from vertical side
    printf("%lld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/