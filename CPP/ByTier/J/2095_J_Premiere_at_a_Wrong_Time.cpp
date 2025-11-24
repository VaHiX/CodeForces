// Problem: CF 2095 J - Premiere at a Wrong Time
// https://codeforces.com/contest/2095/problem/J

#include <iostream>
#include <string>

/*
J. Premiere at a Wrong Time
Code Purpose: This program reads a string input and outputs a specific message based on whether the input equals "first".
Algorithms/Techniques: String comparison operation
Time Complexity: O(n) where n is the length of the input string
Space Complexity: O(n) where n is the length of the input string (for storing the string)

The program uses a simple conditional (ternary) operator to decide which message to output.
*/
int main() {
  std::string s;           // Declare a string variable to store input
  std::cin >> s;           // Read input string from standard input
  // Compare string with "first" and output accordingly using ternary operator
  std::cout << (s == "first" ? "Nauuo and Votes" : "Nauuo and Chess")
            << std::endl;
}

// https://github.com/VaHiX/codeForces/