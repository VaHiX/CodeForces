// Problem: CF 2098 E - Bermuda Triangle
// https://codeforces.com/contest/2098/problem/E

/*
E. Bermuda Triangle

Purpose:
This code solves a problem where an airplane moves inside a right triangle with vertices at (0,0), (0,n), and (n,0).
The airplane starts at point (x,y) and moves with velocity vector (vx, vy). It reflects off the boundary of the
triangle according to the laws of physics. The program determines whether the airplane can escape from the
triangle by reaching a vertex, and if so, how many times it hits the boundary before escaping.

Algorithms:
- Extended Euclidean Algorithm for solving linear Diophantine equations.
- Modular arithmetic to compute time of collision.
- Mathematical analysis of trajectory using reflections.

Time Complexity: O(log(min(vx, vy)) + log(n)) per test case. This accounts for GCD and extended Euclidean operations.
Space Complexity: O(1) - only a constant amount of extra space is used.
*/

#include <algorithm>
#include <iostream>
#include <utility>

#define whatis(x) cerr << #x << " is " << x << endl;
using ll = long long;
using namespace std;

void solve() {
  ll n, x, y, vx, vy;
  cin >> n >> x >> y >> vx >> vy;
  // Mirror the initial position to make calculations easier
  x = n - x;
  y = n - y;
  ll speeddiff = __gcd(vx, vy);
  vx /= speeddiff;
  vy /= speeddiff;

  // Compute GCDs for normalization
  ll an = __gcd(vx, n);
  ll bn = __gcd(vy, n);

  // If position is not divisible by the normalized speeds, no solution exists
  if (x % an || y % bn) {
    cout << "-1\n";
    return;
  }

  // Extended Euclidean Algorithm for solving vx * t ≡ x (mod n)
  pair<pair<ll, ll>, pair<ll, ll>> euclidX;
  euclidX.first = {1, 0};
  euclidX.second = {0, 1};
  pair<ll, ll> currx = {vx, n};
  while (currx.second != 0) {
    ll num = currx.first / currx.second;
    swap(currx.first, currx.second);
    currx.second -= num * currx.first;
    swap(euclidX.first, euclidX.second);
    euclidX.second.first -= num * euclidX.first.first;
    euclidX.second.second -= num * euclidX.first.second;
  }

  // Extended Euclidean Algorithm for solving vy * t ≡ y (mod n)
  pair<pair<ll, ll>, pair<ll, ll>> euclidY;
  euclidY.first = {1, 0};
  euclidY.second = {0, 1};
  pair<ll, ll> curry = {vy, n};
  while (curry.second != 0) {
    ll num = curry.first / curry.second;
    swap(curry.first, curry.second);
    curry.second -= num * curry.first;
    swap(euclidY.first, euclidY.second);
    euclidY.second.first -= num * euclidY.first.first;
    euclidY.second.second -= num * euclidY.first.second;
  }

  // Scale the solutions
  euclidX.first.first *= x / an;
  euclidY.first.first *= y / bn;

  // Compute GCD of normalized speeds to check compatibility
  ll gc = __gcd(n / an, n / bn);
  if ((euclidX.first.first - euclidY.first.first) % gc) {
    cout << "-1\n";
    return;
  }

  // Extended Euclidean Algorithm for solving (n/an) * t ≡ (euclidY.first.first - euclidX.first.first) / gc (mod n/bn)
  pair<pair<ll, ll>, pair<ll, ll>> euclidZ;
  euclidZ.first = {1, 0};
  euclidZ.second = {0, 1};
  pair<ll, ll> currz = {n / an, n / bn};
  while (currz.second != 0) {
    ll num = currz.first / currz.second;
    swap(currz.first, currz.second);
    currz.second -= num * currz.first;
    swap(euclidZ.first, euclidZ.second);
    euclidZ.second.first -= num * euclidZ.first.first;
    euclidZ.second.second -= num * euclidZ.first.second;
  }

  ll z = euclidZ.first.first;
  z *= (euclidY.first.first - euclidX.first.first) / gc;

  // Compute time of first collision
  ll time = euclidX.first.first + (z * (n / an));
  time %= n / an / gc * (n / bn);
  if (time < 0) {
    time += n / an / gc * (n / bn);
  }

  // Compute number of times each coordinate hits boundary
  ll one = (time * vx + n - x) / n;
  ll two = (time * vy + n - y) / n;

  if (one < two) {
    swap(one, two);
  }

  // Final result includes boundary hits and adjustment factor
  cout << one + two - 2 + (one - two) / 2 + (one + two) / 2 << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/