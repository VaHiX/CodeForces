// Problem: CF 725 A - Jumping Ball
// https://codeforces.com/contest/725/problem/A

/*
 * Problem: Jumping Ball
 * 
 * Purpose: 
 *   Given a sequence of bumpers represented by '<' and '>', determine how many starting positions
 *   will cause the ball to eventually fall off the edge of the board.
 *   - '<' means the ball moves left (i-1)
 *   - '>' means the ball moves right (i+1)
 *   - If the ball goes out of bounds, it falls from the field.
 * 
 * Algorithm:
 *   - For the leftmost section, we count consecutive '<' characters from the start.
 *     These positions will fall to the left if the ball starts here.
 *   - For the rightmost section, we count consecutive '>' characters from the end.
 *     These positions will fall to the right if the ball starts here.
 *   - The total count is the sum of these two counts.
 * 
 * Time Complexity: O(n), where n is the length of the string.
 * Space Complexity: O(1), only using a few variables for counting.
 */

#include <iostream>
#include <string>

int main() {
  int n;
  std::cin >> n;
  std::string s;
  std::cin >> s;
  long count(0);
  
  // Count consecutive '<' from the beginning
  for (int p = 0; p < s.size(); p++) {
    if (s[p] == '<') {
      ++count;
    } else {
      break;  // Stop when we hit a '>' - ball won't fall past this point
    }
  }
  
  // Count consecutive '>' from the end
  for (int p = s.size() - 1; p >= 0; p--) {
    if (s[p] == '>') {
      ++count;
    } else {
      break;  // Stop when we hit a '<' - ball won't fall past this point
    }
  }
  
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/