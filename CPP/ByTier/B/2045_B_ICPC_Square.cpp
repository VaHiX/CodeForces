// Problem: CF 2045 B - ICPC Square
// https://codeforces.com/contest/2045/problem/B

/*
B. ICPC Square
Purpose: Given a hotel with N floors, a maximum step D, and starting floor S,
         find the highest floor reachable using allowed elevator moves (y is multiple of x and y-x <= D).

Algorithm:
- The process involves finding valid multiples of current floor that are within the limit D.
- We try to build a chain of such steps from S to maximize destination.
- Key optimization: if we can form a sequence where each step doubles or almost doubles, 
  then the result is optimized. Otherwise, we check for small factors of n after adjustment.

Time Complexity: O(sqrt(N)) - due to factorization up to sqrt(N)
Space Complexity: O(1) - only using fixed number of variables

*/
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  long long n, d, s, m = 0, shit = -1;
  cin >> n >> d >> s;
  d /= s, n = min(n / s, 2 * d); // Normalize the problem: scale down by s and cap n
  if (n % 2) { // Only process odd numbers for factorization 
    for (long long i = 3; i * i <= n && m == 0; i++) // Factorize n to find smallest divisor > 1
      if (!(n % i)) // If i divides n, then it's a factor
        m = i;
    if ((m != 0 && (m - 1) * (n / m) <= d) || d == n - 1) // Check if it satisfies condition for reaching top
      shit = 0;
  }
  cout << s * max(n + max(shit, -n % 2), 1LL); // Final result: scale back up and adjust based on conditions
  return 0;
}


// https://github.com/VaHiX/codeForces/