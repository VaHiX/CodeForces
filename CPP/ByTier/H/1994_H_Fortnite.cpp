// Problem: CF 1994 H - Fortnite
// https://codeforces.com/contest/1994/problem/H

/*
 * Purpose: Solve the interactive problem of determining polynomial hash parameters (p and m)
 *          from only 3 queries. The method uses mathematical properties of the polynomial hash
 *          and modular arithmetic to deduce the values.
 *
 * Algorithm:
 * 1. First query: input "aa" to get hash value p1. This gives us p1 = 1 + 1*p % m => p1 = 1 + p % m
 *    So p = (p1 - 1) % m => p1 - 1 = k*m (for some integer k) => p1-1 = (p1-1) % m if m > p1 - 1
 *    So we can derive an upper bound on p if we know the range of p (p > 26 and p <= 50).
 *    We set p = p1 - 1 (since we're working in modular arithmetic and we're looking for correct p).
 * 
 * 2. Second query: input a string of 50 'z's to get hash value a. We use this to determine the relationship
 *    between m and p. Since all characters are 'z' (ascii 122), the hash is 122*(p^n - 1)/(p - 1) mod m,
 *    where n is length of string = 50.
 *    This allows us to find relation p^50 ≡ x mod m and deduce that m > p^50 / x.
 *    But since we know 26 < p <= 50 and p + 1 < m <= 2 * 10^9, we can reverse-engineer p by finding
 *    p such that (a - 122) mod p = 0 (approximation).
 *
 * 3. Third query: With calculated p, find the actual value of m in the form m = (a * p - 1 + c)
 *    where c is derived from the third query output.
 *
 * Time Complexity: O(1) per test case — fixed number of operations independent of input size.
 * Space Complexity: O(1) — only using fixed-size variables and a string of length 50.
 */

#include <string>
#include <iostream>

const int N = 100010, INF = 0x3f3f3f3f;
inline void solve(void) {
  // First query: Input "aa" to get a hash value p
  std::cout << "? aa" << std::endl;
  int p; // Store input hash result from first query
  std::cin >> p;
  --p; // Subtracting 1 to extract the base p (from hash formula)
  
  // Second query: input a string of 50 'z's to get hash value a
  std::string s(50, 'z'); // Initialize a string of 50 'z' characters
  std::cout << "? " << s << std::endl;
  int a, b = 1; // a stores hash of 'z' repeated 50 times, b will be used to calculate m
  std::cin >> a;
  
  // Adjust string s to calculate p based on a and first computation
  --s[0]; // Reduce first character by 1 to adjust for calculation
  
  // Loop to adjust the string s depending on value of a to find correct base p
  for (long long i = 0, base = 1; a >= base; ++i, base *= p) {
    int v = (a / base) % p; // Extract digit in base p
    if (v <= 24) // Update the character if v is not too high
      s[i] -= v;
    else // Otherwise adjust next character and update b
      --s[i + 1], b += base * (p - v);
  }
  
  // Third query: Input modified string s to get another hash value c
  std::cout << "? " << s << std::endl;
  int c; // Store hash value from third query
  std::cin >> c;
  
  // Output final p and m values determined from queries
  std::cout << "! " << p << " " << b + c << std::endl;
  return;
}

int main(void) {
  int T; // Number of test cases
  std::cin >> T;
  while (T--)
    solve(); // Process each test case
  return 0;
}


// https://github.com/VaHiX/CodeForces/