// Problem: CF 1864 D - Matrix Cascade
// https://codeforces.com/contest/1864/problem/D

/*
Algorithm: Matrix Cascade
Techniques: Greedy, Difference Array, Simulation

Time Complexity: O(n^2)
Space Complexity: O(n^2)

This solution simulates the process of turning all matrix elements to 0 by 
performing operations on cells and propagating the effect to a triangular region
below and around the selected cell. We use a difference array technique to 
efficiently track the operations and their effects.

The algorithm processes the matrix from top to bottom, left to right. For each 
cell that is 1, we must perform an operation on that cell to flip it. The effect 
of this operation propagates to cells in a triangular region defined by the 
constraint x-i >= |y-j|. We use a difference array to efficiently manage 
the propagation of operations.
*/

#include <stdio.h>
#include <iosfwd>

using namespace std;
const int N = 3005;
int T, n, a[N][N], cnt[N][N];
const int SIZE = 1 << 23;
char buf[SIZE], *p1 = buf, *p2 = buf, pbuf[SIZE], *pp = pbuf;
#define getchar()                                                              \
  (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, SIZE, stdin), p1 == p2)        \
       ? EOF                                                                   \
       : *p1++)
#define putchar(c)                                                             \
  (pp - pbuf == SIZE ? (fwrite(pbuf, 1, SIZE, stdout), pp = pbuf, *pp++ = c)   \
                     : *pp++ = c)
inline int read() {
  int x = 0;
  char c = getchar();
  while (c < '0' || c > '9')
    c = getchar();
  while (c >= '0' && c <= '9') {
    x = (x << 1) + (x << 3) + (c ^ 48);
    c = getchar();
  }
  return x;
}
inline int readchar() {
  char c = getchar();
  while (c < '0' || c > '9')
    c = getchar();
  return (c ^ 48);
}
inline void write(int x) {
  int out[20], cnt = 0;
  do {
    out[++cnt] = (int)(x % 10);
    x /= 10;
  } while (x);
  for (int i = cnt; i >= 1; i--)
    putchar((char)(out[i] ^ 48));
  return;
}
inline void rev(int x, int y) {
  if (a[x][y] == 0)
    a[x][y] = 1;
  else
    a[x][y] = 0;
}
int main() {
  T = read();
  while (T--) {
    n = read();
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        a[i][j] = readchar(), cnt[i][j] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cnt[i][j] %= 2;
        if (cnt[i][j] == 1)
          rev(i, j);
        if (a[i][j] == 1)
          rev(i, j), ans++, cnt[i][j]++;
        cnt[i][j] %= 2;
        if (cnt[i][j] == 1) {
          rev(i + 1, j), cnt[i + 1][j - 1]++, cnt[i + 1][j + 1]++;
          if (j != 1 && j != n)
            cnt[i + 2][j] += cnt[i][j];
        }
      }
    }
    write(ans), putchar('\n');
  }
  fwrite(pbuf, 1, pp - pbuf, stdout);
  return 0;
}


// https://github.com/VaHiX/CodeForces/