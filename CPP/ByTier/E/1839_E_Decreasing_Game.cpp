// Problem: CF 1839 E - Decreasing Game
// https://codeforces.com/contest/1839/problem/E

/*
 * Problem: Decreasing Game
 * 
 * Purpose: This code solves an interactive two-player game where players take turns 
 *          decreasing elements of an array. The goal is to determine whether the 
 *          first or second player has a winning strategy.
 * 
 * Algorithm: 
 *   - Use dynamic programming to compute all possible sums that can be achieved
 *     using subsets of the array elements.
 *   - If the total sum is odd, the first player has an advantage and wins.
 *   - If the total sum is even, we check if it's possible to split the array into two 
 *     subsets with equal sums. If so, we use a greedy strategy based on the subset 
 *     assignment to ensure a win.
 *   
 * Time Complexity: O(N * S), where N is the size of the array and S is the sum of all elements.
 * Space Complexity: O(N * S), for the dp table storing subset sums.
 * 
 * Techniques:
 *   - Dynamic Programming with bitsets for optimized subset sum calculation
 *   - Game theory strategy based on subset partitioning
 *   - Interactive problem handling with proper I/O flush
 */

#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

using namespace std;
#define sz(x) ((int)(x).size())
typedef long long ll;
typedef pair<int, int> pii;
template <class T> void print(T &x) { cout << x; }
template <class T, class U> void print(pair<T, U> &p) {
  cout << "(";
  print(p.first);
  cout << ", ";
  print(p.second);
  cout << ")";
}
template <class T> void print(vector<T> &v) {
  cout << "{";
  if (sz(v))
    print(v[0]);
  for (int i = 1; i < sz(v); i++)
    cout << ", ", print(v[i]);
  cout << "}\n";
}
const int n = 301;
vector<bitset<n * n>> dp;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;
  vector<int> A(N);
  int sum = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    sum += A[i];
  }
  dp = vector<bitset<n * n>>(N + 1);
  dp[0][0] = true;
  for (int i = 0; i < N; i++) {
    dp[i + 1] = dp[i] | (dp[i] << A[i]); // Update dp with new element
  }
  function<int(int)> f;
  bool isFirst = false;
  set<int> s1, s2;
  if (sum % 2 == 1 || !dp[N][sum / 2]) {
    // If sum is odd or no equal partition exists, first player wins by choosing any positive element
    f = [&](int other) {
      for (int i = 0; i < N; i++) {
        if (A[i] > 0)
          return i;
      }
      return -1;
    };
    isFirst = true;
  } else {
    // If sum is even and can be partitioned, strategy based on subset assignment
    int curV = sum / 2;
    for (int i = N - 1; i >= 0; i--) {
      if (dp[i][curV]) {
        s1.insert(i);
      } else {
        s2.insert(i);
        curV -= A[i];
      }
    }
    // Function to determine next move based on current player's role
    f = [&](int other) {
      set<int> *curS = &s1;
      if (s1.count(other)) // If other player's move is in s1, play in s2
        curS = &s2;
      for (int i : *curS) {
        if (A[i] > 0)
          return i;
      }
      return -1;
    };
  }
  cout << (isFirst ? "First" : "Second") << endl;
  int other = -3;
  while (true) {
    if (!isFirst) {
      cin >> other;
      other--;
    }
    if (other == -1)
      break;
    int me = f(other);
    cout << me + 1 << endl;
    if (isFirst) {
      cin >> other;
      other--;
    }
    if (other == -1)
      break;
    int minV = min(A[me], A[other]);
    A[me] -= minV;
    A[other] -= minV;
  }
}


// https://github.com/VaHiX/CodeForces/