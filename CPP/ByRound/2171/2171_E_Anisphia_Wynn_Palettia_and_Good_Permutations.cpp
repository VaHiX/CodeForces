// Problem: CF 2171 E - Anisphia Wynn Palettia and Good Permutations
// https://codeforces.com/contest/2171/problem/E

/*
Purpose: This code constructs a "good" permutation of length n for each test case, 
         where a permutation is considered good if it has at most 6 bad indices. 
         A bad index is defined as an index i such that a[i], a[i+1], a[i+2] are all 
         pairwise coprime (gcd(a[i], a[i+1]) = gcd(a[i], a[i+2]) = gcd(a[i+1], a[i+2]) = 1).

         The approach uses a periodic pattern of two 6-element sequences to avoid 
         having more than 6 bad indices in total.

Algorithms/Techniques:
- Constructing a permutation using two base patterns of 6 elements
- Using periodic construction to ensure coprime properties are minimized
- Greedy placement of remaining elements in order

Time Complexity: O(n) per test case, as we iterate through the array once
Space Complexity: O(n) for storing the permutation array

*/
#include <iostream>

using namespace std;
const int N = 200005;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, p[N], i, j, k;
  int x[6] = {1, 2, 4, 5, 6, 3};  // First base pattern
  int y[6] = {1, 3, 6, 5, 4, 2};  // Second base pattern
  cin >> t;
  while (t--) {
    cin >> n;
    k = n / 6;  // Number of complete 6-element blocks
    for (i = 0; i < k; i++) {
      if (i % 2 == 0)
        for (j = 0; j < 6; j++)
          p[i * 6 + j] = x[j] + i * 6;  // Use pattern x for even blocks
      else
        for (j = 0; j < 6; j++)
          p[i * 6 + j] = y[j] + i * 6;  // Use pattern y for odd blocks
    }
    for (i = k * 6; i < n; i++)
      p[i] = i + 1;  // Fill remaining positions with consecutive integers
    for (i = 0; i < n; i++)
      cout << p[i] << ' ';  // Output the permutation
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/