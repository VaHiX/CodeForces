// Problem: CF 1107 C - Brutality
// https://codeforces.com/contest/1107/problem/C

/*
C. Brutality
Algorithms/Techniques: Greedy, Sliding window approach on groups of consecutive same characters

Time complexity: O(n log n) due to sorting within each group of consecutive same characters
Space complexity: O(n) for storing the vector 'a' and temporary vectors for each group

You are playing a new famous fighting game: Kortal Mombat XII. You have to perform a brutality on your opponent's character.
You are playing the game on the new generation console so your gamepad have 26 buttons. Each button has a single lowercase Latin letter from 'a' to 'z' written on it. All the letters on buttons are pairwise distinct.
You are given a sequence of hits, the i-th hit deals a_i units of damage to the opponent's character. To perform the i-th hit you have to press the button s_i on your gamepad. Hits are numbered from 1 to n.
You know that if you press some button more than k times in a row then it'll break. You cherish your gamepad and don't want to break any of its buttons.
To perform a brutality you have to land some of the hits of the given sequence. 
You are allowed to skip any of them, however changing the initial order of the sequence is prohibited. The total damage dealt is the sum of a_i over all i for the hits which weren't skipped.
Note that if you skip the hit then the counter of consecutive presses the button won't reset.
Your task is to skip some hits to deal the maximum possible total damage to the opponent's character and not break your gamepad buttons.
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll n, k;
  std::cin >> n >> k;
  std::vector<ll> v(n);
  for (ll p = 0; p < n; p++) {
    std::cin >> v[p]; // Read damage values
  }
  std::string s;
  std::cin >> s; // Read sequence of button presses
  long idx(0); // Index to traverse the string
  ll dmg(0); // Total damage accumulated
  while (idx < n) {
    char x = s[idx]; // Current character/group of consecutive same characters
    std::vector<ll> a; // Vector to store damages for current group
    while (idx < n && s[idx] == x) { // While we are in the same group of characters
      a.push_back(v[idx]); // Add damage value to current group
      ++idx; // Move to next index
    }
    sort(a.rbegin(), a.rend()); // Sort damages in descending order to take maximum k values
    for (ll p = 0; p < a.size() && p < k; p++) { // Take only first k elements (maximum k damages)
      dmg += a[p]; // Add to total damage
    }
  }
  std::cout << dmg << std::endl; // Output the maximum possible damage
  return 0;
}


// https://github.com/VaHiX/codeForces/