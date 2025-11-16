// Problem: CF 799 C - Fountains
// https://codeforces.com/contest/799/problem/C

/*
 * Problem: C. Fountains
 * Purpose: Find two fountains with maximum total beauty that can be bought using given coins and diamonds.
 * 
 * Algorithm:
 * - Use two Binary Indexed Trees (Fenwick Trees): one for coins (C) and one for diamonds (D).
 * - For each fountain, check if it can be bought with available coins/diamonds.
 * - Query the BITs to find the best possible second fountain that can be bought along with current.
 * - Update BITs after considering each fountain.
 * 
 * Time Complexity: O(n * log(max_cost))
 * Space Complexity: O(max_cost) where max_cost is up to 100000
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>

#define N 100010
using namespace std;
int C[N], D[N], n, c, d, ans = 0, b, p, ret;
char s[5];

// Add value 'd' at position 'x' in BIT 'C'
void add(int C[], int x, int d) {
  for (; x <= 100000; x += x & -x) // Iterate through BIT
    C[x] = max(C[x], d); // Update maximum beauty at position
}

// Query maximum value in BIT 'C' up to position 'x'
int query(int C[], int x) {
  int y = -1e9; // Initialize with very small number
  for (; x; x -= x & -x) // Iterate through BIT
    y = max(y, C[x]); // Find max beauty in range
  return y;
}

int main() {
  scanf("%d%d%d", &n, &c, &d);
  memset(C, 128, sizeof(C)); // Initialize BITs with -1e9
  memset(D, 128, sizeof(D));
  
  for (int i = 0; i < n; i++) {
    scanf("%d%d%s", &b, &p, s);
    if (s[0] == 'C') {
      // Fountain costs in coins
      if (p > c) continue; // Skip if not affordable
      ret = max(query(C, c - p), query(D, d)); // Find max beauty from remaining coins or diamonds
      add(C, p, b); // Add current fountain to BIT for coins
    } else {
      // Fountain costs in diamonds
      if (p > d) continue; // Skip if not affordable
      ret = max(query(C, c), query(D, d - p)); // Find max beauty from remaining coins or diamonds
      add(D, p, b); // Add current fountain to BIT for diamonds
    }
    ans = max(ans, ret + b); // Update answer with total beauty
  }
  printf("%d", ans);
}


// https://github.com/VaHiX/CodeForces/