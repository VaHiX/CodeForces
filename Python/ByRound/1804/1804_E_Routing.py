# Problem: CF 1804 E - Routing
# https://codeforces.com/contest/1804/problem/E

"""
Code Purpose:
This code solves the WRP (Weird Routing Protocol) routing problem on a network of servers. 
The goal is to assign an auxiliary server a(u) for each server u such that any server can 
reach any other server using the specified routing procedure. This is done by finding a 
valid assignment of neighbors as auxiliary servers that ensures reachability.

Algorithms/Techniques:
- Depth-First Search (DFS) using a bootstrap technique for iterative DFS
- Bitmasking to track visited states in DFS
- Backtracking to explore possible assignments
- Graph traversal to check connectivity and cycle detection

Time Complexity: O(n * 2^n) where n is the number of nodes, due to bitmasking and DFS exploration
Space Complexity: O(n * 2^n) for the note and circles arrays to store visited states and cycle detection
"""

from types import GeneratorType


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
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


n, m = map(int, input().split())
path = [[] for _ in range(n)]
for _ in range(m):
    u, v = map(lambda x: int(x) - 1, input().split())
    path[u].append(v)
    path[v].append(u)


def check():
    # Check if a valid assignment has been found
    new_ans = ans[:]
    for i in range(n):
        if ans[i] is None:
            for x in path[i]:
                if ans[x] is not None:
                    new_ans[i] = x
                    break
            else:
                return
    print("Yes")
    print(*[x + 1 for x in new_ans])
    exit()


@bootstrap
def dfs(u, mask):
    # Mark current state as visited
    note[u][mask] = 1
    for v in path[u]:
        # If v is a valid neighbor to set as auxiliary
        if v > i and (mask >> v) & 1 == 0 and not note[v][mask + (1 << v)]:
            ans[u] = v
            # Recursively explore this state
            yield dfs(v, mask + (1 << v))
            # Backtrack
            ans[u] = None
        # If it's a cycle detection case
        if v == i and not circles[mask]:
            circles[mask] = 1
            ans[u] = i
            check()
            ans[u] = None
    yield


ans = [None] * n
note = [[0] * (1 << n) for _ in range(n)]
circles = [0] * (1 << n)
for i in range(n):
    dfs(i, 1 << i)
print("No")


# https://github.com/VaHiX/CodeForces/