// Problem: CF 922 B - Magic Forest
// https://codeforces.com/contest/922/problem/B

#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 15
#define inf 100000
#define pp pair<char, char>
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  int x, y;
  cin >> n;
  ll cnt = 0;
  // Iterate through all possible pairs (i, j) where i, j <= n
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      // Calculate xor of i and j
      x = i ^ j;
      // Check if the xor result is within bounds and positive
      if (x <= n && x > 0) {
        k = 0;
        // Check triangle inequality conditions:
        // If sum of two sides is less than or equal to the third,
        // it's invalid for a non-degenerate triangle
        if (i + j <= x)
          k++;
        else if (i + x <= j)
          k++;
        else if (x + j <= i)
          k++;
        // If none of the triangle inequalities are violated, increment counter
        if (k <= 0)
          cnt++;
      }
    }
  }
  // Since we count each valid triangle triple (a,b,c) 6 times due to symmetry,
  // divide by 6 to get the correct count
  cout << cnt / 6;
  return 0;
}


// https://github.com/VaHiX/CodeForces/