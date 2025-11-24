// Problem: CF 1177 A - Digits Sequence (Easy Edition)
// https://codeforces.com/contest/1177/problem/A

#include <iostream>
#include <string>

using namespace std;

/*
A. Digits Sequence (Easy Edition)
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
Let's write all the positive integer numbers one after another from $$$1$$$ without any delimiters (i.e. as a single string). It will be the infinite sequence starting with 
123456789101112131415161718192021222324252627282930313233343536...
Your task is to print the $$$k$$$-th digit of this sequence.
Input
The first and only line contains integer $$$k$$$ ($$$1 \le k \le 10000$$$) — the position to process ($$$1$$$-based index).
Output
Print the $$$k$$$-th digit of the resulting infinite sequence.

Algorithms/Techniques: String concatenation, digit-by-digit construction

Time Complexity: O(n^2) where n is the maximum number (up to 10000)
Space Complexity: O(n^2) for storing the concatenated string
*/

int main() {
  int k, i;
  string a;
  // Build the sequence by concatenating numbers from 0 to 9999
  for (i = 0; i < 10000; i++) {
    a += to_string(i); // Convert number to string and append to sequence
  }
  cin >> k;
  cout << a[k]; // Output the k-th digit (0-indexed)
}

// https://github.com/VaHiX/codeForces/