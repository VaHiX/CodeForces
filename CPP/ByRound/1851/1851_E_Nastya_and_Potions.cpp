// Problem: CF 1851 E - Nastya and Potions
// https://codeforces.com/contest/1851/problem/E

/*
 * Problem: Nastya and Potions
 * Purpose: Find minimum cost to obtain each potion type, considering that some potions can be made by mixing others.
 * Algorithm: Topological sorting with dynamic programming
 * Time Complexity: O(n + m) where n is number of potion types and m is total number of mixing relations
 * Space Complexity: O(n + m) for storing the graph and auxiliary arrays
 */

#include <stdio.h>
#include <algorithm>
#include <queue>
#include <vector>

#define int ll
#define lll __int128_t
#define ST                                                                     \
  int T;                                                                       \
  scanf("%lld", &T);                                                           \
  while (T--) {
#define STF                                                                    \
  int T;                                                                       \
  T = read();                                                                  \
  while (T--) {
#define ED }
#define foi(N) for (int i = 1; i <= N; i++)
#define foj(N) for (int j = 1; j <= N; j++)
#define fok(N) for (int k = 1; k <= N; k++)
#define fo(i, l, r) for (int i = l; i <= r; i++)
#define ro(i, l, r) for (int i = l; i >= r; i--)
#define YES printf("YES\n")
#define NO printf("NO\n")
#define W 64
#define CLR(Q)                                                                 \
  while (!Q.empty())                                                           \
    Q.pop_front();
#define lt(N) (1LL << N)
typedef long long ll;
const int inf = 2e18;
const int mod = 998244353;
namespace FAST {
char buf[1 << 20], *p1, *p2;
char gc() {
  return p1 == p2 ? p2 = buf + fread(p1 = buf, 1, 1 << 20, stdin),
                    (p1 == p2) ? EOF : *p1++ : *p1++;
}
inline int read(int f = 1, char c = gc(), int x = 0) {
  while (c < '0' || c > '9')
    f = (c == '-') ? -1 : 1, c = gc();
  while (c >= '0' && c <= '9')
    x = x * 10 + c - '0', c = gc();
  return f * x;
}
}
using FAST::read;
using namespace std;
int n, k;
int c[200010]; // cost to buy each potion
vector<int> a[200010]; // adjacency list for reverse graph (which potions depend on current potion)
int in[200010]; // in-degree of each node
int w[200010]; // minimum cost to obtain each potion type

signed main() {
  STF n = read();
  k = read();
  foi(n) c[i] = read();
  foi(k) {
    int buffer = read();
    c[buffer] = 0; // Already have this potion, so cost is zero
  }
  foi(n) a[i].clear();
  foi(n) {
    int m = read(); // number of ingredients needed to make potion i
    foj(m) {
      int buffer = read(); // ingredient index
      a[buffer].push_back(i); // add edge from ingredient to potion
      in[i]++; // increase in-degree of potion
    }
  }
  queue<int> q;
  while (!q.empty()) // Clear queue
    q.pop();
  foi(n) w[i] = 0; // Initialize costs to zero
  foi(n) if (in[i] <= 0) { // If no ingredients are needed for potion i
    w[i] = c[i]; // Cost is just the buying cost
    q.push(i); // Add to queue for processing
  }
  while (!q.empty()) { // Process nodes in topological order
    int x = q.front();
    q.pop();
    // Update the cost of potion x (in case it was cheaper when processed earlier)
    w[x] = min(w[x], c[x]);
    // For each potion that depends on potion x
    for (vector<int>::iterator it = a[x].begin(); it != a[x].end(); it++) {
      w[*it] += w[x]; // Accumulate cost
      in[*it]--; // Decrease in-degree
      if (in[*it] <= 0) // If all dependencies are met
        q.push(*it); // Add to queue for processing
    }
  }
  foi(n) printf("%lld ", w[i]); // Print results
  printf("\n");
  ED return 0;
}


// https://github.com/VaHiX/CodeForces/