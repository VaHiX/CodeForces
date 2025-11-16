// Problem: CF 1942 C2 - Bessie's Birthday Cake (Hard Version)
// https://codeforces.com/contest/1942/problem/C2

/*
Purpose: This code solves the problem of maximizing the number of triangular pieces
         of a polygon cake by choosing additional vertices to draw non-intersecting diagonals.
         It uses greedy strategy to determine optimal vertex selection for triangulation.

Algorithms/Techniques:
- Greedy algorithm
- Sorting and interval analysis
- Bit manipulation for parity checking

Time Complexity: O(x * log(x) + k * log(k)) where x is the number of pre-chosen vertices
                 and k is the number of gaps between chosen vertices.
Space Complexity: O(x + k) where x is the number of pre-chosen vertices and k is the
                  number of gaps considered.

*/

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
constexpr int Spp{1 << 20};
char buf[Spp], *p1, *p2;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, Spp, stdin), p1 == p2)         \
       ? EOF                                                                   \
       : *p1++)
template <typename T> void read(T &x) {
  char c;
  int f{1};
  do
    x = (c = getchar()) ^ 48;
  while (!isdigit(c) && c != '-');
  if (x == 29)
    f = -1, x = 0;
  while (isdigit(c = getchar()))
    x = (x << 3) + (x << 1) + (c ^ 48);
  x *= f;
}
template <typename T, typename... Args> void read(T &x, Args &...args) {
  read(x);
  read(args...);
}
int main() {
  int T;
  read(T);
  while (T--) {
    int n, x, y;
    read(n, x, y);
    int lst{0}, first{0};
    vector<int> awa; // stores the gaps between chosen vertices
    int ans{x - 2}; // initial number of triangles from x chosen vertices
    vector<int> V;
    while (x--) {
      int w;
      read(w);
      V.push_back(w);
    }
    sort(V.begin(), V.end()); // sort chosen vertices
    for (auto Q : V) { // iterate through all chosen vertices
      if (lst) {
        if (Q - lst - 1 == 1) // if gap is exactly 1
          ++ans;
        if (Q - lst - 1 >= 2) // if gap is 2 or more, add to gaps
          awa.push_back(Q - lst - 1);
      } else // first vertex
        first = Q;
      lst = Q; // update last vertex
    }
    // handle the wrap-around gap from last to first vertex
    if (first + n - lst - 1 >= 2)
      awa.emplace_back(first + n - lst - 1);
    if (first + n - lst - 1 == 1)
      ++ans;
    sort(awa.begin(), awa.end()); // sort the gaps
    for (auto z : awa) // try to fill odd-sized gaps first
      if ((z & 1) && y >= z / 2) { // if gap is odd and we can fill it
        y -= z / 2; // reduce remaining y
        ans += z / 2 * 2 + 1; // add triangles
      } else if ((z & 1)) { // if gap is odd but we don't have enough y
        ans += y * 2; // fill what we can
        goto bed; // exit early
      }
    for (auto z : awa) // handle even gaps
      if ((~z & 1) && y >= z / 2) {
        y -= z / 2;
        ans += z / 2 * 2;
      } else if (~z & 1) {
        ans += y * 2;
        goto bed;
      }
  bed:;
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/