// Problem: CF 1070 A - Find a Number
// https://codeforces.com/contest/1070/problem/A

/*
A. Find a Number
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
You are given two positive integers d and s. Find minimal positive integer n which is divisible by d and has sum of digits equal to s.

Algorithms/Techniques: BFS (Breadth-First Search) with state tracking
Time Complexity: O(d * s)
Space Complexity: O(d * s)

This solution uses BFS to explore all possible digit combinations that can form numbers 
with a specific digit sum, while tracking the remainder when divided by d. 
The BFS ensures we find the lexicographically smallest valid number.
*/

#include <stdio.h>
#include <iostream>
#include <queue>
#include <utility>

using namespace std;
bool vis[505][5005];  // Visited array to track (remainder, digit_sum) states
pair<pair<int, int>, int> par[505][5005];  // Parent tracking for path reconstruction

// Function to reconstruct and print the result number from BFS path
void go(pair<int, int> s) {
  if (!s.second)
    return;
  go(par[s.first][s.second].first);  // Recursively go to parent state
  cout << par[s.first][s.second].second;  // Print the digit added to reach this state
}

int main() {
  int d, s;
  cin >> d >> s;
  queue<pair<int, int>> q;  // BFS queue storing {remainder, digit_sum}
  q.push({0, 0});  // Start with remainder 0 and digit sum 0
  vis[0][0] = 1;  // Mark the initial state as visited

  while (!q.empty()) {
    auto cur = q.front();
    q.pop();
    
    for (int i = 0; i < 10; i++) {  // Try appending each digit 0-9
      int nd = (cur.first * 10 + i) % d, ns = cur.second + i;  // New remainder and digit sum
      if (ns <= s && !vis[nd][ns]) {  // If still within bounds and not visited
        vis[nd][ns] = 1;  // Mark as visited
        par[nd][ns] = {cur, i};  // Record parent state and added digit
        q.push({nd, ns});  // Add to BFS queue
      }
    }
  }

  if (!vis[0][s])  // If final state with remainder 0 and digit sum s is unreachable
    printf("-1");
  else
    go({0, s});  // Reconstruct and print the answer

  return 0;
}


// https://github.com/VaHiX/codeForces/