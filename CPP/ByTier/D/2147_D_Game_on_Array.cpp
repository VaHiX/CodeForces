// Problem: CF 2147 D - Game on Array
// https://codeforces.com/contest/2147/problem/D

/*
D. Game on Array

Algorithms/Techniques: Greedy, Sorting, Map usage

Time Complexity: O(N log N) per test case due to sorting of odd frequency elements.
Space Complexity: O(N) for the map and vector storage.

The problem simulates a game where two players (Alice and Bob) take turns reducing values in an array.
Each turn, a player selects a value x > 0 present in the array. They gain points equal to the count of x,
and all instances of x in the array decrease by 1.
The goal is to compute the final score for both players when playing optimally.

Approach:
- Count frequency of each element in the array.
- For odd frequencies, collect their counts (as these elements will be used an odd number of times).
- Sort them in descending order.
- Alternate adding and subtracting from total to determine optimal gain.

The algorithm works by modeling how points are distributed between the two players based on element frequencies.
*/

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
#define int long long
signed main() {
  int TT;
  cin >> TT;
  while (TT--) {
    int N;
    cin >> N;
    int al = 0; // total sum of array elements
    map<int, int> m; // to store frequency of each element
    for (int i = 0; i < N; i++) {
      int a;
      cin >> a;
      m[a]++;
      al += a;
    }
    vector<int> S = {}; // stores frequencies of elements with odd counts
    for (auto [a, b] : m)
      if (a % 2) // only consider elements whose values are odd
        S.push_back(b);
    sort(S.rbegin(), S.rend()); // sort in descending order
    int w = 0; // net difference between Alice and Bob's scores
    for (int i = 0; i < S.size(); i++) {
      if (i % 2 == 0) // Alice's turn to add
        w += S[i];
      else // Bob's turn to subtract
        w -= S[i];
    }
    cout << (al + w) / 2 << ' ' << (al - w) / 2 << endl; // Alice score and Bob score
  }
}


// https://github.com/VaHiX/CodeForces/