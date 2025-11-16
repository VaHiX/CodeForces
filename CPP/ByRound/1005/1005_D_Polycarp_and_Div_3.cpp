// Problem: CF 1005 D - Polycarp and Div 3
// https://codeforces.com/contest/1005/problem/D

/*
 * Problem: Polycarp and Div 3
 * 
 * Algorithm: Greedy approach
 * 
 * Time Complexity: O(n), where n is the length of the input string
 * Space Complexity: O(1), only using a constant amount of extra space
 * 
 * The solution works by scanning the digits from left to right and greedily
 * making cuts when we find a number divisible by 3. A number is divisible by 3
 * if the sum of its digits is divisible by 3. We track the last two digits
 * to help determine if a new number formed by adding the current digit can be
 * divisible by 3.
 */

#include <cstdio>
int n, d, a, b;
char m;
int main() {
  while ((m = getchar()) != '\n') {
    n = m - 48; // Convert character digit to integer
    // Check if current digit alone is divisible by 3,
    // or if combining with previous digit(s) forms a number divisible by 3
    if (n % 3 == 0 || (n + a) % 3 == 0 || (n + a + b) % 3 == 0)
      d++, a = b = 0; // Increment count and reset tracking variables
    else
      b = a, a = n; // Shift tracking variables for next iteration
  }
  printf("%d", d); // Output the maximum number of divisible parts
}


// https://github.com/VaHiX/CodeForces/