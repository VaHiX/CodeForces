// Problem: CF 1662 L - Il Derby della Madonnina
// https://codeforces.com/contest/1662/problem/L

/*
L. Il Derby della Madonnina
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

The derby between Milan and Inter is happening soon, and you have been chosen as the assistant referee for the match, also known as linesman. Your task is to move along the touch-line, namely the side of the field, always looking very carefully at the match to check for offside positions and other offences.
Football is an extremely serious matter in Italy, and thus it is fundamental that you keep very close track of the ball for as much time as possible. This means that you want to maximise the number of kicks which you monitor closely. You are able to monitor closely a kick if, when it happens, you are in the position along the touch-line with minimum distance from the place where the kick happens.
Fortunately, expert analysts have been able to accurately predict all the kicks which will occur during the game. That is, you have been given two lists of integers, t_1, ..., t_n and a_1, ..., a_n, indicating that t_i seconds after the beginning of the match the ball will be kicked and you can monitor closely such kick if you are at the position a_i along the touch-line. 
At the beginning of the game you start at position 0 and the maximum speed at which you can walk along the touch-line is v units per second (i.e., you can change your position by at most v each second). What is the maximum number of kicks that you can monitor closely?

Algorithms/Techniques:
- Greedy approach with interval scheduling
- Line sweep / event processing
- Binary search with segment tree or upper_bound for efficient interval management
- Sorting and dynamic programming idea using LIS-based greedy technique (similar to finding longest increasing subsequence)

Time Complexity: O(n log n) due to sorting + operations on vector of pairs.
Space Complexity: O(n) for storing the intervals and auxiliary vectors.

*/

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
const int sz = 2e5 + 5;
int a[sz], t[sz];

int main() {
  int n;
  ll v;
  cin >> n >> v;
  for (int i = 0; i < n; i++)
    scanf("%d", &t[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  vector<pair<ll, ll>> p; // Store valid intervals [start, end] where we can attend the kick
  for (int i = 0; i < n; i++) {
    // Calculate minimum and maximum position needed to catch this kick given the speed v
    if (t[i] * v - abs(a[i]) < 0)
      continue; // Skip kicks that are impossible to reach under the time/speed constraint
    p.emplace_back(t[i] * v - a[i], t[i] * v + a[i]); // interval [start, end]
  }
  sort(p.begin(), p.end()); // Sort intervals by start time for greedy selection

  vector<ll> b; // This is an optimized data structure like lis but used for overlapping intervals
  for (auto &[x, y] : p) {
    if (b.empty() || b.back() <= y)
      b.push_back(y); // If current interval can be added without overlap
    else
      *upper_bound(b.begin(), b.end(), y) = y; // Replace first element > y with y to maintain ordering
  }
  cout << b.size();
}


// https://github.com/VaHiX/codeForces/