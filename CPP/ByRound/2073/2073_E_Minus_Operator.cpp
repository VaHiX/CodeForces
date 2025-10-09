// Problem: CF 2073 E - Minus Operator
// https://codeforces.com/contest/2073/problem/E

/*
 * Code Purpose:
 * This program solves the problem of reconstructing a binary expression tree
 * composed of variables 'x' connected by minus operators. The expression follows 
 * the grammar: E ::= x | (E - E). 
 *
 * It uses a combination of query-based probing and recursive reconstruction to 
 * deduce the structure of the hidden expression.
 *
 * Algorithms Used:
 * 1. Interactive querying with binary strings to determine the structure of the tree.
 * 2. Stack-based tracking of the parse state.
 * 3. Recursive traversal of the reconstructed structure using a depth-first approach.
 * 4. Backtracking and elimination logic to infer the relationship between nodes.
 *
 * Time Complexity: O(n^2)
 * Space Complexity: O(n)
 */

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int n;
int stk[210], fa[210], top; // stack for tracking node relationships, parent tracking, and stack pointer
int query(vector<bool> x) {
  printf("query "); // Output the query command
  for (bool v : x) { // Print each bit of the query vector
    if (v)
      printf("1");
    else
      printf("0");
  }
  printf("\n");
  fflush(stdout); // Ensure output is sent immediately
  int ans;
  scanf("%d", &ans); // Read response from judge
  return ans;
}
string Solve(int l, int r) { // Recursively construct the expression string from nodes l to r
  if (l == r)
    return "x"; // Base case: a single variable node
  for (int j = r; j > l; --j) {
    if (fa[j] == l) { // Find a node where l is its parent
      string ans = "("; // Start building the expression with parentheses
      ans = ans + Solve(l, j - 1) + "-"; // Left subtree
      ans = ans + Solve(j, r) + ")"; // Right subtree
      return ans;
    }
  }
  return ""; // Default case (should not be reached)
}
void solve() {
  stk[++top] = 0; // Initialize the stack with node 0
  stk[++top] = 1; // Add node 1 to the stack
  for (int i = 2; i < n; ++i) { // Process each additional variable node
    vector<bool> x(n); // Create a probe vector for the query
    for (int i = 0; i < n; ++i)
      x[i] = 0; // Initialize all entries to 0
    for (int i = 1; i <= top; ++i)
      x[stk[i]] = 1; // Mark nodes that are currently in the stack
    x[i] = 1; // Also mark current node for query
    if (query(x) == (top & 1)) // Query and check if the result matches parity of stack size
      --top; // If so, remove top element from stack
    while (1) {
      if (top <= 2) { // Special case when small stack
        fa[i] = stk[top]; // Set parent of node i
        stk[++top] = i; // Push node i onto the stack
        break;
      }
      vector<bool> x(n); // Another probe vector setup
      for (int i = 0; i < n; ++i)
        x[i] = 0; // Reset to zero
      for (int i = 1; i <= top - 2; ++i)
        x[stk[i]] = 1; // Mark all but last two stack elements
      x[i] = 1; // Also mark the current node
      if (query(x) == (top & 1)) { // Perform query and check result against stack parity
        fa[i] = stk[top]; // Set parent
        stk[++top] = i; // Push node i onto stack
        break;
      } else
        top -= 2; // Backtrack by popping two elements from stack
    }
  }
  printf("answer "); // Output the final result command
  cout << Solve(0, n - 1) << '\n'; // Print the fully reconstructed expression
  fflush(stdout);
  return;
}
int main() {
  scanf("%d", &n); // Read number of terminals
  solve(); // Start solving the puzzle
  return 0;
}


// https://github.com/VaHiX/codeForces/