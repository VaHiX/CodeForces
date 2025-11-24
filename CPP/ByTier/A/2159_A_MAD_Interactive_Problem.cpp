// Problem: CF 2159 A - MAD Interactive Problem
// https://codeforces.com/contest/2159/problem/A

/*
TASK: A. MAD Interactive Problem
ALGORITHMS/TECHNIQUES: Binary search, interactive problem solving, MAD (Maximum Appearing Duplicate) query technique

TIME COMPLEXITY: O(n^2) per test case due to nested loops in worst-case scenario for identifying duplicates.
SPACE COMPLEXITY: O(n) for storing the sequence and auxiliary arrays.

The approach uses two phases:
1. Identify positions of elements that appear twice by querying subsets
2. Determine exact values at each position using additional queries

The solution works by first finding all indices where MAD query returns non-zero,
indicating a repeated element. Then it iterates through all possible positions
and determines the value at each index using subset queries.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
const int N = 1010;
vector<int> s, t;
int n, a[N], v[N];

void work() {
  cin >> n;
  s.clear();
  t.clear();
  for (int i = 1; i <= 2 * n; i++)
    v[i] = 0;
  for (int i = 1; i <= 2 * n; i++) {
    s.push_back(i);
    cout << "? " << s.size() << " ";
    for (int x : s)
      cout << x << " ";
    cout << endl;
    int r;
    cin >> r;
    if (r) { // If MAD returns a non-zero value, it means element 'r' appears at least twice
      s.pop_back();
      a[i] = r, t.push_back(i); // Store index and value of duplicate
    }
  }
  for (int x : s)
    v[x] = 1; // Mark indices that were not part of duplicates
  for (int i = 1; i <= 2 * n; i++)
    if (v[i]) { // For indices with no duplicate, query to determine their value
      cout << "? " << t.size() + 1 << " ";
      for (int x : t)
        cout << x << " ";
      cout << i << " ";
      cout << endl;
      cin >> a[i]; // The answer will be the value of this unique element
    }
  cout << "! ";
  for (int i = 1; i <= 2 * n; i++)
    cout << a[i] << " ";
  cout << endl;
  return;
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--)
    work();
  return 0;
}


// https://github.com/VaHiX/CodeForces/