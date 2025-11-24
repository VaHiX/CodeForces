// Problem: CF 1886 B - Fear of the Dark
// https://codeforces.com/contest/1886/problem/B

/*
 * Problem: Fear of the Dark
 * 
 * Purpose: Find the minimum power `w` such that two lanterns at points A and B can 
 *          illuminate a path from origin O=(0,0) to house P=(Px, Py).
 * 
 * Approach:
 * - We model the problem using geometric reasoning:
 *   - Each lantern illuminates a circle of radius `w`.
 *   - A valid path exists if there's a way to traverse from O to P entirely within 
 *     the union of the two illuminated circles.
 * - Key insight: The minimum `w` is determined by the smallest radius such that:
 *   - Either O or P is covered by one lantern's light,
 *   - Or there is a path that uses the coverage of both lanterns, e.g., going from O to a point on the line AB, 
 *     then to P, such that this path is fully illuminated.
 * - Candidates for minimum `w` are:
 *   - Distance from O to A, O to B (if those are needed to illuminate O)
 *   - Distance from P to A, P to B (if those are needed to illuminate P)
 *   - Half the distance between A and B (to cover the path through the midpoint)
 *   - Any combination that ensures a continuous illuminated path.

 * Time Complexity: O(1) per test case — constant time operations.
 * Space Complexity: O(1) — only a few variables used.

 * Algorithms/Techniques:
 * - Geometry (Euclidean distance calculation)
 * - Greedy selection (choosing minimum `w` that covers necessary arcs)
 */

#include <cmath>
#include <cstdio>
#include <utility>

double dist(std::pair<double, double> u, std::pair<double, double> v) {
  return std::sqrt((u.first - v.first) * (u.first - v.first) +
                   (u.second - v.second) * (u.second - v.second));
}

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    std::pair<double, double> h, a, b;
    scanf("%lf %lf", &h.first, &h.second);
    scanf("%lf %lf", &a.first, &a.second);
    scanf("%lf %lf", &b.first, &b.second);
    
    // Calculate distances:
    // za = distance from origin O (0,0) to lantern A
    double za = dist(std::pair<double, double>(0.0, 0.0), a);
    // zb = distance from origin O (0,0) to lantern B
    double zb = dist(std::pair<double, double>(0.0, 0.0), b);
    // ha = distance from house P to lantern A
    double ha = dist(h, a);
    // hb = distance from house P to lantern B
    double hb = dist(h, b);
    // ab = distance between lantern A and B, then halved for midpoint consideration
    double ab = dist(a, b);
    ab /= 2.0;

    // Initialize result with maximum possible candidate
    double res = (za > ha) ? za : ha;
    double cand = (zb > hb) ? zb : hb;
    res = (res < cand) ? res : cand;

    // Consider cases where path goes from O to a point near A, then to P
    cand = (za > ab) ? za : ab;
    cand = (cand > hb) ? cand : hb;
    res = (cand < res) ? cand : res;

    // Consider cases where path goes from O to a point near B, then to P
    cand = (zb > ab) ? zb : ab;
    cand = (cand > ha) ? cand : ha;
    res = (cand < res) ? cand : res;

    printf("%.8lf\n", res);
  }
}


// https://github.com/VaHiX/CodeForces/