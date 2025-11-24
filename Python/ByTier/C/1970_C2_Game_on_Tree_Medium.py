# Problem: CF 1970 C2 - Game on Tree (Medium)
# https://codeforces.com/contest/1970/problem/C2

"""
Algorithm: Game on Tree (Medium)
Purpose: Determine the winner of a game played on a tree where two players (Ron and Hermione) 
         take turns moving a stone from one node to an adjacent inactive node. 
         The player who cannot make a move loses.

Techniques:
- Depth-First Search (DFS) with game theory (minimax-like approach)
- Tree traversal to simulate the game state
- Game state evaluation based on optimal play

Time Complexity: O(n) where n is the number of nodes in the tree. Each node is visited exactly once.
Space Complexity: O(n) for adjacency list, visited set, and recursion stack.
"""

def game_on_tree_winner(n, edges, initial_stone):
    # Build adjacency list representation of the tree
    adj_list = [[] for _ in range(n + 1)]
    for u, v in edges:
        adj_list[u].append(v)
        adj_list[v].append(u)
    
    visited = set()

    # Recursive DFS to determine the winner from a given node
    def dfs(player, node):
        # Mark current node as visited to avoid cycles
        visited.add(node)
        # Switch to the other player (0 -> 1, 1 -> 0)
        next_player = 1 - player
        # Traverse all neighbors
        for neighbor in adj_list[node]:
            if neighbor not in visited:
                # Recursively check result of moving to this neighbor
                winner = dfs(next_player, neighbor)
                # If the result is the current player's win, return it
                if winner == player:
                    return winner
        # If no move leads to current player's win, opponent wins
        return next_player

    # Start the game with Ron (player 0) at the initial stone position
    return "Ron" if dfs(0, initial_stone) == 0 else "Hermione"


# Read input
n, t = map(int, input().split())
edges = [tuple(map(int, input().split())) for _ in range(n - 1)]
initial = int(input())
print(game_on_tree_winner(n, edges, initial))


# https://github.com/VaHiX/CodeForces/