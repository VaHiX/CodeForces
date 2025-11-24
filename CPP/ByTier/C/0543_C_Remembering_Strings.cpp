// Problem: CF 543 C - Remembering Strings
// https://codeforces.com/contest/543/problem/C

/*
 * Problem: C. Remembering Strings
 * 
 * Purpose: Minimize the cost to make a multiset of strings "easy to remember" 
 *          by changing characters in the strings. A set is easy to remember if 
 *          each string can be distinguished by a unique character at some position.
 * 
 * Algorithm:
 * - Use dynamic programming with bitmask to represent which strings are already assigned.
 * - For each unassigned string, try all possible positions to assign a unique character.
 * - Use bitmask to track assigned strings and compute minimal cost.
 * 
 * Time Complexity: O(2^n * n * m) where n is number of strings and m is length of strings.
 * Space Complexity: O(2^n) for the DP memoization table.
 */

#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
int mat[20][20];
string s[20];
int n, m;
int dp[2000000];

// Recursive function to calculate minimum cost using bitmask DP
int solve(int mask) {
  // Base case: all strings are assigned
  if (mask == (1 << n) - 1)
    return 0;
  // If already computed, return memoized result
  if (dp[mask] != -1)
    return dp[mask];
  
  // Find the first unassigned string
  int p = -1;
  for (int i = 0; i < n; i++) {
    if ((mask & (1 << i)) == 0) {
      p = i;
      break;
    }
  }
  
  // Initialize dp value to a large number
  dp[mask] = 100000000;
  
  // Try all positions for the current string
  for (int i = 0; i < m; i++) {
    // Option 1: Assign character at position i without grouping
    dp[mask] = min(dp[mask], solve(mask | (1 << p)) + mat[p][i]);
    
    // Option 2: Group strings that have same character at position i
    int valor = 0;
    int maior = 0;
    int par = 0;
    
    for (int j = 0; j < n; j++) {
      // If string j and p have same character at position i
      if (s[j][i] == s[p][i]) {
        valor += mat[j][i];  // Sum all costs for the group
        maior = max(maior, mat[j][i]);  // Track maximum cost for exclusion
        par |= (1 << j);  // Mark j as part of this group
      }
    }
    
    // Subtract max cost to simulate selecting unique character
    valor -= maior;
    // Update dp with the better option of grouping
    dp[mask] = min(dp[mask], solve(mask | par) + valor);
  }
  return dp[mask];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
    cin >> s[i];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++)
      cin >> mat[i][j];
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(0) << endl;
}


// https://github.com/VaHiX/CodeForces/