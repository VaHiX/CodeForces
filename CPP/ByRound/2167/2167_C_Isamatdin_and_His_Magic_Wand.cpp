// Problem: CF 2167 C - Isamatdin and His Magic Wand!
// https://codeforces.com/contest/2167/problem/C

/*
Purpose: This code solves the problem of sorting an array of integers using a special swapping rule. 
         The rule allows swapping only if the two elements have different parity (one even, one odd).
         The goal is to produce the lexicographically smallest arrangement possible.

Algorithms/Techniques:
- Greedy approach: If the array contains both even and odd numbers, we can sort it completely. 
  Otherwise, if all elements are of the same parity, no swaps are possible and we output the original array.
- Time Complexity: O(n log n) per test case due to sorting, where n is the number of elements.
- Space Complexity: O(n) for storing the array.

*/
#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define io                                                                     \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL)
typedef long long int ll;

// Function to check if a number is prime (not used in current solution)
bool isPrime(ll n) {
  if (n <= 1)
    return false;
  if (n <= 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;
  for (ll i = 5; i * i <= n; i = i + 6)
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  return true;
}

// Function to compute greatest common divisor (not used in current solution)
ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  bool even = false;
  bool odd = false;
  // Check if array has both even and odd numbers
  for (int x : a) {
    if (x % 2)
      odd = true;
    else
      even = true;
  }
  // If all elements have same parity, no swaps possible, output original array
  if ((even && !odd) || (odd && !even)) {
    for (int x : a)
      cout << x << " ";
    cout << "\n";
    return;
  }
  // Sort the array to get lexicographically smallest arrangement
  sort(a.begin(), a.end());
  for (int x : a)
    cout << x << " ";
  cout << "\n";
  return;
}

int main() {
  io;
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/