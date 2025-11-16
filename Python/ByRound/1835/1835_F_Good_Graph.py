# Problem: CF 1835 F - Good Graph
# https://codeforces.com/contest/1835/problem/F

"""
Algorithm: Bipartite Graph Goodness Check and Optimization
Techniques: 
- Hall's Marriage Theorem for checking if a bipartite graph is "good"
- Augmenting path algorithm to find maximum matching
- Tarjan's algorithm for finding Strongly Connected Components (SCCs)
- Graph contraction and edge addition to minimize edges while preserving tight sets

Time Complexity: O(n^3) - The worst case involves augmenting paths and Tarjan's SCC algorithm
Space Complexity: O(n^2) - For storing adjacency lists, matching, and SCC-related data structures

The problem is to determine if a bipartite graph is "good", meaning that for all subsets S of left vertices, |S| <= |N(S)|. 
If good, find a minimal edge graph with same tight sets; otherwise, find a violating subset.
"""

def solve_good_graph():
    n, m = map(int, input().split())
    graph = [set() for _ in range(n + 1)]

    for _ in range(m):
        u, v = map(int, input().split())
        graph[u].add(v - n)  # Convert right vertex to 1-based index in range [1,n]

    matching = [0] * (n + 1)
    rev_matching = [0] * (n + 1)

    def augment(u, visited):
        """Find an augmenting path starting from vertex u in L."""
        for v in graph[u]:
            if not visited[v]:
                visited[v] = True
                if matching[v] == 0 or augment(matching[v], visited):
                    matching[v] = u
                    rev_matching[u] = v
                    return True
        return False

    unmatched_set = []
    for i in range(1, n + 1):
        visited = [False] * (n + 1)
        if not augment(i, visited):

            unmatched_set = [i]

            for j in range(1, n + 1):
                if matching[j] and visited[j]:
                    unmatched_set.append(matching[j])

            print("NO")
            print(len(unmatched_set))
            print(" ".join(map(str, unmatched_set)))
            return

    print("YES")

    # Create a directed graph representing the difference between the original graph and the matching
    directed_graph = [[] for _ in range(n + 1)]
    for u in range(1, n + 1):
        for v in graph[u]:
            if matching[v] != u:  # If u is not matched to v through the matching
                directed_graph[u].append(matching[v])  # Add edge from u to the matched vertex of v

    graph = None  # Free up memory

    def tarjan_scc():
        scc = []
        index = {}
        lowlink = {}
        stack = []
        onstack = set()
        current_index = 0

        def strongconnect(v):
            nonlocal current_index
            index[v] = current_index
            lowlink[v] = current_index
            current_index += 1
            stack.append(v)
            onstack.add(v)

            for w in directed_graph[v]:
                if w not in index:
                    strongconnect(w)  # Continue DFS
                    lowlink[v] = min(lowlink[v], lowlink[w])
                elif w in onstack:  # Back edge
                    lowlink[v] = min(lowlink[v], index[w])

            if lowlink[v] == index[v]:
                component = []
                while True:
                    w = stack.pop()
                    onstack.remove(w)
                    component.append(w)
                    if w == v:
                        break
                scc.append(component)

        for v in range(1, n + 1):
            if v not in index:
                strongconnect(v)

        return scc

    sccs = tarjan_scc()

    vertex_to_scc = {}
    for i, component in enumerate(sccs):
        for v in component:
            vertex_to_scc[v] = i

    scc_graph = [set() for _ in range(len(sccs))]
    for u in range(1, n + 1):
        u_scc = vertex_to_scc[u]
        for v in directed_graph[u]:
            v_scc = vertex_to_scc[v]
            if u_scc != v_scc:
                scc_graph[u_scc].add(v_scc)

    directed_graph = None  # Free up memory

    scc_reachable = [set() for _ in range(len(sccs))]
    for start_scc in range(len(sccs)):

        stack = [start_scc]
        visited = {start_scc}

        while stack:
            current_scc = stack.pop()
            scc_reachable[start_scc].add(current_scc)

            for next_scc in scc_graph[current_scc]:
                if next_scc not in visited:
                    visited.add(next_scc)
                    stack.append(next_scc)

    new_edges = []

    # Add edges from the original matching
    for i in range(1, n + 1):
        new_edges.append((i, rev_matching[i] + n))

    # Add edges inside SCC cycles
    for component in sccs:
        if len(component) > 1:
            for i in range(len(component)):
                u = component[i]
                v = component[(i + 1) % len(component)]
                new_edges.append((u, rev_matching[v] + n))

    # Connect SCCs to ensure all edges are preserved
    for i in range(len(sccs)):

        if len(sccs[i]) == 1 and len(scc_reachable[i]) == 1:
            continue  # Skip isolated SCCs

        targets = scc_reachable[i].copy()
        targets.discard(i)

        if not targets:
            continue

        targets_list = list(targets)
        targets_list.sort(key=lambda x: len(scc_reachable[x]), reverse=True)

        covered = {i}

        for target in targets_list:
            if target not in covered:

                u = sccs[i][0]
                v = sccs[target][0]
                new_edges.append((u, rev_matching[v] + n))

                covered.add(target)
                covered.update(scc_reachable[target])

    new_edges_set = set(new_edges)

    print(len(new_edges_set))
    for u, v in new_edges_set:
        print(f"{u } {v }")


if __name__ == "__main__":
    solve_good_graph()


# https://github.com/VaHiX/CodeForces/