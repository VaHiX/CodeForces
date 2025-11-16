// Problem: CF 1936 A - Bitwise Operation Wizard
// https://codeforces.com/contest/1936/problem/A

/*
 * Problem: Find two indices i and j such that p[i] XOR p[j] is maximized.
 * Algorithm: 
 *   1. First, find the index with the maximum value using queries of the form "? idx idx idx idx".
 *      This finds the index mx such that p[mx] is the largest possible value in the permutation.
 *   2. Then, iterate through all indices to find the index my such that p[mx] XOR p[my] is maximized.
 *      This is done by comparing p[mx] | p[my] with p[mx] | p[i] for all i.
 *   3. If the comparison result indicates that the current pair is better, update my.
 * 
 * Time Complexity: O(n) for each test case, since we make at most 3n queries.
 * Space Complexity: O(1) - only using a few variables.
 */
#include <cstdio>
#include <iosfwd>

using namespace std;
int n, m, k, l, mx, my, t;
char query(int a, int b, int c, int d) {
  printf("? %d %d %d %d\n", a, b, c, d);
  fflush(stdout);
  char anc;
  scanf(" %c", &anc);
  return anc;
}
void solve() {
  scanf("%d", &n);
  mx = my = 0;
  // Find the index of the maximum element in the permutation
  for (int i = 1; i < n; ++i)
    if (query(mx, mx, i, i) == '<')
      mx = i;
  char c;
  // Find the index that maximizes the XOR with mx
  for (int i = 1; i < n; ++i) {
    c = query(mx, my, mx, i);
    if (c == '>')
      continue;
    if (c == '=' && query(my, my, i, i) == '<')
      continue;
    my = i;
  }
  printf("! %d %d\n", mx, my);
  fflush(stdout);
}
int main() {
  scanf("%d", &t);
  while (t--)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/