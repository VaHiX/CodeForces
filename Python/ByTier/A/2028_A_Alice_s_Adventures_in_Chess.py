# Problem: CF 2028 A - Alice's Adventures in ''Chess''
# https://codeforces.com/contest/2028/problem/A

"""
Alice's Adventures in "Chess"

Algorithms/Techniques:
- Simulation with periodic movement pattern
- Coordinate tracking using 2D grid operations
- Early termination when position matches target

Time Complexity: O(n * k) where n is length of string and k is the number of repetitions needed to potentially reach the target,
                 but since constraints are small (n, a, b <= 10), effectively constant time per test case.
Space Complexity: O(1) - only using fixed space variables and not storing large data structures.

"""

t = int(input())
for i in range(t):
    n, a, b = map(int, input().split())  # Read n (length of moves), a (target x), b (target y)
    s = input()
    s += s  # Double the string to avoid edge case handling for repeating
    s += s
    s += s
    s += s
    # Now s has repeated 4 times, enough to simulate more than sufficient steps
    
    pos_a = 0   # Alice's x-coordinate starting at (0, 0)
    pos_b = 0   # Alice's y-coordinate starting at (0, 0)

    for c in s:
        if c == "N":
            pos_b += 1    # Move north: increment y
        elif c == "S":
            pos_b -= 1    # Move south: decrement y
        elif c == "E":
            pos_a += 1    # Move east: increment x
        else:
            pos_a -= 1    # Move west: decrement x
            
        if pos_a == a and pos_b == b:   # Check if Alice has met the Red Queen
            print("YES")
            break
    else:
        print("NO")  # If loop completes without breaking, Alice never reaches Queen


# https://github.com/VaHiX/codeForces/