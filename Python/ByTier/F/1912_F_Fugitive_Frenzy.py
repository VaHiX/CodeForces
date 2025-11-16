# Problem: CF 1912 F - Fugitive Frenzy
# https://codeforces.com/contest/1912/problem/F

"""
Purpose: Solve the Fugitive Frenzy problem on a tree where a police officer and fugitive 
         play a game with optimal strategies. The goal is to find the expected duration 
         of the chase.

Algorithms/Techniques:
- Tree preprocessing using BFS to compute distances
- Linear system solving via iterative relaxation
- Game theory with optimal mixed strategies

Time Complexity: O(n^3) where n is the number of vertices in the tree
Space Complexity: O(n^2) for storing distance matrix and auxiliary arrays

The solution models the game as a system of linear equations representing expected 
game durations from each node, then solves it iteratively using relaxation method.
"""

import sys


def readings():
    xender, signum, champu = 0, 1, sys.stdin.read(1)
    while champu < "0" or champu > "9":
        if champu == "-":
            signum = 0
        champu = sys.stdin.read(1)
    while champu >= "0" and champu <= "9":
        xender = xender * 10 + ord(champu) - ord("0")
        champu = sys.stdin.read(1)
    return xender if signum else -xender


def writings(xender):
    if xender < 0:
        sys.stdout.write("-")
        xender = -xender
    if xender > 9:
        writings(xender // 10)
    sys.stdout.write(chr(xender % 10 + ord("0")))


def doofsmart(xender, freak, rot):
    global daru, Elephant
    daru[rot][xender] = daru[rot][freak] + 1
    for vishwa in Elephant[xender]:
        if vishwa != freak:
            doofsmart(vishwa, xender, rot)


def calculations(i):
    global xender, disstrack, nunu
    sum, sumd = 0, nunu - 1
    for j in range(1, nunu + 1):
        sum += xender[j]
        sumd += disstrack[i][j] * xender[j]
    xender[i] = sum / sumd


mango = readings()
Elephant = [[] for _ in range(103)]
xender = [0] * 103
daru = [[0] * 103 for _ in range(103)]
num = [0] * 103
disstrack = [[0] * 103 for _ in range(103)]
nunu = 0

for i in range(1, mango):
    x, y = readings(), readings()
    Elephant[x].append(y)
    Elephant[y].append(x)

num[0] = readings()

for i in range(1, mango + 1):
    daru[i][0] = -1
    doofsmart(i, 0, i)
    if len(Elephant[i]) == 1:
        nunu += 1
        num[nunu] = i

for i in range(nunu + 1):
    for u in range(nunu + 1):
        disstrack[i][u] = daru[num[i]][num[u]]

for i in range(1, nunu + 1):
    xender[i] = 1

for Tasty in range(1, 1001):
    for i in range(1, nunu + 1):
        calculations(i)

Aloos, Began = nunu - 1, 0

for i in range(1, nunu + 1):
    Aloos += xender[i] * disstrack[0][i]
    Began += xender[i]

result = Aloos / Began
print("{:.10f}".format(result))


# https://github.com/VaHiX/CodeForces/