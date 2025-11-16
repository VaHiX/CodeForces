// Problem: CF 1812 G - Colour Vision
// https://codeforces.com/contest/1812/problem/G

/*
 * Problem: G. Colour Vision
 * 
 * Purpose: Determines if two strings (representing color sequences) are compatible 
 *          under specific transformation rules. Two colors are compatible if:
 *          - Both are 'R' (Red)
 *          - One is 'B' (Blue) and the other is 'G' (Green)
 *          - Both are 'B' (Blue)
 *          - Both are 'G' (Green)
 * 
 * Algorithm:
 *   - For each position in the two strings, check if the pair of characters 
 *     satisfies one of the valid compatibility conditions.
 *   - If any mismatch is found, set a flag to false.
 *   - Output "YES" if all positions are valid, otherwise "NO".
 * 
 * Time Complexity: O(n) where n is the length of the strings.
 * Space Complexity: O(1) excluding input storage.
 */

#include <stddef.h>
#include <iostream>
#include <string>

using namespace std;
#define pb push_back
#define ll long long
#define lol long long int
#define ff first
#define ss second
#define sz(v) (int)v.size()
#define All(v) v.begin(), v.end()
#define yes cout << "YES" << endl
#define no cout << "NO" << endl
#define minus cout << "-1" << endl
const int sz = 1e5 + 5;
const int mod = 1e9 + 7;
const int N = 1e6 + 100;
const int zc = 2e5 + 100;
const int MOD = 998244353;

void hira() {
  ll n;
  cin >> n;
  string x, y;
  cin >> x >> y;
  bool ok = true;  // Flag to indicate if all color pairs are compatible
  for (ll i = 0; i < n; i++) {
    // If both are 'R', they are compatible
    if (x[i] == 'R' and y[i] == 'R')
      ;
    // If x is 'B' and y is 'G', they are compatible
    else if (x[i] == 'B' and y[i] == 'G')
      ;
    // If both are 'B', they are compatible
    else if (x[i] == 'B' and y[i] == 'B')
      ;
    // If both are 'G', they are compatible
    else if (x[i] == 'G' and y[i] == 'G')
      ;
    // If x is 'G' and y is 'B', they are compatible
    else if (x[i] == 'G' and y[i] == 'B')
      ;
    // All other cases are incompatible
    else
      ok = false;
  }
  if (ok) {
    yes;
  } else {
    no;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  ll t;
  cin >> t;
  while (t--) {
    hira();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/