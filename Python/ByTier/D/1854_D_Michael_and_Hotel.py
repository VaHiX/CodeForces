# Problem: CF 1854 D - Michael and Hotel
# https://codeforces.com/contest/1854/problem/D

"""
Algorithm: Find all rooms where Michael can meet Brian (room 1) using teleporters.
Technique: Binary search on teleportation paths combined with cycle detection.

Time Complexity: O(n * log(n) * log(10^9)) for queries, where n <= 500.
Space Complexity: O(n) for storing the set of reachable rooms and cycle detection.

The algorithm works by:
1. Detecting cycles in teleportation paths by checking teleportation after many steps (up to 10^7)
2. Using binary search via queries to narrow down destinations
3. Determining if a room is part of the reachable set via multiple queries with large k values
"""

n = int(input())

ops = 0


def search(u, k, l):
    """Binary search to find the destination room for a teleportation path"""
    global ops

    z = len(l)

    if z == 1:
        return l[0]

    left = l[: z // 2]
    right = l[z // 2 :]

    print("?", u, k, len(left), " ".join(map(str, left)), flush=True)
    ops += 1

    if int(input()):
        return search(u, k, left)
    else:
        return search(u, k, right)


full = False

SZ = 125

cyc = set()
for i in range(10**7, 10**7 + SZ):
    # Check for a fixed number of iterations to detect cycles
    nex = search(1, i, list(range(1, n + 1)))

    if nex in cyc:
        full = True
        break

    cyc.add(nex)

assert ops <= SZ * 9

if full:
    # If we have detected a full cycle, we'll include all rooms to check
    for i in range(1, n + 1):
        print("?", i, 10**8, len(cyc), " ".join(map(str, cyc)), flush=True)
        ops += 1
        if int(input()):
            cyc.add(i)
else:
    # If not, we still ensure full coverage up to SZ
    assert len(cyc) == SZ

    # Check remaining rooms that may be reachable
    for i in range(1, n + 1):
        if i not in cyc:
            print("?", i, 125, len(cyc), " ".join(map(str, cyc)), flush=True)
            ops += 1
            if int(input()):
                cyc.add(i)

    assert ops <= 1500

    # Further optimization if we are close to 250 reachable rooms
    if len(cyc) >= 250:
        for i in range(1, n + 1):
            if i not in cyc:
                print("?", i, 250, len(cyc), " ".join(map(str, cyc)), flush=True)
                ops += 1
                if int(input()):
                    cyc.add(i)

        assert ops <= 1500 + 250

        for i in range(1, n + 1):
            if i not in cyc:
                print("?", i, 10**8, len(cyc), " ".join(map(str, cyc)), flush=True)
                ops += 1
                if int(input()):
                    cyc.add(i)
    else:
        for i in range(1, n + 1):
            if i not in cyc:
                print("?", i, 10**8, len(cyc), " ".join(map(str, cyc)), flush=True)
                ops += 1
                if int(input()):
                    cyc.add(i)

        assert ops <= 1875


assert ops <= 2000
print("!", len(cyc), " ".join(map(str, cyc)))


# https://github.com/VaHiX/CodeForces/