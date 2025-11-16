# Problem: CF 1970 C1 - Game on Tree (Easy)
# https://codeforces.com/contest/1970/problem/C1

"""
Algorithm: Game on Tree (Easy)
Techniques: Tree traversal, parity analysis

Time Complexity: O(n) - We traverse the tree from the starting node to find the path,
                        which in the worst case visits all nodes.
Space Complexity: O(n) - The adjacency list representation of the tree uses O(n) space.

This solution treats the tree as a linear array since it has exactly two leaves.
The game is modeled by counting the number of steps from the starting node to the end of the tree,
and using parity (even/odd) to determine the winner based on optimal play.
"""

def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    index = 0
    n = int(data[index])  # Read number of nodes
    int(data[index + 1])  # Read number of rounds (but t=1)
    index += 2
    g = [0] * (n + 1)  # Build a simple parent array to represent the tree as a path
    for _ in range(n - 1):
        x = int(data[index])  # Read edge endpoint x
        y = int(data[index + 1])  # Read edge endpoint y
        index += 2
        # Store the neighbor of x (since it's a path, one node points to another)
        g[x] = y
    u = int(data[index])  # Starting node for current round
    c = 0  # Counter for steps taken
    # Traverse from the starting node to the end of the path
    while g[u] != 0:
        u = g[u]  # Move to the next node in the path
        c += 1  # Increment step count
    # Determine winner based on parity of steps and remaining nodes
    # c is number of steps to reach an endpoint
    # n - c - 1 is number of remaining nodes after taking c steps from start
    # If both values are even, Hermione wins; otherwise Ron wins
    if c % 2 == 0 and (n - c - 1) % 2 == 0:
        print("Hermione")
    else:
        print("Ron")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/