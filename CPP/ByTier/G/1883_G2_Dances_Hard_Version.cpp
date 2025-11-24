// Problem: CF 1883 G2 - Dances (Hard Version)
// https://codeforces.com/contest/1883/problem/G2

/*
Purpose: This code solves the problem of finding the minimum number of operations to make array 'a' element-wise less than array 'b' for all elements after reordering both arrays. The key idea is to optimize the pairing between elements of the two arrays to minimize the operations required. A greedy approach with sorting and deque operations is applied. For each test case, we compute the result for 'm' pairs of arrays.

Algorithms/Techniques:
- Sorting arrays to enable greedy matching
- Using deque for efficient push/pop from both ends
- Greedy matching of largest elements from 'a' with smallest elements from 'b'
- Counting required operations based on mismatches
- Optimizing by tracking how many operations can be saved for each pair

Time Complexity: O(n log n) per test case, due to sorting, where n is the size of the arrays.
Space Complexity: O(n) for storing the arrays and deque.

*/
#include <algorithm>
#include <deque>
#include <iostream>

using namespace std;
typedef long long ll;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int t, n, m;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    deque<int> a(n - 1), b(n);
    for (int &i : a)
      cin >> i;
    for (int &i : b)
      cin >> i;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    ll ops = 0;
    for (int i = n - 2, ctr = n - 1; i >= 0; i--, ctr--) {
      if (a[i] >= b[ctr]) {
        a.pop_back(); // Remove the largest element from a that can't be matched
        b.pop_front(); // Remove the smallest element from b that can't be matched
        ops += m; // Increment operations required
      }
    }
    bool can = true;
    m -= min(m, b[0] - 1); // Adjust m based on smallest element in b
    for (int i = 0; i < a.size(); i++) {
      if (a[i] >= b[i])
        can = false; // If an element in a is >= element in b, check if it can be resolved
      if (!can)
        ops += min(m, b[i + 1] - b[i]); // Add operations needed to resolve mismatches
      m -= min(m, b[i + 1] - b[i]); // Decrease m by the number of operations saved
      if (m == 0)
        break; // Stop early if no more operations can be performed
    }
    cout << ops + m << '\n'; // Print total operations
  }
}


// https://github.com/VaHiX/CodeForces/