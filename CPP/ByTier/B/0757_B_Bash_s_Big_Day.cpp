// Problem: CF 757 B - Bash's Big Day
// https://codeforces.com/contest/757/problem/B

/*
Code Purpose:
This program solves the problem of finding the maximum number of Pokemon Bash can take such that their strengths have a GCD greater than 1.
The approach uses a technique similar to the sieve of Eratosthenes to count how many numbers in the input are divisible by each possible divisor.
It then finds the maximum count among all divisors (greater than 1), which corresponds to the largest group of Pokemon with GCD > 1.

Algorithms/Techniques:
- Frequency counting with a sieve-like approach
- For each number i from 2 to N, we accumulate counts of its multiples in cnt[i]
- The result is the maximum value in cnt array (excluding index 1)

Time Complexity: O(N * log(N)) where N = 10^5
Space Complexity: O(N) for the cnt array
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
const int N = 1 << 17; // Upper bound for input values (2^17)
int n, x, cnt[N], res = 1; // cnt stores frequency of each strength value, res tracks max group size
int main() {
  cin >> n; // Read number of Pokemon
  for (int i = 0; i < n; i++)
    scanf("%d", &x), cnt[x]++; // Count frequency of each strength value
  for (int i = 2; i < N; i++) // For each possible divisor starting from 2
    for (int j = i + i; j < N; j += i) // For all multiples of i
      cnt[i] += cnt[j]; // Accumulate counts of multiples into cnt[i]
  for (int i = 2; i < N; i++)
    res = max(res, cnt[i]); // Find maximum group size
  cout << res << endl; // Output result
}


// https://github.com/VaHiX/CodeForces/