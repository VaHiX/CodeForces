// Problem: CF 1336 B - Xenia and Colorful Gems
// https://codeforces.com/contest/1336/problem/B

/*
B. Xenia and Colorful Gems
time limit per test
3 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Xenia is a girl being born a noble. Due to the inflexibility and harshness of her family, Xenia has to find some ways to amuse herself.
 
Recently Xenia has bought n_r red gems, n_g green gems and n_b blue gems. Each of the gems has a weight.
Now, she is going to pick three gems.
Xenia loves colorful things, so she will pick exactly one gem of each color.
Xenia loves balance, so she will try to pick gems with little difference in weight.
Specifically, supposing the weights of the picked gems are x, y and z, Xenia wants to find the minimum value of (x-y)^2+(y-z)^2+(z-x)^2. As her dear friend, can you help her?

Algorithms/Techniques:
- Three pointers technique combined with sorting
- For each permutation of gem colors (red, green, blue), we use two pointers to efficiently find minimal difference
- Sort all arrays first to enable binary search techniques
- Time complexity: O(n log n) per test case where n = sum of all gem counts
- Space complexity: O(1) extra space excluding input storage

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
ll ans;
int a[3][N], n[3];
ll sq(int x) { return 1ll * x * x; }
void f(int p, int q, int r) {
  // Two pointers approach for finding optimal triplet
  int j = -1, k = 0;
  for (int i = 0; i < n[p]; i++) {
    // Advance k to find smallest element in array r that is >= a[p][i]
    while (k < n[r] && a[r][k] < a[p][i])
      k++;
    if (k == n[r]) // No valid element in r found
      break;
    // Adjust j to find largest element in array q that is <= a[p][i]
    while (j + 1 < n[q] && a[q][j + 1] <= a[p][i])
      j++;
    if (j == -1) // No valid element in q
      continue;
    // Compute squared differences and update minimum
    ans = min(ans, sq(a[p][i] - a[q][j]) + sq(a[q][j] - a[r][k]) +
                       sq(a[p][i] - a[r][k]));
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    cin >> n[0] >> n[1] >> n[2];
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < n[i]; j++)
        cin >> a[i][j];
      sort(a[i], a[i] + n[i]); // Sort each gem array
    }
    ans = 5e18;
    f(0, 1, 2); // Try red-green-blue order
    f(0, 2, 1); // Try red-blue-green order
    f(1, 0, 2); // Try green-red-blue order
    f(1, 2, 0); // Try green-blue-red order
    f(2, 0, 1); // Try blue-red-green order
    f(2, 1, 0); // Try blue-green-red order
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/codeForces/