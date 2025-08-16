# Contest 2120, Problem F: Superb Graphs
# URL: https://codeforces.com/contest/2120/problem/F

import sys
import random

# Increase recursion limit for deep graphs that can occur in the 2-SAT solver.
sys.setrecursionlimit(605 * 2) 

class TwoSAT:
    """
    A 2-SAT solver using Kosaraju's algorithm for Strongly Connected Components.
    Variables are 0-indexed from 0 to n-1.
    A literal (var, is_neg) represents a variable or its negation.
    """
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(2 * n)]
        self.rev_graph = [[] for _ in range(2 * n)]

    def _literal_to_node(self, literal):
        var, is_negated = literal
        return var + self.n if is_negated else var

    def add_clause(self, literal1, literal2):
        """Adds a clause (literal1 OR literal2) to the instance."""
        # A clause (l1 OR l2) is equivalent to (~l1 => l2) AND (~l2 => l1).
        neg_literal1 = (literal1[0], not literal1[1])
        neg_literal2 = (literal2[0], not literal2[1])

        # Add edge for ~l1 => l2
        u, v = self._literal_to_node(neg_literal1), self._literal_to_node(literal2)
        self.graph[u].append(v)
        self.rev_graph[v].append(u)

        # Add edge for ~l2 => l1
        u, v = self._literal_to_node(neg_literal2), self._literal_to_node(literal1)
        self.graph[u].append(v)
        self.rev_graph[v].append(u)

    def solve(self):
        """Checks if the 2-SAT instance is satisfiable."""
        order = []
        visited = [False] * (2 * self.n)

        def dfs1(u):
            visited[u] = True
            for v_neighbor in self.graph[u]:
                if not visited[v_neighbor]:
                    dfs1(v_neighbor)
            order.append(u)

        for i in range(2 * self.n):
            if not visited[i]:
                dfs1(i)

        scc = [-1] * (2 * self.n)
        scc_count = 0

        def dfs2(u):
            scc[u] = scc_count
            for v_neighbor in self.rev_graph[u]:
                if scc[v_neighbor] == -1:
                    dfs2(v_neighbor)

        while order:
            u = order.pop()
            if scc[u] == -1:
                dfs2(u)
                scc_count += 1
        
        for i in range(self.n):
            if scc[i] == scc[i + self.n]:
                return False
        return True

def solve_case():
    try:
        line = sys.stdin.readline()
        if not line: return
        n, k = map(int, line.split())
    except (IOError, ValueError):
        return

    ts = TwoSAT(n)

    # Use polynomial hashing with two different random bases and moduli to avoid collisions.
    MOD1, P1 = 10**9 + 7, random.randint(n + 1, 1000)
    powers1 = [pow(P1, i, MOD1) for i in range(n)]
        
    MOD2, P2 = 10**9 + 9, random.randint(n + 1, 1000)
    powers2 = [pow(P2, i, MOD2) for i in range(n)]

    for _ in range(k):
        m_str = sys.stdin.readline()
        if not m_str.strip(): # Handles potential blank lines in input
             m_str = sys.stdin.readline()
        m = int(m_str)
        
        adj = [[False] * n for _ in range(n)]
        for _ in range(m):
            u, v = map(int, sys.stdin.readline().split())
            u -= 1
            v -= 1
            adj[u][v] = adj[v][u] = True

        hashes1 = [sum(adj[i][j] * powers1[j] for j in range(n)) % MOD1 for i in range(n)]
        hashes2 = [sum(adj[i][j] * powers2[j] for j in range(n)) % MOD2 for i in range(n)]

        for u in range(n):
            for v in range(u + 1, n):
                # Check for structural identity using hashing.
                # N(u)\{v} == N(v)\{u} is equivalent to adj[u] and adj[v] rows being
                # identical except at columns u and v.
                
                h_u1 = (hashes1[u] - (adj[u][u] * powers1[u]) - (adj[u][v] * powers1[v])) % MOD1
                h_v1 = (hashes1[v] - (adj[v][u] * powers1[u]) - (adj[v][v] * powers1[v])) % MOD1

                h_u2 = (hashes2[u] - (adj[u][u] * powers2[u]) - (adj[u][v] * powers2[v])) % MOD2
                h_v2 = (hashes2[v] - (adj[v][u] * powers2[u]) - (adj[v][v] * powers2[v])) % MOD2

                if h_u1 == h_v1 and h_u2 == h_v2:
                    # Pair (u,v) is structurally identical. Add the corresponding clause.
                    if adj[u][v]:
                        # edge (u,v) exists -> requires (B_u=IS or B_v=IS)
                        ts.add_clause((u, False), (v, False))
                    else:
                        # no edge (u,v) -> requires (B_u=CLIQUE or B_v=CLIQUE)
                        ts.add_clause((u, True), (v, True))
    
    if ts.solve():
        print("Yes")
    else:
        print("No")

def main():
    """Main function to handle multiple test cases."""
    try:
        t_str = sys.stdin.readline()
        if not t_str: return
        t = int(t_str)
        for _ in range(t):
            solve_case()
    except (IOError, ValueError):
        return

if __name__ == "__main__":
    main()
