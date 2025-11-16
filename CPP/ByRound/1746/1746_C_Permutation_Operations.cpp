// Problem: CF 1746 C - Permutation Operations
// https://codeforces.com/contest/1746/problem/C

/*
Code Purpose:
This code solves the problem of minimizing inversions in a permutation after performing n operations.
Each operation i increases all elements of a chosen suffix by i. 
The strategy is to determine for each operation i, which suffix to choose to minimize inversions.
The key insight is to find the position where each element i (in sorted order) should be placed to minimize the number of inversions.
This is done by mapping each element to its original position and determining a greedy choice for operation suffix.

Algorithms/Techniques:
- Greedy strategy based on position mapping
- Uses an auxiliary array to store positions of elements

Time Complexity: O(n) per test case
Space Complexity: O(n) for the arrays used to store positions and input

*/
#include <algorithm>
#include <iostream>

using namespace std;
int t, n, a[200001], b[200001];
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      b[a[i]] = i + 1;  // Store the position (1-indexed) of each element in the original array
    }
    for (int i = 1; i <= n; i++)
      cout << min(b[i], n) << " ";  // For each element i, choose the suffix ending at min(position, n)
    cout << "\n";
  }
}


// https://github.com/VaHiX/CodeForces/