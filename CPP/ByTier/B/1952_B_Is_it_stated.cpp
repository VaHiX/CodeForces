// Problem: CF 1952 B - Is it stated?
// https://codeforces.com/contest/1952/problem/B

/*
B. Is it stated?
time limit per test2 seconds
memory limit per test256 megabytes
Input
The first line contains an integer
t
(
1≤t≤100
) — the number of testcases.
The following
t
lines each contain a string of length at most
100
consisting of lowercase English letters.
Output
For each test case, output "YES" or "NO", denoting the answer.
Example
input
Copy
10
is
it
stated
submit
ac
accepted
wa
wronganswer
tle
timelimitexceeded
output
Copy
NO
YES
NO
YES
NO
NO
NO
NO
NO
YES

Algorithm: String matching using find()
Time Complexity: O(n*m) where n is number of test cases and m is average string length
Space Complexity: O(m) where m is the maximum string length
*/

#include <iostream>
#include <string>
int main() {
  std::ios_base::sync_with_stdio(false); // Disable C-style i/o synchronization for faster input/output
  long t;
  std::cin >> t; // Read number of test cases
  while (t--) {
    std::string s;
    std::cin >> s; // Read the input string
    // Check if substring "it" exists in current string
    // find() returns std::string::npos if not found, any other value means found
    std::cout << (s.find("it") != std::string::npos ? "YES" : "NO")
              << std::endl; // Print YES if "it" found, NO otherwise
  }
}


// https://github.com/VaHiX/codeForces/