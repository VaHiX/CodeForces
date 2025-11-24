# Problem: CF 1503 A - Balance the Bits
# https://codeforces.com/contest/1503/problem/A

"""
Balance the Bits

Algorithm:
This problem involves constructing two balanced bracket sequences a and b based on a binary string s. 
The key insight is to process the string from left to right while maintaining balance counters and 
adjusting the bracket types to satisfy the constraints.

Time Complexity: O(n) where n is the length of the string s
Space Complexity: O(n) for storing the result strings a and b

Approach:
1. Initially, we try to build sequences a and b greedily.
2. For each '0' in s, we choose the bracket type such that a[i] != b[i].
3. For each '1' in s, we set a[i] = b[i].
4. During construction, we track the balance (number of unmatched opening brackets).
5. After building the initial sequences, we adjust them to ensure validity.
"""

import sys

input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    s = input()[:-1]
    a = []
    b = []
    a1 = b1 = ew = 0
    for i in s:
        if i == "0":
            # When s[i] is '0', a[i] and b[i] must be different
            # If a1 > b1, then a has more opening brackets; so we use closing in a and opening in b
            if a1 > b1:
                a1 -= 1
                b1 += 1
                a.append(")")
                b.append("(")
            else:
                # Otherwise, we ensure that a[i] and b[i] differ
                a1 += 1
                b1 -= 1
                a.append("(")
                b.append(")")
        else:
            # When s[i] is '1', a[i] and b[i] must be the same
            a1 += 1
            b1 += 1
            a.append("(")
            b.append("(")
        # If b1 becomes negative, it means we have more closing brackets than opening
        if b1 < 0:
            ew = 1
            break
    # If final balance a1 is odd, then it's impossible to form valid brackets
    if a1 % 2 or ew == 1:
        print("NO")
    else:
        c = 0
        # Reverse pass to verify the constructed sequences are balanced
        for i in range(n - 1, -1, -1):
            if s[i] == "1":
                # Adjust positions where s[i] is '1' to ensure that both sequences remain balanced
                if a1 > 0:
                    a1 -= 2
                    a[i] = ")"
                    b[i] = ")"
            # Check for valid bracket sequence by simulating stack behavior
            if b[i] == ")":
                c += 1
            else:
                c -= 1
            if c < 0:
                break
        # If c != 0, sequences are not valid
        if c != 0:
            print("NO")
        else:
            print("YES")
            print("".join(a))
            print("".join(b))


# https://github.com/VaHiX/CodeForces/