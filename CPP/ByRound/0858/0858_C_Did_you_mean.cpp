// Problem: CF 858 C - Did you mean...
// https://codeforces.com/contest/858/problem/C

/*
Purpose: This code detects typos in words based on consecutive consonants and inserts minimum number of spaces to fix them.
Algorithm: 
1. Identify blocks of 3 or more consecutive consonants that contain at least 2 different letters.
2. Insert a space before the start of such a block to split the word.
3. Use a queue to store the positions where spaces need to be inserted.

Time Complexity: O(n) where n is the length of the string. We traverse the string once to detect typos and once to output the result.
Space Complexity: O(n) for storing the string and the queue to store space insertion positions.
*/

#include <algorithm>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100005
#define inf 10000000
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int a[26]; // unused array, could be removed
  char ch[] = {'a', 'e', 'i', 'o', 'u'}; // vowels
  string s;
  queue<int> q; // queue to store positions where spaces should be inserted
  cin >> s;
  memset(a, 0, sizeof(s)); // this line is incorrect and unused, should be memset(a, 0, sizeof(a))
  n = s.length();
  i = 0;
  while (true) {
    set<char> sx; // set to hold 3 consecutive characters
    if (i + 2 >= n) // if we are at the end, no more triplets possible
      break;
    sx.insert(s[i]);
    sx.insert(s[i + 1]);
    sx.insert(s[i + 2]);
    k = 0;
    for (j = 0; j < 5; j++) {
      if (ch[j] == s[i] || ch[j] == s[i + 1] || ch[j] == s[i + 2])
        k++; // count of vowels in the triplet
    }
    if (k == 0 && sx.size() > 1) // if all are consonants and there are different letters
      q.push(i + 1), i = i + 2; // insert space before first consonant and advance index
    else
      i++; // advance index
  }
  for (i = 0; i < n; i++) {
    cout << s[i];
    if (q.size()) {
      if (i == q.front()) // if current position matches front of queue
        cout << ' ', q.pop(); // print space and remove from queue
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/