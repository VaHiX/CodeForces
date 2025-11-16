// Problem: CF 1093 D - Beautiful Graph
// https://codeforces.com/contest/1093/problem/D

/*
 * Problem: D. Beautiful Graph
 * 
 * Purpose: Given an undirected unweighted graph, assign numbers 1, 2, or 3 to each vertex
 * such that for every edge, the sum of the numbers on its two vertices is odd.
 * Count the number of valid assignments modulo 998244353.
 * 
 * Approach:
 * - For each edge (u,v), the sum of values on u and v must be odd.
 *   This means one vertex has an even value and the other has an odd value.
 * - A vertex can have value 1,2, or 3: odd values are {1,3}, even values are {2}.
 * - Since the constraint applies to all edges, the graph must be bipartite to allow such coloring,
 *   where we assign alternating even/odd values to connected components.
 * - This is essentially a 2-coloring problem on subsets of vertices, followed by valid assignment counts:
 *   Each connected component can be seen as a bipartition (two color classes). 
 *   For a connected component with n1 nodes colored first and n2 colored second, 
 *   we compute: 3 * n1 * 3 * n2 assignments for each node.
 *   However, since we are not allowed to use two identical values across an edge,
 *   and the constraints are more complex than simple coloring, a simpler way is:
 *   - For each component:
 *     - If it's bipartite (no odd-length cycles), then assign 2 choices of parity per connected component (color classes).
 *     - Assign the first vertex in each component arbitrarily to one color.
 *     - Then for each node in a group (say, n1 nodes) you can choose from {1,3} or {2}.
 *       So there are 2^k valid ways to assign numbers for k connected components.
 * - But since vertices can take one of three values and we need all edges to sum to odd:
 *   - A graph is good if it's bipartite.
 *   - If a component contains n nodes, it can be colored into two groups (say size a,b)
 *     such that no edge connects same-colored nodes.
 *     So each group can use values {1,3} or {2}, which gives:
 *       For one group of size a -> 2^a choices,
 *       For other group of size b -> 2^b choices total 2^(a+b) = 2^n ways.
 *   - But wait! We must consider that for an edge (u,v), if u=1, v=2; or u=3, v=2 etc.
 *     That's all combinations allowed by (odd+even).
 * - Thus, valid value assignments follow a bipartite coloring rule:
 *   If the graph is NOT bipartite -> no solutions possible.
 *   If it IS bipartite -> count components, for each component with sizes n1 and n2,
 *                        number of ways to assign (1,3) = 2^(n1), (2) = 1,
 *                        but we must assign 1,2 or 3. So the answer is:
 *   Each connected component contributes 2^(n1 + n2) ways if bipartite.
 * - However, here each vertex can be assigned 1 or 2 or 3, so instead:
 *   - If a connected component has sizes n1 and n2 (two groups), there are:
 *     (ways to choose color for first group) * (ways to choose color for second group)
 *     Which leads to 2^(n1) + 2^(n2) combinations.
 *   - But this counts how many ways two groups can be filled by valid colors.
 *   - Correctly interpreted:
 *     Color the graph with two colors. For each connected component, we have two color classes of
 *     sizes n1 and n2. Each node in color class 1 can have 2 choices (1 or 3).
 *     Each node in color class 2 can also have 2 choices (1 or 3).
 *     But wait! We want each edge to sum to odd value.
 *       This implies: if one end is {odd} = {1,3}, the other must be {even} = {2}.
 *     So we split graph into two independent sets (bipartition),
 *     And then:
 *     For each node in a set, there are 2 valid choices (1 or 3 for odd nodes).
 *     But that makes no sense either.
 *
 *   Let’s rethink carefully:
 *   - An edge sums to odd iff one endpoint is even and other is odd.
 *   - Each vertex gets value from {1,2,3}.
 *   - We have odd values: {1,3}; even values {2}.
 *   - If the graph is bipartite (can be colored using two colors), then we split nodes into two sets.
 *     The first set must take only {1,3} and second only {2}. We don't use other combinations.
 *     So count of nodes in each part = n1, n2.
 *     Ways to assign 1 or 3 to all nodes of 1st color group: 2^n1
 *     Ways to assign 2 to all nodes of 2nd color group: 1^m2 = 1
 *     Total = 2^n1 (only for this component, not accounting all choices!)
 *   - But actually, we can choose either set as the one containing only {1,3} or the one with only {2}.
 *     That gives us 2*2^(n1) = 2^(n1 + 1) for a valid assignment.
 *     So each component contributes 2^a + 2^b where sizes are a and b (two parts of bipartition).
 *     But again, how?
 *     If both groups get to choose from either {1,3} or {2}, that would be 2^a * 2^b = 2^(a+b).
 *     But this conflicts with valid parity.
 *   
 * Better Approach:
 *   - Let’s see: Each node can take one of 3 values. 
 *   - Constraint is all edges sum to odd numbers.
 *   - So the coloring must be such that for an edge (u,v), color(u)+color(v) = odd.
 *   - This happens when u and v have different colors.
 *   - Therefore we need bipartite structure.
 *   - Now: for two-colorable components:
 *     Let one part of bipartite have size a, other b. The valid assignments are those
 *     assigning values so adjacent nodes take odd/even combinations.
 *     So the number of edges must be satisfied by:
 *     For a connected component of size n with two groups (a and b), 
 *     each node in first group (a) can have value 1 or 3 = 2^a choices.
 *     Each in second group (b) can have value 2 = 1 choice.
 *     But we can swap: a can be the even group, b can be odd group. 
 *     Total = 2*2^a for one color class and 2*2^b.
 *     Wait... again: if both parts exist in the component:
 *     Total assignments where part1 has {1,3}, part2 has {2} = 2^a * 1^b = 2^a
 *     Swapping roles of groups (part1 gets {2}, part2 gets {1,3}) = 2^b * 1^a = 2^b
 *     Total for component = 2^a + 2^b
 *   - But we also must remember to account the base case.
 *
 *  Actually: 
 *   Think again:
 *   We're allowed to assign {1,2,3} to nodes.
 *   The total number of assignments satisfying edge condition is:
 *      We partition the graph into connected components. Then for each component,
 *      if it's bipartite with sizes c1,c2 (color classes),
 *      Total valid assignments = sum over all components of 2^c1 + 2^c2.
 *
 *   However, we can improve this:
 *    Let’s reframe:
 *    - We assign colors to graph: each node gets color 0 or 1. Then for every edge (u,v),
 *      if color(u) == color(v), then u and v have same parity value (both even, or both odd),
 *      which makes their sum even => invalid.
 *    - So we require no edges to connect nodes of same color ⇒ bipartite graph.
 *    - Let’s say a connected component has two groups: size c1, c2.
 *    - Then, for each group, we must be careful not to assign both same values,
 *      unless that's a case when the two adjacent values give odd sum.
 *     
 *    The real approach:
 *     - Assign one value from {1,3} to all nodes in color 0 group: 2 choices per node = 2^c1 ways
 *     - Assign one value from {2} to all nodes in color 1 group = 1 choice = 1 way
 *     - Or vice versa:
 *     - Assign only {1,3} to color 1 group → 2^c2 
 *     - Assign only {2} to color 0 group → 1 way
 *     - So the number of ways for one connected component = 2^c1 + 2^c2.
 *
 * Complexity:
 *   Time complexity: O(n+m) per test case due to DFS traversal and preprocessing.
 *   Space complexity: O(n+m) for the adjacency list and auxiliary arrays.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 300010
#define inf 100000000
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pff(n, m) printf("%d %d\n", n, m)
#define pffl(n, m) printf("%I64d %I64d\n", n, m)
#define pfl(n) printf("%I64d ", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<string, int>
const int mod = 998244353;
using namespace std;
bool f; // flag for detecting odd-length cycles (bipartite check)
int color[N]; // store colors of vertices: -1 means unvisited, 0 and 1 are two colors
ll co[2], p[N]; // co[i] = count of nodes with color i, p[i] = 2^i mod mod
vector<int> adj[N]; // adjacency list

// DFS function to perform bipartite checking and coloring of component
void dfs(int s, int c) {
  if (f) return; // early termination if odd cycle found
  color[s] = c;
  co[c]++;
  for (int e : adj[s]) { // traverse neighbors
    if (color[e] == -1)
      dfs(e, 1 - c); // assign opposite color
    else if (color[e] == c) {
      f = true; // found same-colored edge => not bipartite
      return;
    }
  }
}

int main() {
  int i, j, k;
  int n, m, t;
  int u, v;
  p[0] = 1;
  for (i = 1; i < N; i++)
    p[i] = (2 * p[i - 1]) % mod; // precompute powers of 2 under mod
  sf(t);
  while (t--) {
    sff(n, m);
    for (i = 1; i <= n; i++)
      adj[i].clear(), color[i] = -1;
    
    for (i = 0; i < m; i++) {
      sff(u, v);
      adj[u].pb(v);
      adj[v].pb(u);
    }
    
    ll cnt = 1, cnt2;
    for (i = 1; i <= n; i++) {
      if (color[i] == -1) { // unvisited component
        f = false;
        co[0] = co[1] = 0;
        dfs(i, 0); // start with color 0

        if (f) { // found an odd cycle => not valid coloring
          cnt = 0; // invalid graph
          break;
        }

        // compute combinations for current component:
        // each group contributes 2^(size_of_group)
        cnt2 = (p[co[0]] + p[co[1]]) % mod;
        cnt = (cnt * cnt2) % mod; // multiply with overall result
      }
    }
    pf(cnt);
    nl;
  }
  return 0;
}

// https://github.com/VaHiX/codeForces/