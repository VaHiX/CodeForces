/*
 * Problem URL : https://codeforces.com/contest/601/problem/A
 * Submit Date : 2025-09-04
 */

/*
 * Problem URL : https://codeforces.com/contest/601/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>
#include <deque>
#include <vector>

int getDistance(std::vector<std::vector<bool>> g, bool flag) {

  const int n = g.size();
  const int start(0);
  const int target(n - 1);

  int dist(0);
  std::deque<int> q;
  std::vector<int> distance(n, 0);
  q.push_front(start);
  while (!q.empty()) {
    int currentNode = q.back();
    q.pop_back();
    for (int p = 0; p < n; p++) {
      if (p == start || distance[p] > 0 || g[currentNode][p] != flag) {
        continue;
      }
      distance[p] = distance[currentNode] + 1;
      if (p == target) {
        return distance[target];
      }
      q.push_front(p);
    }
  }

  return -1;
}

int main() {

  int n, m;
  scanf("%d %d\n", &n, &m);
  std::vector<std::vector<bool>> graph(n, std::vector<bool>(n, 0));
  for (int p = 0; p < m; p++) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    --a;
    --b;
    graph[a][b] = graph[b][a] = 1;
  }

  printf("%d\n", getDistance(graph, !graph[0][n - 1]));

  return 0;
}
