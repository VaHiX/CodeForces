// Problem: CF 2033 F - Kosuke's Sloth
// https://codeforces.com/contest/2033/problem/F

/*
F. Kosuke's Sloth
time limit per test1 second
memory limit per test256 megabytes

Task:
Find the index of the n-th Fibonacci number that is divisible by k.
Fibonacci sequence: f(1)=f(2)=1, f(n)=f(n−1)+f(n−2) for n≥3.
G(n,k) = index of the n-th Fibonacci number divisible by k.
Return G(n,k) mod (10^9 + 7).

Algorithm:
- Use properties of modular arithmetic to find the cycle of Fibonacci remainders modulo k.
- Once we find the period, we can compute how many steps are needed to reach the n-th divisible number using cycles.

Time Complexity: O(k), where k is the divisor. The inner loop runs at most k iterations since there are at most k possible remainders.
Space Complexity: O(1). Only a few variables are used regardless of input size.

Approach:
- Compute Fibonacci sequence modulo k until we find a repetition (cycle).
- Once period p is found, we determine the n-th multiple of k using periodicity.
- Apply modular arithmetic to avoid overflow and return result mod 1e9+7.
*/

#include <iostream>

using namespace std;
typedef long long ll;
ll M = 1e9 + 7;
int main() {
  int T;
  cin >> T;
  while (T--) {
    ll n, k;
    cin >> n >> k;
    n %= M; // Reduce n modulo M to prevent overflow in final result
    ll a = 1, b = 0, c, p = 1; // a is fib(i) % k, b is fib(i-1) % k, p is step counter
    while (a % k) // Loop until we find a Fibonacci number divisible by k
      c = a, a = (a + b) % k, b = c, p++; // Update Fibonacci numbers and step count
    
    // Multiply by n to get the position of the n-th such number
    cout << p * n % M << endl;
  }
}


// https://github.com/VaHiX/codeForces/