// Problem: CF 914 B - Conan and Agasa play a Card Game
// https://codeforces.com/contest/914/problem/B

/*
Algorithm/Techniques: Map-based counting and parity check
Time Complexity: O(n log n) - due to map operations (insertion and iteration)
Space Complexity: O(n) - for storing the count of each unique number in the map

The game is about choosing cards and removing all smaller cards. 
The key insight is that the player who makes the last move (when no cards remain) loses.
So, the total number of moves determines the winner:
- If the total number of moves (i.e., number of distinct values in the sorted order) is odd, Conan wins.
- Otherwise, Agasa wins.

The solution leverages the fact that for each unique card value, we process it in descending order.
Each move consumes one card of the current value (or removes all smaller ones), and the parity of total moves decides the winner.
*/

#include <cstdio>
#include <map>
#include <iterator>
#include <utility>

int main() {
  long n;
  scanf("%ld", &n);
  std::map<long, long> cnt; // Count frequency of each card value
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++cnt[x]; // Increment count of the card value x
  }
  bool first(false);
  // Traverse from the largest to smallest card value
  for (std::map<long, long>::reverse_iterator rit = cnt.rbegin();
       rit != cnt.rend(); rit++) {
    if ((rit->second) & 1) { // If frequency is odd
      first = true; // Conan wins if there's at least one odd frequency
      break;
    }
  }
  puts(first ? "Conan" : "Agasa"); // Output the winner
  return 0;
}


// https://github.com/VaHiX/CodeForces/