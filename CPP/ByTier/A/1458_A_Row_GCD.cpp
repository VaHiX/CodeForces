// Problem: CF 1458 A - Row GCD
// https://codeforces.com/contest/1458/problem/A

/*
Purpose: 
    Computes the GCD of sequences where each element of sequence 'a' is added to each element of sequence 'b'.
    For each b_j, calculates GCD(a_1 + b_j, a_2 + b_j, ..., a_n + b_j).

Algorithms/Techniques:
    - Use GCD properties: GCD(a1+b, a2+b, ..., an+b) = GCD((a1-b), (a2-b), ..., (an-b), b)
    - However, here we compute GCD of differences first, then use that to compute final answer.
    - Row GCD optimization using __gcd and prefix difference.

Time Complexity: O(n * log(max(a_i)) + m * log(max(a_i)))
Space Complexity: O(1)

Input:
    n, m (number of elements in sequences a and b respectively)
    Sequence a of size n
    Sequence b of size m

Output:
    For each b_j, output GCD(a1+bj, a2+bj, ..., an+bj)
*/

#include <bits/std_abs.h>
#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  long long x, g = 0, n, m, a1;
  cin >> n >> m >> a1; // Read n, m and first element of sequence a
  for (int i = 1; i < n; i++) // Loop through remaining elements of sequence a
    cin >> x, g = __gcd(g, abs(x - a1)); // Compute GCD of differences from first element
  for (int i = 0; i < m; i++) // Loop through each element of sequence b
    cin >> x, cout << __gcd(g, a1 + x) << " "; // Output final GCD for current b_j
  return 0;
}


// https://github.com/VaHiX/codeForces/