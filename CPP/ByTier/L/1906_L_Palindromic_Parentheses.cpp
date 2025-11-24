// Problem: CF 1906 L - Palindromic Parentheses
// https://codeforces.com/contest/1906/problem/L

/*
 * Problem: L. Palindromic Parentheses
 * 
 * Approach:
 * - Given N (even number) and K, construct a balanced parentheses sequence of length N 
 *   such that the longest palindromic subsequence (LPS) has exactly K characters.
 * 
 * Key Observations:
 * - A balanced parentheses sequence of length N has exactly N/2 opening and closing brackets.
 * - The minimum possible LPS length for a balanced sequence is N/2 (e.g., ((...)))
 * - The maximum possible LPS length is N-1 (e.g., ()()...() with one extra unmatched bracket)
 * - For building a sequence with LPS = K:
 *   - Start with a base structure: (n/2) opening brackets followed by (n/2) closing brackets
 *   - To increase LPS beyond N/2, we can insert pairs of parentheses (like "()") in a way 
 *     that maximizes palindromic subsequences while maintaining balance.
 * 
 * Algorithm:
 * - Check if K is within valid range [N/2, N-1]. If not, output -1.
 * - Let `num = N / 2` (number of pairs).
 * - Let `excess = K - num` (how much we want to increase LPS beyond minimum).
 * - We place `excess/2` pairs of "()" at the beginning.
 * - Then place `num - excess` opening and closing brackets.
 * - Finally, place `(excess + 1)/2` pairs of "()" at the end.
 * 
 * Time Complexity: O(N) - single pass through the length N
 * Space Complexity: O(1) - only using a constant amount of additional space
 */
#include <stdio.h>
#include <utility>

#pragma GCC optimize(3)
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
int n, k, a[MAXN];
int main() {
  scanf("%d%d", &n, &k);
  // Check if K is within valid range for balanced parentheses sequence of length N
  if (k < n / 2 || k > n - 1) {
    puts("-1");
    return 0;
  }
  int num = n / 2;  // Number of pairs
  int excess = k - num;  // Extra characters to increase LPS
  // Add 'excess/2' pairs of parentheses to the front
  for (int i = 0; i < (excess) / 2; i++)
    printf("()");
  // Add 'num - excess' opening brackets followed by same number of closing brackets
  for (int i = 0; i < num - excess; i++)
    printf("(");
  for (int i = 0; i < num - excess; i++)
    printf(")");
  // Add '(excess + 1)/2' pairs of parentheses to the end
  for (int i = 0; i < (excess + 1) / 2; i++)
    printf("()");
  printf("\n");
  return 0;
}


// https://github.com/VaHiX/CodeForces/