// Problem: CF 1791 A - Codeforces Checking
// https://codeforces.com/contest/1791/problem/A

/*
A. Codeforces Checking
time limit per test1 second
memory limit per test256 megabytes
Given a lowercase Latin character (letter), check if it appears in the string
codeforces
.
Input
The first line of the input contains an integer
t
(
1≤t≤26
) — the number of test cases.
The only line of each test case contains a character
c
 — a single lowercase Latin character (letter).
Output
For each test case, output "YES" (without quotes) if
c
satisfies the condition, and "NO" (without quotes) otherwise.
You can output the answer in any case (for example, the strings "yEs", "yes", "Yes" and "YES" will be recognized as a positive answer).
Example
input
Copy
10
a
b
c
d
e
f
g
h
i
j
output
Copy
NO
NO
YES
YES
YES
YES
NO
NO
NO
NO

Algorithms/Techniques: String search using std::string::find()
Time Complexity: O(n*m) where n is the number of test cases and m is the length of target string "codeforces"
Space Complexity: O(1) - constant extra space excluding input/output
*/

#include <iostream>
#include <string>

int main() {
  std::string target = "codeforces"; // Target string to search in
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the character as a string
    // Check if the character exists in target string
    std::cout << ((target.find(s) != std::string::npos) ? "YES" : "NO")
              << std::endl; // Output YES if found, NO otherwise
  }
}


// https://github.com/VaHiX/codeForces/