# Problem: CF 2025 D - Attribute Checks
# https://codeforces.com/contest/2025/problem/D

"""
Algorithm: Dynamic Programming with Segment Tree Optimization
Approach:
- We process the records sequentially, handling point acquisitions and attribute checks.
- For each point acquisition (r == 0), we update our DP table accordingly.
- For attribute checks (r != 0), we use a segment tree technique to efficiently track
  how many checks can be passed by allocating points optimally.
- The DP array `d[i]` represents the maximum number of checks that can be passed
  when we have `i` points allocated to Strength.
- The `add` array is used to implement a difference array technique for range updates.

Time Complexity: O(n * log(n))
Space Complexity: O(n)
"""

n, m = map(int, input().split())
rs = map(int, input().split())
d = [-int(1e9)] * (m + 1)  # DP array to store max checks for i points spent on Strength
d[0] = 0
add = [0] * (m + 2)  # Difference array for efficient range updates


def addSegment(l, r):
    # Mark the range [l, r] for incrementing in the difference array
    if l <= r:
        add[l] += 1
        add[r + 1] -= 1


def pushAll():
    # Apply the difference array updates to actual DP array
    sum = 0
    for i in range(m + 1):
        sum += add[i]
        d[i] += sum
    for i in range(m + 2):
        add[i] = 0


cntPoints = 0  # Counter for number of points currently acquired
for r in rs:
    if r == 0:
        # Process a point acquisition
        pushAll()
        # Update DP: for each possible number of points spend on Strength,
        # keep the best result (maximize number of passed checks)
        for i in range(m, 0, -1):
            d[i] = max(d[i], d[i - 1])
        cntPoints += 1
    else:
        # Process an attribute check
        lf, rg = 0, 0
        if r > 0:
            # Intelligence check: need at least |r| Intelligence
            # So allocate at least |r| to Intelligence => at most m - |r| to Strength
            lf = min(r, m + 1)
            rg = m
        else:
            # Strength check: need at least |r| Strength
            # The available points to spend on Strength are cntPoints + r (negative value represents needed points)
            lf = 0
            rg = max(-1, cntPoints + r)
        addSegment(lf, rg)  # Mark the range where we could place points to satisfy this check

pushAll()
print(max(d))  # Return the maximum number of checks we can pass


# https://github.com/VaHiX/CodeForces/