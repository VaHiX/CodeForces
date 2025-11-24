// Problem: CF 2171 F - Rae Taylor and Trees (hard version)
// https://codeforces.com/contest/2171/problem/F

/*
Code Purpose:
This code determines whether a given permutation can represent a valid tree where each edge connects two nodes such that the smaller node appears before the larger node in the permutation. It constructs a tree if possible using a priority queue and greedy technique.

Algorithms/Techniques:
- Greedy approach to build a tree by analyzing the permutation
- Priority queue (min-heap) to manage nodes that appear before a current node
- Stack-like logic using vectors to store edges

Time Complexity: O(n log n) per test case due to priority queue operations
Space Complexity: O(n) for storing the permutation and auxiliary structures

*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
const int MAXN = 2e5 + 5;
int n, a[MAXN], b[MAXN], c[MAXN], d[MAXN];
int main() {
  ios::sync_with_stdio(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++)
      cin >> a[i];
    priority_queue<int, vector<int>, greater<int>> q; // Min-heap to store values
    vector<int> st, ed; // Vectors to store start and end of edges
    int nmin = a[0]; // Track minimum value seen so far
    for (int i = 1; i < n; i++) {
      if (a[i] < nmin)
        q.push(a[i]); // If current value is less than minimum, push to heap
      else {
        st.push_back(a[i]); // Add edge from a[i] to nmin
        ed.push_back(nmin);
        while (!q.empty() && q.top() < a[i]) // Process all elements in heap smaller than a[i]
          nmin = min(nmin, q.top()), st.push_back(a[i]), ed.push_back(q.top()),
          q.pop();
      }
    }
    if (q.empty()) { // If heap is empty, valid tree exists
      cout << "Yes\n";
      for (int i = 0; i < st.size(); i++) {
        cout << st[i] << ' ' << ed[i] << '\n'; // Output edges
      }
    } else
      cout << "No\n"; // Invalid permutation
  }
}


// https://github.com/VaHiX/CodeForces/