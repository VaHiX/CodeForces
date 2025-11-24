// Problem: CF 2133 B - Villagers
// https://codeforces.com/contest/2133/problem/B

/*
B. Villagers
Time Complexity: O(n log n) per test case due to sorting; overall complexity depends on total n across all test cases.
Space Complexity: O(n) for the array storage.

Algorithms/Techniques:
- Greedy algorithm with sorting
- Pairing elements from largest to smallest in a greedy manner to minimize total emeralds spent

The problem involves making all villagers friends by pairing them optimally. Each operation combines two villagers, 
reducing their grumpiness and giving away emeralds based on max(grumpiness). Goal is to minimize total emeralds.

The optimal strategy is to always pair the largest available grumpiness values possible:
- Sort the array in ascending order.
- Greedily pick the largest remaining element and pair it with an element two positions before it (to ensure
  we get a valid pairing and maintain minimum cost).
- Accumulate emeralds given based on max of the two elements in each pair.

This greedy approach works because we're minimizing the "cost" per operation by always selecting the maximum
available values to be paired, minimizing overall emerald spending.
*/

#include <algorithm>
#include <iostream>

using namespace std;
long long t, n, a[200005], p, l;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + n + 1); // Sort the array to enable greedy selection of pairs
    l = n;                  // Start from the largest element
    p = 0;                  // Initialize total emeralds needed
    while (l >= 1) {
      p += a[l];            // Add the max grumpiness value in current pair
      l -= 2;               // Move to next unpaired element (greedy step)
    }
    cout << p << endl;
  }
}


// https://github.com/VaHiX/codeForces/