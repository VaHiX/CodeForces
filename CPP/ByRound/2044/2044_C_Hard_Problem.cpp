// Problem: CF 2044 C - Hard Problem
// https://codeforces.com/contest/2044/problem/C

/*
C. Hard Problem
time limit per test1 second
memory limit per test256 megabytes

Ball is the teacher in Paperfold University. The seats of his classroom are arranged in
2
rows with
m
seats each.
Ball is teaching
a+b+c
monkeys, and he wants to assign as many monkeys to a seat as possible. Ball knows that
a
of them only want to sit in row
1
,
b
of them only want to sit in row
2
, and
c
of them have no preference. Only one monkey may sit in each seat, and each monkey's preference must be followed if it is seated.
What is the maximum number of monkeys that Ball can seat?

Algorithm:
For each test case, we first assign monkeys with fixed preferences (a from row 1, b from row 2).
Then, remaining seats are filled with monkeys having no preference (c), choosing the row that maximizes seating.

Time Complexity: O(1) per test case
Space Complexity: O(1)

Input
The first line contains an integer
t
(
1≤t≤
10^4
) — the number of test cases.
Each test case contains four integers
m
,
a
,
b
, and
c
(
1≤m,a,b,c≤
10^8
).
Output
For each test case, output the maximum number of monkeys you can seat.
Example
input
Copy
5
10 5 5 10
3 6 1 1
15 14 12 4
1 1 1 1
420 6 9 69
output
Copy
20
5
30
2
84
Note
In the second test case,
6
monkeys want to sit in the front row, but only
3
seats are available. The monkeys that have no preference and the monkeys who prefer sitting in the second row can sit in the second row together. Thus, the answer is
3+2=5
.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long m, a, b, c;
    scanf("%ld %ld %ld %ld", &m, &a, &b, &c);
    long cnt(0);
    // Assign monkeys to row 1 with fixed preference
    if (a < m) {
      cnt += a;                        // All 'a' monkeys sit in row 1
      long rem = m - a;                // Remaining seats in row 1
      long slc = (rem < c ? rem : c);  // Take minimum of remaining seats and no preference monkeys
      cnt += slc;                      // Add them to row 1
      c -= slc;                        // Reduce count of no preference monkeys
    } else {
      cnt += m;                        // All seats in row 1 filled
    }
    
    // Assign monkeys to row 2 with fixed preference
    if (b < m) {
      cnt += b;                        // All 'b' monkeys sit in row 2
      long rem = m - b;                // Remaining seats in row 2
      long slc = (rem < c ? rem : c);  // Take minimum of remaining seats and no preference monkeys
      cnt += slc;                      // Add them to row 2
    } else {
      cnt += m;                        // All seats in row 2 filled
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/