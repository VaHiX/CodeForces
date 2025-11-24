// Problem: CF 2001 D - Longest Max Min Subsequence
// https://codeforces.com/contest/2001/problem/D

/*
D. Longest Max Min Subsequence
Algorithms/Techniques: Stack-based approach with greedy selection, maintaining a valid subsequence that maximizes length and minimizes lexicographical order after transformation.

Time Complexity: O(n) amortized per test case due to each element being pushed and popped from the stack at most once.
Space Complexity: O(n) for arrays and auxiliary space used in the stack.

The problem asks to find the longest subsequence such that when elements at odd positions are multiplied by -1, the result is lexicographically smallest among all longest subsequences.

This code uses a stack-like approach to greedily maintain a valid subsequence while ensuring:
- We always try to keep longer sequences.
- When multiple valid sequences of same length exist, we prefer lexicographically smaller ones after transformation.
*/
#include <iostream>

#define ll long long
using namespace std;
const int N = 3e5 + 10;
int n, a[N], lst[N], s[N], top;
bool vis[N];
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++)
    vis[i] = lst[i] = 0;
  for (int i = 1; i <= n; i++)
    cin >> a[i], lst[a[i]] = i; // Store last occurrence index of each value
  for (int i = 1; i <= n; i++) {
    if (vis[a[i]])
      continue; // Skip elements already in the current subsequence
    
    // Remove elements from the top of stack that are "better" than current element,
    // maintaining valid subsequence rules.
    while (top && (top & 1 ? a[s[top]] < a[i] : a[s[top]] > a[i]) &&
           lst[a[s[top]]] > i)
      vis[a[s[top--]]] = 0; 
    
    // Handle pair removals to optimize for smaller lexicographical order.
    while (top > 1 && (top & 1 ? a[s[top - 1]] > a[i] : a[s[top - 1]] < a[i]) &&
           lst[a[s[top - 1]]] > i && lst[a[s[top]]] > i)
      vis[a[s[top--]]] = 0, vis[a[s[top--]]] = 0;
    
    s[++top] = i, vis[a[i]] = 1; // Add current element to stack
  }
  cout << top << "\n";
  for (int i = 1; i <= top; i++)
    cout << a[s[i]] << " ";
  cout << "\n";
  top = 0;
}
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/