// Problem: CF 869 A - The Artful Expedient
// https://codeforces.com/contest/869/problem/A

/*
 * Problem: A. The Artful Expedient
 * 
 * Purpose: 
 *   Given two arrays x and y of n distinct integers each, the task is to count the number of ordered pairs 
 *   (i, j) such that x[i] XOR y[j] is one of the 2n values in the combined arrays. If the count is even, 
 *   Karen wins; otherwise, Koyomi wins.
 * 
 * Algorithm:
 *   - For each pair (i, j), compute x[i] XOR y[j] and check if the result exists in the union of the two arrays.
 *   - However, the given solution simply prints "Karen" regardless of input.
 * 
 * Time Complexity: O(1) - The solution does not process the input or perform any computation.
 * Space Complexity: O(1) - Only a constant amount of extra space is used.
 * 
 * Techniques:
 *   - Reading input
 *   - Simple output
 * 
 * Note:
 *   The actual optimal solution would involve precomputing all XOR results and checking membership in the set.
 *   But the current implementation is naive and always prints "Karen".
 */

#include <stdio.h>
#include <iostream>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int cnt = 0;
  scanf("%d", &n); // Read the size of the arrays
  int x[n], y[n];
  for (i = 0; i < n; i++)
    scanf("%d", &x[i]); // Read array x
  for (i = 0; i < n; i++)
    scanf("%d", &y[i]); // Read array y
  cout << "Karen"; // Output the winner (always Karen in this implementation)
  return 0;
}


// https://github.com/VaHiX/CodeForces/