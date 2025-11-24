// Problem: CF 1544 A - Binary Decimal
// https://codeforces.com/contest/1544/problem/A

/*
Algorithm: Finding Maximum Digit in String
Techniques: 
- Using max_element from <algorithm> to find maximum character in string
- Converting character digit to integer by subtracting '0'

Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(1) - only using a constant amount of extra space

This code finds the largest digit in each input string and outputs it.
The problem is actually about representing a number as sum of binary decimals,
but this version just finds the maximum digit in the decimal representation.
*/
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main() {
  int t;
  cin >> t; // Read number of test cases
  while (t--) {
    string s;
    cin >> s; // Read the number as a string
    cout << *max_element(s.begin(), s.end()) - '0' << endl; 
    // Find maximum character in string and convert to integer
  }
}


// https://github.com/VaHiX/codeForces/