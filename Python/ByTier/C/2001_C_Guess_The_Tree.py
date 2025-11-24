# Problem: CF 2001 C - Guess The Tree
# https://codeforces.com/contest/2001/problem/C

"""
Algorithm: Guess The Tree
Techniques: Interactive Tree Construction with Queries
Time Complexity: O(n^2) in worst case due to nested queries and DFS
Space Complexity: O(n) for storing visited nodes and edges

The problem involves reconstructing a tree structure using distance queries.
We use a DFS-based approach to explore and identify edges in the tree.
By querying pairs of nodes and analyzing the response, we can determine
which node minimizes the distance difference, helping us identify
the structure of the tree.
"""

def ask(a, b):
    """
    Function to perform the query and return the response.
    Queries the distance minimizing node between nodes a and b.
    """
    print(f"? {a } {b }")
    response = int(input())
    return response


def dfs(v, u, visited, edges):
    """
    Depth-First Search to explore the tree structure.
    v: current node being explored
    u: node to connect with v
    visited: list to track visited nodes
    edges: list to store the discovered edges
    """
    if visited[u]:
        return

    x = ask(u, v)

    if x == u:
        # If x equals u, it means u is on the path between v and some other node
        # and we can directly add this edge
        visited[u] = True
        edges.append((u, v))
        return

    # Continue DFS exploration
    dfs(v, x, visited, edges)
    dfs(x, u, visited, edges)


def test_case():
    """
    Handles a single test case.
    Reads the number of nodes and determines the tree structure.
    """
    n = int(input())

    visited = [False] * (n + 1)
    edges = []

    visited[1] = True

    for i in range(2, n + 1):
        # For each unvisited node, perform DFS to find its connection
        dfs(1, i, visited, edges)

    print("!", " ".join(f"{u } {v }" for u, v in edges))


def main():
    """
    Main function to handle multiple test cases.
    """
    t = int(input())
    for _ in range(t):
        test_case()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/