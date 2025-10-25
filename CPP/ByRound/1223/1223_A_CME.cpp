// Problem: CF 1223 A - CME
// https://codeforces.com/contest/1223/problem/A

/*
 * Problem: Minimum Matches to Buy for a Correct Match Equation (CME)
 *
 * A Correct Match Equation (CME) is an equation of the form a + b = c
 * where a, b, and c are positive integers. Each integer is represented by
 * a certain number of matches (e.g., 1 requires 2 matches, 2 requires 5 matches, etc.).
 *
 * The pattern for match count per digit:
 * 0: 6 matches, 1: 2 matches, 2: 5 matches, 3: 5 matches,
 * 4: 4 matches, 5: 5 matches, 6: 6 matches, 7: 3 matches,
 * 8: 7 matches, 9: 6 matches.
 *
 * However, the problem is simplified: we want to find the minimum matches to buy
 * so that total matches (n + bought) can form a valid CME using all of them.
 *
 * Observations:
 * - To form an equation a + b = c, we need a + b + c matches in total.
 * - Since a, b, c are positive integers, the smallest sum is 1+1=2 (requires 2+2+1=5 matches).
 * - For n matches, if we can construct a valid CME using all n matches, output 0.
 * - Otherwise, calculate minimum extra matches required to form such an equation.
 *
 * Simplified approach:
 * Let’s define the minimal structure of a CME using matches.
 * For a valid expression "a+b=c", total matches needed is:
 * match_count(a) + match_count(b) + match_count(c).
 * 
 * But since we don't know digit representations, and only given n (total matches),
 * we observe from examples that the result follows this pattern:
 * For any n ≥ 3:
 *   if n is odd => 1 (we need to add one match)
 *   if n is even => 0 (already balanced)
 * However, for n = 2, the answer is 2.
 * So logic becomes:
 * if n < 3 then return 2
 * else {
 *   if n % 2 == 1 then return 1  // odd case
 *   else return 0               // even case
 * }
 *
 * Time Complexity: O(1) - constant time per query.
 * Space Complexity: O(1) - no extra space used.
 */

#include <iostream>
int main() {
  int q, n;
  std::cin >> q;
  while (q--) {
    std::cin >> n;
    // If n is less than 3, we must buy at least 2 matches to get valid CME
    // For n >= 3: 
    //   if n is odd -> we need 1 more match to make it even (so that a+b=c balance works)
    //   if n is even -> already enough to form one
    std::cout << (n < 3 ? 2 : (n % 2 ? 1 : 0)) << '\n';
  }
}


// https://github.com/VaHiX/codeForces/