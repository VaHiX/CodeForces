// Problem: CF 2149 C - MEX rose
// https://codeforces.com/contest/2149/problem/C

/*
 * Problem: C. MEX rose
 * Purpose: Find the minimum number of operations to make the MEX of array equal to k.
 *          An operation allows setting any element to any value in [0, n].
 *
 * Algorithm:
 *   - Use a frequency vector to count occurrences of each number in input array.
 *   - Count how many numbers from 0 to k-1 are missing (countk).
 *   - If v[k] > 0, it means we have at least one element equal to k, which would prevent MEX from being k.
 *   - The result is max(countk, v[k]) because:
 *     - countk represents the minimum operations needed to ensure all numbers from 0 to k-1 exist.
 *     - v[k] accounts for whether we need to change elements equal to k or not.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) due to frequency vector
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n, k;
    cin >> n >> k;
    vector<long long> v(n + 1, 0); // Frequency vector to count occurrences
    for (int i = 0; i < n; i++) {
      long long num;
      cin >> num;
      v[num]++; // Increment frequency of the number
    }
    long long countk = 0;
    for (int i = 0; i < k; i++) {
      if (v[i] == 0)
        countk++; // Count how many numbers from 0 to k-1 are missing
    }
    long long s = max(countk, v[k]); // Minimum operations needed
    cout << s << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/