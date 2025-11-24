// Problem: CF 472 A - Design Tutorial: Learn from Math
// https://codeforces.com/contest/472/problem/A

/*
Purpose: This code solves the problem of expressing a given integer n (≥ 12) as the sum of two composite numbers.
         It uses the fact that if we fix one composite number x, then n - x must also be composite for the solution to be valid.
         The algorithm iterates through even composite numbers starting from 4, and checks if the remaining part (n - x) is also composite.
         If so, it outputs the pair.

Algorithms/Techniques: 
- Iteration through even composite numbers starting from 4
- Prime checking function to verify if a number is not prime (i.e., is composite)
- Greedy approach: iterate until valid decomposition is found

Time Complexity: O(sqrt(n) * (n/2)) in worst case, where sqrt(n) is the time to check if a number is prime, and (n/2) is the maximum 
                 iterations needed for small n. In practice, it is much faster due to density of composite numbers.
Space Complexity: O(1) - only using a constant amount of extra space.

Note: The algorithm relies on the fact that almost all even numbers greater than 4 are composite, so finding a valid pair quickly.
*/

#include <iostream>

using namespace std;
#define ll long long
#define endl "\n"
#define input cin >>
#define output cout <<
#define pb push_back

void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
}

// Function to check if a number is prime
bool isPrime(int n) {
  if (n < 2)  // Numbers less than 2 are not prime
    return false;
  for (int i = 2; i * i <= n; i++) {  // Check divisibility up to sqrt(n)
    if (n % i == 0)
      return false;
  }
  return true;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 4;; i += 2) {  // Start with 4 and increment by 2 to get even numbers (composites)
    if (isPrime(n - i))  // If the complement is prime, skip it
      continue;
    else {  // If the complement is not prime (i.e., composite), we have found the answer
      cout << i << " " << n - i << endl;
      break;
    }
  }
}

int main() {
  fastIO();
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/