// Problem: CF 1896 F - Bracket Xoring
// https://codeforces.com/contest/1896/problem/F

/*
 * Problem: F. Bracket Xoring
 * 
 * Purpose: This code determines if a binary string of length 2n can be reduced to all zeros
 *          using a series of operations where each operation applies a balanced bracket sequence
 *          to toggle bits in specific ranges.
 * 
 * Approach:
 * 1. First check if it's possible to make all bits zero based on parity and boundary conditions.
 * 2. Handle special case of n=1.
 * 3. For larger n, construct a sequence of at most 10 operations using the following steps:
 *    - Create bracket sequence to flip the first and last bits.
 *    - Create bracket sequence to fix pairs of adjacent bits.
 *    - Repeat with specific bracket patterns and operations to ensure all bits become 0.
 * 
 * Time Complexity: O(n) per test case, since we process each bit at most a constant number of times.
 * Space Complexity: O(n) for storing the bracket sequences and result.
 * 
 * Algorithms/Techniques:
 * - Greedy approach with bracket matching
 * - Bit manipulation via toggle operations
 * - Construction of balanced bracket sequences
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int n, db;
string s;
vector<string> ans;

// Toggle the bit at index 'a' (0 -> 1, 1 -> 0)
void flip(int a) {
  if (s[a] == '1')
    s[a] = '0';
  else
    s[a] = '1';
}

// Add a bracket sequence to the list of operations
void add(string p) { ans.push_back(p); }

void solve() {
  db = 0;
  cin >> n >> s;
  
  // Count number of 1s in the string
  for (auto x : s) {
    if (x == '1') {
      db++;
    }
  }
  
  // If first and last bits differ, or number of 1s is odd, impossible to solve
  if (s[0] != s[2 * n - 1] || db % 2) {
    cout << -1 << "\n";
    return;
  }
  
  // Special case when n=1
  if (n == 1) {
    if (s[0] == '0') {
      cout << 0 << "\n";
    } else {
      cout << 1 << "\n";
      cout << "()" << "\n";
    }
    return;
  }
  
  // Build and apply the first operation
  string p;
  p += "(";
  flip(0), flip(2 * n - 1);  // Toggle first and last bits
  for (int i = 1; i < 2 * n - 1; i += 2) {
    if (s[i] != s[i - 1]) {
      flip(i), flip(i + 1);  // Toggle two adjacent bits if they differ
      p += ")(";
    } else {
      p += "()";
    }
  }
  p += ")";
  add(p);
  p.clear();
  
  // If first bit is 1, apply a second operation to toggle it
  if (s[0] == '1') {
    for (int i = 0; i < 2 * n; i += 2) {
      flip(i), flip(i + 1);  // Toggle pairs
      p += "()";
    }
    add(p);
    p.clear();
  }
  
  // Apply third operation
  p += "((";
  for (int i = 2; i < 2 * n - 2; i += 2) {
    p += ")(";
  }
  p += "))";
  flip(0), flip(2 * n - 1);  // Toggle first and last bits again
  add(p);
  p.clear();
  
  // Apply fourth operation
  flip(0), flip(2 * n - 1);  // Toggle first and last bits again
  p += "((";
  for (int i = 2; i < 2 * n - 2; i += 2) {
    if (s[i] == '1') {
      p += "()";
      flip(i), flip(i + 1);  // Toggle if needed
    } else {
      p += ")(";
    }
  }
  p += "))";
  add(p);
  p.clear();
  
  // Output the number of operations and the bracket sequences
  cout << ans.size() << "\n";
  for (auto x : ans) {
    cout << x << "\n";
  }
  ans.clear();
}

int main() {
  ios_base::sync_with_stdio(false);
  int w;
  cin >> w;
  while (w--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/