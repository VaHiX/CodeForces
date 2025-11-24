// Problem: CF 2086 F - Online Palindrome
// https://codeforces.com/contest/2086/problem/F

/*
F. Online Palindrome
time limit per test1 second
memory limit per test512 megabytes

This is an interactive problem.
The jury has a string s consisting of lowercase Latin letters. The following constraints apply to this string:
- the string has an odd length that does not exceed 99;
- the string consists only of the characters "a" and "b".
There is also a string t, which is initially empty. Then, |s| steps happen. During the i-th step, the following events occur:
- first, the jury tells you the character s_i and appends it to the end of the string t;
- then, you may swap any two characters in t, or do nothing.
Your task is to ensure that after the |s|-th step, the string t is a palindrome.

Algorithms/Techniques:
- Greedy approach with precomputed palindrome construction using 'a' and 'b'
- For odd-length strings, we try to construct optimal palindromic prefix
- At each step of input processing:
  - If current length is odd: we compute an optimal palindrome and perform a swap if needed.
  - If current length is even: we consider adding 'a' or 'b' and check which yields minimal mismatches with computed palindromes.
  
Time Complexity: O(n^3) where n is the input string length (up to 99), since for each prefix we try all pairs of positions to swap.
Space Complexity: O(n) for storing intermediate strings and temporary variables.

*/

#include <iostream>
#include <string>
#include <utility>

#define sz size()
#define bk back()
#define fi first
#define se second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

// Function to build a palindrome from the current string s.
// It greedily takes pairs of 'a' and 'b', then appends leftover single chars,
// Then mirrors the result to form a symmetric palindrome.
string f(string &s) {
  int a = 0;
  int b = 0;
  for (char c : s) {
    if (c == 'a')
      a++;
    else
      b++;
  }
  string ret;
  while (a >= 2 || b >= 2) {
    if (a >= 2 && b >= 2) {
      ret += "ab";
      a -= 2;
      b -= 2;
    } else if (a >= 2) {
      ret += "a";
      a -= 2;
    } else if (b >= 2) {
      ret += "b";
      b -= 2;
    }
  }
  if (a == 1)
    ret += 'a';
  else if (b == 1)
    ret += 'b';
  // Mirror the string to form a palindrome
  for (int i = ret.sz - 2; i >= 0; i--)
    ret += ret[i];
  return ret;
}

int main() {
  string s;
  while (1) {
    char c;
    cin >> c;
    if (c == '0')
      break;
    s += c;
    
    // If the current length is odd, attempt to make the palindrome matching.
    if (s.sz & 1) {
      string x = f(s);
      if (x == s) {
        cout << 0 << ' ' << 0 << endl;
        continue;
      }
      int i = -1;
      int j = -1;
      for (int k = 0; k < x.sz; k++) {
        if (x[k] == s[k])
          continue;
        if (i == -1)
          i = k;
        else if (j == -1) {
          j = k;
          break;
        }
      }
      swap(s[i], s[j]);
      cout << i + 1 << ' ' << j + 1 << endl;
      continue;
    }
    
    // If the current length is even, build palindromes by adding 'a' and 'b'
    // to see how they match with the existing string.
    s += 'a';
    string x = f(s);
    s.pop_back();
    s += 'b';
    string y = f(s);
    s.pop_back();
    
    bool flag = false;
    for (int i = 0; i < s.sz; i++) {
      for (int j = i + 1; j < s.sz; j++) {
        swap(s[i], s[j]);
        int diff = 0;
        for (int k = 0; k < s.sz; k++) {
          if (s[k] == x[k])
            continue;
          if (++diff == 3)
            break;
        }
        if (diff == 3) {
          swap(s[i], s[j]);
          continue;
        }
        diff = 0;
        for (int k = 0; k < s.sz; k++) {
          if (s[k] == y[k])
            continue;
          if (++diff == 3)
            break;
        }
        if (diff == 3) {
          swap(s[i], s[j]);
          continue;
        }
        cout << i + 1 << ' ' << j + 1 << endl;
        flag = true;
        break;
      }
      if (flag)
        break;
    }
    if (!flag)
      cout << 0 << ' ' << 0 << endl;
  }
}


// https://github.com/VaHiX/codeForces/