// Problem: CF 1090 K - Right Expansion Of The Mind
// https://codeforces.com/contest/1090/problem/K

/*
Problem A. Right Expansion Of The Mind
Time limit: 2 seconds
Memory limit: 512 megabytes

Task:
Given n people, each with two strings s_i and t_i, we form an infinite string w_i = s_i + t_i + t_i + ...
Two people are "interested" if the infinite string of one is a subsequence of the other's (and vice versa).
We must partition all people into minimum number of groups such that everyone in a group is mutually interested.

Approach:
1. For each person, compute how the mind expands: w_i = s_i + t_i + t_i + ...
2. Two minds are equivalent if they're subsequences of each other.
3. This happens when:
   - The set of characters in t_i matches that in t_j (i.e., t_i and t_j use same letters)
   - The "extra" part of s_i, after truncating leading non-t characters, is the same
4. So we represent each mind by a pair: 1) set of t's chars (as bitmask), 2) reversed suffix (from s_i).
5. Sort these pairs to group equivalent ones.
6. Group them accordingly and output.

Algorithms/Techniques:
- Bitmasking to represent the character sets.
- String processing and reversal.
- Sorting + grouping algorithm.
- Subsequence equivalence checking in infinite strings via canonical representation.

Time Complexity: O(n * L * log(n)) where L is average length of strings, due to sorting.
Space Complexity: O(n * L) for storing strings and structures.
*/

#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int n;
char p[1010000], q[1010000], tp[1010000];

struct A {
  string s;       // reversed suffix of s after trimming leading non-t chars
  int ck, num;    // bitmask of t's characters, original index
  bool operator<(const A &p) const { 
    return ck != p.ck ? ck < p.ck : s < p.s;  // sort by mask then string
  }
} w[101000];

vector<vector<int>> Res;

int main() {
  int i, j;
  scanf("%d", &n);
  
  for (i = 1; i <= n; i++) {
    scanf("%s%s", p, q); // read s and t
    
    int t = 0;  // bitmask of characters in t
    for (j = 0; q[j]; j++) {
      t |= 1 << (q[j] - 'a');  // set bit for each character in t
    }
    
    w[i].ck = t; // store mask
    
    int L = 0;  // length of processed suffix
    int ck = 0; // flag to indicate we've seen a non-t char
    // Process p from right to left: find the longest suffix that starts with a 't' char
    for (j = 0; p[j]; j++) {}
    for (j = j - 1; j >= 0; j--) {
      if (!((t >> (p[j] - 'a')) & 1)) // if current char is not in t
        ck = 1;                       // set flag to ignore leading chars
      if (ck)                         // until we hit a non-t char,
        tp[L++] = p[j];               // add it to suffix
    }
    
    tp[L] = 0;
    w[i].s = tp;   // store reversed suffix
    w[i].num = i;  // original index
  }
  
  sort(w + 1, w + n + 1);  // sort based on group criteria
  
  vector<int> T;
  T.push_back(w[1].num);
  
  for (i = 2; i <= n; i++) {
    if (w[i - 1] < w[i]) {  // check if we need new group
      Res.push_back(T);
      T.clear();
    }
    T.push_back(w[i].num);  // add to current group
  }
  
  Res.push_back(T);  // push last group
  
  printf("%d\n", Res.size());
  for (auto &t : Res) {
    printf("%d ", t.size());
    for (auto &x : t) {
      printf("%d ", x);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/