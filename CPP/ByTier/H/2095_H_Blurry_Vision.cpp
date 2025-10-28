// Problem: CF 2095 H - Blurry Vision
// https://codeforces.com/contest/2095/problem/H

#include <iostream>
#include <string>

using namespace std;
/*
H. Blurry Vision
Purpose: This code reads an integer input and outputs the word at the corresponding index from a predefined array.
Algorithms/Techniques: Direct array indexing
Time Complexity: O(1) - Constant time lookup
Space Complexity: O(1) - Fixed size array of 11 strings

Input: One integer x (1≤x≤11) — the line number.
Output: The word on line number x.

Example:
input: 1
output: CODEFORCES
*/
int main() {
  int n;                    // Declare variable to store input
  cin >> n;                 // Read the input number
  string s[11] = {"CODEFORCES", "EYE",   "TESTING",   "SYSTEM",
                  "APRIL",      "FOOLS", "YOU",       "READ",
                  "POORLY",     "GET",   "EYEGLASSES"};  // Predefined array of words
  cout << s[n - 1];        // Output the word at index (n-1) since array is 0-indexed
}

// https://github.com/VaHiX/codeForces/