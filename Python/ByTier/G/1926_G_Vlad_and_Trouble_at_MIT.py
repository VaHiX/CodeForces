# Problem: CF 1926 G - Vlad and Trouble at MIT
# https://codeforces.com/contest/1926/problem/G

"""
Problem: Vlad and Trouble at MIT
Algorithm: Tree Dynamic Programming (DP)
Time Complexity: O(n) per test case, where n is the number of vertices
Space Complexity: O(n) for storing the DP arrays and parent information

This solution uses a post-order tree DP approach to determine the minimum number 
of thick walls needed to separate partying students (P) from sleepy students (S).
The idea is to traverse the tree from leaves to root and for each node compute:
- dp0[i]: minimum thick walls needed if node i is a "party" node (can play music)  
- dp1[i]: minimum thick walls needed if node i is a "sleep" node (cannot hear music)

For each node, we consider all its children and decide whether to place a thick wall
on the edge connecting the child to the parent to ensure music doesn't reach sleepers.
"""

def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    INF = 1 << 61
    idx = 0
    t = int(data[idx])
    idx += 1
    out_lines = []

    def fun(n, parents, s):
        # dp0[i] represents min thick walls if we allow music at node i (P or C)
        # dp1[i] represents min thick walls if we forbid music at node i (S or C)
        dp0 = [0] * n
        dp1 = [0] * n
        
        # Traverse from leaves to root (post-order)
        for i in range(n - 1, -1, -1):
            if s[i] == "S":
                # If student is sleepy, force dp1[i] to INF (no way to let music through)
                dp1[i] = INF
            elif s[i] == "P":
                # If student wants to party, force dp0[i] to INF (can't block their music)
                dp0[i] = INF
                
            p = parents[i]
            if p >= 0:
                # Update parent's DP values with contributions from current node
                # dp0[p] + min(dp0[i], 1 + dp1[i]): no thick wall on edge (let child contribute)
                # dp1[p] + min(1 + dp0[i], dp1[i]): place thick wall (block music)
                dp0[p] += min(dp0[i], 1 + dp1[i])
                dp1[p] += min(1 + dp0[i], dp1[i])
                
        # Return the minimum thick walls needed for the root node
        return min(dp0[0], dp1[0])

    for _ in range(t):
        n = int(data[idx])
        idx += 1
        parents = [-1] + [int(data[idx + i]) - 1 for i in range(n - 1)]
        idx += n - 1
        s = data[idx]
        idx += 1
        res = fun(n, parents, s)
        out_lines.append(str(res))
    sys.stdout.write("\n".join(out_lines) + "\n")


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/