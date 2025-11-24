// Problem: CF 514 A - Chewbaсca and Number
// https://codeforces.com/contest/514/problem/A

/*
 * Problem: Chewbacca and Number
 * Algorithm: Greedy approach to minimize the number by inverting digits
 * Time Complexity: O(n) where n is the number of digits in the input
 * Space Complexity: O(n) for storing the string representation of the number
 * 
 * Approach:
 * 1. For the first digit, if it's greater than '4' and not '9', invert it to reduce the value
 * 2. For remaining digits, if they are greater than '4', invert them to minimize the number
 * 3. This greedy approach works because inverting a digit t gives 9-t, which is minimized when t is maximized
 * 4. Special case for first digit: we can't have leading zero, hence only invert if digit is not '9'
 * 
 * Example walkthrough:
 * Input: "27" -> First digit '2' <= '4', so don't invert. Second digit '7' > '4', so invert to '2'. Result: "22"
 * Input: "4545" -> First digit '4' <= '4', so don't invert. Other digits '5' > '4', so invert to '4'. Result: "4444"
 */

#include <iostream>
#include <string>

int main() {
  std::string number;
  getline(std::cin, number);
  
  // For the first digit, if it's greater than '4' and not '9', invert it
  // We only invert if it's not '9' because inverting '9' gives '0', which would create a leading zero
  if (number[0] > '4' && number[0] != '9') {
    number[0] = '0' + 9 - (number[0] - '0');
  }
  
  // For all other digits, if they are greater than '4', invert them
  // This minimizes the overall value of the number
  for (int p = 1; p < number.size(); p++) {
    if (number[p] > '4') {
      number[p] = '0' + 9 - (number[p] - '0');
    }
  }
  
  std::cout << number << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/