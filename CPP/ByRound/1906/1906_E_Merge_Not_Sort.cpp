// Problem: CF 1906 E - Merge Not Sort
// https://codeforces.com/contest/1906/problem/E

/*
 * Problem: E. Merge Not Sort
 * 
 * Purpose: Given a permutation C of integers from 1 to 2*N, construct two arrays A and B of length N each 
 * such that Merge(A, B) = C. If impossible, output -1.
 * 
 * Algorithm: 
 * - The key insight is that we can partition the array C into groups where each group contains elements 
 *   that form a contiguous subsequence in the merged result.
 * - These groups help determine whether we can split C into arrays A and B.
 * - The solution uses dynamic programming with bitsets to check if a valid split exists.
 * - Then backtracking via a stack determines how to assign groups to A and B.
 * 
 * Time Complexity: O(N^2) - due to checking group assignment and processing groups
 * Space Complexity: O(N^2) - for storing groups, quantities, and bitset for DP
 * 
 * Techniques:
 * - Grouping elements based on increasing max value seen so far
 * - Dynamic Programming with bitsets to determine valid combinations
 * - Stack-based reconstruction of assignment
 */

#include <ctype.h>
#include <stdio.h>
#include <algorithm>
#include <bitset>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
template <class T> using PQMax = priority_queue<T>;
template <class T> using PQMin = priority_queue<T, vector<T>, greater<T>>;
template <class T1, class T2> void maximize(T1 &a, T2 b) {
  if (b > a)
    a = b;
}
template <class T1, class T2> void minimize(T1 &a, T2 b) {
  if (b < a)
    a = b;
}
template <class T> void read(T &number) {
  bool negative = false;
  register int c;
  number = 0;
  c = getchar();
  while (c != '-' && !isalnum(c))
    c = getchar();
  if (c == '-') {
    negative = true;
    c = getchar();
  }
  for (; (c > 47 && c < 58); c = getchar())
    number = number * 10 + c - 48;
  if (negative)
    number *= -1;
}
template <class T, class... Ts> void read(T &a, Ts &...args) {
  read(a);
  read(args...);
}
#define MAX 2005
#define MOD 1000000007
#define fi first
#define se second
#define FOR(type, i, a, b) for (type i = (a); i <= (b); i++)
#define FORD(type, i, b, a) for (type i = (b); i >= (a); i--)
#define testBit(n, bit) (((n) >> (bit)) & 1)
#define flipBit(n, bit) ((n) ^ (1ll << (bit)))
#define cntBit(n) __builtin_popcount(n)
#define cntBitll(n) __builtin_popcountll(n)
#define randomize                                                              \
  mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
int n;
int c[MAX];
int maxVal[MAX];
vector<int> groups[MAX];
int cntGr = 0;
int grQuantity[MAX];
bitset<MAX> f[MAX];
bool check() {
  f[0] = 1;
  FOR(int, i, 1, cntGr)
  f[i] = f[i - 1] | (f[i - 1] << grQuantity[i]);
  return f[cntGr][n];
}
stack<int> st[2];
vector<int> answer[2];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cin >> n;
  FOR(int, i, 1, n * 2) cin >> c[i];
  FOR(int, i, 1, n * 2) maxVal[i] = max(maxVal[i - 1], c[i]);
  FOR(int, i, 1, n * 2) {
    if (maxVal[i] != maxVal[i - 1])
      cntGr++;
    groups[cntGr].push_back(c[i]);
    grQuantity[cntGr]++;
  }
  if (not check()) {
    cout << -1;
    return 0;
  }
  int tmp = n;
  FORD(int, i, cntGr, 1) {
    if (f[i - 1][tmp])
      st[1].push(i);
    else
      st[0].push(i), tmp -= grQuantity[i];
  }
  FOR(int, i, 0, 1) while (not st[i].empty()) {
    int gr = st[i].top();
    st[i].pop();
    for (int num : groups[gr])
      answer[i].push_back(num);
  }
  FOR(int, i, 0, 1)
  FOR(int, j, 0, n - 1)
  cout << answer[i][j] << " \n"[j == n - 1];
}


// https://github.com/VaHiX/CodeForces/