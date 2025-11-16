// Problem: CF 676 A - Nicholas and Permutation
// https://codeforces.com/contest/676/problem/A

/*
 * Problem: Nicholas and Permutation
 * 
 * Purpose: To maximize the distance between the minimum element (1) and the maximum element (n)
 *          in a permutation by performing exactly one swap.
 * 
 * Approach:
 * 1. Find the positions of elements 1 and n in the given array.
 * 2. Calculate the possible distances between 1 and n after swapping:
 *    - Swap 1 with first element (distance = |pos_of_1 - 1|)
 *    - Swap 1 with last element (distance = |pos_of_1 - n|)
 *    - Swap n with first element (distance = |pos_of_n - 1|)
 *    - Swap n with last element (distance = |pos_of_n - n|)
 * 3. Sort all these distances and take the maximum.
 * 
 * Time Complexity: O(n) for finding positions + O(1) for sorting 4 elements => O(n)
 * Space Complexity: O(1) additional space (vector size is fixed at 4)
 * 
 * Algorithms/Techniques: 
 * - Linear scan to find indices
 * - Sorting of fixed-size vector
 */

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>
#include <vector>

typedef long long int ll;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, mi, fi;
  cin >> n;
  ll a[n];
  vector<ll> v;
  for (i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == n) {
      mi = i + 1; // Store position of maximum element (1-indexed)
    } else if (a[i] == 1) {
      fi = i + 1; // Store position of minimum element (1-indexed)
    }
  }
  // Compute all possible distances after one swap
  v.push_back(abs(mi - 1));      // Distance if we swap n with first element
  v.push_back(abs(mi - n));      // Distance if we swap n with last element
  v.push_back(abs(fi - 1));      // Distance if we swap 1 with first element
  v.push_back(abs(fi - n));      // Distance if we swap 1 with last element
  sort(v.begin(), v.end());      // Sort to get maximum at the end
  cout << v[3];                  // Output maximum possible distance
  return 0;
}


// https://github.com/VaHiX/CodeForces/