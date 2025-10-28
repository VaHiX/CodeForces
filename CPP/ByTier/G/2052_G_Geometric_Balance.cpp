// Problem: CF 2052 G - Geometric Balance
// https://codeforces.com/contest/2052/problem/G

/*
Purpose: This code finds the smallest positive angle b such that rotating the turtle by b degrees and executing the same sequence of commands produces the same ink-covered image.

Algorithms/Techniques:
- Simulation of turtle movements with coordinate tracking
- Compression of consecutive identical operations
- Hash map for tracking inked points and their orientations
- Comparison of image sets after rotation

Time Complexity: O(n * 360 * log(n)) where n is the number of commands.
Space Complexity: O(n) for storing compressed commands and intermediate points.

The algorithm works by:
1. Parsing and compressing commands (combining consecutive same-type operations)
2. For each possible rotation angle (multiples of 45), simulating the turtle's path
3. Tracking which points are inked and in which directions
4. Comparing the resulting set of inked points for each angle with the base case (0 degrees)
5. Returning the first valid angle that produces the same image

*/
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using ll = long long;
#define int long long
const int dir[8][4] = {{1, 0, 0, 0},  {0, 1, 0, 1},  {0, 0, 1, 0},
                       {0, -1, 0, 1}, {-1, 0, 0, 0}, {0, -1, 0, -1},
                       {0, 0, -1, 0}, {0, 1, 0, -1}};
struct Point {
  array<ll, 5> pos;
  void move(int d, int v) {
    d /= 45;
    for (int i = 0; i < 4; i++) {
      pos[i] += dir[d][i] * v;
    }
  }
  bool operator<(const Point &ne) const { return pos < ne.pos; }
};
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<array<int, 2>> op;
  for (int i = 0; i < n; i++) {
    string s;
    int v;
    cin >> s >> v;
    array<int, 2> cur = {0, 0};
    if (s == "draw")
      cur = {1, v};
    else if (s == "move")
      cur = {2, v};
    else
      cur = {3, v};
    if (op.empty() || op.back()[0] != cur[0]) {
      op.push_back(cur);
    } else {
      op.back()[1] += cur[1];
    }
  }
  n = op.size();
  function<vector<Point>(int)> work = [&](int d) {
    Point cur = {0, 0, 0, 0, 0};
    vector<Point> res;
    map<Point, vector<int>> mp;
    int cd = d % 360;
    for (int i = 0; i < n; i++) {
      if (op[i][0] == 1) {
        if (!mp.count(cur)) {
          mp[cur] = vector<int>(8);
        }
        mp[cur][(cd / 45)] = 1;
        cur.move(cd, op[i][1]);
        if (!mp.count(cur)) {
          mp[cur] = vector<int>(8);
        }
        mp[cur][(cd / 45) ^ 4] = 1;
      } else if (op[i][0] == 2) {
        cur.move(cd, op[i][1]);
      } else {
        cd += op[i][1];
        cd %= 360;
      }
    }
    for (auto [k, v] : mp) {
      int cnt = 0;
      int las = -1;
      for (int i = 0; i <= 7; i++) {
        if (i < 4 && v[i] == 1 && v[i + 4] == 1) {
          v[i] = v[i + 4] = 0;
        }
        if (v[i]) {
          las = i;
          cnt++;
        }
      }
      if (cnt > 0) {
        Point nw = k;
        nw.pos[4] = las;
        res.push_back(nw);
      }
    }
    sort(res.begin(), res.end());
    return res;
  };
  vector<Point> base = work(0);
  function<bool(int)> check = [&](int d) {
    vector<Point> cp = work(d);
    int len = cp.size();
    for (int i = 0; i < len; i++) {
      for (int j = 0; j < 5; j++) {
        cp[i].pos[j] -= base[i].pos[j];
      }
    }
    for (int i = 0; i < len - 1; i++) {
      if (cp[i].pos != cp[i + 1].pos)
        return false;
    }
    return true;
  };
  for (int i = 45; i <= 360; i += 45) {
    if (check(i)) {
      cout << i << "\n";
      return 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/