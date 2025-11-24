// Problem: CF 1352 A - Sum of Round Numbers
// https://codeforces.com/contest/1352/problem/A

/*
Purpose: This program decomposes a given positive integer n into the minimum number of round numbers (numbers of the form d00...0) such that their sum equals n.

Algorithm:
- For each digit in the number from right to left:
  - Extract the digit and multiply it by the corresponding power of 10.
  - If the resulting value is non-zero, add it to the array of round numbers.
- Output the count of round numbers and the numbers themselves.

Time Complexity: O(log n) per test case, since we process each digit once.
Space Complexity: O(log n) due to the array storing round numbers (at most log n digits).

Techniques:
- Mathematical decomposition: Using modulo and division to extract digits.
- Greedy approach: Each non-zero digit contributes one round number.

*/

#include <stdio.h>
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n, arr[6], k = 0, p = 1, i;
    scanf("%d", &n);
    // Process each digit from right to left
    for (; n > 0; p *= 10, n /= 10)
      // Compute round number for current digit and add to array if non-zero
      if ((arr[k] = (n % 10) * p) > 0)
        k++;
    printf("%d\n", k);
    // Print all the round numbers
    for (i = 0; i < k; i++)
      printf("%d ", arr[i]);
  }
}


// https://github.com/VaHiX/CodeForces/