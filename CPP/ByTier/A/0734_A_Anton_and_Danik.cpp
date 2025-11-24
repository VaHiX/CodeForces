// Problem: CF 734 A - Anton and Danik
// https://codeforces.com/contest/734/problem/A

/*
Purpose: Determine the winner of a series of chess games between Anton and Danik based on the outcome of each game.
Algorithm: Count occurrences of 'A' and 'D' in the input string and compare the counts.
Time Complexity: O(n), where n is the number of games.
Space Complexity: O(1), excluding the input string storage.
*/

#include <iostream>
#include <string>

typedef long long int ll;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, m;
  ll a = 0, b = 0;  // Counters for Anton and Danik's wins
  string s;
  cin >> n >> s;  // Read number of games and the result string

  // Iterate through the string to count wins for each player
  for (i = 0; i < n; i++) {
    if (s[i] == 'A')
      a++;  // Increment Anton's count if 'A'
    else if (s[i] == 'D')
      b++;  // Increment Danik's count if 'D'
  }

  // Compare counts and output the result
  if (a > b)
    cout << "Anton" << endl;
  else if (a < b)
    cout << "Danik" << endl;
  else
    cout << "Friendship" << endl;

  return 0;
}


// https://github.com/VaHiX/CodeForces/