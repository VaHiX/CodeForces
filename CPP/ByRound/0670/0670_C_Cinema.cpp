// Problem: CF 670 C - Cinema
// https://codeforces.com/contest/670/problem/C

/*
Code Purpose:
This program solves the problem of selecting the best movie for a group of scientists
to maximize the number of "very pleased" scientists (those who know the audio language),
and in case of a tie, maximize the number of "almost satisfied" scientists (those who know the subtitles).

Algorithm:
1. Read the number of scientists and their known languages into a map for efficient lookup.
2. Read the movies' audio and subtitle languages.
3. For each movie, calculate how many scientists know the audio language (scoreA) and how many know the subtitle language (scoreB).
4. Select the movie that maximizes scoreA, and in case of a tie, maximizes scoreB.

Time Complexity: O(n + m), where n is the number of scientists and m is the number of movies.
Space Complexity: O(n + m), for storing the scientist languages map and the movies vector.
*/

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <utility>

int main() {
  long n;
  scanf("%ld\n", &n);
  std::map<long, long> counts; // Map to store count of scientists knowing each language
  for (long p = 0; p < n; p++) {
    long x;
    std::cin >> x;
    if (counts.count(x) > 0) {
      ++counts[x];
    } else {
      counts[x] = 1;
    }
  }
  long m;
  scanf("%ld\n", &m);
  std::vector<std::pair<long, long>> lang(m, std::make_pair(0, 0)); // Store pairs of (audio_language, subtitle_language)
  for (long p = 0; p < m; p++) {
    scanf("%ld ", &lang[p].first);  // Read audio language
  }
  for (long p = 0; p < m; p++) {
    scanf("%ld ", &lang[p].second); // Read subtitle language
  }
  long best(0), scoreA(-1), scoreB(-1); // best: index of best movie, scoreA: max very pleased, scoreB: max almost satisfied
  for (long p = 0; p < m; p++) {
    long countA = (counts.count(lang[p].first) > 0) ? counts[lang[p].first] : 0; // Number of scientists knowing audio language
    long countB = (counts.count(lang[p].second) > 0) ? counts[lang[p].second] : 0; // Number of scientists knowing subtitle language
    if (countA > scoreA || (countA == scoreA && countB > scoreB)) { // Update best movie if current is better
      scoreA = countA;
      scoreB = countB;
      best = p + 1; // Movie indices are 1-based
    }
  }
  printf("%ld\n", best);
  return 0;
}


// https://github.com/VaHiX/CodeForces/