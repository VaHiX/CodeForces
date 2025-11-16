// Problem: CF 1742 G - Orray
// https://codeforces.com/contest/1742/problem/G

/*
Purpose: To rearrange the elements of an array such that the resulting prefix OR array is lexicographically maximum.
Algorithm: Greedy approach with sorting. For each position, we sort the remaining elements in a way that maximizes the prefix OR at that step.
Time Complexity: O(32 * n * log(n)) where n is the size of the array. The 32 comes from the number of bits in an integer.
Space Complexity: O(1) excluding the input array, as we use only a few extra variables.
*/
#include <algorithm>
#include <iostream>

using namespace std;
int n, t, k, a[200005];
// Custom comparator that sorts based on OR with current k value to maximize prefix OR
bool cmp(int x, int y) { return (x | k) > (y | k); }
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    k = 0; // k keeps track of the OR of elements processed so far
    // Iterate through each position up to 32 (since integers are up to 10^9)
    for (int i = 0; i < min(n, 32); i++) {
      sort(a + i, a + n, cmp); // Sort from index i to end based on comparator
      k |= a[i]; // Update k with the OR of current element
    }
    for (int i = 0; i < n; i++) {
      cout << a[i] << " "; // Output the rearranged array
    }
    cout << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/