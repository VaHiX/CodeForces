// Problem: CF 474 A - Keyboard
// https://codeforces.com/contest/474/problem/A

/*
 * Code Purpose:
 *   This program decodes a message that was typed on a keyboard where the user's hands
 *   were shifted one position left or right. Given the direction of shift and the
 *   incorrectly typed string, the program determines what the original message was.
 *
 * Algorithms/Techniques:
 *   - Character mapping using predefined keyboard layouts.
 *   - Linear search through keyboard rows to find character positions.
 *   - Adjustment of character index based on shift direction.
 *
 * Time Complexity:
 *   O(n * m), where n is the length of the input string and m is the average length
 *   of the keyboard rows (around 10). Since m is constant, the effective time complexity
 *   is O(n).
 *
 * Space Complexity:
 *   O(1) for the keyboard layout storage (fixed size), and O(n) for the input string,
 *   making the total space complexity O(n).
 */

#include <cstdio>
#include <iostream>
#include <string>

int main() {
  // Define the three rows of the keyboard
  std::string upper = "qwertyuiop";
  std::string middle = "asdfghjkl;";
  std::string lower = "zxcvbnm,./";
  
  // Read the direction of shift ('L' or 'R')
  std::string direction;
  getline(std::cin, direction);
  
  // Read the input string that was typed
  std::string input;
  getline(std::cin, input);
  
  // Convert direction to a number for index adjustment: -1 for right shift, 1 for left shift
  int dirNum = (direction[0] == 'R') ? (-1) : 1;
  
  // Process each character in the input string
  int pos(0);
  for (int p = 0; p < input.size(); p++) {
    // Check if the character exists in the upper row
    pos = upper.find(input[p]);
    if (pos != std::string::npos) {
      // Print the character that corresponds to the original position
      printf("%c", upper[pos + dirNum]);
    }
    
    // Check if the character exists in the middle row
    pos = middle.find(input[p]);
    if (pos != std::string::npos) {
      // Print the character that corresponds to the original position
      printf("%c", middle[pos + dirNum]);
    }
    
    // Check if the character exists in the lower row
    pos = lower.find(input[p]);
    if (pos != std::string::npos) {
      // Print the character that corresponds to the original position
      printf("%c", lower[pos + dirNum]);
    }
  }
  
  // Print a newline at the end
  puts("");
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/