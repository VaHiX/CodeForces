// Problem: CF 1610 D - Not Quite Lee
// https://codeforces.com/contest/1610/problem/D

/*
Code Purpose:
This program counts the number of "good" subsequences in a given array. A subsequence is considered good if there exists a set of sequences where each sequence contains consecutive integers, and the sum of all elements in all sequences equals zero.

The approach leverages the observation that for a sequence of length `b_i`, the sum of consecutive integers can be zero if and only if the length is even (since the sum of an odd number of consecutive integers is never zero). Therefore, for each element in the input array, we determine the highest power of 2 that divides it, and count how many elements belong to each power-of-2 group. Using this information, we compute the number of subsequences satisfying the good condition.

Algorithms/Techniques:
- Bit manipulation to find the highest power of 2 dividing a number using __builtin_ctz
- Dynamic programming with prefix sums to compute the result efficiently
- Modular arithmetic to handle large numbers

Time Complexity: O(n + log(max(a_i))) → O(n) since log(max(a_i)) is bounded
Space Complexity: O(1) → Only a fixed-size array of size 35 is used

*/
#include <iostream>

using namespace std;
int n, db[35]; // db[i] will count elements whose highest power of 2 factor is 2^i
long long ans, mod = 1e9 + 7;

// Fast exponentiation to compute 2^db mod (mod)
long long po(int db) {
  long long ans = 1;
  while (db--)
    ans = 2 * ans % mod;
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    // Count how many times each power of 2 divides x
    db[__builtin_ctz(x)]++;
  }
  // Total number of non-empty subsequences = 2^n - 1
  ans = po(n) - 1;
  // Process powers of 2 from high to low
  for (int i = 30; i >= 1; i--) {
    // Accumulate counts from higher to lower powers of 2
    db[i] += db[i + 1];
    // If current count is greater than previous, subtract invalid subsequences
    if (db[i] > db[i + 1])
      ans = (ans + mod - po(db[i] - 1)) % mod;
  }
  cout << ans << "\n";
  return 0;
}


// https://github.com/VaHiX/CodeForces/