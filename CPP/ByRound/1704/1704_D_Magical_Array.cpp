// Problem: CF 1704 D - Magical Array
// https://codeforces.com/contest/1704/problem/D

/*
Purpose:
This code determines the special array among n given arrays and counts how many times Operation 2 was applied to it.
The approach uses prefix sums to analyze the difference between arrays and identify the one that differs, thus indicating it's the special array.

Algorithms/Techniques:
- Prefix Sum: Used to calculate cumulative sums of each array.
- Difference Analysis: Compares prefix sums of arrays to identify the one with different total sum, indicating operation 2 was used.
- Deduction Logic: Based on problem constraints, identifies which array is special based on the number of differing arrays.

Time Complexity:
O(n * m) where n is the number of arrays and m is the length of each array. This is due to iterating through all elements of all arrays once.

Space Complexity:
O(n) for storing the prefix sums of each array.
*/

#include <iostream>

#define ll long long
using namespace std;
ll s1[100010]; // Array to store prefix sums of each input array

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, m, i, cnt = 0, p; // cnt counts differing arrays, p stores index of differing array
    cin >> n >> m;
    for (i = 1; i <= n; i++) {
      ll s2 = 0; // running sum for current array
      s1[i] = 0; // reset prefix sum for current array
      for (int j = 0; j < m; j++) {
        ll x;
        cin >> x;
        s2 += x; // accumulate current element to s2
        s1[i] += s2; // accumulate prefix sum into s1[i]
      }
      if (s1[i] != s1[1]) // if prefix sum differs from first array's prefix sum
        p = i, cnt++; // store index and increment counter
    }
    if (cnt == 1) // exactly one array differs, hence it's the special one
      cout << p << ' ' << s1[1] - s1[p] << endl; // output index and number of operations
    else // if more than one or no array differs, the first one is special
      cout << 1 << ' ' << s1[2] - s1[1] << endl; // output first index and operations on second array
  }
}


// https://github.com/VaHiX/CodeForces/