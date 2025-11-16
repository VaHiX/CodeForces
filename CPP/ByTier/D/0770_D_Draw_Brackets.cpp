// Problem: CF 770 D - Draw Brackets!
// https://codeforces.com/contest/770/problem/D

/*
 * Problem: Draw Brackets!
 * Algorithm/Technique: Simulation with Stack Height Tracking
 *
 * Time Complexity: O(n^2) where n is the length of the bracket sequence.
 *                    The nested loops for constructing and printing the result take O(n^2) time.
 * Space Complexity: O(n^2) for storing the character grid of size up to 333 x 555.
 *
 * The solution simulates drawing brackets by tracking the depth of nesting.
 * For each bracket, it calculates where to place the vertical and horizontal lines.
 * The image is built by placing '|' for vertical connections, '+' for junctions, and '-' for horizontal segments.
 * The height of the image is determined by the maximum nesting depth.
 * The algorithm ensures that the brackets are drawn with minimal height while maintaining correct structure.
 */

#include <cstdio>
char ans[333][555];
void prt(int h, int d, int f, int c) {
  int r = h;
  for (int p = 0; p < d; p++)
    ans[r - p][c] = ans[r + p][c] = '|';  // Draw vertical lines for the bracket
  ans[r - d][c] = ans[r + d][c] = '+';    // Place the '+' at the top and bottom of the bracket
  ans[r - d][c + f] = ans[r + d][c + f] = '-';  // Place '-' at the ends of the bracket
}
int main() {
  int n;
  char s[111];
  scanf("%d\n%s", &n, s);
  int mh(0), c(0), d(0);
  for (int p = 0; p < n; p++) {
    d += (s[p] == '[') ? 1 : -1;  // Increase or decrease depth based on bracket type
    mh = (mh > d) ? mh : d;       // Track maximum depth
  }
  d = c = 0;
  for (int p = 0; p < n; p++) {
    if (p) {
      c += (s[p - 1] == '[' && s[p] == ']') ? 4 : 1;  // Advance column for spacing
    }
    if (s[p] == '[') {
      d++;  // Increase depth on opening bracket
    }
    prt(mh, mh - d + 1, (s[p] == '[') ? 1 : -1, c);  // Draw the current bracket
    if (s[p] == ']') {
      d--;  // Decrease depth on closing bracket
    }
  }
  for (int p = 0; p <= 2 * mh; p++) {
    for (int j = 0; j <= c; j++) {
      putchar(ans[p][j] ?: ' ');  // Print character or space if empty
    }
    puts("");  // Print newline at end of each row
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/