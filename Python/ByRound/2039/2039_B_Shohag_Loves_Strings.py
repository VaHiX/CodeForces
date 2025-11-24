# Problem: CF 2039 B - Shohag Loves Strings
# https://codeforces.com/contest/2039/problem/B

"""
Algorithm/Techniques: Greedy approach
- The key insight is that for a string p, the number of distinct substrings f(p) is even if:
  - There exists a substring of length 2 with identical characters (e.g., "aa"), which gives 3 distinct substrings: "a", "a", "aa" → 3 distinct = 3 (odd), but actually we need to count unique substrings.
  - So a better approach is to realize that in most cases, if we can find a substring of length 2 or 3 such that:
    1. A substring of length 2 with same characters gives 3 distinct substrings: "a", "a", "aa" → 3 unique = 2 (even).
    2. A substring of length 3 with all different characters like "abc" gives 7 distinct substrings = 7 (odd).
  - Actually, let's reconsider: 
     For any string of length k, the number of distinct substrings can be computed by:
     If all characters are same, f(p) = k*(k+1)/2 (even or odd depending on k).
     If all characters are different, f(p) = k*(k+1)/2 and this is a triangular number.
     The key is to find a substring where there are at least 2 same characters or 3 different characters.
     When we have two identical adjacent characters, it can be used to form a substring with f = 3 which gives 3 distinct substrings. 
     So we try to find such a case.
  - In code:
    1. We scan for two adjacent identical characters.
    2. If found, return the 2-character substring → f = 3, 1 unique “a” + 1 unique “a” + 1 unique “aa”
       Actually, unique substrings are: a, aa → only 2 unique. Hmm, let's check the example.
    - Example given: "abaa", it gives 8 unique substrings: a, b, aa, ab, ba, aba, baa, abaa. That's 8 which is even.
    - Let's try: "aa", unique substrings are "a", "aa" → 2 substrings, even. That works!
    - So if we have two adjacent same characters, we can return that 2-char substring.
    - Otherwise, we look for 3-char substring with all different characters.
    - For "abc" → substrings: a, b, c, ab, bc, abc → 6 unique, even.
    - So in code:
      1. If s[i] == s[i+1], return s[i:i+2] → 2 chars → f(p) = 3 (from example, unique substrings = 2), so we need to recheck...
      2. Let’s compute f for 2 chars:
         s = "aa", substrings: "a", "a", "aa" → unique: a, aa → count = 2 (i.e., even). So we can pick this.
         s = "ab", substrings: "a", "b", "ab" → unique: a, b, ab → count = 3 (odd).
      3. Now if a string has 2 same chars like "aa", unique substrings are "a", "aa" → count = 2 (even).  
      4. For 3 chars not all distinct, e.g., "aab", unique: a, b, aa, ab, aab → count = 5 (odd).
         For 3 chars all different, e.g., "abc", unique: a, b, c, ab, bc, abc → count = 6 (even).
    - So we can greedily take 2 adjacent same characters or if no such pair, take 3 different unique chars.
    - Hence, approach:
      1. Scan for two consecutive identical chars: if found, return substring of size 2.
      2. Else scan for three consecutive different chars (and thus we get valid even f(p)).
    - If both do not work, return -1.

Time Complexity: O(n), where n is the length of input string due to linear scanning.
Space Complexity: O(1) as only a few variables are used.
"""

import sys

input = sys.stdin.readline


def main():
    t = int(input())

    while t:
        s = input().strip()
        n = len(s)
        result = "-1"
        found = False

        # Look for two adjacent characters that are the same
        for i in range(n - 1):
            if s[i] == s[i + 1]:
                result = s[i : i + 2]
                found = True
                break

        # If no such pair found, look for three consecutive characters that are pairwise different
        if not found:
            for i in range(n - 2):
                a = s[i]
                b = s[i + 1]
                c = s[i + 2]
                if a != b and a != c and b != c:
                    result = s[i : i + 3]
                    found = True
                    break

        print(result)
        t -= 1


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/