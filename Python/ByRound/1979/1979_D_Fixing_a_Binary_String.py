# Problem: CF 1979 D - Fixing a Binary String
# https://codeforces.com/contest/1979/problem/D

"""
Algorithm: 
- The problem involves transforming a binary string to be k-proper using a specific operation.
- The operation includes reversing the prefix of length p and then performing a left cyclic shift by p positions.
- A k-proper string has the property that every k-length substring is all zeros or all ones, but no two adjacent k-length substrings are identical.
- Strategy:
  1. First, find a suitable p such that the first k-length chunk of the modified string is consistent (all same characters).
  2. Then verify if the entire resulting string becomes k-proper by checking that each k-length chunk is uniform and adjacent chunks differ.
- Time Complexity: O(n) for each test case
- Space Complexity: O(n) due to string operations

Approach:
- Analyze the structure of the string in segments of k-length chunks.
- Use prefix analysis to identify where to split the string (this helps find valid p).
- Perform the reverse and shift operation manually as per problem description.
- Validate k-proper condition afterwards.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
sint = lambda: int(input())
mint = lambda: map(int, input().split())
ints = lambda: list(map(int, input().split()))


def gcd(a: int, b: int) -> int:
    while b != 0:
        tmp = a % b
        a = b
        b = tmp
    return a


def lcm(a: int, b: int) -> int:
    return a * b // gcd(a, b)


def cf1979D():
    n, k = mint()
    s = input()

    c = 0
    mode = s[0]
    ans = n
    f = False
    # Scan the string to detect segments longer or shorter than k
    for i, x in enumerate(s):
        if x == mode:
            c += 1
        else:
            if c > k:
                # If we find a segment longer than k, we must place the split before k characters into it
                ans = i - k
                f = True
            elif c < k:
                # If we find a segment shorter than k, we should split at the start of this segment
                ans = i
                f = True
            mode = x
            c = 1
    # If no split was found, then we might have a uniform segment
    if (not f) and c > k:
        print(-1)
        return
    elif (not f) and c < k:
        print(-1)
        return
    if not f:
        print(ans)
        return
    
    # Preform the reverse and shift operation using the found split point
    pre = s[:ans]
    s = s[ans:] + pre[::-1]
    
    # Validate if resulting string is k-proper
    c = 0
    mode = s[0]
    for i, x in enumerate(s):
        if x == mode:
            c += 1
        else:
            if c != k:
                print(-1)
                return
            mode = x
            c = 1
    if c != k:
        print(-1)
        return
    print(ans)
    return


if __name__ == "__main__":
    t = sint()
    for _ in range(t):
        cf1979D()


# https://github.com/VaHiX/CodeForces/