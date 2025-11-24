// Problem: CF 2085 D - Serval and Kaitenzushi Buffet
// https://codeforces.com/contest/2085/problem/D

/*
D. Serval and Kaitenzushi Buffet
Purpose: Maximize the sum of deliciousness of plates taken from a conveyor belt, where each plate has k pieces of sushi.
         Serval can take a plate or eat one piece of previously taken sushi each minute.
         The strategy uses a greedy approach with a max heap (priority queue) to always select the best available plate
         when it's optimal to do so based on timing.

Algorithms/Techniques:
- Greedy algorithm + Priority Queue (Max Heap)
- Simulate the process of picking plates optimally

Time Complexity: O(n log n) per test case due to heap operations
Space Complexity: O(n) for storing the priority queue and input data

*/

#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;
const int maxn = 2e5 + 5;
int t, n, k;
priority_queue<int> q; // Max heap to keep track of deliciousness of plates taken but not yet eaten
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> t;
  for (int iiii = 1; iiii <= t; iiii++) {
    cin >> n >> k;
    long long ans = 0;
    while (q.size()) {
      q.pop(); // Clear the heap for each new test case
    }
    for (int i = 1; i <= n; i++) {
      int x;
      cin >> x;
      q.push(x); // Add current plate's deliciousness to heap
      // When we are near the end of the conveyor belt and have enough plates,
      // it's optimal to eat one already taken plate that has highest value (greedy)
      if ((n - i + 1) % (k + 1) == 0 && n - i) {
        ans += q.top(); // Add the maximum deliciousness plate we've taken so far
        q.pop();        // Remove it from the heap since we've eaten it
      }
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/