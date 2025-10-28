# Problem: CF 2059 E2 - Stop Gaming (Hard Version)
# https://codeforces.com/contest/2059/problem/E2

"""
Algorithm: Greedy approach to simulate operations on arrays to transform
original arrays into target arrays.

The core idea is to process each row of the arrays and determine how many
elements need to be inserted at the beginning of the current array to make
the transformation possible. We maintain a sliding window of the current
state of each array and determine when to perform operations.

Time Complexity: O(n * m) - where n is number of arrays and m is length of each array.
Each element is processed at most a constant number of times.
Space Complexity: O(n * m) - to store the results and intermediate states.
"""

t = int(input())
for tt in range(0, t):
    n, m = map(int, input().split())
    vals = []
    targ = []
    for _ in range(0, n):
        vals.append(list(map(int, input().split())))
    for _ in range(0, n):
        targ.append(list(map(int, input().split())))
    numOps = 0
    ro = 0  # row offset
    co = 0  # column offset
    v = vals[0]
    idx = 0
    idx2 = 0
    foundIdx = -1
    work = True
    res = []
    while idx < m:
        if v[idx2] == targ[0][idx]:
            if foundIdx == -1:
                foundIdx = idx
            idx2 += 1
            idx += 1
        else:
            if foundIdx != -1:
                work = False
                break
            res.append([1, targ[0][idx]])
            idx += 1
    if work and foundIdx != -1:
        res = res[::-1]
        numOps += foundIdx
        co += foundIdx
        if co >= m:
            ro += 1
            co -= m
    else:
        res = list(zip([1] * m, targ[0][::-1]))
        numOps += m
        ro += 1
    for i in range(1, n):
        if co == 0:
            v = vals[i - ro]
        else:
            v = vals[i - 1 - ro][(m - co) :] + vals[i - ro][: (m - co)]
        idx = 0
        idx2 = 0
        if ro != 0:
            aidx = len(res)
            while idx < m:
                if v[idx2] == targ[i][idx]:
                    idx2 += 1
                    idx += 1
                else:
                    res.insert(aidx - idx2, [i + 1, targ[i][idx]])
                    numOps += 1
                    co += 1
                    idx += 1
            if co >= m:
                ro += 1
                co -= m
        else:
            fidx = -1
            tidx = co
            work = True
            nc = 0
            while idx < m:
                if v[idx2] == targ[i][idx]:
                    if idx2 == tidx:
                        fidx = idx
                    idx2 += 1
                    idx += 1
                else:
                    if fidx != -1:
                        work = False
                        break
                    res.insert(tidx - idx2, [i + 1, targ[i][idx]])
                    numOps += 1
                    co += 1
                    idx += 1
            if not work:
                for l in range(fidx, m):
                    res.insert(0, [i + 1, targ[i][l]])
                numOps += m - fidx
                co += m - fidx
            if co >= m:
                ro += 1
                co -= m
    print(numOps)
    for a in res:
        print(*a)


# https://github.com/VaHiX/CodeForces/