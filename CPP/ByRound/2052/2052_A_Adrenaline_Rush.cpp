// Problem: CF 2052 A - Adrenaline Rush
// https://codeforces.com/contest/2052/problem/A

/*
Purpose: This code determines the maximum number of overtakes that could have occurred 
         during a race to achieve a given final car order. It simulates the process 
         of reversing the final order into the initial order by swapping adjacent cars,
         counting each swap as an overtake event.

Algorithms/Techniques: 
- Simulation technique to reverse the final order to initial order.
- Greedy swapping approach to minimize the number of swaps needed.
- Uses a mapping from car positions in final order to determine the necessary swaps.

Time Complexity: O(n^2) where n is the number of cars, due to nested loops for finding 
                 the correct position and swapping.

Space Complexity: O(n) for storing car positions and the sequence of overtakes.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#define ll long long
#define uint unsigned int
using namespace std;
constexpr int m = 998244353;

void call() {
  int n;
  cin >> n;
  vector<int> v(n), ans(n);  // v stores final order, ans stores current order
  map<int, int> m;  // Maps a car to the car it overtakes
  vector<pair<int, int>> sol;  // Stores the sequence of overtakes
  for (int i = 0; i < n; i++) {
    cin >> v[i];
    ans[i] = i + 1;  // Initialize ans to [1, 2, ..., n]
  }
  // Build mapping of which car overtakes which based on final order
  for (int i = 0, j = 0; i < n; i++) {
    for (j = i; j < n; j++) {
      if (v[i] > v[j]) {  // If v[i] should be ahead of v[j] in final arrangement
        m[v[i]] = v[j];  // v[i] overtakes v[j]
        break;
      }
    }
    if (j == n)  // No car after i is smaller than v[i]
      m[v[i]] = -1;
  }
  int k = 0;
  // Simulate the process until the order matches final arrangement
  while (k < n) {
    for (int i = 1; i < n; i++) {
      // If the car at position i-1 should overtake the car at position i
      if (m[ans[i - 1]] == ans[i]) {
        break;  // No more overtakes needed at this step
      }
      // Record the overtake event: ans[i-1] overtakes ans[i]
      sol.push_back({ans[i], ans[i - 1]});
      // Swap the cars in the current order
      int t = ans[i - 1];
      ans[i - 1] = ans[i];
      ans[i] = t;
    }
    k++;
  }
  cout << sol.size() << "\n";  // Print total number of overtakes
  for (auto x : sol)  // Output all overtakes
    cout << x.first << " " << x.second << "\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  while (t--) {
    call();
    cout << endl;
  }
}


// https://github.com/VaHiX/CodeForces/