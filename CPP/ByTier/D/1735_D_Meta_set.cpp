// Problem: CF 1735 D - Meta-set
// https://codeforces.com/contest/1735/problem/D

/*
 * Code Purpose: This code solves the "Meta-set" problem where we need to count the number of 5-card groups 
 *               (meta-sets) such that there are strictly more than one valid Set (3-card subset) within the group.
 * 
 * Algorithm: 
 * 1. For every pair of cards, compute the third card that would form a valid Set with them.
 * 2. Store the count of how many times each such "third card" appears in the dataset.
 * 3. For each card in the input, add to the result the number of ways to choose 2 cards from the count of valid third cards,
 *    which represents the number of sets involving that card as part of the meta-set.
 * 
 * Time Complexity: O(n^2 * k), where n is the number of cards and k is the number of features.
 * Space Complexity: O(n^2), for storing the map of potential third cards.
 * 
 * Techniques:
 * - Use modular arithmetic to compute the third card needed for a valid Set.
 * - Utilize a map to count occurrences of potential third cards efficiently.
 * - Mathematical combination formula (count * (count - 1) / 2) to compute the number of ways to select 2 from 'count'.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
  int n, k, ans = 0; // Initialize answer to 0
  cin >> n >> k;
  vector<vector<int>> a(n, vector<int>(k)); // Store all cards
  map<vector<int>, int> mp; // Map to count occurrences of potential third cards
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      cin >> a[i][j]; // Read each card's features
    }
  }
  // For every pair of cards, calculate the third card that would form a Set
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      vector<int> b(k);
      for (int c = 0; c < k; c++) {
        // Compute the third card feature value to complete a Set
        b[c] = (6 - a[i][c] - a[j][c]) % 3;
      }
      mp[b]++; // Increment count of this third card
    }
  }
  // For each card, look up how many valid sets include it
  for (int i = 0; i < n; i++) {
    int count = mp[a[i]]; // Get count of valid third cards for this card
    ans = ans + count * (count - 1) / 2; // Add combinations of choosing 2 from count
  }
  cout << ans << endl; // Output the final answer
}


// https://github.com/VaHiX/CodeForces/