# Problem: CF 2034 G1 - Simurgh's Watch (Easy Version)
# https://codeforces.com/contest/2034/problem/G1

### Code Purpose:
#This program solves the problem of coloring intervals (warrior watch segments) such that for every point in time overlapping with at least one interval, there exists at least one color that appears on exactly one interval at that point. 

### Algorithms/Techniques:
#1. **Sweep Line Algorithm** - to process intervals based on their start and end boundaries.
#2. **Greedy Color Assignment** - assigning colors based on availability and conflict resolution during sweep.
#3. **Fallback to Three Colors** - when two colors cannot resolve overlapping conflicts, a third color is utilized.

### Time and Space Complexity:
#- **Time Complexity**: $ O(n \log n) $, dominated by sorting intervals and events.
#- **Space Complexity**: $ O(n) $, for storing intervals, events, and result arrays.

import sys


def solve():
    # Read all input data at once for efficiency
    it = iter(map(int, sys.stdin.buffer.read().split()))
    t = next(it)
    o = []
    for _ in range(t):
        n = next(it)
        x = [0] * n
        y = [0] * n
        for i in range(n):
            x[i] = next(it)
            y[i] = next(it)
        # Sort intervals by start time, then end time, then index
        ord = sorted(range(n), key=lambda i: (x[i], y[i], i))
        # Check if intervals are non-overlapping
        iv = any(x[ord[i]] <= y[ord[i - 1]] for i in range(1, n))
        if not iv:
            # All intervals are non-overlapping, can use 1 color
            o.append("1")
            o.append(" ".join(["1"] * n))
            continue
        # Create event list for sweep line algorithm
        ev = []
        for i in range(n):
            # Start event: (start_time, -end_time, ~index) 
            # Negative end_time to sort properly, ~index for unique identification
            ev.append((x[i], -y[i], ~i))
            # End event: (end_time, -end_time, index)
            ev.append((y[i], -y[i], i))
        ev.sort()
        z = [0] * n  # Color assignment array
        c = [0, 0, 0]  # Counters for colors (1 and 2)
        f = [0, 0, 0]  # Furthest end_time for each color
        bad = False
        ls = None  # Last event time
        for w, _, q in ev:
            # If time changed, check if we're in a valid state for current coloring
            if ls is not None and w != ls:
                if c[1] != 1 and c[2] != 1 and (c[1] + c[2] > 0):
                    bad = True
                    break
            ls = w
            if q < 0:
                # Start event for interval i (~q is index in original array)
                i = ~q
                # Choose color, preferring color 1 or 2 if only one has 0 or >1 count
                if c[1] == 0 or c[1] > 1:
                    p = 1
                elif c[2] == 0 or c[2] > 1:
                    p = 2
                elif f[1] < f[2]:
                    p = 1
                else:
                    p = 2
                c[p] += 1
                if y[i] > f[p]:
                    f[p] = y[i]
                z[i] = p
            else:
                # End event for interval q (index in original array)
                c[z[q]] -= 1
        if not bad:
            # Successfully assigned 2 colors
            o.append("2")
            o.append(" ".join(map(str, z)))
            continue
        # If two colors is not sufficient, use three colors
        z = [0] * n
        i = 0
        ls = -(10**20)  # Last end_time processed
        nw = 1  # Current color (1 or 2, toggled with ^3)
        while i < n:
            if ls < x[ord[i]]:
                ls = x[ord[i]]
            bs = i
            # Find all overlapping intervals that have the same start or overlap
            while i < n and x[ord[i]] <= ls:
                if y[ord[i]] > y[ord[bs]]:
                    bs = i
                i += 1
            idx = ord[bs]
            z[idx] = nw
            ls = y[idx]
            nw ^= 3  # Toggle between 1 and 2
        o.append("3")
        o.append(" ".join(str(c + 1) for c in z))
    sys.stdout.write("\n".join(o))


if __name__ == "__main__":
    solve()

# https://github.com/VaHiX/CodeForces/