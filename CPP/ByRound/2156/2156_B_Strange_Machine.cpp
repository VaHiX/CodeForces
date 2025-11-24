// Problem: CF 2156 B - Strange Machine
// https://codeforces.com/contest/2156/problem/B

/*
Purpose: This code solves the Strange Machine problem where n machines arranged in a circle perform operations on an integer value a. 
Each machine is of type A (decrease by 1) or B (floor division by 2). The process starts at machine 1, and each second the current machine
operates on a, then moves clockwise. The goal is to determine how many seconds it takes for a to reach zero.

Algorithms/Techniques:
- Simulation with loop unwinding for special cases
- For special cases where all machines are of same type (all A or all B), optimized computation:
    - All A: time = a (since we subtract 1 each step)
    - All B: time = floor(log2(a)) + 1 (since we halve each step)

Time Complexity: O(n * log(max_a)) for general simulation
Space Complexity: O(n) for storing machine types
*/
#include <stddef.h>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;
void solution() {
  int n, q;
  cin >> n >> q;
  string machines;
  cin >> machines;
  int char_cnt = 0;
  for (char i : machines) {
    if (i == 'A')
      char_cnt++;
  }
  for (int i = 0; i < q; i++) {
    int tmp;
    cin >> tmp;
    int time = 0;
    // Optimization for special cases: all machines are of the same type
    if (n == 1 || char_cnt == 0 || char_cnt == n) {
      if (machines[0] == 'A') {
        cout << tmp << "\n";
      } else {
        cout << floor(log2(tmp)) + 1 << "\n";
      }
    } else {
      // General simulation case
      while (tmp != 0) {
        for (int i = 0; i < n; i++) {
          if (machines[i] == 'A') {
            tmp = tmp - 1;
          } else {
            tmp = tmp / 2;
          }
          time++;
          if (tmp == 0) {
            cout << time << "\n";
            break;
          }
          if (i == n - 1) {
            i = -1;
          }
        }
      }
    }
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solution();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/