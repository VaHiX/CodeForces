# Problem: CF 1781 G - Diverse Coloring
# https://codeforces.com/contest/1781/problem/G

"""
Code Purpose:
This code solves the "G. Diverse Coloring" problem where we need to find the minimum disbalance 
in a binary tree's coloring after each vertex addition. The disbalance is defined as the absolute 
difference between the number of white and blue vertices. Each vertex must have at least one 
neighbor with a different color (diverse coloring).

Algorithms/Techniques:
- Tree construction from parent information
- Greedy approach based on vertex degrees to minimize disbalance
- Dynamic programming/assignment of colors based on degree ordering
- Special handling for edge cases like 4-node trees and specific degree configurations

Time Complexity: O(n log n) due to sorting of vertices by degree
Space Complexity: O(n) for storing tree structure and auxiliary arrays
"""

import sys


def read():
    s = 0
    w = 1
    ch = sys.stdin.read(1)
    while ch < "0" or ch > "9":
        if ch == "-":
            w = -1
        ch = sys.stdin.read(1)
    while "0" <= ch <= "9":
        s = s * 10 + ord(ch) - ord("0")
        ch = sys.stdin.read(1)
    return s * w


fa = [0] * 1000003  # Parent of each vertex
deg = [0] * 1000003  # Degree of each vertex (number of children)
ls = [0] * 1000003   # Left child of each vertex  
rs = [0] * 1000003   # Right child of each vertex
flg = [0] * 1000003  # Flag to mark if vertex is processed
ans = [0] * 1000003  # Color assignment (0 = blue, 1 = white) for each vertex


def main():
    T = read()
    for _ in range(T):
        n = read()

        # Initialize arrays for current test case
        for i in range(1, n + 1):
            deg[i] = ls[i] = rs[i] = 0
            flg[i] = ans[i] = 0

        # Build tree structure from parent information
        for i in range(2, n + 1):
            fa[i] = read()
            if ls[fa[i]]:  # If left child exists, set right child
                rs[fa[i]] = i
            else:  # Otherwise set left child
                ls[fa[i]] = i

        # Print intermediate disbalance values
        # This seems like placeholder code or debugging output
        for i in range(2, n + 1):
            if i == 4:
                print((fa[3] == fa[4]) << 1)
            else:
                print(i & 1)

        # Special case handling for n=4
        if n == 4 and fa[3] == fa[4]:
            print("wbww")
            continue

        # Calculate degrees of all vertices
        for i in range(n, 1, -1):  # Process from n down to 2
            if not flg[i]:  # If not yet processed
                deg[fa[i]] += 1  # Increment parent's degree
                flg[fa[i]] = 1   # Mark parent as processed

        # Process root (vertex 1) if not processed
        if not flg[1]:
            if deg[2] == 2 and rs[1] and deg[rs[1]] == 1:
                # Special case for degree configuration
                deg[1] = deg[rs[1]] + 1
                deg[rs[1]] = 0
                flg[rs[1]] = 0
                flg[1] = 1
                ans[1] = 1
            else:
                deg[1] = deg[2] + 1
                deg[2] = 0
                flg[2] = 0
                flg[1] = 1
                ans[1] = 1

                # Additional handling for specific degree configurations
                if deg[1] == 3 and not rs[1]:
                    ok = 0
                    for i in range(2, n + 1):
                        if deg[i] == 2:
                            ok = 1
                    if not ok:
                        x = y = 0
                        # Find children of left child of vertex 2
                        if ls[ls[2]]:
                            x, y = ls[2], ls[ls[2]]
                        if rs[ls[2]]:
                            x, y = ls[2], rs[ls[2]]
                        if ls[rs[2]]:
                            x, y = rs[2], ls[rs[2]]
                        if rs[rs[2]]:
                            x, y = rs[2], rs[rs[2]]

                        deg[1] -= 1
                        flg[x] = 1
                        flg[y] = 0
                        ans[x] = 1
                        deg[x] = deg[y] + 1
                        deg[y] = 0

        # Collect vertices with degree > 1 for processing
        vec = []
        for i in range(1, n + 1):
            if deg[i] > 1:
                vec.append((deg[i] - 1, i))

        # Sort vertices by degree (descending)
        vec.sort(reverse=True)

        # Greedily assign colors to minimize disbalance
        total_sum = 0
        for x, y in vec:
            if total_sum > 0:
                total_sum -= x
                ans[y] ^= 1  # Toggle color
            else:
                total_sum += x

        # Assert correctness of final sum (should match parity of n)
        assert total_sum == (n & 1)

        # Assign colors to remaining unassigned vertices (based on parent)
        for i in range(2, n + 1):
            if not flg[i]:
                ans[i] = ans[fa[i]] ^ 1  # Inherit opposite color from parent

        # Format output string and validate result
        S = sum(ans[1 : n + 1])  # Count white vertices
        for i in range(1, n + 1):
            print("w" if ans[i] else "b", end="")  # Output coloring

        real = abs(S * 2 - n)  # Calculate actual disbalance
        assert real == total_sum  # Validate

        print("")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/