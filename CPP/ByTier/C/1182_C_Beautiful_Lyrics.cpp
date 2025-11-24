// Problem: CF 1182 C - Beautiful Lyrics
// https://codeforces.com/contest/1182/problem/C

/*
 * Problem: Beautiful Lyrics
 * 
 * Purpose: Given a list of words, form as many "beautiful" lyrics as possible.
 * A beautiful lyric is a pair of lines, each with two words, where:
 * 1. The number of vowels in the first words of both lines are equal.
 * 2. The number of vowels in the second words of both lines are equal.
 * 3. The last vowel in both lines are the same.
 * 
 * Algorithm:
 * - For each word, count vowels and store the last vowel.
 * - Group words by (vowel count, last vowel).
 * - Pair up words that share the same vowel count and last vowel.
 * - Use a greedy approach to form pairs of such groups to make lyrics.
 * 
 * Time Complexity: O(n * L + V * log(V)) where n is number of words, L is average word length, V is unique vowel patterns.
 * Space Complexity: O(n * L + V) for storing word data and patterns.
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
const int N = 1e6 + 9;
char s[2 * N], las[N];
int n, st[N], num[N];
vector<pair<int, int>> fiv, sev;  // fiv holds pairs of words with same vowel count and last vowel; sev holds pairs of words with same vowel count and last vowel from same group
unordered_map<int, unordered_map<char, int>> mp;  // maps <vowel_count, {last_vowel, word_index}> 
int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char *ss = s + st[i];  // point to the start of current word in buffer
    scanf("%s", ss);       // read current word
    st[i + 1] = ss + strlen(ss) + 1 - s;  // update pointer to next word location
    for (int j = 0; ss[j]; ++j)
      if (ss[j] == 'a' || ss[j] == 'e' || ss[j] == 'o' || ss[j] == 'i' ||
          ss[j] == 'u') {
        ++num[i];         // increment vowel count for current word
        las[i] = ss[j];   // store last vowel encountered
      }
    // If there is already a word with same (vowel count, last vowel) pair,
    // pair them together in sev
    if (mp[num[i]].count(las[i])) {
      sev.emplace_back(mp[num[i]][las[i]], i);
      mp[num[i]].erase(las[i]);  // remove the matched word from map
    } else
      mp[num[i]][las[i]] = i;  // store the index of first word with this pattern
  }
  // For remaining unmatched (vowel count, last vowel) pairs, we pair them as best as possible
  for (unordered_map<int, unordered_map<char, int>>::iterator it = mp.begin();
       it != mp.end(); ++it) {
    int pre = -1;
    for (auto p : it->second) {
      if (pre < 0)
        pre = p.second;  // take first one as reference
      else {
        fiv.emplace_back(p.second, pre);  // pair current with reference
        pre = -1;  // reset for next pairing
      }
    }
  }
  // If there are more pairs in fiv than in sev, remove some to match sizes
  while (sev.size() > fiv.size()) {
    fiv.push_back(sev.back());
    sev.pop_back();
  }
  printf("%d\n", sev.size());  // Print number of beautiful lyrics
  while (!sev.empty()) {
    // Output the lyrics pairs
    printf("%s %s\n%s %s\n", s + st[fiv.back().first], s + st[sev.back().first],
           s + st[fiv.back().second], s + st[sev.back().second]);
    sev.pop_back();   // Remove used pair from sev
    fiv.pop_back();   // Remove used pair from fiv
  }
}


// https://github.com/VaHiX/CodeForces/