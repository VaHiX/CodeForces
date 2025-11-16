# Problem: CF 1951 E - No Palindromes
# https://codeforces.com/contest/1951/problem/E

"""
Algorithm: No Palindromes
Purpose: Determine if a string can be partitioned into substrings that are not palindromes.
Techniques:
    - Palindrome checking using two pointers
    - Greedy approach to partition the string
Time Complexity: O(n^2) in worst case due to palindrome checks, but typically much faster in practice
Space Complexity: O(1) additional space excluding input storage

Approach:
    1. If all characters are the same, it's impossible to split into non-palindromes.
    2. If the entire string is not a palindrome, it's trivially a valid partition.
    3. Otherwise, try to find a partition by scanning for first differing character.
    4. Use greedy partitions to ensure no palindromes are formed.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()


def ii():
    return int(input())


def mi():
    return map(int, input().split())


def li():
    return list(map(int, input().split()))


def si():
    return input()


def lsi():
    return input().split()


def isPal(low, high):
    # Check if substring from index low to high is a palindrome
    while low < high:
        if s[low] != s[high]:
            return False
        low += 1
        high -= 1
    return True


t = ii()
for _ in range(t):
    s = si()

    # If all characters are the same, it's impossible to partition into non-palindromes
    if len(set(s)) == 1:
        print("NO")
        continue

    # If the whole string is not a palindrome, use it as one part
    if not isPal(0, len(s) - 1):
        print("YES")
        print(1)
        print(s)

    else:
        # Find the first character that differs from the first character
        dif_i = 0
        while s[dif_i] == s[0]:
            dif_i += 1

        # If the suffix starting from dif_i+1 is not palindrome, partition here
        if not isPal(dif_i + 1, len(s) - 1):
            print("YES")
            print(2)
            print(s[: dif_i + 1], s[dif_i + 1 :])
            continue

        # If only one different char, it cannot be split further without forming palindrome
        if dif_i == 1:
            print("NO")

        # If we're splitting near middle, also impossible
        elif dif_i == len(s) // 2:
            print("NO")

        # Else we can try splitting with a few more characters
        else:
            print("YES")
            print(2)
            print(s[: dif_i + 2], s[dif_i + 2 :])


# https://github.com/VaHiX/CodeForces/