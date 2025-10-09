# Contest 1765, Problem L: Project Manager
# URL: https://codeforces.com/contest/1765/problem/L

""" L. Project Manager
https://codeforces.com/contest/1765/problem/L
"""

import io, os, sys

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline  # decode().strip() if str
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

# -----------------------------------------

from heapq import heappush, heappop
from collections import deque

DAYS = {
    "Monday": 0,
    "Tuesday": 1,
    "Wednesday": 2,
    "Thursday": 3,
    "Friday": 4,
    "Saturday": 5,
    "Sunday": 6,
}


def main():
    N, M, K = list(map(int, input().split()))
    workdays = [
        [DAYS[t] for t in input().decode().strip().split()[1:]] for _ in range(N)
    ]
    holidays = set(map(int, input().split()))
    projects = [deque(list(map(int, input().split()))[1:]) for _ in range(K)]

    d2w = [dict() for _ in range(7)]  # day -> (worker, num blocked projects)
    w2p = [[] for _ in range(N)]  # worker -> blocked projects
    for p in range(K):
        w = projects[p].popleft() - 1
        for d in workdays[w]:
            d2w[d][w] = d2w[d].get(w, 0) + 1
        heappush(w2p[w], p)

    t = 1
    res = [-1] * K
    rem = K
    while rem:
        if t not in holidays:
            cur, nxt = [], []
            for w in d2w[(t - 1) % 7]:
                p = heappop(w2p[w])
                cur.append(w)
                if not projects[p]:
                    res[p] = t
                    rem -= 1
                else:
                    w = projects[p].popleft() - 1
                    nxt.append((w, p))

            for w in cur:
                for d in workdays[w]:
                    d2w[d][w] -= 1
                    if not d2w[d][w]:
                        d2w[d].pop(w)

            for w, p in nxt:
                for d in workdays[w]:
                    d2w[d][w] = d2w[d].get(w, 0) + 1
                heappush(w2p[w], p)

        t += 1

    print(*res)


if __name__ == "__main__":
    main()
