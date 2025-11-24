# Problem: CF 1975 B - 378QAQ and Mocha's Array
# https://codeforces.com/contest/1975/problem/B

"""
Algorithm: 
The key insight is to find two elements in the array such that every element in the array
is divisible by at least one of these two elements.

Approach:
1. Find the minimum element 'a' in the array.
2. Filter out all elements divisible by 'a' and store them in list B.
3. If B is empty, then all elements were divisible by 'a', so return "YES".
4. Otherwise, find the minimum element 'b' in B.
5. Check if all elements in B are divisible by 'b'.
   - If yes, then all elements in the array are divisible by either 'a' or 'b', return "YES".
   - If any element in B is not divisible by 'b', return "NO".

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the filtered list B
"""

import sys

input = sys.stdin.readline
out = []

ivar = lambda: int(input())
ivars = lambda: map(int, input().split())
ilist = lambda: list(map(int, input().split()))
stri = lambda: input().strip()


def solve():
    ivar()  # read n (not used)
    A = ilist()  # read array
    a = min(A)  # find minimum element in array
    B = []
    for x in A:
        if x % a != 0:  # if x is not divisible by a, add it to B
            B.append(x)

    if B == []:  # if all elements are divisible by a
        return "Yes"
    b = min(B)  # find minimum of remaining elements
    for x in B:
        if x % b != 0:  # if any element in B is not divisible by b
            return "No"

    return "Yes"


for _ in range(int(input())):
    out.append(solve())

print("\n".join(map(str, out)))


# https://github.com/VaHiX/CodeForces/