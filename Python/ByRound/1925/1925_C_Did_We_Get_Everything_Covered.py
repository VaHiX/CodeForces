# Problem: CF 1925 C - Did We Get Everything Covered?
# https://codeforces.com/contest/1925/problem/C

"""
Code Purpose:
This code solves the problem of determining whether all possible strings of length n
formed using the first k lowercase English letters appear as subsequences in a given string s.
If not all such strings are present, it outputs one such string that is missing.

Approach:
- Iterate through the string s and collect unique characters in a set.
- When the set reaches size k (meaning we've seen all k letters), we append the current character
  to the result string `ans` and reset the set.
- If `ans` contains at least n characters, then all combinations are covered.
- Otherwise, we construct a missing string by taking the first (n - len(ans)) characters
  from the alphabet that are not in the final set, and append them to `ans`.

Time Complexity: O(m + n) per test case where m is the length of string s and n is the given length.
Space Complexity: O(k + n) where k is the number of distinct characters and n is the required string length.

Algorithms/Techniques:
- Set-based tracking of unique characters
- Subsequence verification via character accumulation
- Greedy approach to find missing subsequence
"""

import sys

input = sys.stdin.readline


def solve():
    n, k, m = map(int, input().split())
    s = input().strip()
    ls = "abcdefghijklmnopqrstuvwxyz"
    st = set()
    ans = ""
    for i in s:
        st.add(i)
        if len(st) == k:  # When we've seen all k characters
            st = set()   # Reset set to track next group
            ans += i     # Append current char to result
    if len(ans) >= n:
        print("YES")
        return
    print("NO")
    for i in ls:
        if i not in st:  # Find first character not in the final set
            print(ans + (n - len(ans)) * i)  # Construct and print missing string
            break


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/