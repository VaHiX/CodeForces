# Problem: CF 1685 B - Linguistics
# https://codeforces.com/contest/1685/problem/B

"""
Algorithm/Technique:
This problem is about determining if a given string can be broken down into specific words from a language consisting of "A", "B", "AB", and "BA". 
The approach uses a greedy matching method to determine how many of each word type we can construct from the given string, and then checks if the required counts match.

Time Complexity: O(n log n) per test case due to sorting of lists cl and dl.
Space Complexity: O(n) for storing the lists cl and dl.

The algorithm analyzes consecutive characters in the string to determine if they form parts of our words. 
It tracks the count of each word type and verifies whether the given counts of words can possibly be constructed from the string.

The key insight is that when we have a sequence of consecutive identical characters, it can either form:
1. A single 'A' or 'B' word (if the length is odd)
2. Multiple "BA" or "AB" words (if the length is even)

We then use backtracking logic to try to match counts of words required.
"""

import sys

t = int(sys.stdin.readline().strip())
for _ in range(t):
    A, B, C, D = map(int, sys.stdin.readline().strip().split())
    node = sys.stdin.readline().strip()
    a, b, c, d = 0, 0, 0, 0
    n = len(node)
    pre = 0
    cl = []  # Stores lengths of consecutive B sequences (for AB words)
    dl = []  # Stores lengths of consecutive A sequences (for BA words)
    for i in range(n - 1):
        if node[i] == "A" and node[i + 1] == "A":
            if (i - pre + 1) % 2:  # Odd length segment
                a += 1  # Count as a single 'A'
            else:  # Even length segment
                d += 1  # Count as "BA" word(s)
                dl.append(i - pre + 1)  # Store the length for later processing
            pre = i + 1
        elif node[i] == node[i + 1] == "B":
            if (i - pre + 1) % 2:  # Odd length segment
                b += 1  # Count as a single 'B'
            else:  # Even length segment
                c += 1  # Count as "AB" word(s)
                cl.append(i - pre + 1)  # Store the length for later processing
            pre = i + 1
    # Handle the last segment
    if (n - 1 - pre + 1) % 2:
        if node[-1] == "A":
            a += 1
        else:
            b += 1
    else:
        if node[-1] == "A":
            d += 1
            dl.append(n - pre)
        else:
            c += 1
            cl.append(n - pre)
    # Check if current counts of 'A' and 'B' are valid against required counts
    if a - b == A - B and a <= A:
        e = A - a
        if e >= (c + d):
            print("YES")
        else:
            cl.sort()
            dl.sort()
            for i in cl:
                if C >= i // 2:
                    c -= 1
                    C -= i // 2
            for i in dl:
                if D >= i // 2:
                    D -= i // 2
                    d -= 1
            if e >= (c + d):
                print("YES")
            else:
                print("NO")
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/