// Problem: CF 2038 I - Polyathlon
// https://codeforces.com/contest/2038/problem/I

/*
I. Polyathlon
time limit per test3 seconds
memory limit per test512 megabytes

Algorithms/Techniques: Simulation with preprocessed participant elimination logic.
Time Complexity: O(n * m)
Space Complexity: O(n * m)

Berland is this year's host country of the International Collegiate Polyathlon Competition! Similar to biathlon being a competition of two sports, polyathlon is a competition of many sports. This year, there are m sports. Also, there are n participants in the event. The sports are numbered from 1 to m, and the participants are numbered from 1 to n.
Some participants are skilled in multiple sports. You are given a binary matrix n×m such that the j-th character of the i-th row is 1 if the i-th participant is skilled in the j-th sport, and 0, otherwise. It's also known that, for each pair of participants, there exists at least one sport such that one of them is skilled in that sport and the other one isn't.
The order of sports in the competition is determined at the opening ceremony. Historically, it's done by the almighty Random Number Generator. A random number x from 1 to m is rolled. The competition then starts with the sport x, then the sport (xmodm+1) is played, then the sport ((x+1)modm+1), and so on.
Each sport is played as follows. If all remaining participants (all participants which are not eliminated yet) are not skilled in that sport, everyone goes through to the next sport. Otherwise, all skilled participants go through to the next sport, and all unskilled participants are eliminated from the competition. Once there is a single participant remaining in the competition, the competition ends, and that participant is declared the winner.
As an organizer of the competition, you are curious of the possible outcomes of the competition beforehand (not that you are going to rig the random roll, how could you possibly think that...). For each sport x, print the index of the winner if the competition starts with the sport x.
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
const int N = 1e6 + 1, M = 1e6 + 1;
int n, m;
int main() {
  ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cin >> n >> m;
  string s[n]; // store skillsets of participants
  for (int i = 0; i < n; i++) {
    cin >> s[i];
    s[i] += s[i]; // duplicate the string for easier index handling later
  }
  vector<int> f(n), g; // f stores current active participants, g is temporary buffer
  int ans[2 * m]; // array to store results for each starting sport
  for (int i = 0; i < n; i++)
    f[i] = i + 1; // initially all participants are active

  // process from last to first sport (reverse order)
  for (int i = 2 * m - 1; i >= 0; i--) {
    // Separate skilled and unskilled participants for current sport
    for (int &j : f) // iterate over currently active participants
      if (s[j - 1][i] == '1') // j-1 is zero-based index in s, i is the index of current sport
        g.push_back(j); // add skilled participants to g

    for (int &j : f) // iterate again over same active set
      if (s[j - 1][i] == '0') // unskilled participants go here
        g.push_back(j);

    f = g; // overwrite f with newly sorted list
    g.clear(); // clear g for next iteration
    ans[i] = f[0]; // winner of this partial round is first in the list
  }

  // print only first m answers corresponding to actual sports
  for (int i = 0; i < m; i++)
    cout << ans[i] << " ";
  return 0;
}


// https://github.com/VaHiX/codeForces/