# Problem: CF 1986 D - Mathematical Problem
# https://codeforces.com/contest/1986/problem/D

"""
Algorithm: Mathematical Problem
Time Complexity: O(n^2) where n is the length of the string s
Space Complexity: O(1) - only using a constant amount of extra space

This problem involves finding the minimum value of an arithmetic expression formed by inserting 
n-2 operators (+ or *) between digits of a string. The solution handles special cases for small 
strings, and for longer strings, it attempts to minimize the result by strategically placing 
operators.

Approach:
1. For n=2, return the number itself since no operators can be inserted.
2. For n=3, try all possible placements of one operator and return the minimum.
3. For larger n:
   - If there is any '0' in the string, the minimum value is 0 (since 0 * x = 0).
   - Otherwise, we find the best two-digit number to minimize the result.
   - Then add all other digits to the result to create the minimal sum.
"""

import sys

input = sys.stdin.read


def solve():
    data = input().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        s = data[index]
        index += 1
        if n == 2:
            results.append(int(s))
            continue
        if n == 3:
            if s[0] == "0" or s[2] == "0":
                results.append(0)
            else:
                # Try all combinations of operations for 3-digit string
                k = min((int(s[0]) * int(s[1:3])), (int(s[0]) + int(s[1:3])))
                k = min(k, (int(s[2]) * int(s[0:2])))
                k = min(k, (int(s[2]) + int(s[0:2])))
                results.append(k)
            continue
        cnt0 = 0
        for i in range(n):
            if s[i] == "0":
                cnt0 += 1
                results.append(0)
                break
        if cnt0 > 0:
            continue
        k = "99"
        j = 0
        # Find the smallest two-digit number to minimize the product
        for i in range(n - 1):
            if s[i] < k[0] or (s[i] == k[0] and s[i + 1] > k[1]):
                k = s[i : i + 2]
                j = i
        p = int(k)
        # Add all other digits to the result to obtain the minimal sum
        for i in range(n):
            if i != j and i != j + 1:
                if s[i] == "1":
                    continue
                p += int(s[i])
        results.append(p)
    sys.stdout.write("\n".join(map(str, results)) + "\n")


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/