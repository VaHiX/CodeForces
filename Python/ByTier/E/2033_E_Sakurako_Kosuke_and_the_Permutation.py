# Problem: CF 2033 E - Sakurako, Kosuke, and the Permutation
# https://codeforces.com/contest/2033/problem/E

"""
E. Sakurako, Kosuke, and the Permutation
Algorithms/Techniques: Cycle Detection in Permutations

Time Complexity: O(n) amortized over all test cases
Space Complexity: O(n)

The problem reduces to finding cycles in a permutation and determining the minimum 
number of swaps needed to make each cycle simple (i.e., all elements in the cycle point to themselves or form a 2-cycle).

For each cycle of length l, we need at least (l - 1) // 2 swaps to make it simple.
"""

t = int(input())
while t:
    t -= 1
    n = int(input())
    p = [0] + list(map(int, input().split()))  # 1-indexed permutation
    us = [0] * (n + 1)  # visited array to track nodes in cycles
    re = 0  # result: total number of swaps needed

    for i in range(1, n + 1):
        if us[i] == 0:  # if node not yet processed
            cu, le = i, 0  # current node and cycle length
            while us[cu] == 0:
                le += 1
                us[cu] = 1  # mark as visited
                cu = p[cu]   # move to next node in the cycle
            re += (le - 1) // 2  # number of swaps needed for this cycle

    print(re)


# https://github.com/VaHiX/codeForces/