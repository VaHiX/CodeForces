// Problem: CF 1993 F1 - Dyn-scripted Robot (Easy Version)
// https://codeforces.com/contest/1993/problem/F1

/*
 * Problem: F1. Dyn-scripted Robot (Easy Version)
 * 
 * Purpose:
 *   This code calculates how many times a robot returns to the origin (0,0) 
 *   after executing a script of moves repeatedly for k times, with dynamic 
 *   script modifications when the robot hits borders.
 * 
 * Approach:
 *   - The solution leverages periodic behavior of robot movements and uses 
 *     mathematical tools like modular arithmetic, extended GCD, and inverse 
 *     modular operations to efficiently count valid return points.
 *   - It models the script on a grid, computes positions, and detects periodic 
 *     cycles to avoid simulating the full k repetitions.
 * 
 * Time Complexity: O(n)
 *   - The dominant factor is looping through the script once for precomputing 
 *     cumulative positions and a second loop for counting valid return times.
 * 
 * Space Complexity: O(n)
 *   - Additional space is required for storing cumulative x and y positions, 
 *     and string buffer.
 * 
 * Algorithms/Techniques Used:
 *   - Modular arithmetic
 *   - Extended Euclidean algorithm
 *   - Modular inverse
 *   - GCD and LCM computation
 *   - Periodic pattern detection
 */

#include <algorithm>
#include <iostream>

#define ll long long
using namespace std;

// Extended Euclidean Algorithm to find x, y such that ax + by = gcd(a, b)
ll exgcd(ll a, ll b, ll &x, ll &y) {
  if (!b)
    return x = 1, y = 0, a;
  ll g = exgcd(b, a % b, y, x);
  return y -= a / b * x, g;
}

// Compute modular inverse of a mod p
ll inv(ll a, ll p) {
  ll x, y;
  exgcd(a, p, x, y);
  return (x % p + p) % p;
}

const int MAXN = 1e6 + 5;
int px[MAXN], py[MAXN];  // prefix sums of x and y coordinates
char str[MAXN];          // input script string

void solve() {
  ll _, k, n, m, ans = 0;
  cin >> _ >> k >> m >> n >> (str + 1), n *= 2, m *= 2;  // double dimensions for simulation

  // Precompute cumulative x and y positions
  for (int i = 1; i <= _; ++i) {
    px[i] = (px[i - 1] + (str[i] == 'D' ? n - 1 : str[i] == 'U')) % n;
    py[i] = (py[i - 1] + (str[i] == 'L' ? m - 1 : str[i] == 'R')) % m;
  }

  // Compute total displacement in x and y directions
  ll dx = px[_], dy = py[_];

  // Compute GCDs to find fundamental periods
  ll gx = __gcd(dx, n), gy = __gcd(dy, m);

  // Normalize period lengths
  ll p = n / gx, q = m / gy;

  // Compute modular inverses
  ll ix = inv(dx /= gx, p), iy = inv(dy /= gy, q);

  // Extended GCD for solving system of congruences
  ll u, v, d = exgcd(p, q, u, v), e = p / d * q;

  // Loop over all starting positions in the script
  for (int i = 1; i <= _; ++i) {
    // Compute required displacement to return to (0,0)
    ll rx = (n - px[i]) % n, ry = (m - py[i]) % m;

    // Skip if not compatible with the periodic pattern
    if (rx % gx || ry % gy)
      continue;

    // Use modular inverse to solve system of congruences
    rx = rx / gx * ix % p, ry = ry / gy * iy % q;

    // Skip if not solvable
    if ((ry - rx) % d)
      continue;

    // Solve equation to find the earliest return time
    ll z = q / d, s = ((ry - rx) / d * u % z + z) % z, k0 = s * p + rx;

    // If early enough, count valid occurrences within k steps
    if (k0 < k)
      ans += (k - k0 - 1) / e + 1;
  }
  cout << ans << "\n";
}

signed main() {
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/