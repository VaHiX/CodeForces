# Contest 350, Problem C: Bombs
# URL: https://codeforces.com/contest/350/problem/C

import sys

def solve():
    data = sys.stdin.read().split()
    n = int(data[0])
    coords = []
    idx = 1
    for _ in range(n):
        x = int(data[idx])
        y = int(data[idx+1])
        idx += 2
        coords.append((x, y))

    # Sort by squared distance from origin
    coords.sort(key=lambda p: p[0]*p[0] + p[1]*p[1])

    out = []
    for (x, y) in coords:
        # Move from (0,0) to (x,y)
        if x < 0:
            out.append(f"1 {abs(x)} L")
        elif x > 0:
            out.append(f"1 {abs(x)} R")
        if y < 0:
            out.append(f"1 {abs(y)} D")
        elif y > 0:
            out.append(f"1 {abs(y)} U")
        
        # Pick up the bomb
        out.append("2")
        
        # Move back to (0,0)
        if y < 0:
            out.append(f"1 {abs(y)} U")
        elif y > 0:
            out.append(f"1 {abs(y)} D")
        if x < 0:
            out.append(f"1 {abs(x)} R")
        elif x > 0:
            out.append(f"1 {abs(x)} L")
        
        # Destroy the bomb
        out.append("3")

    # Print everything at once
    print(len(out))
    print("\n".join(out))
solve()