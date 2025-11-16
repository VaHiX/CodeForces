// Problem: CF 838 A - Binary Blocks
// https://codeforces.com/contest/838/problem/A

/*
Algorithm/Techniques: 
- Prefix sum for efficient range sum queries
- Brute-force over possible block sizes k (from 2 to min(n, m))
- For each k, divide the image into k x k blocks and calculate minimum toggles needed
- For each block, compute number of 1s; toggle to make all 0s or all 1s, choose smaller count
- Time complexity: O(min(n,m) * n * m)
- Space complexity: O(n * m)

Code Purpose:
This program compresses a binary image by dividing it into k x k blocks and 
determines the minimum number of pixels to toggle to make the image compressible for some choice of k > 1.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
constexpr int Maxn = 2505;
int n, m;
char arr[Maxn][Maxn];
int S[Maxn][Maxn];
int res = Maxn * Maxn;

// Function to get sum of 1s in a submatrix using prefix sums
int Get(int r1, int c1, int r2, int c2) {
  r2 = min(r2, n), c2 = min(c2, m);
  return S[r2][c2] - S[r1 - 1][c2] - S[r2][c1 - 1] + S[r1 - 1][c1 - 1];
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(__null);
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; ++i)
    scanf("%s", arr[i] + 1);
  // Build prefix sum array for efficient range queries
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      S[i][j] = S[i - 1][j] + S[i][j - 1] - (S[i - 1][j - 1]) +
                (int)(arr[i][j] == '1');
  // Try all possible block sizes k from 2 up to min(n, m)
  for (int i = 2; i <= n || i <= m; ++i) {
    int sum = 0;
    // Check every block of size i x i
    for (int j = 1; j <= n; j += i)
      for (int k = 1; k <= m; k += i) {
        int g = Get(j, k, j + i - 1, k + i - 1);
        // Calculate minimum toggles for current block
        sum += min(g, i * i - g);
      }
    res = min(res, sum);
  }
  cout << res << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/