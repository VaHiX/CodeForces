// Problem: CF 493 B - Vasya and Wrestling
// https://codeforces.com/contest/493/problem/B

/*
 * Problem: Vasya and Wrestling
 * Purpose: Determine the winner of a wrestling match based on point accumulation,
 *          lexicographical comparison of point sequences, and last technique performed.
 *
 * Algorithms/Techniques:
 * - Simulation of point scoring for two wrestlers
 * - Lexicographical comparison of sequences
 * - Simple comparison logic for tie-breaking
 *
 * Time Complexity: O(n), where n is the number of techniques. We iterate through all techniques once.
 * Space Complexity: O(n), due to storing the sequences of points for both wrestlers.
 */

#include <algorithm>
#include <iostream>
#include <vector>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, p, l;
  ll s1 = 0, s2 = 0;
  vector<ll> f;
  vector<ll> s;
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> p;
    if (i == n - 1)
      l = p;
    if (p > 0) {
      s1 += p;
      f.push_back(p);
    } else {
      s2 += (-1 * p);
      s.push_back(p * -1);
    }
  }
  if (s1 > s2)
    cout << "first" << endl;
  else if (s2 > s1)
    cout << "second" << endl;
  else {
    if (s == f) {
      if (l > 0)
        cout << "first";
      else
        cout << "second";
    } else {
      vector<ll>::iterator p = f.begin();
      vector<ll>::iterator q = s.begin();
      while (p != f.end() || q != s.end()) {
        if (*p == *q) {
          p++;
          q++;
        } else {
          if (*p > *q)
            cout << "first";
          else
            cout << "second";
          break;
        }
      }
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/