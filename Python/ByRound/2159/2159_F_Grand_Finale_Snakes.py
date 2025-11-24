# Problem: CF 2159 F - Grand Finale: Snakes
# https://codeforces.com/contest/2159/problem/F

"""
Problem: Grand Finale: Snakes
Algorithm: Interactive problem solving using binary search and priority queue
Time Complexity: O(n^2 * log(n^2) + m * log(m)) where n is grid size and m is number of queries
Space Complexity: O(n^2) for storing grid, position mapping, and auxiliary arrays

The problem involves finding the m smallest values of f(l, T) where f(l, T) is the maximum number
covered by a snake of length l at time T. Snakes move from top-left to bottom-right in a grid,
starting at the first row.

Approach:
1. Preprocess the grid to build a position mapping for each number
2. For each snake length, initialize the maximum values at the first timestep
3. Use a priority queue to efficiently query the minimum possible values
4. Perform binary search-like queries to determine which values are actually covered
5. Collect and output the m smallest values
"""

import heapq
import sys


def read_ints():
    return list(map(int, sys.stdin.readline().split()))


def main():
    data = sys.stdin
    tt_line = data.readline().strip()
    if not tt_line:
        return
    tt = int(tt_line)
    for _ in range(tt):
        line = data.readline().strip()
        while line == "":
            line = data.readline().strip()
        n, m = map(int, line.split())
        g = [[0] * n for _ in range(n)]
        pos = [None] * (n * n)
        for i in range(n):
            row = []
            while len(row) < n:
                row += list(map(int, data.readline().split()))
            for j in range(n):
                v = row[j] - 1
                g[i][j] = v
                pos[v] = (i, j)
        a = [[-1] * (2 * n - 1) for _ in range(n + 1)]
        b = [[0] * (2 * n - 1) for _ in range(n + 1)]
        for length in range(1, n + 1):
            mx = -1
            for j in range(length):
                mx = max(mx, g[0][j])
                b[length][length - 1 - j] = max(b[length][length - 1 - j], mx)
            a[length][0] = b[length][0]

        Q = 0

        def Ask(length, t):
            nonlocal Q
            if a[length][t] != -1:
                return a[length][t]
            Q += 1
            assert Q <= 120 * n + m

            print("? {} {}".format(length, t + 1))
            sys.stdout.flush()

            resp_line = sys.stdin.readline().strip()
            while resp_line == "":
                resp_line = sys.stdin.readline().strip()
            ret = int(resp_line) - 1
            i, j = pos[ret]
            if i > 0:
                ssum = i + j
                end = min(2 * n - 1, ssum + length)
                for x in range(ssum, end):
                    if b[length][x] < ret:
                        b[length][x] = ret
            a[length][t] = ret
            return ret

        cnt = [0] * (n * n)
        for length in range(1, n + 1):
            Ask(length, 2 * n - 2)
            cnt[a[length][0]] += 1
            cnt[a[length][2 * n - 2]] += 1

        heap = []
        for length in range(1, n + 1):
            mn = n * n + 1
            for i in range(1, 2 * n - 2):
                if b[length][i] < mn:
                    mn = b[length][i]
            heapq.heappush(heap, (mn, length, 0, 0, 2 * n - 2, 0))

        LIM = 200
        res = []
        for val in range(n * n):
            while True:
                if cnt[val] > 0:
                    res.append(val)
                    cnt[val] -= 1
                    if len(res) == m:
                        break
                    continue
                if not heap:
                    break
                mn, length, _zero, l, r, k = heapq.heappop(heap)
                if mn > val:

                    heapq.heappush(heap, (mn, length, _zero, l, r, k))
                    break
                if k < LIM:

                    if l + 1 < r:
                        actual_mn = min(b[length][l + 1 : r])
                    else:
                        actual_mn = n * n + 1
                    if actual_mn > mn:
                        heapq.heappush(heap, (actual_mn, length, 0, l, r, k + 1))
                        continue
                mid = max(l + 1, min(r - 1, (l + r) >> 1))
                cnt[Ask(length, mid)] += 1
                if l + 1 < mid:
                    new_mn = min(b[length][l + 1 : mid])
                    heapq.heappush(heap, (new_mn, length, 0, l, mid, 0))
                if mid + 1 < r:
                    new_mn = min(b[length][mid + 1 : r])
                    heapq.heappush(heap, (new_mn, length, 0, mid, r, 0))
            if len(res) == m:
                break

        out = ["!"]
        out.extend(str(x + 1) for x in res)
        print(" ".join(out))
        sys.stdout.flush()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/