// Problem: CF 2010 C1 - Message Transmission Error (easy version)
// https://codeforces.com/contest/2010/problem/C1

/*
C1. Message Transmission Error (easy version)
time limit per test2 seconds
memory limit per test256 megabytes

This is a simplified version of the problem. It differs from the difficult one only in its constraints.
At the Berland State University, the local network between servers does not always operate without errors. When transmitting two identical messages consecutively, an error may occur, resulting in the two messages merging into one. In this merging, the end of the first message coincides with the beginning of the second. Of course, the merging can only occur at identical characters. The length of the merging must be a positive number less than the length of the message text.
For example, when transmitting two messages "abrakadabra" consecutively, it is possible that it will be transmitted with the described type of error, resulting in a message like "abrakadabrabrakadabra" or "abrakadabrakadabra' (in the first case, the merging occurred at one character, and in the second case, at four).
Given the received message t, determine if it is possible that this is the result of an error of the described type in the operation of the local network, and if so, determine a possible value of s.
A situation where two messages completely overlap each other should not be considered an error. For example, if the received message is "abcd", it should be considered that there is no error in it. Similarly, simply appending one message after another is not a sign of an error. For instance, if the received message is "abcabc", it should also be considered that there is no error in it.

Algorithms/Techniques: String matching, substring comparison

Time complexity: O(n^2) where n is the length of the string
Space complexity: O(n) for storing the input string and substrings

*/

#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  cin >> s;
  int n = s.length();
  int k = (n / 2) + 1; // Start checking from half length + 1 to avoid full overlap
  for (int i = k; i < n; i++) { // Loop through possible overlapping lengths
    if (s.substr(0, i) == s.substr(n - i, i)) { // Check if prefix and suffix match
      cout << "YES" << endl;
      cout << s.substr(0, i) << endl; // Output the matching part
      return 0;
    }
  }
  cout << "NO" << endl; // No valid overlap found
  return 0;
}


// https://github.com/VaHiX/codeForces/