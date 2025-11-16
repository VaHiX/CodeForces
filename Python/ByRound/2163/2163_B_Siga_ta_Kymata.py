# Problem: CF 2163 B - Siga ta Kymata
# https://codeforces.com/contest/2163/problem/B

"""
Algorithm: Siga ta Kymata
Purpose: Given a permutation p and a binary string x, determine if we can set certain positions of a binary string s to 1 using at most 5 operations such that for every position i where x[i] = 1, we also have s[i] = 1.

Approach:
1. For each test case, we analyze the positions of elements 1 and n in the permutation.
2. If either the first or last element of x is 1, or if either position 1 or n in the permutation has a 1 in x, then it's impossible to satisfy the constraints.
3. Otherwise, we simulate the operations to set s[i] = 1 for required positions.
   
Time Complexity: O(n) per test case, as we process each element in the permutation once.
Space Complexity: O(n) for storing the permutation and the output lines.

Operations:
We use at most 5 operations to ensure s[i] = 1 for all positions required by x.

This approach leverages the fact that we can use range operations to fill certain areas of the string s based on values in the permutation p. 
"""

import sys


def solve():
    input = sys.stdin.read
    data = input().split()

    t = int(data[0])
    idx = 1
    out_lines = []

    for _ in range(t):
        n = int(data[idx])
        idx += 1
        p = [0] + list(map(int, data[idx : idx + n]))  # 1-indexed permutation
        idx += n
        x = " " + data[idx]  # 1-indexed binary string
        idx += 1

        # Find positions of 1 and n in the permutation
        pos1 = 0
        posn = 0
        for i in range(1, n + 1):
            if p[i] == 1:
                pos1 = i
            if p[i] == n:
                posn = i

        # Check if it's impossible to satisfy x
        # If any of first or last positions in x are 1 and they correspond to 1 or n in the permutation
        if x[1] == "1" or x[n] == "1" or x[pos1] == "1" or x[posn] == "1":
            out_lines.append("-1")
            continue

        # Ensure pos1 <= posn to simplify algorithm
        if pos1 > posn:
            pos1, posn = posn, pos1

        operations = []

        # Perform 5 operations to fill in the necessary bits
        operations.append((1, pos1))  # Set all elements from 1 to pos1 which are between 1 and p[pos1]
        operations.append((1, posn))  # Set all elements from 1 to posn which are between 1 and p[posn] 
        operations.append((pos1, n))  # Set all elements from pos1 to n which are between p[pos1] and n
        operations.append((posn, n))  # Set all elements from posn to n which are between p[posn] and n
        operations.append((pos1, posn))  # Set all elements from pos1 to posn which are between p[pos1] and p[posn]

        out_lines.append(str(len(operations)))
        for l, r in operations:
            out_lines.append(f"{l } {r }")

    print("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/