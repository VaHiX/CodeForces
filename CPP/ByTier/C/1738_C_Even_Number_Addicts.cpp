// Problem: CF 1738 C - Even Number Addicts
// https://codeforces.com/contest/1738/problem/C

/*
 * Problem: C. Even Number Addicts
 * 
 * Algorithm/Technique: Game Theory, Parity Analysis
 * 
 * Time Complexity: O(n) per test case, where n is the length of the array.
 * Space Complexity: O(1), only using a few variables for computation.
 * 
 * Approach:
 * The key insight is to analyze the parity (odd/even nature) of the numbers.
 * 
 * - If the total count of odd numbers is even, Alice can always pick an even number
 *   of odd numbers to ensure her sum is even.
 * - If the total count of odd numbers is odd, Alice will pick an odd number of odd numbers,
 *   making her sum odd, allowing Bob to win.
 * 
 * However, the code uses a more elegant and compact logic:
 *   - Count the number of odd elements (`a` in the code).
 *   - Based on how many odd numbers there are and the total length `n`, decide the outcome.
 *   - The condition `a % 4 == 2 || a % 4 == 1 && n % 2` determines whether Bob wins.
 * 
 * Explanation for logic:
 * - If the number of odds mod 4 is 2 or 1 and n is odd, Bob wins.
 * - Else Alice wins.
 * 
 * This works because in optimal play:
 *   - If there's an odd number of odd elements, Bob will have the last move and win 
 *     by copying Alice's choice parity.
 *   - If there's an even number of odd elements, Alice wins by ensuring her selections are even.
 * 
 * Note:
 * The code is written with a compact style (for loop and ternary operator),
 * which may reduce readability but is concise.
 * 
 * Input:
 *   - t: number of test cases.
 *   - For each test case:
 *     - n: size of array.
 *     - n integers: elements of the array.
 * 
 * Output:
 *   - "Alice" or "Bob", depending on who wins with optimal play.
 */

#include <stdio.h>
#include <iostream>

using namespace std;
int main() {
  int n, a;
  for (cin >> n; a = 0, cin >> n;
       puts(a % 4 == 2 || a % 4 == 1 && n % 2 ? "Bob" : "Alice"))
    for (int i = n, x; i--; a += x & 1)  // Loop through all elements, count odd numbers
      cin >> x;
}


// https://github.com/VaHiX/CodeForces/