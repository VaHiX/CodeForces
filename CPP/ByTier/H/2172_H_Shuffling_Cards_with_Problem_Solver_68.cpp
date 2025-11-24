// Problem: CF 2172 H - Shuffling Cards with Problem Solver 68!
// https://codeforces.com/contest/2172/problem/H

/*
Algorithm: This solution uses the concept of suffix array and periodicity to find the lexicographically smallest string that can be produced after performing a fixed number of riffle shuffles on a deck of cards, where each shuffle interleaves two halves of the deck.

The key idea is to:
1. Generate a suffix array (SA) of the string using a modified comparison function that takes into account the t-th power of the riffle operation.
2. For the riffle operation, we simulate it using a periodic structure based on powers of 2.
3. By leveraging the periodicity of the shuffle operation and the SA, we efficiently compute which cut position gives the lexicographically smallest result.

Time Complexity: O(2^k * k * log(2^k)) -> O(2^k * k^2) due to sorting and building SA with k rounds.
Space Complexity: O(2^k) for storing suffix array, ranks, and intermediate structures.

*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int k, t;

// Function to build suffix array based on a modified comparison that considers riffle operations
vector<int> buildsa(string &s) {
  int n = s.size();
  vector<int> sa(n), r(n + 1), nr(n + 1);
  // Initialize suffix array and rank array
  for (int i = 0; i < n; ++i)
    sa[i] = i, r[i] = s[i];
  // Process for k rounds (each round corresponds to one shuffle step in the context of the problem)
  for (int dd = 0; dd < k; dd++) {
    int d = (1 << ((k - t + dd) % k)); // Compute the periodicity based on t and dd
    // Lambda function for comparing two suffixes
    auto cmp = [&](int i, int j) {
      return r[i] < r[j] || (r[i] == r[j] && r[(i + d) % n] < r[(j + d) % n]);
    };
    // Sort the suffixes using the custom comparator
    sort(sa.begin(), sa.end(), cmp);
    nr[sa[0]] = 1; // Assign a rank to the first suffix
    for (int i = 1; i < n; ++i)
      nr[sa[i]] = nr[sa[i - 1]] + cmp(sa[i - 1], sa[i]); // Assign ranks based on comparison
    r = nr; // Update rank array for next iteration
  }
  return sa; // Return the final suffix array
}

int main() {
  ios_base ::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> k >> t;
  t = t % k; // Reduce t modulo k to handle the periodicity
  string str;
  cin >> str;
  vector<int> sa = buildsa(str); // Build suffix array
  int s = sa[0]; // Get the starting index of the lexicographically smallest suffix
  int sz = (1 << k); // Size of the deck
  // Output the result by simulating the riffle effects
  for (int i = 0; i < (1 << (k - t)); i++) {
    for (int j = 0; j < (1 << t); j++) {
      cout << str[(s + i + j * (1 << (k - t))) % sz]; // Extract character according to calculated indices
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/