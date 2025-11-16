// Problem: CF 1807 E - Interview
// https://codeforces.com/contest/1807/problem/E

/*
Algorithm: Binary search on the answer
We are trying to find the pile that contains the special stone (which weighs 2 grams instead of 1 gram per stone).
The idea is to use binary search on the piles.
We can query the sum of weights of a subset of piles.
If we query a subset of piles and the total weight is equal to the expected weight of all stones in those piles (assuming no special stone),
then the special stone is not in that subset.
Otherwise, the special stone is in that subset.

Time Complexity: O(n * log n) - Binary search over n elements, each query takes O(log n) time for the sum
Space Complexity: O(n) - For storing the array and prefix sums

Approach:
1. Precompute prefix sums for fast range sum queries
2. Perform binary search on the indices of piles
3. For each query, ask for the sum of weights of a range of piles
4. Compare the actual sum to the expected sum (assuming all stones weigh 1 gram)
5. Based on comparison, narrow down the search space
*/

#include <iostream>

using namespace std;
const int MAX = 2e5 + 2;
int a[MAX], p[MAX], n, x;
void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[i] = p[i - 1] + a[i];  // Compute prefix sum
  }
  int l = 1;
  int r = n;
  int mid = 0;
  while (l <= r) {
    mid = (l + r) / 2;
    cout << '?' << " " << mid - l + 1 << " ";  // Query size
    for (int i = l; i <= mid; i++)             // Print pile indices
      cout << i << " ";
    cout << "\n\n";
    cout.flush();  // Flush output
    cin >> x;
    if (x == p[mid] - p[l - 1]) {  // If the sum is exactly what we expect (no special stone)
      l = mid + 1;                 // Special stone must be in right half
    } else {
      r = mid - 1;  // Special stone must be in left half
    }
  }
  cout << '!' << " " << l << "\n";  // Output the index of pile with special stone
  cout.flush();
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/