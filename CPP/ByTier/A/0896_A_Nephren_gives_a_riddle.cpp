// Problem: CF 896 A - Nephren gives a riddle
// https://codeforces.com/contest/896/problem/A

/*
 * Purpose: This program solves a problem where an infinite sequence of strings is defined recursively.
 *          Each string f[i] is built from the previous string f[i-1] by wrapping it in a template.
 *          The task is to find the k-th character of f[n] efficiently without constructing the full string.
 *
 * Algorithms/Techniques:
 * - Recursive string construction with memoization-like approach using precomputed lengths.
 * - Binary search-like traversal to determine which part of the recursive definition the k-th character belongs to.
 * - Precomputed lengths of each f[i] to avoid recalculating and reduce time complexity.
 *
 * Time Complexity: O(1) per query after preprocessing. Preprocessing takes O(1) time (fixed size array).
 * Space Complexity: O(1). The array f has a fixed size of 55 elements; all variables are constant space.
 */

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;
#define LL long long
int n, q;
LL k, f[55] = {75}; // Precomputed lengths of f[i], starting with f[0] = 75
string str = "What are you doing at the end of the world? Are you busy? Will "
             "you save us?"; // The base string f[0]
string fi = "What are you doing while sending \"", // Prefix for f[i] when i > 0
       se = "\"? Are you busy? Will you send \"", ed = "\"?"; // Middle and suffix parts

// Function to compute the k-th character of f[n]
char calc(int n, LL k) {
  // If k is beyond the length of f[n], return '.'
  if (n < 53 && k > f[n])
    return '.';
  // Base case: if n == 0, return character from the base string str
  if (n == 0)
    return str[k - 1];
  // If k is within the prefix fi, return character from it
  if (k <= 34)
    return fi[k - 1];
  // If k is in the portion derived from f[n-1], recurse
  if (n >= 54 || k <= f[n - 1] + 34)
    return calc(n - 1, k - 34);
  // If k is in the middle part of f[i], return from se
  if (k <= f[n - 1] + 66)
    return se[k - f[n - 1] - 35];
  // If k is in the ending part, return from ed
  if (k >= f[n] - 1)
    return ed[1 - (f[n] - k)];
  // Recurse for the rest part of f[n]
  return calc(n - 1, k - f[n - 1] - 66);
}

int main() {
  // Precompute the lengths of f[i] using recurrence: f[i] = f[i-1] * 2 + 68
  for (int i = 1; i < 55; i++)
    f[i] = f[i - 1] * 2 + 68;
  // Read number of queries
  for (cin >> q; q--;) {
    cin >> n >> k;
    putchar(calc(n, k)); // Output character for current query
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/