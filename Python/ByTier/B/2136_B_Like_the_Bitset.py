# Problem: CF 2136 B - Like the Bitset
# https://codeforces.com/contest/2136/problem/B

"""
B. Like the Bitset

Purpose:
This code attempts to construct a permutation of integers from 1 to n such that for every position i where s[i] == '1',
the maximum element in any interval [l, r] with length at least k covering position i is not equal to p[i].
If no such permutation exists, it outputs "NO".

Algorithms/Techniques:
- Greedy assignment of values to positions.
- First check for forbidden patterns (k consecutive 1s), which immediately makes the problem unsolvable.
- Assign larger numbers to '0' characters first (to avoid conflicts with '1's).
- Then assign remaining numbers to '1' characters.

Time Complexity: O(n) per test case
Space Complexity: O(n)

"""
import sys

input = sys.stdin.readline
for t in range(int(input())):
    n, k = map(int, input().split())
    s = input().strip()
    # If there are k consecutive 1s, it's impossible to construct the permutation
    if "1" * k in s:
        print("NO")
        continue
    print("YES")
    bpmn = [0] * n
    x = n
    # Assign largest available numbers to '0' characters
    for i, ch in enumerate(s):
        if ch == "0":
            bpmn[i] = x
            x -= 1
    # Then assign remaining numbers to '1' characters
    for i, ch in enumerate(s):
        if ch == "1":
            bpmn[i] = x
            x -= 1
    print(*bpmn)


# https://github.com/VaHiX/codeForces/