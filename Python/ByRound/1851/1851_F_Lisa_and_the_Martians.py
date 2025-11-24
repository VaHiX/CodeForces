# Problem: CF 1851 F - Lisa and the Martians
# https://codeforces.com/contest/1851/problem/F

"""
Algorithm: Maximize (a_i ⊕ x) & (a_j ⊕ x) for given martian numbers
Approach: 
1. Use a greedy recursive method to find two indices i, j that maximize the result
2. For each bit position from highest to lowest, partition candidates into two groups
3. Recursively solve for each group and choose the better result
4. Compute x using the formula x = (~(a_i & a_j)) & ((1 << k) - 1) to maximize the expression

Time Complexity: O(n * k) where n is number of elements and k is the bit length
Space Complexity: O(n + k) for storing the array and recursion stack depth
"""

from sys import gettrace, stdin

if not gettrace():

    def input():
        return next(stdin)[:-1]


def solve():
    n, k = map(int, input().split())
    aa = [int(a) for a in input().split()]

    def eval(i, j):
        # Evaluate the expression (a_i ⊕ x) & (a_j ⊕ x) for given i,j and x
        x = (~(aa[i] & aa[j])) & ((1 << k) - 1)
        return (x ^ aa[i]) & (x ^ aa[j])

    def mxmatch(k, candidates):
        # Find the maximum value by recursively dividing candidates based on bit k
        if len(candidates) < 2:
            return -1, None, None
        elif k < 0:
            # Base case: no more bits to check, just evaluate
            return eval(candidates[0], candidates[1]), candidates[0], candidates[1]
        else:
            c0 = []
            c1 = []
            # Partition candidates based on the k-th bit
            for c in candidates:
                if aa[c] & (1 << k):
                    c1.append(c)
                else:
                    c0.append(c)
            # Recursively solve for both partitions
            v0, a0, b0 = mxmatch(k - 1, c0)
            v1, a1, b1 = mxmatch(k - 1, c1)
            # Return the better result from the two partitions
            if v0 == -1 and v1 == -1:
                return eval(candidates[0], candidates[1]), candidates[0], candidates[1]
            else:
                if v0 >= v1:
                    return v0, a0, b0
                else:
                    return v1, a1, b1

    _, i, j = mxmatch(k - 1, list(range(n)))
    # Compute optimal x value based on the selected i,j
    x = (~(aa[i] & aa[j])) & ((1 << k) - 1)
    print(i + 1, j + 1, x)


def main():
    for _ in range(int(input())):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/