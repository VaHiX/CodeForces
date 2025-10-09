/*
 * Problem URL : https://codeforces.com/problemset/problem/1869/F
 * Submit Date : 2025-08-13
 */

#include <algorithm>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int N = 1e6 + 10;
int n;
pair<int, int> d[N];

void connect(int a, int b) {
  printf("%d %d\n", d[a].second, d[b].second);
  d[a].first--;
  d[b].first--;
}

void createCycle(int start, int end) {
  for (int i = start; i < end; i++) {
    connect(i, i + 1);
  }
  connect(end, start);
}

void solveLeaves(int totalLeaves) {
  for (int i = 0, j = totalLeaves; i < totalLeaves; i++) {
    while (d[j].first == 0)
      j++;
    connect(i, j);
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int cases;
  scanf("%d", &cases);
  while (cases--) {
    scanf("%d", &n);

    long long sum = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &d[i].first);
      d[i].second = i + 1;
      sum += d[i].first;
    }
    sort(d, d + n);
    int ones = 0, twos = 0;
    while (ones < n && d[ones].first == 1)
      ones++;
    while (ones + twos < n && d[ones + twos].first == 2)
      twos++;
    int left = n - ones - twos;

    if (sum != 2 * n || left == 1) {
      printf("No\n");
    } else if (ones == 0 || twos == 0) {
      printf("Yes\n");
      createCycle(ones, n - 1);
      solveLeaves(ones);
    } else if ((left + twos) % 2 == 0) {
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      int nxt = n - 1, nxtnxt = n - 2;
      for (int i = n - 3; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else if (twos + left < 5) {
      printf("No\n");
    } else if (d[n - 1].first >= 4) {
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      int nxt = n - 1, nxtnxt = n - 2;
      connect(n - 3, n - 1);
      for (int i = n - 4; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else if (left >= 3 && left + twos >= 7) {
      printf("Yes\n");
      createCycle(n - 2, n - 1);
      connect(n - 3, n - 1);
      connect(n - 4, n - 2);
      connect(n - 5, n - 3);
      int nxt = n - 3, nxtnxt = n - 4;
      for (int i = n - 6; i >= ones; i--) {
        connect(i, nxt);
        nxt = nxtnxt;
        nxtnxt = i;
      }
      solveLeaves(ones);
    } else {
      printf("No\n");
    }
  }

  return 0;
}
