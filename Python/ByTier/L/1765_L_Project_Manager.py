# Problem: CF 1765 L - Project Manager
# https://codeforces.com/contest/1765/problem/L

""" L. Project Manager
https://codeforces.com/contest/1765/problem/L

Algorithms/Techniques: 
- Simulation with priority queue and hash map
- Day-by-day simulation of work
- Employees are assigned to projects based on priority (earlier projects first)
- Each day, only working days are considered for task assignment
- Holidays skip all work
- Tasks must be completed in sequential order for each project
- Use of heap to always pick the highest priority project for an employee
- Hash map to track how many projects require an employee for specific working days
- Time and space complexity are optimized for large input sizes

Time Complexity: O(n * 7 + m + k * p * log k) where p is average project length
Space Complexity: O(n * 7 + k * p + m)
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
from collections import deque
from heapq import heappop, heappush

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
    # Read working days for each employee
    workdays = [
        [DAYS[t] for t in input().decode().strip().split()[1:]] for _ in range(N)
    ]
    # Read holidays
    holidays = set(map(int, input().split()))
    # Read project data
    projects = [deque(list(map(int, input().split()))[1:]) for _ in range(K)]
    # d2w tracks which employees are needed on specific days
    d2w = [dict() for _ in range(7)]
    # w2p tracks which projects are scheduled for each employee
    w2p = [[] for _ in range(N)]
    # Initialize the data structures for the first day
    for p in range(K):
        w = projects[p].popleft() - 1  # Get the first worker for this project
        for d in workdays[w]:
            # Count how many projects require this employee on this day
            d2w[d][w] = d2w[d].get(w, 0) + 1
        heappush(w2p[w], p)  # Add this project to the heap for this worker
    t = 1  # Start from day 1
    res = [-1] * K  # Track when each project finishes
    rem = K  # Remaining projects to finish
    while rem:  # Continue until all projects are completed
        if t not in holidays:  # Only process days that are not holidays
            cur, nxt = [], []  # Track current and next workers
            # Process all employees who work on current day
            for w in d2w[(t - 1) % 7]:  # Current day (0-6 mapping)
                p = heappop(w2p[w])  # Get the highest priority project
                cur.append(w)
                # If this project is completed (no more parts)
                if not projects[p]:
                    res[p] = t  # Record completion day
                    rem -= 1
                else:
                    # Schedule next part of the project
                    w = projects[p].popleft() - 1  # Get the next worker
                    nxt.append((w, p))  # Schedule them for next part
            
            # Update d2w for current day workers
            for w in cur:
                for d in workdays[w]:
                    d2w[d][w] -= 1  # Decrease count since part was completed
                    # Remove if no more projects need this employee on this day
                    if not d2w[d][w]:
                        d2w[d].pop(w)
            
            # Update d2w for next workers
            for w, p in nxt:
                for d in workdays[w]:
                    d2w[d][w] = d2w[d].get(w, 0) + 1  # Increase count
                heappush(w2p[w], p)  # Schedule project for next worker
        t += 1  # Move to the next day
    print(*res)  # Output results


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/