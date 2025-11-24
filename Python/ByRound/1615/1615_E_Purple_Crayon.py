# Problem: CF 1615 E - Purple Crayon
# https://codeforces.com/contest/1615/problem/E

"""
Algorithm: Tree Dynamic Programming with Segment Trees
Time Complexity: O(n log n)
Space Complexity: O(n)

This problem involves a game on a tree where two players (Red and Blue) color nodes,
with Red going first and limited to k nodes. The goal is to compute the final score
w*(r-b) under optimal play, where w, r, b are counts of white, red, and blue nodes respectively.

The solution uses:
1. Tree preprocessing to compute depths and parent relationships
2. Segment tree to efficiently query and update the node with maximum depth
3. Greedy strategy for both players to maximize/minimize score:
   - Red chooses subtrees to maximize the number of red nodes (up to k)
   - Blue chooses subtrees to maximize the number of blue nodes, avoiding red nodes

Key steps:
- Identify all leaf nodes of the tree
- If k >= number of leaves, Red can color enough nodes to force Blue to have 0 blue nodes
- Otherwise, simulate Red's strategy using segment trees to efficiently select optimal subtrees
- Calculate the final score considering optimal play by both players
"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline

n, k = map(int, input().split())

E = [[] for i in range(n)]

for i in range(n - 1):
    x, y = map(int, input().split())
    x -= 1
    y -= 1
    E[x].append(y)
    E[y].append(x)

LEAF = []
for i in range(1, n):
    if len(E[i]) == 1:
        LEAF.append(i)

LEAFS = len(LEAF)

if k >= LEAFS:
    ANS = 0
    for i in range(LEAFS, k + 1):
        ANS = max(ANS, (n - i) * i)

    print(ANS)
    exit()

QUE = [0]
Parent = [-1] * (n)
Parent[0] = n
TOP_SORT = []

while QUE:
    x = QUE.pop()
    TOP_SORT.append(x)
    for to in E[x]:
        if Parent[to] == -1:
            Parent[to] = x
            QUE.append(to)

Depth = [1] * (n)

for x in TOP_SORT[1:][::-1]:
    Depth[Parent[x]] = max(Depth[x] + 1, Depth[Parent[x]])


def seg_function(x, y):

    if x[0] > y[0]:
        return x
    else:
        return y


seg_el = 1 << ((n + 2).bit_length())
SEG = [[0, 0] for i in range(2 * seg_el)]

for i in range(n):
    SEG[i + seg_el] = [Depth[i], i]

for i in range(seg_el - 1, 0, -1):
    SEG[i] = seg_function(SEG[i * 2], SEG[i * 2 + 1])


def update(n, x, seg_el):
    i = n + seg_el
    SEG[i] = x
    i >>= 1

    while i != 0:
        SEG[i] = seg_function(SEG[i * 2], SEG[i * 2 + 1])
        i >>= 1


def getvalues(l, r):
    L = l + seg_el
    R = r + seg_el
    ANS = [0, 0]

    while L < R:
        if L & 1:
            ANS = seg_function(ANS, SEG[L])
            L += 1

        if R & 1:
            R -= 1
            ANS = seg_function(ANS, SEG[R])
        L >>= 1
        R >>= 1

    return ANS


MAXB = n

for i in range(k):
    dep, ind = getvalues(0, n)

    MAXB -= dep

    while True:
        update(ind, [0, 0], seg_el)
        Depth[ind] = 0

        if dep == 1:
            break

        for to in E[ind]:
            if Depth[to] == dep - 1:
                ind = to
                dep -= 1
                break

ANS = 1 << 60

for i in range(MAXB + 1):
    ANS = min(ANS, (n - k - i) * (k - i))

print(ANS)


# https://github.com/VaHiX/CodeForces/