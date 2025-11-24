// Problem: CF 1933 G - Turtle Magic: Royal Turtle Shell Pattern
// https://codeforces.com/contest/1933/problem/G

/*
Code Purpose:
This code solves the "Turtle Magic: Royal Turtle Shell Pattern" problem, which involves placing fortune cookies (circle or square) on an n×m grid such that no three consecutive cells (in any of the 8 directions) contain cookies of the same shape. The solution uses a periodic pattern approach with 8 distinct patterns to determine valid configurations based on the position modulo 4.

Algorithms/Techniques:
- Periodic pattern recognition (8 distinct patterns)
- Bitwise operations for pattern matching
- Dynamic computation of valid configurations

Time Complexity: O(q) per test case where q is the number of operations, plus O(1) preprocessing
Space Complexity: O(1) - fixed size arrays and matrices used
*/

#include <stddef.h>
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#pragma region
#define all(x) x.begin(), x.end()
#define lef(x) (x << 1)
#define rig(x) (lef(x) | 1)
#define ft first
#define sd second
#define mt make_tuple
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define rep(i, begin, end)                                                     \
  for (__typeof(begin) i = (begin) - ((begin) > (end));                        \
       i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))
typedef long long ll;
typedef pair<ll, ll> pll;
typedef pair<int, int> pii;
typedef pair<double, double> pdb;
template <typename T, typename T1>
ostream &operator<<(ostream &os, pair<T, T1> p) {
  os << "(" << p.ft << " " << p.sd << ")";
  return os;
}
template <typename T, typename T1>
istream &operator>>(istream &is, pair<T, T1> &p) {
  is >> p.ft >> p.sd;
  return is;
}
#pragma endregion
const int N = 200100;
int can[8] = {0}; // Tracks whether each pattern is still valid
vector<vector<int>> mat[8]; // Precomputed 4x4 pattern matrices for each of 8 patterns

void test() {
  // Initialize 8 distinct 4x4 pattern matrices
  mat[0] = {{0, 1, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 0}, {0, 1, 0, 1}};
  mat[1] = {{0, 1, 1, 0}, {1, 0, 0, 1}, {0, 1, 1, 0}, {1, 0, 0, 1}};
  mat[2] = {{0, 1, 0, 1}, {0, 1, 0, 1}, {1, 0, 1, 0}, {1, 0, 1, 0}};
  mat[3] = {{0, 0, 1, 1}, {1, 1, 0, 0}, {0, 0, 1, 1}, {1, 1, 0, 0}};
  // Generate the remaining 4 matrices by flipping bits of the first 4 matrices
  rep(c, 4, 8) {
    mat[c] = mat[c - 4]; // Copy the previous pattern
    rep(i, 0, 4) rep(j, 0, 4) { mat[c][i][j] ^= 1; } // XOR with 1 to flip bits
  }
  
  // All patterns start as valid
  rep(c, 0, 8) {
    can[c] = 1;
  }
  
  int rs = 8; // Initial number of valid patterns
  int n, m, q;
  cin >> n >> m >> q;
  cout << rs << '\n'; // Output initial count
  
  while (q--) {
    int x, y;
    string s;
    cin >> x >> y;
    x--, y--; // Convert to 0-based indexing
    int tp = 1; // 0 for circle, 1 for square
    cin >> s;
    if (s == "circle")
      tp = 0;
    
    rs = 0; // Reset result count
    x %= 4; // Get position within the 4x4 pattern
    y %= 4;
    
    // Check each pattern at current position
    rep(c, 0, 8) {
      if (mat[c][x][y] != tp) // If this pattern has an incompatible shape at position
        can[c] = 0; // Mark pattern as invalid
      rs += can[c]; // Add valid patterns to count
    }
    cout << rs << '\n'; // Output current count of valid patterns
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--)
    test();
  return 0;
}


// https://github.com/VaHiX/CodeForces/