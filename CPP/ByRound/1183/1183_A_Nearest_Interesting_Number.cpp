// Problem: CF 1183 A - Nearest Interesting Number
// https://codeforces.com/contest/1183/problem/A

/*
A. Nearest Interesting Number
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Polycarp knows that if the sum of the digits of a number is divisible by 3, then the number itself is divisible by 3. He assumes that the numbers, the sum of the digits of which is divisible by 4, are also somewhat interesting. Thus, he considers a positive integer n interesting if its sum of digits is divisible by 4.
Help Polycarp find the nearest larger or equal interesting number for the given number a. That is, find the interesting number n such that n >= a and n is minimal.

Algorithms/Techniques: Brute force search
Time Complexity: O(d * k) where d is the number of digits in the input number and k is the number of iterations needed to find the answer (at most 40 for practical purposes)
Space Complexity: O(1)

*/
#include <stdio.h>
#include <iosfwd>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n")
#define N 1000100
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<char, int>
using namespace std;
bool foo(int n) {
  int sum = 0; // Calculate sum of digits
  while (n) {
    sum += (n % 10); // Add last digit to sum
    n /= 10; // Remove last digit
  }
  if (sum % 4 == 0) // Check if sum is divisible by 4
    return true;
  else
    return false;
}
int main() {
  int i, j, k;
  int n, m;
  sf(n); // Read input number
  while (true) {
    if (foo(n)) { // If current number is interesting
      pf(n); // Print the number
      return 0; // Exit
    }
    n++; // Increment to next number
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/