// Problem: CF 1097 A - Gennady and a Card Game
// https://codeforces.com/contest/1097/problem/A

/*
Problem: A. Gennady and a Card Game
Purpose: Determine if any card in the player's hand can be played based on matching suit or rank with the card on the table.
Algorithm/Techniques: Simple iteration through cards in hand to check for match in suit or rank.
Time Complexity: O(1) - We always check exactly 5 cards in hand.
Space Complexity: O(1) - Only using a fixed amount of string storage.

Input:
- First line: one card on the table (format: rank + suit)
- Second line: five cards in hand (each format: rank + suit)

Output:
- YES if at least one card from hand matches suit or rank with table card
- NO otherwise

Sample Input 1:
AS
2H 4C TH JH AD
Sample Output 1:
YES

Sample Input 2:
2H
3D 4C AC KD AS
Sample Output 2:
NO

Sample Input 3:
4D
AS AC AD AH 5H
Sample Output 3:
YES
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  string s, t; // s = card on table, t = current card from hand being checked
  cin >> s; // read the card on the table
  while (cin >> t) { // read each card from hand one by one
    if (s[0] == t[0] || s[1] == t[1]) // check if rank or suit matches
      return cout << "YES", 0; // if match found, print YES and exit
  }
  cout << "NO"; // if no match found after checking all cards, print NO
}


// https://github.com/VaHiX/codeForces/