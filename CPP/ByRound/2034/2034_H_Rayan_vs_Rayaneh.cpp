// Problem: CF 2034 H - Rayan vs. Rayaneh
// https://codeforces.com/contest/2034/problem/H

/*
Algorithm/Technique: 
The problem involves finding the largest integer linearly independent subset from a given set of integers.
This is essentially about selecting elements such that none can be expressed as an integer linear combination of others.
The approach involves:
1. Preprocessing prime factors and divisors for optimization.
2. Using combinations of small primes to identify potential candidates for independence.
3. Applying a greedy or graph-based method to construct the largest valid subset.
4. Special handling for edge cases when initial combinations fail.

Time Complexity: O(N * sqrt(MAX) + T * N * log N) where N is the size of the input array and T is the number of test cases.
Space Complexity: O(MAX * log(MAX)) for storing divisors, prime powers, and auxiliary data structures.

*/

#include <stdio.h>
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

using namespace std;
typedef pair<int, int> pii;
typedef pair<int, vector<int>> pivi;
const int MAX = 1e5 + 1;
const int ROOT = 46;
int prime[MAX];
vector<pivi> combs;
vector<pii> adj[MAX], out[MAX];
vector<int> pws[MAX], divs[MAX];
vector<int> nodes;
int label[MAX];
int mult[MAX];

void init() {
  // Sieve of Eratosthenes to find smallest prime factor for each number
  for (int i = 2; i < MAX; i++)
    if (!prime[i])
      for (int j = i; j < MAX; j += i)
        if (!prime[j])
          prime[j] = i;

  // Precompute prime power decomposition for each number
  for (int i = 2; i < MAX; i++) {
    int j = i / prime[i];
    pws[i] = pws[j];
    if (j % prime[i])
      pws[i].push_back(1);
    pws[i].back() *= prime[i];
  }

  // Sort prime powers in descending order for easier access
  for (int i = 1; i < MAX; i++)
    sort(pws[i].begin(), pws[i].end(), greater<int>());

  // Precompute divisors for each number
  for (int i = 1; i < MAX; i++)
    for (int j = i; j < MAX; j += i)
      divs[j].push_back(i);

  // Generate combinations of small primes to look for integer linearly independent subsets
  for (int i = 2; i < MAX; i++)
    for (int j = 1; j < ROOT && j < pws[i].back(); j++)
      if (pws[j].size() == 1 && i % prime[j]) {
        vector<int> tmp = pws[i];
        tmp.push_back(j);
        int prod = i * j;
        for (auto &it : tmp)
          it = prod / it;
        combs.push_back({prod, tmp});
      }
}

void give(int u, int v, int w) {
  // Adds edge to adjacency list and updates node list
  if (adj[u].empty())
    nodes.push_back(u);
  adj[u].push_back({v, w});
}

void add_edge(int u, int v, int w) {
  // Adds bidirectional edge
  give(u, v, w);
  give(v, u, w);
}

void solve() {
  int N;
  scanf("%d", &N);
  vector<int> a(N);
  for (auto &it : a)
    scanf("%d", &it);

  // Sort input array for easier processing
  sort(a.begin(), a.end());

  vector<int> ans;

  // Count occurrences of divisors
  for (auto it1 : a)
    for (auto it2 : divs[it1])
      mult[it2]++;

  // Find largest combination that could form an independent set
  pivi opt;
  for (const auto &it : combs)
    if (it.second.size() > opt.second.size()) {
      bool ok = true;
      for (auto elem : it.second)
        if (mult[elem] == (it.first < MAX ? mult[it.first] : 0)) {
          ok = false;
          break;
        }
      if (ok)
        opt = it;
    }

  // Use optimal combination for forming answer
  for (auto it : opt.second)
    for (auto elem : a)
      if (elem % opt.first && !(elem % it)) {
        ans.push_back(elem);
        break;
      }

  // Decrement counts after use
  for (auto it1 : a)
    for (auto it2 : divs[it1])
      mult[it2]--;

  // Handle case where optimal combination is small
  if (ans.size() < 3) {
    for (auto it : a)
      if (pws[it].size() >= 2 && pws[it][1] > ROOT)
        add_edge(prime[pws[it][0]], prime[pws[it][1]], it);

    // Process edges to get potential candidates for larger subset
    for (auto it1 : nodes)
      for (auto it2 : adj[it1])
        if (pii(adj[it1].size(), it1) < pii(adj[it2.first].size(), it2.first))
          out[it1].push_back(it2);

    // Check for trios using graph structure
    for (auto it1 : nodes) {
      for (auto it2 : out[it1])
        label[it2.first] = it2.second;
      for (auto it2 : out[it1])
        for (auto it3 : out[it2.first])
          if (label[it3.first])
            ans = {it2.second, it3.second, label[it3.first]};
      for (auto it2 : out[it1])
        label[it2.first] = 0;
    }

    for (auto it : nodes) {
      adj[it].clear();
      out[it].clear();
    }
    nodes.clear();
  }

  // Final fallback for even smaller size sets
  if (ans.size() < 2) {
    ans = {a[0]};
    for (int i = 1; i < N; i++)
      if (a[i] % a[i - 1]) {
        ans = {a[i], a[i - 1]};
        break;
      }
  }

  printf("%d\n", ans.size());
  for (auto it : ans)
    printf("%d ", it);
  puts("");
}

int main() {
  init();
  int tc;
  scanf("%d", &tc);
  while (tc--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/