// Problem: CF 1220 C - Substring Game in the Lesson
// https://codeforces.com/contest/1220/problem/C

/*
C. Substring Game in the Lesson
Algorithms/Techniques: Greedy approach with prefix minimum tracking
Time complexity: O(n), where n is the length of the string
Space complexity: O(1), excluding input storage

The game is about determining the winner for each starting position k,
where players alternately try to minimize the lexicographically value of 
the substring [l, r] with l = r = k initially.
This problem can be solved optimally by observing that at each step,
a player will choose to extend the current substring to the left or right
as long as they can find a smaller character, which leads to a greedy approach.

The key insight is that we only need to track the smallest character seen so far
from the beginning of the string. If the current character is less than or equal 
to this minimum, then the first player (Mike) wins; otherwise, the second player (Ann) wins.
*/

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;
string s;
int main() {
  ios::sync_with_stdio(false);
  cin >> s;
  char mi = 'z' + 1;  // Initialize minimum character to a value larger than 'z'
  for (auto c : s) {
    if (c <= mi)
      cout << "Mike\n";  // If current char is less than or equal to min, Mike wins
    else
      cout << "Ann\n";   // Otherwise Ann wins
    mi = min(mi, c);     // Update the minimum character seen so far
  }
}


// https://github.com/VaHiX/codeForces/