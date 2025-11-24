# Problem: CF 1314 A - Recommendations
# https://codeforces.com/contest/1314/problem/A

"""
Problem: News recommendation system needs to ensure each category has a different number of publications.
We are given initial counts (a_i) and time (t_i) to add one publication to each category.
Goal: Find minimum total time to make all counts unique.

Algorithm:
- Sort categories by their current count (a_i)
- Group consecutive elements with same count into segments
- For each segment, compute the minimal time needed to increase counts to be unique
- Use a priority queue to efficiently manage and update costs

Time Complexity: O(n log n) due to sorting and heap operations
Space Complexity: O(n) for storing arrays and heap
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
write = lambda x: sys.stdout.write(x + "\n")
writef = lambda x: print("{:.12f}".format(x))
debug = lambda x: sys.stderr.write(x + "\n")
YES = "Yes"
NO = "No"
pans = lambda v: print(YES if v else NO)
INF = 10**18
LI = lambda: list(map(int, input().split()))
II = lambda: int(input())


def debug(_l_):
    for s in _l_.split():
        print(f"{s}={eval(s)}", end=" ")
    print()


def dlist(*l, fill=0):
    if len(l) == 1:
        return [fill] * l[0]
    ll = l[1:]
    return [dlist(*ll, fill=fill) for _ in range(l[0])]


from heapq import heappop as hpp
from heapq import heappush as hp

n = int(input())
a = list(map(int, input().split()))
t = LI()
index = list(range(n))
index.sort(key=lambda i: a[i])
a = [a[i] for i in index]
t = [t[i] for i in index]
p = -100
l = []
ans = 0
start = None


def sub(l, start):
    if start is None:
        return 0
    n = len(l)
    res = 0
    h = []
    total = 0
    j = 0
    for val in range(start, start + n):
        # Add all elements from l that can be accommodated at current time stamp 'val'
        while j < n and a[l[j]] <= val:
            hp(h, -t[l[j]])  # Use negative to simulate max heap
            total += t[l[j]]
            j += 1
        v = hpp(h)
        v *= -1  # Convert back to positive
        total -= v  # Remove the largest cost element (greedy choice)
        res += total  # Add remaining total cost to result
    return res


for i in range(n):
    v = a[i]
    if v >= p:
        # Process previous group when we move to new value range
        ans += sub(l, start)
        l = [i]  # Start a new group
        p = v + 1  # Next possible unique count
        start = v  # Set start of current interval
    else:
        l.append(i)  # Continue adding to same group
        p += 1  # Increase the target value to maintain uniqueness

# Process the last group
ans += sub(l, start)
print(ans)


# https://github.com/VaHiX/codeForces/