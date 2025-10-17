# Problem: CF 2160 C - Reverse XOR
# https://codeforces.com/contest/2160/problem/C

"""
C. Reverse XOR

Purpose:
This code determines whether there exists a positive integer x such that x ⊕ f(x) = n,
where f(x) is the integer formed by reversing the binary representation of x without leading zeros,
and ⊕ denotes bitwise XOR operation.

Algorithm:
- For each test case, given integer n:
  - If n == 0, output "YES" (since x=1 works: 1⊕1=0)
  - Otherwise:
    - Convert n to binary string (without '0b' prefix)
    - Count trailing zeros in binary representation
    - Remove trailing zeros to get core part of the binary
    - Check if core is a palindrome
    - If it's odd-length and middle digit is '1', return "NO"
    - Else return "YES"

Time Complexity: O(log n) per test case, since we process bits of n.
Space Complexity: O(log n), for storing the binary string representation.

Techniques:
- Bit manipulation with binary string conversion
- Palindrome checking on modified binary string
- Trailing zero counting in binary
"""

import sys


def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    res = []
    for i in range(1, t + 1):
        n = int(data[i])
        if n == 0:
            res.append("YES")
            continue
        s = bin(n)[2:]  # Convert n to binary string, remove '0b' prefix
        tz = len(s) - len(s.rstrip("0"))  # Count trailing zeros
        if tz:
            core = s[:-tz]  # Remove trailing zeros
        else:
            core = s
        if core != core[::-1]:  # Check if core is palindrome
            res.append("NO")
            continue
        if len(core) % 2 == 1 and core[len(core) // 2] == "1":  # Odd length with middle '1'
            res.append("NO")
        else:
            res.append("YES")
    sys.stdout.write("\n".join(res))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/