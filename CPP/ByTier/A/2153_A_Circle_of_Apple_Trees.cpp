// Problem: CF 2153 A - Circle of Apple Trees
// https://codeforces.com/contest/2153/problem/A

/*
A. Circle of Apple Trees
Algorithms/Techniques: Greedy approach with set usage to track unique values in a circular arrangement.

Time Complexity: O(n log n) per test case due to insertion into set.
Space Complexity: O(n) for storing elements and using set data structure.

The problem involves eating apples from trees arranged in a circle, where each apple has a beauty value.
You can only eat an apple if its beauty is strictly greater than the last eaten apple's beauty. The goal
is to maximize the total number of apples eaten by making optimal choices.

The solution provided here does not correctly solve the actual problem described above,
but instead counts unique values in the input array, which relates to a simpler version or misinterpretation.
For the intended task, a more complex greedy or dynamic programming approach would be needed.
*/

#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;
#define int long long
constexpr int mod = 1e9 + 7, inf = 1e17;

void solution() {
  int n;
  cin >> n;
  vector<int> a(n);
  set<int> s; // Set to store unique beauty values
  for (int &i : a)
    cin >> i, s.emplace(i); // Read and insert each value into the set
  cout << s.size(); // Output number of unique values
}

int32_t main() {
#ifdef JahonaliX
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solution();
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/