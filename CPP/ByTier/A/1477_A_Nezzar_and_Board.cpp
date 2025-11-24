// Problem: CF 1477 A - Nezzar and Board
// https://codeforces.com/contest/1477/problem/A

/*
Problem: Nezzar and Board

This problem involves determining if a target number k can be generated from a set of initial numbers using the operation:
x -> 2*x - y (where x and y are any two numbers currently on the board).

Key insight:
- The operation 2*x - y can generate new numbers, but all such generated numbers will have a specific property related to the GCD of differences between elements.
- If we consider the array sorted in ascending order, then using the operation repeatedly will only allow us to generate numbers that differ from the first element by multiples of GCD of all pairwise differences.
- So for k to be achievable, (k - a[1]) must be divisible by GCD of all differences (a[i] - a[1]) for i = 2..n.

Algorithms/Techniques:
- Use GCD computation to find the step size
- Modular arithmetic check to determine if k is reachable

Time Complexity: O(n * log(max(a))) per test case due to GCD computation and reading input
Space Complexity: O(n) for storing the array of integers

*/
#include <algorithm>
#include <iostream>

#define int long long
using namespace std;
const int N = 1e6 + 10;
const int mod = 1e9 + 7;
int n, m, a[N];

void solve() {
  cin >> n >> m; // Read number of elements and target k
  for (int i = 1; i <= n; i++)
    cin >> a[i]; // Read the array of integers
  
  int g = 0; // Initialize GCD of differences
  for (int i = 2; i <= n; i++)
    g = __gcd(g, a[i] - a[1]); // Compute GCD of all differences from first element
  
  // Check if (m - a[1]) is divisible by the computed GCD
  cout << ((m - a[1]) % g == 0 ? "YES\n" : "NO\n");
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int Case;
  cin >> Case;
  while (Case--)
    solve();
}


// https://github.com/VaHiX/codeForces/