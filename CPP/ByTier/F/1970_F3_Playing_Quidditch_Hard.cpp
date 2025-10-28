// Problem: CF 1970 F3 - Playing Quidditch (Hard)
// https://codeforces.com/contest/1970/problem/F3

/*
 * Problem: F3. Playing Quidditch (Hard)
 *
 * Purpose: Simulate a Quidditch match with players, balls, goals, and special items.
 *          Determine the winner based on scoring and catching the Golden Snitch.
 *
 * Algorithms/Techniques:
 * - Grid simulation with entity tracking
 * - State management for player carrying Quaffle
 * - Collision detection for elimination and scoring
 * - Game termination on Golden Snitch catch
 *
 * Time Complexity: O(T * N * M) where T is number of steps, and N,M are grid dimensions
 * Space Complexity: O(N * M + T) for grid storage and actions
 */

#include <stdlib.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using V = array<int, 2>;
int n, m, T, bel, rs, bs;
V qua, blu, gs, b[10], r[10];
vector<V> bg, rg;

// Move entity in specified direction
void mov(V &v, char c) {
  if (c == 'U')
    v[0]--;
  if (c == 'D')
    v[0]++;
  if (c == 'L')
    v[1]--;
  if (c == 'R')
    v[1]++;
}

// Print final score and exit
void print() {
  cout << "FINAL SCORE: " << rs << " " << bs;
  exit(0);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> n >> m;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) {
      string op;
      cin >> op;
      if (op == "BG")
        bg.push_back({i, j});
      else if (op[0] == 'B')
        b[op[1] - '0'] = {i, j};
      if (op == "RG")
        rg.push_back({i, j});
      else if (op[0] == 'R')
        r[op[1] - '0'] = {i, j};
      if (op == ".Q")
        qua = {i, j};
      if (op == ".B")
        blu = {i, j};
      if (op == ".S")
        gs = {i, j};
    }
  cin >> T;
  for (int t = 0; t < T; t++) {
    string p, q;
    char c;
    cin >> p >> c;
    if (c == 'C') {
      cin >> q;
      if (q == ".S") {
        cout << t << (p[0] == 'R' ? " RED" : " BLUE")
             << " CATCH GOLDEN SNITCH\n";
        (p[0] == 'R' ? rs : bs) += 10;
        print();
      }
      if (q == ".Q")
        bel = (p[0] == 'R') * 10 + p[1] - '0' + 1;
    } else if (c == 'T') {
      bel = 0;
      for (auto &x : bg)
        if (x == qua)
          cout << t << " RED GOAL\n", qua = {(n + 1) / 2, (m + 1) / 2}, rs++;
      for (auto &x : rg)
        if (x == qua)
          cout << t << " BLUE GOAL\n", qua = {(n + 1) / 2, (m + 1) / 2}, bs++;
    } else if (p == ".S")
      mov(gs, c);
    else if (p == ".Q")
      mov(qua, c);
    else if (p == ".B") {
      mov(blu, c);
      for (int i = 0; i < 10; i++)
        if (b[i] == blu) {
          cout << t << " B" << i << " ELIMINATED\n", b[i] = {0, 0};
          if (bel == i + 1)
            bel = 0;
        }
      for (int i = 0; i < 10; i++)
        if (r[i] == blu) {
          cout << t << " R" << i << " ELIMINATED\n", r[i] = {0, 0};
          if (bel == i + 11)
            bel = 0;
        }
    } else {
      int id = (p[0] == 'R') * 10 + p[1] - '0' + 1;
      V &a = id > 10 ? r[id - 11] : b[id - 1];
      mov(a, c);
      if (bel == id)
        qua = a;
      if (a == blu) {
        cout << t << " " << p << " ELIMINATED\n", a = {0, 0};
        if (bel == id)
          bel = 0;
      }
    }
  }
  print();
}


// https://github.com/VaHiX/CodeForces/