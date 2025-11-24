// Problem: CF 1038 A - Equality
// https://codeforces.com/contest/1038/problem/A

/*
A. Equality
Algorithm/Techniques: Greedy approach
Time Complexity: O(n), where n is the length of the string
Space Complexity: O(1), since we use a fixed-size array of 26 elements

The problem asks to find the longest subsequence where each of the first k letters appears 
the same number of times. The key insight is that the maximum length of such a subsequence 
is determined by how many complete sets of k characters we can form, which is limited by 
the character that appears the least.
*/
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 105
#define inf 10000000000000000
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d ", n)
#define pff(n, m) printf("%d %d\n", n, m)
#define pffl(n, m) printf("%I64d %I64d\n", n, m)
#define pfl(n) printf("%I64d\n", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s;
  int a[26]; // Array to count frequency of each character (A-Z)
  memset(a, 0, sizeof(a)); // Initialize all counts to zero
  sff(n, k); // Read n and k
  cin >> s; // Read the input string
  for (i = 0; i < n; i++) {
    a[s[i] - 'A']++; // Count frequency of each character
  }
  int mn = n; // Initialize minimum count to n (maximum possible)
  for (i = 0; i < k; i++)
    mn = min(mn, a[i]); // Find minimum frequency among first k characters
  pf(mn * k); // Multiply by k to get total length of longest good subsequence
  return 0;
}


// https://github.com/VaHiX/codeForces/