# Problem: CF 1817 B - Fish Graph
# https://codeforces.com/contest/1817/problem/B

"""
Algorithm: DFS-based cycle detection with backtracking to find a "fish graph"
Time Complexity: O(n + m) for each test case, where n is number of nodes and m is number of edges
Space Complexity: O(n + m) for adjacency list and visited array

A "fish graph" is defined as a simple cycle with a special node 'u' on the cycle, 
with exactly 2 additional edges connecting to node 'u', but not to any other node in the cycle.

Approach:
1. Use DFS traversal to detect cycles in the graph
2. When a back edge is found (indicating a cycle), trace the cycle path
3. Check if there are exactly 2 extra edges connecting to the special node (the start of cycle)
4. If such a configuration exists, return the edges of the fish graph
"""

from types import GeneratorType

global adj
global vis
global stk


def bootstrap(f, stack=[]):
    def wrappedfunc(*args, **kwargs):
        if stack:
            return f(*args, **kwargs)
        else:
            to = f(*args, **kwargs)
            while True:
                if type(to) is GeneratorType:
                    stack.append(to)
                    to = next(to)
                else:
                    stack.pop()
                    if not stack:
                        break
                    to = stack[-1].send(to)
            return to

    return wrappedfunc


@bootstrap
def dfs(node, par):
    for a in adj[node]:
        while stk[-1] != node:  # Clean up stack until reaching current node
            vis[stk.pop(-1)] = 2
        if a == par or vis[a] == 2:  # Skip parent or already processed node
            continue
        elif vis[a] != 0:  # Found a cycle
            s = {a}  # Set of nodes in the cycle
            i = len(stk) - 1  # Start of cycle in stack
            prev = a  # Previous node in cycle
            ans = []  # Resultant edges of fish graph
            while stk[i] != a:  # Extract the cycle path
                ans.append([prev, stk[i]])
                s.add(stk[i])
                prev = stk[i]
                i -= 1
            ans.append([prev, stk[i]])  # Add last edge of the cycle
            good = False  # Flag to check if we found 2 extra edges
            extra = []  # Store extra edges found from nodes of the cycle
            for j in range(i, len(stk)):  # Check each node in the cycle for extra edges
                num = 0
                for b in adj[stk[j]]:  # Iterate through neighbors of current node
                    if b in s:  # Skip edges within the cycle
                        continue
                    else:
                        num += 1
                        extra.append([stk[j], b])  # Record this extra edge
                        if num == 2:  # Found two extra edges
                            good = True
                            break
                if good:  # Stop checking once we have valid edges
                    break
            if good:
                ans.append(extra[-1])  # Add the last two extra edges
                ans.append(extra[-2])
                yield True, ans  # Return success and fish graph
        else:
            vis[a] = 1  # Mark node as visited
            stk.append(a)  # Add to stack
            f, ans = yield dfs(a, node)  # Recursive DFS call
            if f:
                yield f, ans  # Propagate success
    yield False, []  # Return failure if no cycle found


t = int(input())
for _ in range(t):
    n, m = map(int, input().split())
    adj = [[] for __ in range(n)]
    vis = [0] * n
    for i in range(m):
        u, v = map(int, input().split())
        adj[u - 1].append(v - 1)  # Convert to 0-indexed
        adj[v - 1].append(u - 1)
    for i in range(n):
        if vis[i] != 0:  # Skip already visited nodes
            continue
        else:
            stk = [i]  # Stack to track path during DFS
            vis[i] = 1
            f, ans = dfs(i, -1)  # Start DFS
            for a in stk:  # Mark all nodes in current component as processed
                vis[a] = 2
            if f:
                break  # Found fish graph, exit loop
    if f:
        print("YES")
        print(len(ans))
        for a in ans:
            print(a[0] + 1, a[1] + 1)  # Convert back to 1-indexed
    else:
        print("NO")


# https://github.com/VaHiX/CodeForces/