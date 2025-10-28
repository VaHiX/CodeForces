// Problem: CF 1994 D - Funny Game
// https://codeforces.com/contest/1994/problem/D

/*
Purpose: Solve the "Funny Game" problem where we need to build a connected graph by adding edges based on divisibility conditions.
Algorithm: 
    - For each operation x (from n-1 down to 1), we group vertices by their value modulo x.
    - If two vertices have the same remainder when divided by x, their difference is divisible by x.
    - We connect such pairs greedily to ensure connectivity.
    - A simple union-find or seen tracking is used to avoid reusing vertices.
Time Complexity: O(N^2) per test case due to nested loops over vertices and modulo classes.
Space Complexity: O(N) for storing arrays and vectors.
*/
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define fi first
#define se second
const int MOD = 1e9 + 7;
const int INF = (1 << 30);
const long long LL_INF = (1LL << 60);
const int MAX_N = 2000;
int T, N;
int A[MAX_N + 5];
int cnc[MAX_N + 5];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> T;
  while (T--) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
      cin >> A[i];
      cnc[i] = i;
    }
    vector<bool> seen(N + 1);
    vector<pair<int, int>> ans;
    for (int i = N - 1; i >= 1; i--) {
      vector<int> occ(i + 1, -1); // Array to track last seen index for each remainder
      for (int j = 1; j <= N; j++) {
        if (seen[j])
          continue;
        if (occ[A[j] % i] != -1) {
          ans.push_back({j, occ[A[j] % i]}); // Connect j with previous vertex having same mod
          seen[j] = true;
          break;
        }
        occ[A[j] % i] = j; // Mark this vertex as seen for this remainder
      }
    }
    reverse(ans.begin(), ans.end()); // Reverse to output in correct order (1 to n-1)
    cout << "YES\n";
    for (auto [u, v] : ans) {
      cout << u << " " << v << "\n";
    }
  }
}


// https://github.com/VaHiX/CodeForces/