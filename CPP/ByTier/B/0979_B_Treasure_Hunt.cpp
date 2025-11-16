// Problem: CF 979 B - Treasure Hunt
// https://codeforces.com/contest/979/problem/B

/*
Code Purpose:
This program determines the winner of a treasure hunt game among three cats (Kuro, Shiro, and Katie) based on the beauty of their ribbons after a given number of turns.
Each cat has a ribbon represented as a string of characters. The beauty of a ribbon is defined as the maximum number of times a subribbon appears in the ribbon.
In each turn, a cat can change one character of their ribbon to another character (different from the original).
The solution computes the maximum possible beauty each cat can achieve after n turns and declares the winner.

Algorithms/Techniques:
- Frequency counting to determine the most frequent character in a ribbon
- Greedy strategy to maximize the beauty value by changing characters optimally
- Simulation of turn count effect on beauty

Time Complexity: O(L) where L is the length of the ribbon (since we process each character once for frequency count and once for max computation)
Space Complexity: O(1) as we use a fixed-size array of 256 for character frequency counting and a few variables
*/

#include <cstdio>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> res(3, 0); // Store the maximum beauty for each cat
  for (long w = 0; w < 3; w++) {
    std::string s;
    std::cin >> s;
    std::vector<long> a(256, 0); // Frequency array for all possible ASCII characters
    for (long p = 0; p < s.size(); p++) {
      ++a[s[p]]; // Count frequency of each character
    }
    long mx(0); // Maximum frequency of any character
    for (long p = 0; p < a.size(); p++) {
      mx = (mx > a[p]) ? mx : a[p];
    }
    // Special case: if all characters are same and only one turn allowed
    if (mx == s.size() && n == 1) {
      mx = s.size() - 1;
    } else {
      // Add turns to the max frequency, but cap at the length of the string
      mx += n;
      mx = (mx < s.size()) ? mx : s.size();
    }
    res[w] = mx; // Store the computed maximum beauty for this cat
  }
  // Determine the winner based on maximum beauty values
  if (res[0] > res[1] && res[0] > res[2]) {
    puts("Kuro");
  } else if (res[1] > res[0] && res[1] > res[2]) {
    puts("Shiro");
  } else if (res[2] > res[0] && res[2] > res[1]) {
    puts("Katie");
  } else {
    puts("Draw");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/