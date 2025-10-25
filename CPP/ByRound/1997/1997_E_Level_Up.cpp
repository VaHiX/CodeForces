// Problem: CF 1997 E - Level Up
// https://codeforces.com/contest/1997/problem/E

/*
Algorithm: Using a Binary Indexed Tree (Fenwick Tree) to efficiently track
           the number of fights up to a certain index and determine if a
           monster can be fought based on Monocarp's current level.

Time Complexity: O(N * log(N) + Q * log(N))
Space Complexity: O(N)

The solution uses a Fenwick Tree (sg) to store and query fight counts.
For each monster, we calculate the minimum level Monocarp needs to fight
it by binary searching on the Fenwick tree. Then we update the tree
with this information.

We precompute for all monsters and answer queries in O(log(N)) time.
*/

#include <stdio.h>

static char buf[1000000], *paa = buf, *pd = buf;
static char buf2[1000000], *pp = buf2;
#define getchar()                                                              \
  paa == pd && (pd = (paa = buf) + fread(buf, 1, 1000000, stdin), paa == pd)   \
      ? EOF                                                                    \
      : *paa++
inline void pc(char ch) {
  if (pp - buf2 == 1000000)
    fwrite(buf2, 1, 1000000, stdout), pp = buf2;
  *pp++ = ch;
}
inline void pcc() {
  fwrite(buf2, 1, pp - buf2, stdout);
  pp = buf2;
}
inline int read(void) {
  int w = 1;
  register int x(0);
  register char c(getchar());
  while (c < '0' || c > '9') {
    if (c == '-')
      w = -1;
    c = getchar();
  }
  while (c >= '0' && c <= '9')
    x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
  return w * x;
}
int N, Q, sg[200009], b[200009];
#define lb(n) ((n) & (-(n)))
signed main(void) {
  N = read();
  Q = read();
  for (int i = 1; i <= N; i++) {
    int a = read(); // Level of monster i
    int l = 0, su = 0, ma = N / a; // l: low bound, su: sum so far, ma: max possible
    for (int j = 17; j >= 0; j--) { // Binary search on Fenwick tree
      if (l + (1 << j) <= ma && (su + sg[l + (1 << j)]) >= a * (l + (1 << j))) {
        su += sg[l + (1 << j)]; // Add contribution of current bit
        l += (1 << j); // Move to higher bit
      }
    }
    l++; // Found the minimum index
    b[i] = l; // Store minimum required level for monster i
    while (l <= N) { // Update Fenwick tree
      sg[l]++;
      l += lb(l); // Move to next node in Fenwick tree
    }
  }
  while (Q--) { // Process queries
    int x = read(), y = read(); // x: monster index, y: k value
    if (y >= b[x]) // If k is sufficient for this monster to be fought
      pc('Y'), pc('E'), pc('S'); // Print YES
    else
      pc('N'), pc('O'); // Print NO
    pc('\n');
  }
  pcc(); // Flush output buffer
}


// https://github.com/VaHiX/CodeForces/