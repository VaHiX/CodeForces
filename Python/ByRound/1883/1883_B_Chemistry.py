# Problem: CF 1883 B - Chemistry
# https://codeforces.com/contest/1883/problem/B

"""
Algorithm: Palindrome Rearrangement Check
Techniques: Frequency counting, parity analysis

Time Complexity: O(n) where n is the length of the string
Space Complexity: O(1) since there are at most 26 lowercase letters

The approach involves:
1. Counting the frequency of each character in the string.
2. Determining how many characters have odd frequencies.
3. Analyzing whether we can remove exactly k characters to make a palindrome:
   - For a palindrome, at most one character may have an odd frequency (in case of odd-length palindrome).
   - We simulate removing k characters and check if the remaining can form a palindrome.
"""

import sys

input = sys.stdin.readline


def inp():
    return int(input())


def inlt():
    return list(map(int, input().split()))


def insr():
    s = input()
    return s.strip()


def invr():
    return list(map(int, input().split()))


def doItAll(s, n, k):
    # Count frequency of each character
    mappy = {}
    for c in s:
        mappy[c] = mappy.get(c, 0) + 1
    
    # Determine if the final string will have odd length
    finalOdd = (n - k) % 2 == 1
    
    # Count how many characters have odd frequencies
    numOdd = 0
    for val in mappy.values():
        if val % 2 == 1:
            numOdd += 1
    
    # Calculate how many odd-frequency characters we need to remove
    remainder = k - numOdd
    
    # Check conditions for possible palindrome formation
    if remainder == -1 and finalOdd:
        print("YES")
    elif numOdd > k:
        print("NO")
    elif finalOdd and remainder % 2 == 1:
        print("YES")
    elif not finalOdd and remainder % 2 == 0:
        print("YES")
    else:
        print("NO")


t = inp()
for _ in range(t):
    n, k = invr()
    myStr = insr()
    doItAll(myStr, n, k)


# https://github.com/VaHiX/CodeForces/