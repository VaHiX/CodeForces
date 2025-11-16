// Problem: CF 1761 G - Centroid Guess
// https://codeforces.com/contest/1761/problem/G

/*
Algorithm: Centroid Guess using Distance Queries
Approach:
1. Randomly pick two nodes 's' and 't'.
2. Query distances from 's' and 't' to B randomly chosen nodes.
3. Group these nodes based on the difference in distances (d(s,x) - d(t,x)).
4. Use the most frequent difference group to update 's' or 't' to a node in that group.
5. After several iterations, 's' and 't' will be close to each other.
6. Compute the distances from 's' and 't' to all nodes and store them in a hash map.
7. For each pair (a,b) where a = d(s,i), b = d(t,i), calculate a - b and use this as index for pos array.
8. Count occurrences of each difference in a cnt array.
9. Find the centroid: The node whose distance from 's' and 't' results in a difference that occurs more than n/2 times in the cnt array.

Time Complexity: O(n * log(n)) approximately due to the repeated sampling and hash map operations.
Space Complexity: O(n) for storing the distance differences and auxiliary arrays.
*/
#include <stdio.h>
#include <time.h>
#include <map>
#include <random>
#include <utility>
#include <vector>

using namespace std;
const int maxn = 75005, B = 200;
int n, s, t, st, T = 120;
int cnt[maxn << 1], pos[maxn << 1];
mt19937 rnd(time(0));
map<int, vector<int>> mp;
int query(int x, int y) {
  int res;
  printf("? %d %d\n", x, y), fflush(stdout), scanf("%d", &res);
  return res;
}
int main() {
  scanf("%d", &n), s = rnd() % n + 1, t = rnd() % n + 1;
  while (T--) {
    mp.clear();
    for (int i = 1; i <= B; i++) {
      int x = rnd() % n + 1;
      mp[query(s, x) - query(t, x)].push_back(x);
    }
    int sum = 0, flg = 0;
    for (map<int, vector<int>>::iterator it = mp.begin(); it != mp.end();
         it++) {
      if ((it->second.size()) > B / 2) {
        ((sum * 2 > (B - it->second.size())) ? t : s) = it->second[0];
        break;
      }
      sum += it->second.size();
    }
  }
  st = query(s, t);
  for (int i = 1; i <= n; i++) {
    int a = query(s, i), b = query(t, i);
    if (a + b == st)
      pos[a - b + n] = i;
    cnt[a - b + n]++;
  }
  int sum = 0;
  for (int i = 0; i <= n + n; i++) {
    sum += cnt[i];
    if (sum > n / 2) {
      printf("! %d\n", pos[i]), fflush(stdout);
      return 0;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/