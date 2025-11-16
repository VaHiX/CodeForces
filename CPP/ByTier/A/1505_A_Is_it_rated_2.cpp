// Problem: CF 1505 A - Is it rated - 2
// https://codeforces.com/contest/1505/problem/A

/*
Purpose: This code handles an interactive problem where it reads lines of input from stdin and responds to each with "NO".
         The input is processed line-by-line until EOF is reached.

Algorithms/Techniques: 
  - Uses std::getline() to read input lines one by one.
  - For each line read, outputs "NO" to stdout.
  - Uses freopen() to redirect stdin to read from "in.txt".

Time Complexity: O(N), where N is the total number of lines in the input.
Space Complexity: O(1) excluding the input line storage (which depends on the length of each line, but constant per line).

*/
#include <stdio.h>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define nl printf("\n")
#define N 1010
#define inf 1e9
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m, t;
  string s;
  // Loop until end of file (EOF) is reached
  while (getline(cin, s)) {
    cout << "NO\n"; // Always respond with "NO" regardless of input
    cout.flush();   // Ensures output is immediately written to avoid buffering issues
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/