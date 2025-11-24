// Problem: CF 2132 A - Homework
// https://codeforces.com/contest/2132/problem/A

/*
Problem: Vlad and Dima appending characters to a string based on a distribution.
Algorithm: Simulation of character additions to a string, where 'V' means prepend and 'D' means append.
Time Complexity: O(n * m) per test case, where n is the initial string length and m is the number of operations.
Space Complexity: O(n + m), for storing the input strings and result.
*/

#include <iostream>
#include <string>

using namespace std;

void processTestCases() {
  int numTestCases;
  cin >> numTestCases;
  while (numTestCases--) {
    int initialLength;
    string initialString;
    cin >> initialLength >> initialString;
    int numOperations;
    string charactersToAdd, operations;
    cin >> numOperations >> charactersToAdd >> operations;
    for (int i = 0; i < numOperations; i++) {
      if (operations[i] == 'V') {
        // Vlad prepends character to the beginning of the string
        initialString = charactersToAdd[i] + initialString;
      } else {
        // Dima appends character to the end of the string
        initialString += charactersToAdd[i];
      }
    }
    cout << initialString << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  processTestCases();
  return 0;
}


// https://github.com/VaHiX/codeForces/