// Problem: CF 1734 F - Zeros and Ones
// https://codeforces.com/contest/1734/problem/F

/*
Purpose: This code computes the Hamming distance between two substrings of the Thue-Morse sequence.
         The Thue-Morse sequence is constructed by repeatedly concatenating the current string with 
         its bitwise complement.
Algorithms: 
    - Recursive approach with memoization (DFS + caching)
    - Uses properties of the Thue-Morse sequence to calculate differences efficiently
    - Bit manipulation techniques for parity calculation

Time Complexity: O(log n + log m) per test case, due to the recursive structure and memoization
Space Complexity: O(log n + log m) for memoization storage and recursion stack

The recurrence relation leverages the self-similar structure of the Thue-Morse sequence:
    - For odd y: we compute the parity of (x + y - 1) ^ (y - 1)
    - For even y: we recursively split the problem into two halves
*/

#import <bits/stdc++.h>
using namespace std;
using ll = long long;
ll T, n, m;
map<pair<ll, ll>, ll> mp;
#define P mp[{x, y}]
ll dfs(ll x, ll y) {
  if (P)
    return P;
  if (!y)
    return 0;
  if (y & 1)
    // When y is odd, we add the parity of (x + y - 1) ^ (y - 1) and recurse
    return dfs(x, y - 1) + __builtin_parityll((x + y - 1) ^ (y - 1));
  if (x & 1)
    // When x is odd and y is even, split the problem into two subproblems
    return P = y - dfs(x / 2, y / 2) - dfs(x / 2 + 1, y / 2);
  else
    // When x is even and y is even, solve recursively in a different way
    return P = 2 * dfs(x / 2, y / 2);
}
int main() {
  cin >> T;
  while (T--)
    cin >> n >> m, cout << dfs(n, m) << '\n';
}


// https://github.com/VaHiX/CodeForces/