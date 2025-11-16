// Problem: CF 918 A - Eleven
// https://codeforces.com/contest/918/problem/A

/*
 * Code Purpose: Generate a name for Eleven based on the Fibonacci sequence.
 *               The i-th character of the name is 'O' if i is a Fibonacci number,
 *               otherwise it is 'o'.
 *
 * Algorithm: 1. Generate all Fibonacci numbers up to n.
 *            2. For each index from 1 to n, check if it's a Fibonacci number.
 *            3. Print 'O' if yes, 'o' otherwise.
 *
 * Time Complexity: O(log n + n) - Logarithmic for generating Fibonacci numbers,
 *                  linear for printing the result.
 * Space Complexity: O(log n) - Space to store Fibonacci numbers up to n.
 */

#include <cstdio>
#include <map>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100
#define inf 100000
#define pp pair<char, char>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int a, b;
  map<int, bool> fib; // Map to store Fibonacci numbers for quick lookup
  scanf("%d", &n);
  a = 1, b = 1; // Initialize first two Fibonacci numbers
  while (a <= n) {
    fib[a] = 1; // Mark 'a' as a Fibonacci number
    fib[b] = 1; // Mark 'b' as a Fibonacci number
    m = a + b;  // Compute next Fibonacci number
    a = b;      // Shift a to b
    b = m;      // Shift b to m
  }
  for (i = 1; i <= n; i++) {
    if (fib[i])
      printf("O"); // Print uppercase 'O' if i is Fibonacci
    else
      printf("o"); // Print lowercase 'o' otherwise
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/