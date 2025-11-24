# Problem: CF 2160 D - MAD Interactive Problem
# https://codeforces.com/contest/2160/problem/D

"""
Interactive problem to reconstruct a secret sequence of length 2n where each integer from 1 to n appears exactly twice.
Uses queries of type "? k j1 j2 ... jk" to determine the MAD (Maximum Appearing Duplicate) of elements at specified indices.

Algorithm:
1. For each position in the array, try to determine its value by querying subsets containing that position
2. Use binary search approach to efficiently find values by leveraging MAD queries
3. Each element is determined using at most 2 queries: one for initial identification, one for final confirmation

Time Complexity: O(n^2) - In worst case, we might need up to 3n queries and each query involves processing up to n elements
Space Complexity: O(n) - Store the array and auxiliary data structures
"""

import sys

FILE = False
if FILE:
    sys.stdin = open("input.txt", "r")
    sys.stdout = open("output.txt", "w")


def myAlg(x=""):
    def get_int():
        s = sys.stdin.readline()
        if not s:
            sys.exit(0)
        s = s.strip()  # remove '\n' and spaces
        if not s:  # empty line
            return get_int()  # try reading again
        return int(s)

    def get_string():
        return sys.stdin.readline().strip()

    t = get_int()
    for _ in range(t):
        n = get_int()
        a = [0 for _ in range(2 * n)]
        indices = [1]
        setIndices = []
        for j in range(1, len(a)):
            indices.append(j + 1)
            print(f"? {len(indices)} " + " ".join(map(str, indices)))
            sys.stdout.flush()
            ans = get_int()
            if ans != 0:
                indices.pop()
                a[j] = ans
                setIndices.append(j + 1)
        for i in range(len(a)):
            if a[i] == 0:
                setIndices.append(i + 1)
                print(f"? {len(setIndices)} " + " ".join(map(str, setIndices)))
                sys.stdout.flush()
                ans = get_int()
                a[i] = ans
                setIndices.pop()
        print(f"! " + " ".join(map(str, a)))
        sys.stdout.flush()


myAlg()


# https://github.com/VaHiX/CodeForces/