// Problem: CF 1936 F - Grand Finale: Circles
// https://codeforces.com/contest/1936/problem/F

/*
 * Problem: Find the largest circle contained inside all given circles
 * Algorithm: Welzl's Algorithm for finding the smallest enclosing circle
 * Time Complexity: O(n) expected, O(n^2) worst case
 * Space Complexity: O(n)
 * 
 * The solution uses Welzl's randomized algorithm to find the smallest circle
 * that contains all given circles. The key idea is to iteratively build the
 * solution by maintaining a basis of at most 3 circles that define the current
 * smallest enclosing circle.
 * 
 * The algorithm works as follows:
 * 1. Randomly shuffle input circles
 * 2. For each circle, check if it's already inside the current solution
 * 3. If not, try to build a new solution that includes this circle
 * 4. Use geometric operations to compute circle intersections and centers
 * 
 * The code implements helper functions for geometric computations:
 * - Point operations (addition, subtraction, scaling, distance)
 * - Circle operations (constructing from 1-3 points, checking containment)
 * - Recursive algorithm to build solution (Welzl's method)
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <random>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
using lf = long double;
using pt = pair<lf, lf>;
lf &real(pt &p) { return p.first; }
lf &imag(pt &p) { return p.second; }
pt midp(pt a, pt b) {
  return pt{(real(a) + real(b)) / 2, (imag(a) + imag(b)) / 2};
}
pt addi(pt a, pt b) { return pt{(real(a) + real(b)), (imag(a) + imag(b))}; }
pt subt(pt a, pt b) { return pt{(real(a) - real(b)), (imag(a) - imag(b))}; }
pt mult(pt a, lf b) { return pt{real(a) * b, imag(a) * b}; }
lf abs(pt a) { return sqrtl(powl(real(a), 2) + powl(imag(a), 2)); }
lf dist(pt a, pt b) {
  return sqrtl(powl(real(a) - real(b), 2) + powl(imag(a) - imag(b), 2));
}
struct circ {
  pt p;
  lf r;
};
const lf inf = 1e18;
circ basis0() { return {pt{0, 0}, inf}; }
circ basis1(circ a) { return a; }
circ basis2(circ a, circ b) {
  pt aa = a.p, bb = b.p;
  pt ab = subt(bb, aa), ba = subt(aa, bb);
  lf aab = abs(ab), aba = abs(ba);
  real(ab) /= aab;
  imag(ab) /= aab;
  real(ba) /= aba;
  imag(ba) /= aba;
  pt ar = addi(aa, mult(ab, a.r)), br = addi(bb, mult(ba, b.r));
  return {midp(ar, br), dist(ar, br) / 2.0L};
}
circ basis3(circ a, circ b, circ c) {
  lf x1 = real(a.p), y1 = imag(a.p), r1 = a.r;
  lf x2 = real(b.p), y2 = imag(b.p), r2 = b.r;
  lf x3 = real(c.p), y3 = imag(c.p), r3 = c.r;
  lf a2 = x1 - x2, a3 = x1 - x3, b2 = y1 - y2, b3 = y1 - y3, c2 = r2 - r1,
     c3 = r3 - r1;
  lf d1 = x1 * x1 + y1 * y1 - r1 * r1, d2 = d1 - x2 * x2 - y2 * y2 + r2 * r2,
     d3 = d1 - x3 * x3 - y3 * y3 + r3 * r3;
  lf ab = a3 * b2 - a2 * b3;
  lf xa = (b2 * d3 - b3 * d2) / (ab * 2) - x1;
  lf xb = (b3 * c2 - b2 * c3) / ab;
  lf ya = (a3 * d2 - a2 * d3) / (ab * 2) - y1;
  lf yb = (a2 * c3 - a3 * c2) / ab;
  lf A = xb * xb + yb * yb - 1;
  lf B = 2 * (r1 + xa * xb + ya * yb);
  lf C = xa * xa + ya * ya - r1 * r1;
  lf r = -(A ? (B - sqrtl(B * B - 4 * A * C)) / (2 * A) : C / B);
  return {pt{x1 + xa + xb * r, y1 + ya + yb * r}, r};
}
bool viol(circ p, circ a) { return a.r < p.r + dist(a.p, p.p); }
circ solve(vector<circ> &v) {
  lf _nan = nan("aaa");
  mt19937_64 mt(1999999);
  shuffle(begin(v), end(v), mt);
  vector<circ> basis;
  auto trivial = [&]() {
    if (size(basis) == 0)
      return basis0();
    if (size(basis) == 1)
      return basis[0];
    if (size(basis) == 2)
      return basis2(basis[0], basis[1]);
    return basis3(basis[0], basis[1], basis[2]);
  };
  auto rec = [&](auto rec, int n) -> circ {
    if (n == 0 || size(basis) == 3)
      return trivial();
    auto c = rec(rec, n - 1);
    auto p = v[n - 1];
    if (!viol(c, p) || isnan(c.r))
      return c;
    basis.push_back(p);
    c = rec(rec, n - 1);
    basis.pop_back();
    return c;
  };
  auto c = rec(rec, size(v));
  while (isnan(c.r)) {
    shuffle(begin(v), end(v), mt);
    c = rec(rec, size(v));
  }
  return c;
}
int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n;
  cin >> n;
  vector<circ> v(n);
  for (auto &[p, r] : v) {
    ll x, y, rr;
    cin >> x >> y >> rr;
    p = {x, y};
    r = rr;
  }
  auto ans = solve(v);
  cout << setprecision(16) << fixed << real(ans.p) << " " << imag(ans.p) << " "
       << ans.r << "\n";
}


// https://github.com/VaHiX/CodeForces/