# Problem: CF 1899 F - Alex's whims
# https://codeforces.com/contest/1899/problem/F

"""
Tree Manipulation for Alex's Whims
Algorithm:
- Construct a initial path-based tree (linear chain)
- For each query d:
  - If current leaf distance == d, no operation needed
  - If current leaf distance < d, we need to increase it by moving nodes from branch2 to branch1
  - If current leaf distance > d, we need to decrease it by moving nodes from branch1 to branch2

Time Complexity: O(n * q) in worst case due to operations on lists
Space Complexity: O(n + q) for storing edges and branch lists

This approach maintains a tree structure and manipulates it via edge reconnections
to ensure that the distance between leaves matches the required distances for each query.
"""

def main():
    """
    1 - 2
    2 - branch 1
    2 - branch 2
    """

    t = int(input())
    allans = []
    for _ in range(t):
        n, q = readIntArr()
        edges = []
        for u in range(1, n):
            edges.append((u, u + 1))
        allans.extend(edges)
        branch1 = list(range(2, n + 1))  # Initially all except 1 are in branch1
        branch2 = [2]  # Root of branch2 (initially 2 is in both)
        for __ in range(q):
            d = int(input())
            if len(branch1) == d:
                # No operation needed if current distance matches required distance
                u, v1, v2 = -1, -1, -1
            elif len(branch1) < d:
                # Need to increase distance: move nodes from branch2 to branch1
                cnt = d - len(branch1)
                u = branch2[-cnt]  # Node to move edge from
                v1 = branch2[-cnt - 1]  # Neighbor in branch2 to remove edge from
                v2 = branch1[-1]  # Node in branch1 to connect to
                branch1.extend(branch2[-cnt:])  # Move nodes from branch2 to branch1
                branch2 = branch2[:-cnt]  # Remove moved nodes from branch2
            else:
                # Need to decrease distance: move nodes from branch1 to branch2
                cnt = len(branch1) - d
                u = branch1[-cnt]  # Node to move edge from
                v1 = branch1[-cnt - 1]  # Neighbor in branch1 to remove edge from
                v2 = branch2[-1]  # Node in branch2 to connect to
                branch2.extend(branch1[-cnt:])  # Move nodes from branch1 to branch2
                branch1 = branch1[:-cnt]  # Remove moved nodes from branch1
            allans.append((u, v1, v2))
    multiLineArrayOfArraysPrint(allans)

    return


import sys

input = sys.stdin.buffer.readline


def oneLineArrayPrint(arr):
    print(" ".join([str(x) for x in arr]))


def multiLineArrayPrint(arr):
    print("\n".join([str(x) for x in arr]))


def multiLineArrayOfArraysPrint(arr):
    print("\n".join([" ".join([str(x) for x in y]) for y in arr]))


def readIntArr():
    return [int(x) for x in input().split()]


def makeArr(defaultValFactory, dimensionArr):
    dv = defaultValFactory
    da = dimensionArr
    if len(da) == 1:
        return [dv() for _ in range(da[0])]
    else:
        return [makeArr(dv, da[1:]) for _ in range(da[0])]


def queryInteractive(a, b):
    print("? {} {}".format(a, b))
    sys.stdout.flush()
    return int(input())


def answerInteractive(ans):
    print("! {}".format(ans))
    sys.stdout.flush()


inf = float("inf")




for _abc in range(1):
    main()


# https://github.com/VaHiX/CodeForces/