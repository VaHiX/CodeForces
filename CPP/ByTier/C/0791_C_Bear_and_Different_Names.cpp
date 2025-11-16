// Problem: CF 791 C - Bear and Different Names
// https://codeforces.com/contest/791/problem/C

/*
Code Purpose:
This program assigns names to soldiers such that the effective group conditions given in the input are satisfied.
It uses a greedy approach to assign names to soldiers, ensuring that consecutive groups of k soldiers match the given YES/NO labels.

Algorithm:
1. Initialize first n soldiers with distinct names using a simple naming scheme (Aa, Ab, Ac, ...).
2. For each group of k soldiers, if the label is "NO", we make the last soldier in the group equal to the first soldier,
   ensuring there's a duplicate name in that group.
3. Print out the names of all soldiers.

Time Complexity: O(n * k) 
Space Complexity: O(n)
*/
#include <stdio.h>
#include <iostream>
#include <string>

#define N 200
using namespace std;
string s[N], s1;
int n, k;
int main() {
  cin >> n >> k;
  // Initialize names for soldiers with a simple naming scheme
  for (int i = 1; i <= n; i++)
    s[i] = "Aa", s[i][0] += i / 26, s[i][1] += i % 26;
  // Process each group's label
  for (int i = 1; i <= n - k + 1; i++) {
    cin >> s1;
    // If label is "NO", make the last soldier of the group equal to the first
    if (s1[0] == 'N')
      s[i + k - 1] = s[i];
  }
  // Output the names
  for (int i = 1; i <= n; i++)
    cout << s[i] << ' ';
  printf("\n");
}


// https://github.com/VaHiX/CodeForces/