/*
 * Problem URL : https://codeforces.com/contest/490/problem/B
 * Submit Date : 2025-09-06
 */

#include <cstdio>
#include <map>
#include <set>
#include <vector>

int main() {

  long n;
  scanf("%ld\n", &n);

  std::vector<long> sequence(n, 0);
  std::map<long, long> order;

  for (long p = 0; p < n; p++) {
    long before, after;
    scanf("%ld %ld\n", &before, &after);
    order.insert(std::pair<long, long>(before, after));
  }

  long current = 0;
  for (long p = 1; p < n; p += 2) {
    if (order.find(current) == order.end()) {
      break;
    }
    sequence[p] = order[current];
    order.erase(current);
    current = sequence[p];
  }

  std::set<long> remainingNodes;
  for (std::map<long, long>::iterator mapIter = order.begin();
       mapIter != order.end(); mapIter++) {
    if (mapIter->second == 0) {
      sequence[n - 2] = mapIter->first;
      continue;
    }
    remainingNodes.insert(mapIter->first);
    remainingNodes.insert(mapIter->second);
  }

  for (std::map<long, long>::iterator mapIter = order.begin();
       mapIter != order.end(); mapIter++) {
    remainingNodes.erase(mapIter->second);
  }

  current = (remainingNodes.size() > 0) ? (*remainingNodes.begin()) : -1;
  for (long p = 0; p < n; p += 2) {
    if (current < 0) {
      break;
    }
    sequence[p] = current;
    if (order.find(current) == order.end() || order[current] == 0) {
      break;
    }
    current = order[current];
  }

  for (long p = 0; p < n; p++) {
    printf("%ld ", sequence[p]);
  }
  puts("");

  return 0;
}
