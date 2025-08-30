/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <cstdio>
#include <vector>

std::vector<std::vector<int>> edges;
std::vector<bool> visited;
std::vector<int> distance, parents;
int cycleStart(-1);
bool done(0);

void findCycle(int node, int caller) {

  if (done) {
    return;
  }

  if (parents[node] >= 0) {

    int currentParent = caller;
    cycleStart = caller;
    while (currentParent != node) {

      distance[currentParent] = 0;
      currentParent = parents[currentParent];
    }
    distance[currentParent] = 0;
    done = 1;
    return;
  }

  parents[node] = caller;
  for (int p = 0; p < edges[node].size(); p++) {
    int nextNode = edges[node][p];
    if (nextNode == caller) {
      continue;
    }
    findCycle(nextNode, node);
  }
}

void dfs(int node, int currentDist) {
  if (visited[node]) {
    return;
  }
  visited[node] = 1;
  for (int p = 0; p < edges[node].size(); p++) {
    int nextNode = edges[node][p];
    if (visited[nextNode]) {
      continue;
    }
    if (distance[nextNode] < 0) {
      distance[nextNode] = 1 + currentDist;
    }

    dfs(nextNode, distance[nextNode]);
  }
}

int main() {

  int n;
  scanf("%d\n", &n);
  edges.resize(n + 1);
  visited.resize(n + 1, 0), distance.resize(n + 1, -1);
  parents.resize(n + 1, -1);
  for (int p = 0; p < n; p++) {
    int a, b;
    scanf("%d %d\n", &a, &b);
    edges[a].push_back(b);
    edges[b].push_back(a);
  }

  findCycle(1, 1);
  dfs(cycleStart, 0);
  for (int p = 1; p <= n; p++) {
    printf("%d ", distance[p]);
  };
  puts("");

  return 0;
}
