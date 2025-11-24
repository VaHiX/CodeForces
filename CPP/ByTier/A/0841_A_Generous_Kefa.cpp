// Problem: CF 841 A - Generous Kefa
// https://codeforces.com/contest/841/problem/A

/*
Code Purpose:
This program determines whether Kefa can distribute all his balloons to his friends such that no friend receives more than one balloon of the same color. 
It uses a frequency map to count balloons of each color, and checks if any color appears more than k times (where k is the number of friends).

Algorithms/Techniques:
- Frequency counting using a map (hash table)
- Iteration through the string to check constraints

Time Complexity: O(n + C), where n is the number of balloons and C is the number of unique colors (at most 26 for lowercase letters)
Space Complexity: O(C), where C is the number of unique colors (at most 26)

*/
#include <iostream>
#include <map>
#include <string>

typedef long long int ll;
#define dbg printf("in\n");
#define nl printf("\n");
#define pp pair<int, int>
#define N 50
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  string s;
  cin >> n >> k;             // Read number of balloons and friends
  cin >> s;                  // Read the string of balloon colors
  map<char, int> mp;         // Map to store frequency of each color
  for (i = 0; i < n; i++) {
    mp[s[i]]++;              // Count frequency of each balloon color
  }
  for (i = 0; i < n; i++) {
    if (mp[s[i]] > k) {      // If any color occurs more than k times
      cout << "NO";          // It's impossible to distribute
      return 0;
    }
  }
  cout << "YES";             // All colors can be distributed
  return 0;
}


// https://github.com/VaHiX/CodeForces/