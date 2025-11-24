# Problem: CF 2035 E - Monster
# https://codeforces.com/contest/2035/problem/E

from sys import stdin, stdout

t = int(stdin.readline())
for _ in range(t):
    x, y, z, k = [int(b) for b in stdin.readline().split()]
    lowest = 10**18
    q = 0
    while True:
        # Calculate remaining health after q steps of increasing damage
        h = z - (q * (q + 1) * k) // 2
        if h <= 0:
            # If health is already depleted, compute cost of q increases + q attacks
            cost = q * y + q * k * x
            lowest = min(lowest, cost)
            break
        if q > 0:
            r = 0
        else:
            r = 1
        while True:
            # Compute damage per attack: q*k + r
            denom = q * k + r
            # Total cost: q attacks (each costing y) + attack cost for (h-1)//denom + 1 attacks + r increases (each costing x)
            cost = q * y + ((h - 1) // denom + 1) * y + denom * x
            lowest = min(lowest, cost)
            # Early termination condition
            if denom * denom >= h or r == k:
                break
            r += 1
        if r < k:
            # Try reducing r to optimize further
            for l in range(h // (q * k + r), 0, -1):
                # Re-calculate r based on l and check if it exceeds k
                r = (h - l * q * k - 1) // l + 1
                if r > k:
                    break
                # Recalculate cost with new r
                cost = q * y + ((h - 1) // (q * k + r) + 1) * y + (q * k + r) * x
                lowest = min(lowest, cost)
        q += 1
    stdout.write(str(lowest) + "\n")


# https://github.com/VaHiX/CodeForces/