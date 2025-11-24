# Problem: CF 1765 H - Hospital Queue
# https://codeforces.com/contest/1765/problem/H

""" H. Hospital Queue
https://codeforces.com/contest/1765/problem/H 

Algorithm: Topological Sort with Priority Queue
- Use a modified topological sort to determine the minimum position for each patient
- The key insight is to always select the patient with the smallest p_i value among those with in-degree 0
- The minimum position for a patient is determined by how early we can place them in the ordering

Time Complexity: O((N + M) * log N) - where N is number of patients and M is number of restrictions
- Building adjacency list and in-degree array: O(N + M)
- Heap operations: O((N + M) * log N)

Space Complexity: O(N + M) - for storing adjacency list, in-degrees, and heap
"""

import io
import os
import sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline
output = sys.stdout.write


def debug(*args):
    if os.environ.get("debug") in [None, "0"]:
        return
    from inspect import currentframe, getframeinfo
    from re import search

    frame = currentframe().f_back
    s = getframeinfo(frame).code_context[0]
    r = search(r"\((.*)\)", s).group(1)
    vnames = r.split(", ")
    var_and_vals = [f"{var }={val }" for var, val in zip(vnames, args)]
    prefix = f"{currentframe ().f_back .f_lineno :02d}: "
    print(f'{prefix }{", ".join (var_and_vals )}')


from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        to = f(*args, **kwargs)
        while True:
            if type(to) is GeneratorType:
                stack.append(to)
                to = next(to)
            else:
                stack.pop()
                if not stack:
                    break
                to = stack[-1].send(to)
        return to

    return wrappedfunc


class IntKeyDict(dict):
    from random import randrange

    rand = randrange(1 << 62)

    def __setitem__(self, k, v):
        super().__setitem__(k ^ self.rand, v)

    def __getitem__(self, k):
        return super().__getitem__(k ^ self.rand)

    def __contains__(self, k):
        return super().__contains__(k ^ self.rand)

    def __repr__(self):
        return str({k: v for k, v in self.items()})

    def get(self, k, default=None):
        return super().get(k ^ self.rand, default)

    def keys(self):
        return [k ^ self.rand for k in super().keys()]

    def items(self):
        return [(k ^ self.rand, v) for k, v in super().items()]


INF = float("inf")


from heapq import heapify, heappop, heappush


def solve(N, M, P, edges, n):
    deg = [0] * N  # in-degree array
    adj = [[] for _ in range(N)]  # adjacency list
    for u, v in edges:  # build adjacency list and in-degrees
        adj[v - 1].append(u - 1)
        deg[u - 1] += 1

    # Initialize heap with all nodes with in-degree 0, prioritized by p_i value
    h = [(-P[u], u) for u in range(N) if deg[u] == 0]
    heapify(h)

    res, pos = -1, N  # res stores result, pos tracks current position
    while h:
        p, u = heappop(h)  # get node with smallest p_i value
        if u == n:  # if this is the target patient
            res = pos
            continue
        if res != -1 and -p < pos:  # early termination condition
            break
        for v in adj[u]:  # process neighbors
            deg[v] -= 1  # reduce in-degree
            if deg[v] == 0:  # if in-degree becomes 0, add to heap
                heappush(h, (-P[v], v))
        pos -= 1  # move to next position
        res = pos  # update result

    return res


def main():
    N, M = list(map(int, input().split()))
    P = list(map(int, input().split()))
    edges = [list(map(int, input().split())) for _ in range(M)]
    res = [solve(N, M, P, edges, n) for n in range(N)]
    print(*res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/