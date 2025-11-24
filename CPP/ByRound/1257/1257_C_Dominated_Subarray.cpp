// Problem: CF 1257 C - Dominated Subarray
// https://codeforces.com/contest/1257/problem/C

/*
C. Dominated Subarray
Algorithms/Techniques: Hashing, Sliding window technique
Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)

The problem asks to find the shortest subarray that is "dominated" by some value,
meaning that this value occurs more times than any other value in the subarray.
A subarray is dominated if it has at least 2 elements and one element appears 
more frequently than all others.

This solution uses a hash map to track the last occurrence of each element.
For each position, we check the minimum length subarray ending at that position
which is dominated by the current element. The key insight is that a subarray is
dominated by an element if the same element appears at least twice in it,
and the distance between these two occurrences determines the minimal such subarray.
*/

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
auto max_int = numeric_limits<int>::max();
int main() {
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t, n, e, i;
  cin >> t;
  while (t--) {
    cin >> n;
    vector<int> B(n + 1, -1); // B[v] stores the last index where value v appeared
    int bst = max_int;       // tracks the minimum length of a dominated subarray
    for (i = 0; i < n; B[e] = i++) { // iterate through array elements, update last seen index
      cin >> e;
      // if we have seen 'e' before, calculate the distance and update minimum
      bst = min(B[e] + 1 ? i - B[e] + 1 : max_int, bst);
    }
    cout << (bst == max_int ? -1 : bst) << '\n'; // output result
  }
}


// https://github.com/VaHiX/codeForces/