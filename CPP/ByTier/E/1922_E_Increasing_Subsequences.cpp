// Problem: CF 1922 E - Increasing Subsequences
// https://codeforces.com/contest/1922/problem/E

/*
Algorithm/Techniques: Binary representation, constructive algorithm
Time Complexity: O(62) = O(1) for each test case since we only check up to 62 bits
Space Complexity: O(1) as we use fixed size arrays and vectors

The problem asks us to construct an array of length at most 200 such that it contains exactly X increasing subsequences.
We use the binary representation of X to determine how to build the array:
- Each bit set in X corresponds to a specific pattern of elements.
- By placing elements in a way that mimics the structure of binary numbers, we can control the number of increasing subsequences.
- The approach involves:
  1. Identify the highest bit set in X.
  2. Build the array by placing elements such that increasing subsequences follow the binary structure.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define solveT()                                                               \
  {                                                                            \
    int t;                                                                     \
    cin >> t;                                                                  \
    while (t--)                                                                \
      solve();                                                                 \
  }
#define int long long
int tp[62]; // Precomputed powers of 2 up to 2^61
void solve() {
  int n, o, l = -1000;
  cin >> n;
  vector<int> v;
  int vis[62] = {0}; // Tracks which bits are set in n
  for (int i = 0; i < 62; i++) {
    if (tp[i] & n) { // Check if the i-th bit is set
      o = i;         // Store the highest bit position
      vis[i] = 1;
    }
  }
  // Build the array based on binary structure
  for (int i = 0; i < o; i++) {
    v.push_back(i);           // Add ascending element
    if (vis[o - 1 - i])       // If the corresponding bit is set
      v.push_back(l--);       // Add a decreasing element to control subsequences
  }
  cout << v.size() << '\n';
  for (auto x : v)
    cout << x << " ";
  cout << '\n';
}
signed main(void) {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  tp[0] = 1;
  for (int i = 1; i < 62; i++)
    tp[i] = tp[i - 1] * 2;
  solveT();
  return 0;
}


// https://github.com/VaHiX/CodeForces/