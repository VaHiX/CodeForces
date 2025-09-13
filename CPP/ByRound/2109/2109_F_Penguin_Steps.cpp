/*
 * Problem URL : https://codeforces.com/problemset/problem/2109/F
 * Submit Date : 2025-08-17
 */

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = 0x3f3f3f3f;

struct Point {
  int cost, r, c;
  bool operator>(const Point &other) const { return cost > other.cost; }
};

static const int DR[4] = {-1, 0, 1, 0};
static const int DC[4] = {0, 1, 0, -1};

void solveCase() {
  int N, Pidx, Kcap;
  cin >> N >> Pidx >> Kcap;
  --Pidx;

  vector<vector<int>> terrain(N, vector<int>(N));
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> terrain[i][j];
    }
  }

  vector<string> gridMask(N);
  for (int i = 0; i < N; ++i) {
    cin >> gridMask[i];
  }

  vector<vector<int>> minMaxCost(N, vector<int>(N, INF));
  priority_queue<Point, vector<Point>, greater<Point>> pq1;

  auto pushDij1 = [&](int accumulated, int row, int col) {
    int newCost = max(accumulated, terrain[row][col]);
    if (newCost < minMaxCost[row][col]) {
      minMaxCost[row][col] = newCost;
      pq1.push({newCost, row, col});
    }
  };

  pushDij1(0, Pidx, N - 1);
  while (!pq1.empty()) {
    Point cur = pq1.top();
    pq1.pop();
    if (cur.cost > minMaxCost[cur.r][cur.c])
      continue;

    for (int d = 0; d < 4; ++d) {
      int nr = cur.r + DR[d];
      int nc = cur.c + DC[d];
      if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
        pushDij1(cur.cost, nr, nc);
      }
    }
  }

  int result1 = minMaxCost[0][0];
  int result2 = minMaxCost[N - 1][0];

  vector<vector<bool>> blocked(N, vector<bool>(N, false));
  queue<pair<int, int>> bfsQ;

  auto markBlocked = [&](int rr, int cc) {
    if (!blocked[rr][cc]) {
      blocked[rr][cc] = true;
      bfsQ.emplace(rr, cc);
    }
  };

  for (int i = 0; i < N; ++i) {
    markBlocked(0, i);
  }
  for (int i = 1; i <= Pidx; ++i) {
    markBlocked(i, N - 1);
  }

  while (!bfsQ.empty()) {
    auto [r, c] = bfsQ.front();
    bfsQ.pop();
    if (terrain[r][c] <= result1)
      continue;

    for (int dr = -1; dr <= 1; ++dr) {
      for (int dc = -1; dc <= 1; ++dc) {
        int nr = r + dr;
        int nc = c + dc;
        if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
          markBlocked(nr, nc);
        }
      }
    }
  }

  auto canAchieve = [&](int M) -> bool {
    vector<vector<int>> addCost(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (terrain[i][j] < M) {
          addCost[i][j] = (gridMask[i][j] == '1' ? (M - terrain[i][j]) : INF);
        }
        if (terrain[i][j] >= M) {
          addCost[i][j] = 0;
        }
        if (blocked[i][j] && M > result1) {
          addCost[i][j] = INF;
        }
      }
    }

    vector<vector<int>> dist2(N, vector<int>(N, INF));
    priority_queue<Point, vector<Point>, greater<Point>> pq2;

    auto pushDij2 = [&](int acc, int rr, int cc) {
      ll nd = (ll)acc + addCost[rr][cc];
      if (nd < dist2[rr][cc]) {
        dist2[rr][cc] = (int)nd;
        pq2.push({dist2[rr][cc], rr, cc});
      }
    };

    for (int x = 0; x < N; ++x)
      pushDij2(0, 0, x);
    for (int x = 1; x < N; ++x)
      pushDij2(0, x, 0);
    for (int x = 1; x <= Pidx; ++x)
      pushDij2(0, x, N - 1);

    while (!pq2.empty()) {
      Point cur2 = pq2.top();
      pq2.pop();
      if (cur2.cost > Kcap)
        break;
      if (cur2.cost > dist2[cur2.r][cur2.c])
        continue;

      if (cur2.r == N - 1 || (cur2.c == N - 1 && cur2.r >= Pidx)) {
        return true;
      }

      for (int dr = -1; dr <= 1; ++dr) {
        for (int dc = -1; dc <= 1; ++dc) {
          int nr = cur2.r + dr;
          int nc = cur2.c + dc;
          if (nr >= 0 && nr < N && nc >= 0 && nc < N) {
            pushDij2(cur2.cost, nr, nc);
          }
        }
      }
    }

    return false;
  };

  int low = result2, high = 2000000;
  while (low < high) {
    int mid = (low + high + 1) / 2;
    if (canAchieve(mid)) {
      low = mid;
    } else {
      high = mid - 1;
    }
  }

  cout << result1 << " " << low << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    solveCase();
  }
  return 0;
}