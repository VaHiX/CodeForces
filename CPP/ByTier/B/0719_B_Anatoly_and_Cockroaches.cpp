// Problem: CF 719 B - Anatoly and Cockroaches
// https://codeforces.com/contest/719/problem/B

/*
B. Anatoly and Cockroaches
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Anatoly lives in the university dorm as many other students do. As you know, cockroaches are also living there together with students. Cockroaches might be of two colors: black and red. There are n cockroaches living in Anatoly's room.
Anatoly just made all his cockroaches to form a single line. As he is a perfectionist, he would like the colors of cockroaches in the line to alternate. He has a can of black paint and a can of red paint. In one turn he can either swap any two cockroaches, or take any single cockroach and change it's color.
Help Anatoly find out the minimum number of turns he needs to make the colors of cockroaches in the line alternate.

Algorithm:
This problem can be solved by trying both possible alternating patterns:
1. Pattern "rbrbrb..." (red at even indices, black at odd)
2. Pattern "brbrbr..." (black at even indices, red at odd)

For each pattern, we count how many changes are needed to convert the given string into that pattern.
We do this by:
- Counting mismatches for red at even positions and black at odd positions
- Counting mismatches for black at even positions and red at odd positions

Then we take the minimum of these two configurations.

Time Complexity: O(n)
Space Complexity: O(1)

Input
The first line of the input contains a single integer n (1 ≤ n ≤ 100 000) — the number of cockroaches.
The second line contains a string of length n, consisting of characters 'b' and 'r' that denote black cockroach and red cockroach respectively.

Output
Print one integer — the minimum number of moves Anatoly has to perform in order to make the colors of cockroaches in the line to alternate.
*/

#include <iostream>
#include <string>

int main() {
  long n(0);
  std::cin >> n;
  std::string s("");
  std::cin >> s;
  long countAr(0), countAb(0), countBr(0), countBb(0);
  for (int p = 0; p <= s.size(); p++) { // Loop through each position in the string
    if ((p % 2 == 0) && (s[p] == 'b')) { // Even index, expecting 'r' but got 'b'
      ++countBr;
    } else if ((p % 2 == 0) && (s[p] == 'r')) { // Even index, expecting 'r' but got 'r'
      ++countAb;
    } else if ((p % 2 == 1) && (s[p] == 'b')) { // Odd index, expecting 'r' but got 'b'
      ++countAr;
    } else if ((p % 2 == 1) && (s[p] == 'r')) { // Odd index, expecting 'r' but got 'r'
      ++countBb;
    }
  }
  long countA = (countAr > countAb) ? countAr : countAb; // Min moves for pattern "rbrbr..."
  long countB = (countBr > countBb) ? countBr : countBb; // Min moves for pattern "brbrbr..."
  long count = (countA < countB) ? countA : countB; // Take minimum of two patterns
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/