// Problem: CF 1424 N - BubbleSquare Tokens
// https://codeforces.com/contest/1424/problem/N

/*
N. BubbleSquare Tokens
Algorithms/Techniques: Graph processing, greedy selection of tokens to satisfy unique token counts for each node.
Time Complexity: O(n * d + k), where d is the maximum degree of any node.
Space Complexity: O(n + k), for storing graph structure and auxiliary arrays.

The problem models a graph where nodes are members and edges are friendships.
Each member initially gets 1 token, plus 2 tokens for each friend.
We must assign token counts to edges such that node token counts are all distinct.
Also, each node can return some tokens (up to one per personal token).
Nodes keep their personal token if they cannot be balanced with edge tokens alone.
*/
#include <stdio.h>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;
#define SZ(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define loop(i, n) for (int i = 0; i < (n); ++i)
#define cont(i, n) for (int i = 1; i <= (n); ++i)
#define circ(i, a, b) for (int i = (a); i <= (b); ++i)
#define range(i, a, b, c)                                                      \
  for (int i = (a); ((c) > 0 ? i <= (b) : i >= (b)); i += (c))
#define foreach(it, v)                                                         \
  for (__typeof((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define y0 y0O0OO00OO0OO0OO0OOO00OO0OO0O0O000OO0
#define y1 y1II11II11III11I1III11II111IIII1II1I1
#define pub push_back
#define pob pop_back
#define mak make_pair
typedef long long ll;
typedef long double lf;
const int Inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
int n, k;
int u[1 << 20], v[1 << 20];
bool sel[1 << 14]; // Whether a node keeps its personal token
vector<pair<int, int>> nei[1 << 14], egs[1 << 14]; // nei[i] = edges from node i; egs[i] = edges involving node i
bool lgl[1 << 21]; // Used for marking edge IDs in local scope
int val[1 << 20], F[1 << 20]; // val[i] = assigned tokens to edge i; F[i] = counter for current processing
int main() {
  scanf("%d%d", &n, &k);
  cont(i, k) {
    int a, b;
    scanf("%d%d", &a, &b);
    u[i] = a;
    v[i] = b;
    if (a < b)
      swap(a, b); // Ensure a >= b for consistent indexing
    nei[a].pub(mak(b, i)); // Store edge (b) with its ID (i)
    egs[a].pub(mak(b, i));
    egs[b].pub(mak(a, i));
    val[i] = 1; // Initially each edge contributes 1 token
  }
  cont(i, n) {
    int fix = 0; // Running fix value for current node
    loop(j, SZ(nei[i])) { // Process neighbors of node i
      int to = nei[i][j].first, eg = nei[i][j].second;
      if (sel[to]) { // If neighbor keeps personal token
        sel[to] = 0; // Mark to not keep personal token anymore
        ++val[eg]; // Increase tokens for this edge as compensation
      }
    }
    loop(j, SZ(egs[i])) fix += val[egs[i][j].second]; // Accumulate total fixed tokens from edges
    circ(j, fix - SZ(nei[i]), fix) lgl[j] = 0; // Reset local markings for edge assignment
    loop(j, SZ(nei[i])) lgl[F[nei[i][j].first]] = 1; // Mark edge IDs related to neighbors
    loop(j, SZ(nei[i])) {
      int to = nei[i][j].first, eg = nei[i][j].second;
      if (lgl[fix]) { // If we can assign a token to neighbor
        sel[to] = 1; // Give personal token to neighbor
        --val[eg]; // Reduce edge contribution as compensation
        --fix; // Decrease the fix value
      } else {
        break; // No valid assignment, stop this process
      }
    }
    F[i] = fix; // Store current fix value for this node
  }
  int all = 0;
  cont(i, n) all += sel[i]; // Count how many keep personal tokens
  printf("%d\n", all);
  cont(i, n) if (sel[i]) printf("%d\n", i); // Output members keeping personal tokens
  cont(i, k) printf("%d %d %d\n", u[i], v[i], val[i]); // Output edge assignments
  return 0;
}


// https://github.com/VaHiX/codeForces/