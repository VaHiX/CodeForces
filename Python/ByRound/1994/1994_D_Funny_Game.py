# Problem: CF 1994 D - Funny Game
# https://codeforces.com/contest/1994/problem/D

"""
Code Purpose:
This code solves the "Funny Game" problem where we need to construct a connected graph by adding edges between vertices based on divisibility conditions.
The algorithm uses a greedy approach:
1. For each operation x (from n-1 down to 1), we try to find two vertices u and v such that |a[u] - a[v]| is divisible by x.
2. We group vertices by their remainder when divided by x (mod x).
3. If two vertices in the same group are found, we connect them.
4. If no such pair exists for any x, we output "NO".
5. Finally, ensure we've added exactly n-1 edges to form a connected graph.

Algorithms/Techniques:
- Modular arithmetic for grouping vertices
- Greedy edge selection
- Iterative approach from largest to smallest operation number

Time Complexity: O(n^2) in worst case (due to nested loops and list operations)
Space Complexity: O(n) for storing arrays and intermediate results

"""

def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    idx = 0
    tests = int(data[idx])
    idx += 1
    results = []
    for _ in range(tests):
        n = int(data[idx])
        idx += 1
        a = list(map(int, data[idx : idx + n]))
        idx += n
        pos = list(range(n)) # Positions of vertices not yet connected
        ans = []
        for i in range(n - 1, 0, -1): # Iterate from n-1 down to 1
            occ = [-1] * i # Track last seen position for each mod value
            found = False
            for j in pos: # For each remaining vertex
                mod_val = a[j] % i # Calculate remainder
                if occ[mod_val] != -1: # If we've seen another vertex with same mod
                    ans.append((j, occ[mod_val])) # Add edge
                    pos.remove(j) # Remove vertex from unconnected set
                    found = True
                    break
                occ[mod_val] = j # Mark this vertex as seen for this mod
            if not found: # No suitable pair found
                results.append("NO")
                break
        if len(ans) == n - 1: # If all n-1 edges added successfully
            results.append("YES")
            ans.reverse() # Reverse to get correct operation order
            results.extend(f"{x + 1} {y + 1}" for x, y in ans) # Convert to 1-indexed output
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/