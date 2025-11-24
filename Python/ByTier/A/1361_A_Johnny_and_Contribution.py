# Problem: CF 1361 A - Johnny and Contribution
# https://codeforces.com/contest/1361/problem/A

from collections import defaultdict, deque

def main():
    n, m = map(int, input().split())
    
    # Build adjacency list
    adj = [[] for _ in range(n)]
    for _ in range(m):
        a, b = map(int, input().split())
        a -= 1
        b -= 1
        adj[a].append(b)
        adj[b].append(a)
    
    # Read topic assignments
    topics = list(map(int, input().split()))
    
    # Group nodes by their topics (0-indexed)
    topic_nodes = [[] for _ in range(n)]
    for i in range(n):
        topic_nodes[topics[i] - 1].append(i)
    
    # Result array to store the order
    result = []
    
    # For each topic in order (1 to n)
    for topic in range(n):
        # Check all nodes with current topic
        for node in topic_nodes[topic]:
            # Collect topics of neighbors
            neighbor_topics = set()
            for neighbor in adj[node]:
                neighbor_topics.add(topics[neighbor])
            
            # Find minimum missing topic number
            min_missing = 1
            while min_missing in neighbor_topics:
                min_missing += 1
            
            # If this doesn't match our expected topic, impossible
            if min_missing != topic + 1:
                print(-1)
                return
            
            # Add to result
            result.append(node + 1)
    
    print(*result)

if __name__ == "__main__":
    main()

# **Explanation:**
# 1. Read input to build graph and topic assignments
# 2. Group nodes by their topic numbers (1-indexed)
# 3. Process nodes in topic order (1 to n)
# 4. For each node, find all topics in its neighborhood
# 5. Calculate minimum missing topic number
# 6. If it doesn't match expected topic number, return impossible (-1)
# 7. Otherwise, add node to result order

# **Time Complexity:** O(V + E) where V is vertices and E is edges
# **Space Complexity:** O(V + E) for graph representation and auxiliary arrays


# https://github.com/VaHiX/CodeForces/