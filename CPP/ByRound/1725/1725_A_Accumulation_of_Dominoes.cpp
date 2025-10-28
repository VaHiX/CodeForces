// Problem: CF 1725 A - Accumulation of Dominoes
// https://codeforces.com/contest/1725/problem/A

/*
 * Problem: Count the number of distinct "tight" dominoes in an N x M grid.
 * A domino is tight if the two numbers it connects differ by exactly 1.
 * Grid layout:
 *   Row 1: 1, 2, ..., M
 *   Row 2: M+1, M+2, ..., 2*M
 *   Row 3: 2*M+1, 2*M+2, ..., 3*M
 *   And so on...
 *
 * Algorithm:
 * - For each row, there are (M - 1) horizontal dominoes (consecutive numbers).
 * - There are N rows, so horizontal dominoes = N * (M - 1)
 * - For vertical dominoes:
 *   - Between row i and row i+1, numbers are consecutive in the same column.
 *   - Each column has one vertical domino (from row i to row i+1).
 *   - There are M columns, so vertical dominoes = M * (N - 1)
 * - However, we are counting only distinct dominoes — i.e., we must avoid double-counting
 *   or misunderstanding the structure.
 * 
 * Actually, re-evaluating:
 * - Horizontal dominoes: Each row has M - 1 such dominoes.
 *   So total = N * (M - 1)
 * - Vertical dominoes: In each column, consecutive rows form a domino.
 *   There are M columns and (N - 1) such vertical gaps.
 *   So total = M * (N - 1)
 * - Total = N*(M-1) + M*(N-1)
 * 
 * But this simplifies to:
 * N*M - N - M + 1 = (N-1)*(M-1) + N + M - 2
 * 
 * However, note that the output formula is:
 * (m > 1) ? n * (m - 1) : (n - 1)
 * 
 * This simplifies:
 * - If m > 1: Count only horizontal dominoes = n * (m - 1)
 * - If m = 1: Only vertical dominoes = n - 1
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long long n, m;
  scanf("%lld %lld", &n, &m);
  printf("%lld\n", (m > 1) ? n * (m - 1) : (n - 1));
}


// https://github.com/VaHiX/CodeForces/