// Problem: CF 907 C - Shockers
// https://codeforces.com/contest/907/problem/C

/*
Algorithm/Technique: 
- Maintain a vector of booleans representing which letters are still possible candidates for the selected letter.
- For each action:
  - If it's a word with a shock (!): eliminate letters that are not in the word.
  - If it's a word without shock (.): eliminate letters that are in the word.
  - If it's a guess (?): check if the guess is correct (i.e., the letter is still a candidate).
- Track the number of shocks that could be avoided by counting the shocks after the solution is uniquely determined.

Time Complexity: O(n * m) where n is the number of actions and m is the average word length.
Space Complexity: O(1) since we use a fixed size vector of 26 elements.

*/

#include <iostream>
#include <vector>
#include <string>

int main() {
  const int N = 26;
  std::vector<bool> v(N, 1);  // Tracks possible letters (initially all are possible)
  int sum(N);                 // Number of possible letters
  long count(0);              // Count of excessive shocks
  long n;
  std::cin >> n;
  while (n--) {
    std::string action, word;
    std::cin >> action >> word;
    std::vector<bool> w(N, 0);  // Tracks letters present in current word
    for (int p = 0; p < word.size(); p++) {
      w[word[p] - 'a'] = 1;     // Mark letters in the word as present
    }
    // Count excessive shock if: 
    // 1. Only one candidate left, 
    // 2. There are more actions to come, 
    // 3. The current action is a guess (because guesses cause shocks)
    count += (sum == 1) && (n > 0) && (action[0] != '.');
    if (action[0] == '!') {     // Word caused a shock
      for (int p = 0; p < N; p++) {
        if (v[p] && !w[p]) {    // If letter was possible but not in word, eliminate it
          v[p] = 0;
          --sum;
        }
      }
    } else if (action[0] == '.') { // Word did not cause a shock
      for (int p = 0; p < N; p++) {
        if (v[p] && w[p]) {     // If letter was possible and in word, eliminate it
          v[p] = 0;
          --sum;
        }
      }
    } else if (action[0] == '?') { // Guess about the letter
      int letter = word[0] - 'a';
      if (v[letter]) {          // If guess is correct (still a possible letter)
        --sum;
      }
      v[letter] = 0;            // Mark guess as not possible (to avoid double counting)
    }
  }
  std::cout << count << std::endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/