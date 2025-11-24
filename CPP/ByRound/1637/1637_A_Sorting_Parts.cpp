// Problem: CF 1637 A - Sorting Parts
// https://codeforces.com/contest/1637/problem/A

/*
Algorithm: Sorting Parts
Techniques: Simulation with sorting, linear scan

Time Complexity: O(n log n) per test case due to sorting operations
Space Complexity: O(n) for the array storage

This problem asks whether we can make an array unsorted by choosing a prefix and suffix,
sorting them independently. The key insight is that if the array is already sorted,
then no matter how we split and sort, it will remain sorted. Otherwise, there's a chance
to create an unsorted array through this operation.
*/
#include <algorithm>
#include <iostream>

using namespace std;
int a[10010];
int main() {
  int T, i, n;
  cin >> T;
  while (T--) {
    cin >> n;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    // Check if array is already sorted
    cout << ((is_sorted(a + 1, a + n + 1)) ? "NO\n" : "YES\n");
    // If sorted, answer "NO", otherwise "YES"
  }
}


// https://github.com/VaHiX/codeForces/