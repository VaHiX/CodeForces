// Problem: CF 2155 E - Mimo & Yuyu
// https://codeforces.com/contest/2155/problem/E

/*
E. Mimo & Yuyu
Algorithms/Techniques: Game Theory, Set Operations

The problem involves a game played on an n x m grid where tokens are moved according to specific rules.
Each move consists of selecting a token and a sequence of adjacent cells that:
- Must start at the token's position,
- Must go strictly towards column 1 (non-increasing column indices),
- The first cell must be in a column greater than the second column.

The key insight is that we're essentially tracking which columns have tokens that can initiate such moves.
If a column has an odd number of tokens, it means there's at least one token from which a move is possible (since for each column,
we consider the number of tokens in columns that could potentially start a sequence).
The problem is solved by simulating the process using a set to keep track of columns with tokens.
When processing each token:
- If it's in column 1, skip it (can't be the first element of any valid move).
- For the same column as another token, toggle its presence in the set (as we pair up tokens).
- For a new column, add it to the set.

Time complexity: O(k * log k)
Space complexity: O(k)

*/
#include <iostream>
#include <set>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;

void tc() {
  ll n, m, k;
  cin >> n >> m >> k;
  set<ll> st; // Set to store columns that currently have tokens eligible for moves
  for (ll id = 0; id < k; id++) {
    ll i, j;
    cin >> i >> j;
    if (j == 1) // Tokens in column 1 can't be the starting point of a move
      continue;
    if (n == 1 && j != 2) // Special case, only one row, token must be in column 2 to allow valid moves
      continue;
    if (st.count(j)) // If column already exists, remove it (pair up tokens)
      st.erase(j);
    else // Otherwise add the column (start a new pairing)
      st.insert(j);
  }
  cout << (st.size() > 0 ? "Mimo" : "Yuyu") << '\n'; // If any columns remain, Mimo wins, otherwise Yuyu wins
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll T;
  cin >> T;
  while (T--) {
    tc();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/