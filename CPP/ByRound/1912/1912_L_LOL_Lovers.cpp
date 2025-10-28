// Problem: CF 1912 L - LOL Lovers
// https://codeforces.com/contest/1912/problem/L

/*
L. LOL Lovers
Algorithm: Two-pointer approach to find a valid split point where both users have at least one item,
           and the counts of 'L' and 'O' differ between user and friend.

Time Complexity: O(n), where n is the length of the string s.
Space Complexity: O(1), only using a few variables for counting and indexing.

The problem asks to split a sequence of 'L' (loaf) and 'O' (onion) into two non-empty parts such that:
- Both parts contain at least one item.
- The number of 'L's in the first part differs from the second part.
- The number of 'O's in the first part differs from the second part.

This is solved by:
1. Counting total 'L's and 'O's.
2. Iterating through each possible split point and checking if current prefix satisfies conditions.
3. Return the first valid split point, or -1 if none exists.
*/

#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);
  long n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long na(0), nb(0); // Count of 'L' and 'O' in the entire string
  for (long p = 0; p < s.size(); p++) {
    if (s[p] == 'L') {
      ++na;
    } else if (s[p] == 'O') {
      ++nb;
    }
  }
  long ans(-1), x(0), y(0); // ans: result index, x: count of 'L' in prefix, y: count of 'O' in prefix
  for (long p = 0; ans < 0 && p + 1 < s.size(); p++) { // Iterate until we find a valid split, or reach end
    if (s[p] == 'L') {
      ++x;
    } else if (s[p] == 'O') {
      ++y;
    }
    // Check if the number of 'L's and 'O's in prefix differ from those in suffix
    if ((x != na - x) && (y != nb - y)) {
      ans = p + 1; // Found valid split, index is 0-based so add 1
    }
  }
  std::cout << ans << std::endl;
}


// https://github.com/VaHiX/codeForces/