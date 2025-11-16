// Problem: CF 870 A - Search for Pretty Integers
// https://codeforces.com/contest/870/problem/A

/*
 * Problem: Search for Pretty Integers
 * 
 * Purpose: Find the smallest positive integer that contains at least one digit
 *          from each of two given lists of digits.
 * 
 * Algorithm:
 * 1. Read two lists of digits and store them in boolean arrays for fast lookup.
 * 2. Track the minimum digit from each list.
 * 3. Check for any digit that exists in both lists — if found, that digit is the answer.
 * 4. Otherwise, form the smallest two-digit number by combining the smallest digits from both lists.
 * 
 * Time Complexity: O(n + m + 10) = O(n + m), since we iterate through lists once and check up to 10 digits.
 * Space Complexity: O(1) — we use fixed-size arrays of size 10 regardless of input.
 */

#include <cstdio>
int main() {
  const int N = 10;
  int n, m;
  scanf("%d %d", &n, &m);
  bool a[N] = {0};  // Boolean array to mark digits present in first list
  bool b[N] = {0};  // Boolean array to mark digits present in second list
  int u(10), v(10);  // u = min digit in first list, v = min digit in second list
  for (long p = 0; p < n; p++) {
    int x;
    scanf("%d", &x);
    a[x] = 1;  // Mark digit x as present in first list
    u = (u < x) ? u : x;  // Keep track of minimum digit in first list
  }
  for (long p = 0; p < m; p++) {
    int x;
    scanf("%d", &x);
    b[x] = 1;  // Mark digit x as present in second list
    v = (v < x) ? v : x;  // Keep track of minimum digit in second list
  }
  // Ensure u is the smaller of the two minimums
  if (u > v) {
    int x = u;
    u = v;
    v = x;
  }
  // Check if there is any common digit in both lists
  for (int p = 0; p < N; p++) {
    if (a[p] && b[p]) {  // If digit p is present in both lists
      printf("%d\n", p);
      return 0;
    }
  }
  // If no common digit, form the smallest two-digit number
  printf("%d\n", 10 * u + v);
  return 0;
}


// https://github.com/VaHiX/CodeForces/