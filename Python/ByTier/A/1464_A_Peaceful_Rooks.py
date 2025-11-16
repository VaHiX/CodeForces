# Problem: CF 1464 A - Peaceful Rooks
# https://codeforces.com/contest/1464/problem/A

"""
Algorithm: 
The problem is about placing rooks on the main diagonal with minimum moves, ensuring no two rooks attack each other during the process. This is a graph problem where we treat each rook position as a node, and we follow a chain of rook placements to form cycles. The minimum steps needed to place all rooks on the diagonal corresponds to the sum of (cycle length + 1) for each cycle, because moving one rook to the diagonal requires moving all rooks in a cycle to form a valid configuration.

Time Complexity: O(n) for each test case, amortized due to each cell being processed once.
Space Complexity: O(n) for storing the positions and sets.
"""

import sys

input = lambda: sys.stdin.readline().rstrip()
write = lambda x: sys.stdout.write(x + "\n")
writef = lambda x: print("{:.12f}".format(x))
debug = lambda x: sys.stderr.write(x + "\n")
YES = "Yes"
NO = "No"
pans = lambda v: print(YES if v else NO)
inf = 10**18
LI = lambda: list(map(int, input().split()))


def debug(_l_):
    for s in _l_.split():
        print(f"{s}={eval(s)}", end=" ")
    print()


def dlist(*l, fill=0):
    if len(l) == 1:
        return [fill] * l[0]
    ll = l[1:]
    return [dlist(*ll, fill=fill) for _ in range(l[0])]


t = int(input())
for i in range(t):
    n, m = LI()
    xy = {}
    xs = set()
    for i in range(m):
        x, y = LI()
        xy[x] = y  # Store the rook's row-column mapping
        xs.add(x)  # Keep track of rows already occupied
    
    ans = 0  # Total moves needed
    while xs:  # While there are remaining rooks to move
        for u in xs:  # Pick one rook
            break
        if xy[u] == u:  # If the rook is already on the diagonal
            xs.remove(u)
            continue
        
        c = 1  # Counter for current cycle length
        cur = set([u])  # Track nodes in this cycle
        xs.remove(u)  # Remove the starting node
        while 1:
            v = xy[u]  # Get next node in the path
            if v in cur:  # We've found a cycle
                ans += c + 1  # Add the number of moves needed to resolve cycle
                break
            elif v not in xs:  # If the next node is not in the set
                ans += c  # Add current steps and finish
                break
            xs.remove(v)  # Remove node from unvisited set
            cur.add(v)  # Mark as visited in current cycle
            u = v  # Move to next node
            c += 1  # Increment the path length
    print(ans)


# https://github.com/VaHiX/CodeForces/