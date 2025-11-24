// Problem: CF 1672 F1 - Array Shuffling
// https://codeforces.com/contest/1672/problem/F1
 
/*
 * Problem: F1. Array Shuffling
 * Purpose: Given an array 'a', find a permutation 'b' such that the minimum
 * number of swaps needed to transform 'b' back to 'a' (called sadness) is
 * maximized.
 *
 * Algorithm:
 *   - The sadness of an array is the number of cycles in the permutation that
 * transforms it into 'a'.
 *   - To maximize the sadness, we want to create as many cycles as possible.
 *   - Strategy:
 *     1. Use a multiset to keep track of available elements.
 *     2. For each position, choose the smallest element greater than the
 * current element in the multiset. If no such element exists, choose the
 * smallest one.
 *     3. Remove used elements from the multiset to avoid reuse.
 *
 * Time Complexity: O(n log n) per test case due to multiset operations (insert,
 * erase, upper_bound). Space Complexity: O(n) for storing the array and the
 * multiset.
 */
 
#include <cstdio>
#include <iostream>
#include <set>
 
using namespace std;
int t, n, a[200001];
int main() {
  cin >> t;
  for (int i = 1; i <= t; i++) {
    multiset<int> s;  // Multiset to maintain sorted elements and support
                      // efficient operations
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
      s.insert(a[i]);  // Read array and insert into multiset
    }
    for (int i = 1; i <= n; i++) {
      multiset<int>::iterator it =
          s.upper_bound(a[i]);            // Find smallest element > a[i]
      if (it == s.end()) it = s.begin();  // If none exists, pick the smallest
      cout << *it << " ";                 // Output the chosen element
      s.erase(it);                        // Remove chosen element from multiset
    }
    cout << endl;
  }
}
 
// https://github.com/VaHiX/CodeForces/