// Problem: CF 1878 C - Vasilije in Cacak
// https://codeforces.com/contest/1878/problem/C

/*
C. Vasilije in Cacak

Purpose:
This code determines whether it's possible to select k distinct integers from the range [1, n] such that their sum equals x.

Approach:
- For a given n, k, and x, we compute the minimum and maximum possible sums of k distinct integers in [1, n].
- Minimum sum: Sum of first k integers (1 + 2 + ... + k)
- Maximum sum: Sum of last k integers (n - k + 1 + ... + n)
- If x lies within this range, the answer is "YES", otherwise "NO".

Algorithms/Techniques:
- Mathematical computation of minimum and maximum possible sums using arithmetic progression formula.
- Efficient checking of range for each test case.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input Format:
- First line contains t (number of test cases)
- Each test case contains three integers n, k, x

Output Format:
- "YES" if it's possible to form sum x with k distinct integers in range [1,n], else "NO"
*/

#include <cstdio>
typedef long long ll;

int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n, k, x;
    scanf("%lld %lld %lld", &n, &k, &x);
    
    // Calculate the minimum possible sum of k distinct integers from [1,n]
    ll mn = k * (k + 1) / 2;  // Sum of first k natural numbers
    
    // Calculate the maximum possible sum of k distinct integers from [1,n]
    ll mx = n * k - k * (k - 1) / 2;  // Sum of last k numbers in range [1,n]
    
    // Check if x is within valid range
    puts(mn <= x && x <= mx ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/