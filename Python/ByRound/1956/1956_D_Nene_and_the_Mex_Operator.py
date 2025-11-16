# Problem: CF 1956 D - Nene and the Mex Operator
# https://codeforces.com/contest/1956/problem/D

"""
Algorithm: 
This solution attempts to maximize the sum of an array by performing operations that replace a subarray with the MEX of that subarray. The approach uses a greedy method to find optimal subarrays to operate on, aiming to increase the overall sum.

Time Complexity: O(n^3) where n is the length of the array. This is due to nested loops to find subarrays and compute sums.
Space Complexity: O(n^2) for storing intermediate results and operations.
"""

def getMaxable(lst):
    rls = []
    over_sum = sum(lst)
    for i in range(len(lst)):
        for j in range(i, len(lst)):
            # Calculate new sum if we replace subarray [i, j] with MEX value squared
            sm = sum(lst[:i]) + sum(lst[j + 1 :]) + (j - i + 1) ** 2
            if (dif := sm - over_sum) > 0:
                # Store operations
                for rl in rls:
                    if i > rl[-2] + 1:
                        rls.append(rl + [i, j, dif])
                rls.append([i, j, dif])
    sums = [sum(rl[2::3]) for rl in rls]
    return rls[sums.index(max(sums))] if len(sums) > 0 else []


def addOps(r, l, ops: list):
    if r == l:
        ops.append([r + 1, l + 1])
        return
    addOps(r, l - 1, ops)
    ops.append([r + 1, l + 1])
    addOps(r, l - 1, ops)


def doOps(r, l, lst: list, ops: list):
    ops.append([r + 1, l + 1])
    if lst[r : l + 1].__contains__(0):
        ops.append([r + 1, l + 1])
    ops.append([r + 1, r + 1])
    addOps(r, l, ops)
    ops.append([r + 1, l + 1])
    n = l - r + 1
    lst[r : l + 1] = [n for _ in range(n)]
    return lst


input()
lst = list(map(int, input().split()))

ops = []
rls = getMaxable(lst)
while rls:
    for i in range(0, len(rls), 3):
        r, l = rls[i : i + 2]
        lst = doOps(r, l, lst, ops)
    rls = getMaxable(lst)

print(sum(lst), len(ops))
for r in ops:
    print(*r)


# https://github.com/VaHiX/CodeForces/