// Problem: CF 1759 G - Restore the Permutation
// https://codeforces.com/contest/1759/problem/G

/*
Code Purpose:
This code restores the lexicographically smallest permutation from a given array
b, where each element of b is the maximum of two consecutive elements in the
permutation. The problem involves reconstructing the permutation such that the
given max pairs are satisfied and the result is lexicographically minimal.

Algorithm:
1. For each test case, we process b array to reconstruct the permutation p.
2. We use a set to maintain available numbers, initially all numbers from 1 to
n.
3. For odd indices in b, we greedily assign the smallest possible value that is
less than or equal to b[i] and exists in the set.
4. The even indices are filled greedily based on the values of b, making sure
that the max condition holds.
5. A check is done to make sure that all the assignments are valid.

Time Complexity: O(n log n) per test case due to set operations.
Space Complexity: O(n) for the array and set storage.

*/

#include <bits/stdc++.h>
using namespace std;
int n, a[1 << 18], f, i, t;

void S() {
  cin >> n;
  set<int> s;
  // Initialize set with all numbers from 1 to n
  for (i = n; i; f = 1)
    s.insert(i--);

  // Process the first half of b array (odd positions)
  for (; i < n / 2;) {
    cin >> a[2 * i + 1];        // Read b[i] into a[2*i+1] (odd index)
    f &= s.count(a[2 * i + 1]); // Check if value exists in set
    s.erase(a[2 * i++ + 1]);    // Remove value from set
  }

  i--; // Adjust for loop logic

  // Process the second half (even positions) in reverse order
  for (; i + 1;) {
    auto it = s.lower_bound(a[2 * i + 1]); // Find smallest value >= a[2*i+1]
    if (it == s.begin()) {
      f = 0; // No valid value found, impossible to build permutation
      break;
    }
    a[2 * i--] = *--it; // Assign largest value < a[2*i+1] to even index
    s.erase(it);        // Remove value from set
  }

  n--; // Adjust n for printing loop
  if (!f)
    cout << "-1 "; // Output -1 if impossible
  else
    for (; i < n;)
      cout << a[++i] << ' '; // Print reconstructed permutation
}

int main() {
  for (cin >> t; t--; S())
    cout << '\n'; // Process all test cases
}

// https://github.com/VaHiX/CodeForces/