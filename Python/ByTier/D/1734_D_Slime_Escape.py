# Problem: CF 1734 D - Slime Escape
# https://codeforces.com/contest/1734/problem/D

"""
Slime Escape Problem

Algorithm:
- We simulate the process of moving towards either escape (0 or n+1) while absorbing slimes.
- At each step, we try to move in the direction that allows us to maintain non-negative health.
- The key insight is to determine how much health we can gain from absorbing slimes on each side.
- We use a greedy approach: at each step, we move towards the side (left or right) that allows us to maximize our potential health gain while ensuring we never go negative.

Time Complexity: O(n) - Each slime is visited at most once during the simulation
Space Complexity: O(1) - Only a few variables are used regardless of input size

"""

I = lambda: int(input())
Is = lambda: map(int, input().split())
Li = lambda: list(map(int, input().split()))


def solve():
    n, k = Is()  # n: number of slimes, k: position of our slime
    a = Li()  # a: health of each slime
    r = k  # r: right pointer (initially at our slime)
    k -= 1  # k: 0-based index of our slime
    l = k - 1  # l: left pointer (one position to the left of our slime)
    vl = 0  # vl: maximum health we can gain from absorbing slimes to the left
    vr = 0  # vr: maximum health we can gain from absorbing slimes to the right
    x = 0  # x: cumulative health gain from left side
    y = 0  # y: cumulative health gain from right side
    
    # Greedily move towards escapes while maintaining non-negative health
    while l >= 0 or r < n:
        # Try moving left if we can do so without going negative health
        if l >= 0 and (a[k] + a[l] + x + vr) >= 0:
            x += a[l]  # absorb slime at l
            vl = max(vl, x)  # update maximum left gain
            l -= 1  # move left pointer
        # Try moving right if we can do so without going negative health
        elif r < n and (a[k] + a[r] + y + vl) >= 0:
            y += a[r]  # absorb slime at r
            vr = max(vr, y)  # update maximum right gain
            r += 1  # move right pointer
        else:
            # Cannot proceed further, we can't escape
            break
    
    # If we reached an escape (l < 0 or r >= n), we win
    if l < 0 or r >= n:
        print("YES")
        return
    else:
        print("NO")
    return 1


t = I()
while t:
    solve()
    t -= 1


# https://github.com/VaHiX/CodeForces/