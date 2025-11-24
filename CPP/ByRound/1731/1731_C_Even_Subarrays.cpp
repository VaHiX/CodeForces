// Problem: CF 1731 C - Even Subarrays
// https://codeforces.com/contest/1731/problem/C

/*
Purpose: 
This code solves the problem of counting subarrays whose XOR has an even number of divisors.
It uses a prefix XOR technique combined with a frequency array to efficiently count valid subarrays.

Algorithms/Techniques:
- Prefix XOR: to quickly compute XOR of any subarray
- Frequency counting: to count how many times a particular XOR value has occurred
- Mathematical property: a number has even number of divisors if and only if it's not a perfect square (with 0 considered as having odd divisors)

Time Complexity: O(n * sqrt(n)) per test case, where n is the size of the array
Space Complexity: O(n) for the prefix XOR array and frequency array

Approach:
1. Compute prefix XOR array to quickly calculate XOR of any subarray.
2. For each prefix XOR value, check how many previous prefix XORs, when XORed with a perfect square, give a value that has already been seen.
3. Subtract these counts from the total number of subarrays to get the answer.
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    vector<int> c(n + 1, 0); // prefix XOR array
    for (int i = 1, x; i <= n; i++)
      cin >> x, c[i] = c[i - 1] ^ x; // compute prefix XOR
    vector<int> t(4 * n + 1, 0); // frequency array for XOR values
    long long ans = 1ll * n * (n + 1) / 2; // total number of subarrays
    for (int i = 0; i <= n; i++) {
      // For each prefix XOR value c[i], check for perfect squares
      for (int j = 0; j * j <= 2 * n; j++)
        ans -= t[c[i] ^ (j * j)]; // subtract those which form perfect square when XORed
      t[c[i]]++; // update frequency of current XOR value
    }
    cout << ans << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/