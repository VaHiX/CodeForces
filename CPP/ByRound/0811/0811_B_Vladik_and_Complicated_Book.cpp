// Problem: CF 811 B - Vladik and Complicated Book
// https://codeforces.com/contest/811/problem/B

/*
Purpose: 
This program determines whether a specific element in a permutation remains unchanged after sorting a subsegment of the permutation. 
For each query, it simulates sorting the subarray [l, r] and checks if the element at position x (1-indexed) remains in the same place.

Algorithms/Techniques:
- Simulation of sorting a range and checking position of a specific element
- Counting elements smaller than the target element within the range to determine the final sorted position

Time Complexity: O(m * n) where m is number of queries and n is size of permutation. For each query, we scan a subarray of length up to n.
Space Complexity: O(n) for storing the permutation array.

*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m, p;
  cin >> n >> m;
  vector<int> pgs;
  while (n--) {
    cin >> p;
    pgs.push_back(p);
  }
  int l, r, x, xa, v;
  while (m--) {
    cin >> l >> r >> x;
    l--; // Convert to 0-indexed
    xa = 0; // Count how many elements are smaller than v in range [l, r)
    v = pgs[x - 1]; // The value at the x-th position (1-indexed)
    for (int i = l; i < r; i++)
      if (pgs[i] < v)
        xa++; // Increment count of smaller elements
    if (v == pgs[l + xa]) // Check if v is at its correct sorted position
      cout << "Yes\n";
    else
      cout << "No\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/