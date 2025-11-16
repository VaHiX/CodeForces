# Problem: CF 1946 F - Nobody is needed
# https://codeforces.com/contest/1946/problem/F

"""
Algorithm: 
Use a Fenwick Tree (Binary Indexed Tree) with coordinate compression and reverse iteration.
For each position l from right to left:
1. For each element arr[l], update the end_counts array with the number of valid sequences ending at that element.
2. For all multiples of arr[l], add the count in the Fenwick Tree.
3. For all elements that can extend the sequence (i.e., multiples of arr[l]), update end_counts.
4. Answer queries by performing range sum on the Fenwick Tree.

Time Complexity: O(n * log(n) + q * log(n))
Space Complexity: O(n)
"""

from sys import stdin


def solve():
    n, q = map(int, stdin.readline().split())
    arr = list(map(int, stdin.readline().split()))
    queries = [[] for i in range(n)]
    for i in range(q):
        l, r = map(int, stdin.readline().split())
        queries[l - 1].append((r, i))

    pos = [0] * (n + 1)
    for i, a in enumerate(arr):
        pos[a] = i

    result = [0] * q
    end_counts = [0] * (n + 1)
    fw_tree = [0] * n
    for l in reversed(range(n)):
        a = arr[l]
        end_counts[a] = 1
        for b in range(a, n + 1, a):
            cnt = end_counts[b]
            end_counts[b] = 0

            if cnt > 0:
                i = pos[b]
                while i < n:
                    fw_tree[i] += cnt
                    i |= i + 1

            for c in range(2 * b, n + 1, b):
                if pos[c] > pos[b]:
                    end_counts[c] += cnt

        for r, q_id in queries[l]:
            r -= 1
            res = 0
            while r >= 0:
                res += fw_tree[r]
                r = (r & (r + 1)) - 1
            result[q_id] = res
    return result


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    print(*solve())


# https://github.com/VaHiX/CodeForces/