// Problem: CF 1459 A - Red-Blue Shuffle
// https://codeforces.com/contest/1459/problem/A

/*
Problem: Red-Blue Shuffle
Algorithms/Techniques: Simulation, Comparison of digit sequences
Time Complexity: O(n) per test case
Space Complexity: O(1) additional space (not counting input storage)

This program determines which player (Red or Blue) has a higher probability
of winning a bet based on comparing the final integers R and B formed by
shuffling cards. Each card has a red digit and a blue digit. The comparison
is made by summing up how many times Red's digit is greater than Blue's digit
and vice versa. Leading zeros are ignored during number formation.
*/

#include <stdio.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Disable sync with C stdio for faster I/O
  std::cin.tie(0);                        // Untie cin from cout for faster I/O
  long t;
  std::cin >> t;                          // Read number of test cases
  while (t--) {
    long n;
    std::cin >> n;                        // Read number of cards
    std::string a, b;
    std::cin >> a >> b;                   // Read red and blue digits strings
    long win(0), lose(0);                 // Counters for Red winning and losing
    for (long p = 0; p < n; p++) {
      win += (a[p] > b[p]);               // Increment if red digit > blue digit
      lose += (a[p] < b[p]);              // Increment if red digit < blue digit
    }
    if (win > lose) {                     // If Red has more winning comparisons
      puts("RED");
    } else if (win == lose) {             // If both players are equally likely
      puts("EQUAL");
    } else if (win < lose) {              // If Blue has more winning comparisons
      puts("BLUE");
    }
  }
}


// https://github.com/VaHiX/codeForces/