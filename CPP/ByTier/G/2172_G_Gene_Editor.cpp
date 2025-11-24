// Problem: CF 2172 G - Gene Editor
// https://codeforces.com/contest/2172/problem/G
//
// Added comments and a short explanation + complexity "flowerbox".
//
// Overview:
// - Build a minimal deterministic automaton (DFA) representing allowed
// sequences
//   produced by the gene editor operations using state merging (union-find).
// - Construct the transition adjacency matrix between DFA states (2-letter
// alphabet).
// - Use fast matrix exponentiation to count paths of length n from the start
// state
//   to the state reached after applying the given string t.
// - Output result modulo MOD.
//
// Key ideas:
// - trans[s][c] stores the transition from state s by character c (0/1 for
// letters).
// - parent[] is union-find for merging equivalent states during DFA
// minimization.
// - rels holds relations (patterns) that force merges when followed from a
// state.
// - Build the matrix only on representative states, exponentiate, and answer
// queries.

#include <stddef.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
const int MOD = 998244353;

// Simple dense matrix with mod multiplication used for exponentiation
struct Matrix {
  int size;
  vector<vector<int>> mat;
  Matrix(int s) : size(s), mat(s, vector<int>(s, 0)) {}
  // Identity matrix
  static Matrix identity(int s) {
    Matrix res(s);
    for (int i = 0; i < s; i++) res.mat[i][i] = 1;
    return res;
  }
  // Multiply matrices with modulo
  Matrix operator*(const Matrix &other) const {
    Matrix res(size);
    for (int i = 0; i < size; i++) {
      for (int k = 0; k < size; k++) {
        if (mat[i][k]) {
          long long v = mat[i][k];
          for (int j = 0; j < size; j++) {
            if (other.mat[k][j]) {
              res.mat[i][j] = (res.mat[i][j] + v * other.mat[k][j]) % MOD;
            }
          }
        }
      }
    }
    return res;
  }
};

// Fast exponentiation of matrix a^b
Matrix power(Matrix a, long long b) {
  Matrix res = Matrix::identity(a.size);
  while (b > 0) {
    if (b & 1) res = res * a;
    a = a * a;
    b >>= 1;
  }
  return res;
}

const int MAX_STATES = 605;  // safe upper bound for constructed automaton
int trans[MAX_STATES][2];    // transitions: state x char -> next state (or -1)
int parent[MAX_STATES];      // union-find parent for state merging
int n_states;

// Union-find find with path compression
int find_set(int v) {
  if (v == parent[v]) return v;
  return parent[v] = find_set(parent[v]);
}

// Solve one test case
void solve() {
  string s_str, t_str;
  long long n;
  if (!(cin >> s_str >> t_str >> n)) return;

  // initialize transitions and union-find
  for (int i = 0; i < MAX_STATES; ++i) {
    trans[i][0] = trans[i][1] = -1;
    parent[i] = i;
  }
  n_states = 1;  // start with single state 0

  // Build relation patterns:
  // - first two relations are constants used by problem (examples from original
  // solution)
  // - third relation is derived from input string s_str (converted to 0/1)
  vector<vector<int>> rels;
  rels.push_back({0, 0});     // relation: 00
  rels.push_back({1, 1, 1});  // relation: 111
  vector<int> s_rel;
  for (char c : s_str) s_rel.push_back(c == 'B');  // map 'B' to 1, others to 0
  rels.push_back(s_rel);

  // queue of merges to perform (pairs of states to union)
  vector<pair<int, int>> merge_queue;
  auto push_merge = [&](int u, int v) { merge_queue.push_back({u, v}); };

  // Main loop: build transitions, apply relations to force merges,
  // and expand automaton by creating missing transitions until stable.
  while (true) {
    // Process pending merges: union the states and reconcile transitions
    while (!merge_queue.empty()) {
      auto [u, v] = merge_queue.back();
      merge_queue.pop_back();
      int root_u = find_set(u);
      int root_v = find_set(v);
      if (root_u != root_v) {
        // merge v into u (arbitrary)
        parent[root_v] = root_u;
        // For each character, if root_v had a transition, link it into root_u.
        for (int c = 0; c < 2; ++c) {
          if (trans[root_v][c] != -1) {
            int target_v = find_set(trans[root_v][c]);
            if (trans[root_u][c] != -1) {
              int target_u = find_set(trans[root_u][c]);
              if (target_u != target_v) {
                // Their targets must also be merged
                push_merge(target_u, target_v);
              }
            } else {
              // adopt the transition from root_v
              trans[root_u][c] = target_v;
            }
          }
        }
      }
    }

    // Try to apply relation patterns: if following a relation from state u
    // leads to a state v, then u and v must be equivalent (merge).
    bool merged_from_rel = false;
    vector<int> active_states;
    for (int i = 0; i < n_states; ++i) {
      if (parent[i] == i)
        active_states.push_back(i);  // consider only representatives
    }
    for (int u : active_states) {
      for (const auto &rel : rels) {
        int curr = u;
        bool possible = true;
        // follow the pattern; if any transition missing, pattern not applicable
        for (int c : rel) {
          if (trans[curr][c] == -1) {
            possible = false;
            break;
          }
          curr = find_set(trans[curr][c]);
        }
        if (possible) {
          int root_curr = find_set(curr);
          int root_u = find_set(u);
          if (root_curr != root_u) {
            // enforce merge
            push_merge(root_u, root_curr);
            merged_from_rel = true;
          }
        }
      }
    }
    if (merged_from_rel || !merge_queue.empty()) continue;

    // Expand automaton: create new states for missing transitions
    bool expanded = false;
    for (int i = 0; i < n_states; ++i) {
      if (parent[i] != i) continue;  // skip non-representatives
      for (int c = 0; c < 2; ++c) {
        if (trans[i][c] == -1) {
          if (n_states >= MAX_STATES) break;
          int new_state = n_states++;
          trans[i][c] = new_state;
          // heuristic: for char 0, set new_state's 0 transition back to i
          // this helps create the loops typically required by the problem's
          // automaton
          if (c == 0) {
            trans[new_state][0] = i;
          }
          expanded = true;
          goto end_expand;
        }
      }
    }
  end_expand:;
    if (!expanded) break;
    if (n_states >= MAX_STATES) break;
  }

  // Map each representative state to a contiguous index for matrix construction
  vector<int> mapping(n_states, -1);
  int M = 0;
  for (int i = 0; i < n_states; ++i) {
    if (parent[i] == i) mapping[i] = M++;
  }

  // Build transition matrix T between representatives (size M x M)
  Matrix T(M);
  for (int i = 0; i < n_states; ++i) {
    if (parent[i] == i) {
      int u = mapping[i];
      for (int c = 0; c < 2; ++c) {
        if (trans[i][c] != -1) {
          int v = mapping[find_set(trans[i][c])];
          // multiple transitions (if present) increment count
          // (non-deterministic edges)
          T.mat[u][v]++;
        }
      }
    }
  }

  // Starting from state 0, follow string t_str to reach the target
  // representative
  int curr = find_set(0);
  for (char c : t_str) {
    int x = (c == 'B');  // map 'B' -> 1, other -> 0
    if (trans[curr][x] != -1) {
      curr = find_set(trans[curr][x]);
    }
  }
  int target_idx = mapping[curr];
  int start_idx = mapping[find_set(0)];

  // Compute T^n and read number of paths from start_idx to target_idx
  Matrix Res = power(T, n);
  cout << Res.mat[start_idx][target_idx] << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  if (cin >> q) {
    while (q--) {
      solve();
    }
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/