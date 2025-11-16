// Problem: CF 1053 A - Vasya and Triangle
// https://codeforces.com/contest/1053/problem/A

/*
Algorithm: 
The problem requires finding three integer points forming a triangle with area nm/k.
The area of a triangle with vertices (x1, y1), (x2, y2), (x3, y3) is:
Area = 0.5 * |x1(y2 - y3) + x2(y3 - y1) + x3(y1 - y2)|

We can simplify by choosing two points on the x-axis and one point on the y-axis:
Let (0, 0), (x, 0), (0, y) form a triangle with area 0.5 * x * y.
So we set 0.5 * x * y = nm/k, which means x * y = 2 * nm / k.

Since we are constrained by 0 <= x <= n and 0 <= y <= m:
We try x = n and y = 2 * nm / k / n = 2 * m / k.
We must ensure that y <= m and 2 * nm / k is divisible by n.

If not, we use prime factorization of k to adjust x and y appropriately.
Then we adjust x and y to make sure they are within constraints.

Time Complexity: O(sqrt(k)) - due to prime factorization
Space Complexity: O(1) - constant extra space
*/

#include <ctype.h>
#include <iostream>
#include <stdio.h>
#define int long long
using namespace std;

inline int read() {
  int x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch))
    f |= (ch == 45), ch = getchar();
  while (isdigit(ch))
    x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
  return f ? -x : x;
}

int n, m, k;

signed main() {
  n = read(), m = read(), k = read();
  
  // Check if it's possible: 2 * n * m must be divisible by k
  if ((n * m * 2) % k)
    return puts("NO") & 0;
    
  puts("YES");
  
  // Start with a candidate x and y
  int x = n * 2, y = m;
  
  // Factorize k and adjust x and y to meet constraints
  for (int i = 2; i * i <= k; ++i) {
    while (k % i == 0) {
      k /= i;
      if (x % i == 0)
        x /= i;
      else
        y /= i;
    }
  }
  
  // If after factorization k > 1, adjust x or y accordingly
  if (x % k == 0)
    x /= k;
  else
    y /= k;
    
  // Ensure that x is within bounds, if not scale it and increase y
  if (x > n)
    x /= 2, y *= 2;
    
  // Output the three vertices
  printf("0 0\n%lld 0\n0 %lld", x, y);
  return 0;
}


// https://github.com/VaHiX/CodeForces/