// Problem: CF 743 A - Vladik and flights
// https://codeforces.com/contest/743/problem/A

/*
Purpose: This program determines the minimum cost for Vladik to travel from airport 'a' to airport 'b' 
         based on company ownership of airports and flight costs.

Algorithms/Techniques: 
- Simple comparison of company ownership between start and end airports.
- If both airports belong to the same company, the cost is 0.
- If they belong to different companies, the cost is 1 (since the direct distance between them is 1 
  when considering the minimal path and the problem's constraints).

Time Complexity: O(1) - Only constant time operations are performed after reading input.
Space Complexity: O(n) - Space used for storing the string of airport company assignments.
*/

#include <iostream>
#include <string>

typedef long long int ll;
using namespace std;

int main() {
  ll i, j, k;
  ll n, a, b;
  string s;
  cin >> n >> a >> b;
  cin >> s;
  a--;  // Convert to 0-based indexing
  b--;  // Convert to 0-based indexing
  
  // If both airports belong to the same company, cost is 0
  if (s[a] == s[b])
    cout << "0";
  else
    // If they belong to different companies, the minimum cost is 1
    cout << "1";
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/