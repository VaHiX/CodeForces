# Problem: CF 1765 A - Access Levels
# https://codeforces.com/contest/1765/problem/A

"""
Algorithm: 
This problem is about finding the minimum number of access groups needed to satisfy all access requirements.
The approach uses a bipartite matching algorithm to identify the minimum number of groups:
1. For each document, create a bitmask representing which developers have access to it
2. Build a graph where nodes are these bitmasks, and there's an edge between two masks if one is a subset of another
3. Find maximum matching in this graph to determine grouping
4. Use the matching to form chains of groups and assign levels accordingly

Time Complexity: O(N^2 * M) where N is number of developers and M is number of documents
Space Complexity: O(N * M) for storing masks and adjacency list
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
    var_and_vals = [f"{var}={val}" for var, val in zip(vnames, args)]
    prefix = f"{currentframe().f_back.f_lineno:02d}: "
    print(f'{prefix}{", ".join(var_and_vals)}')


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


def kuhn(adj, L, R):
    """
    adj[l] = all r's connected to l
    L = num nodes on left side (0..L-1)
    R = num nodes on right side (0..R-1)
    returns: matching [](l, r)
    """

    def dfs(l):
        if seen[l]:
            return False
        seen[l] = 1
        for r in adj[l]:
            if match[r] == -1 or dfs(match[r]):
                match[r] = l
                return True
        return False

    match = [-1] * R
    for l in range(L):
        seen = [0] * L
        dfs(l)
    return [(l, r) for r, l in enumerate(match) if l != -1]


def main():
    N, M = list(map(int, input().split()))
    mask = [0] * M
    for j in range(N):
        S = input().decode().strip()
        for i in range(M):
            if S[i] == "1":
                mask[i] |= 1 << j
    uniq_mask = list(set(mask))
    MU = len(uniq_mask)
    mask_val = {i: m for i, m in enumerate(uniq_mask)}
    adj = [[] for _ in range(MU)]
    for i in range(MU):
        for j in range(i):
            both = mask_val[i] & mask_val[j]
            if both == mask_val[i]:
                adj[i].append(j)
            elif both == mask_val[j]:
                adj[j].append(i)
    edges = kuhn(adj, MU, MU)
    adj = [-1] * MU
    deg = [0] * MU
    for l, r in edges:
        adj[l] = r
        deg[r] += 1
    chains = []
    groups = [-1] * MU
    for i in range(MU):
        if deg[i] != 0:
            continue
        groups[i] = len(chains) + 1
        chain = [i]
        while adj[chain[-1]] != -1:
            chain.append(adj[chain[-1]])
            groups[chain[-1]] = groups[i]
        chains.append(chain)
    debug(edges, chains)
    K = len(chains)
    doc_score = [-1] * MU
    for ch in chains:
        for i, doc in enumerate(ch):
            doc_score[doc] = len(ch) - i + 1
    groups_out = [-1] * M
    doc_score_out = [-1] * M
    for i1, m1 in enumerate(mask):
        for i2, m2 in mask_val.items():
            if m1 == m2:
                groups_out[i1] = groups[i2]
                doc_score_out[i1] = doc_score[i2]
                break
    print(K)
    print(*groups_out)
    print(*doc_score_out)
    for i in range(N):
        dev_score = [1] * K
        for k, ch in enumerate(chains):
            for doc in ch:
                if (mask_val[doc] >> i) & 1:
                    dev_score[k] = doc_score[doc]
                    break
        print(*dev_score)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/