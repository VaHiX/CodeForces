# Problem: CF 2006 B - Iris and the Tree
# https://codeforces.com/contest/2006/problem/B

"""
B. Iris and the Tree

Purpose:
This code solves the problem of updating edge weights in a tree and computing the sum 
of maximum distances between consecutive vertices (in cyclic order) after each update.
The algorithm uses tree traversal techniques to compute for each node, the maximum 
possible value of an ancestor in its subtree (Rx), and computes how many times this 
value affects the overall distance sum.

Algorithms/Techniques:
- Tree traversal using parent pointers
- Dynamic programming for computing Rx array
- Efficient updates using counting and incremental calculation

Time Complexity: O(n) per test case, where n is the number of nodes.
Space Complexity: O(n) for storing arrays and tree structure.

"""

import sys

def main():
    input = sys.stdin.read().split()
    ptr = 0
    t = int(input[ptr])  # Read number of test cases
    ptr += 1
    for _ in range(t):
        n, w = int(input[ptr]), int(input[ptr + 1])  # Read n (nodes) and total weight w
        ptr += 2
        p = [0] * (n + 1)  # Parent array to store parent of each node
        for i in range(2, n + 1):
            p[i] = int(input[ptr])  # Populate parent information
            ptr += 1
        children = [[] for _ in range(n + 1)]  # Build adjacency list for children
        for i in range(2, n + 1):
            children[p[i]].append(i)
        
        # Rx[x] stores the maximum vertex number among x and all its descendants
        Rx = [0] * (n + 1)
        for x in range(n, 0, -1):  # Traverse from leaves to root
            Rx[x] = x  # Initialize with x itself
            for c in children[x]:  # Update based on children
                if Rx[c] > Rx[x]:
                    Rx[x] = Rx[c]

        # C[pair] stores how many times a particular pair (in terms of indices) is considered
        C = [0] * (n + 2)
        for x in range(2, n + 1):
            pair1 = x - 1
            pair2 = Rx[x]
            C[pair1] += 1
            C[pair2] += 1

        # processed_count tracks how many times a node's contribution has been added
        processed_count = [0] * (n + 2)
        K = n  # Initially all vertices contribute to distance sum
        S = 0  # Sum of known t values
        output = []
        
        for __ in range(n - 1):
            x = int(input[ptr])  # Read vertex whose weight is being updated
            y = int(input[ptr + 1])  # Read new value of that weight
            ptr += 2
            
            pair1 = x - 1
            pair2 = Rx[x]
            for pair in [pair1, pair2]:
                processed_count[pair] += 1
                if processed_count[pair] == C[pair]:  # If all instances of this pair are seen
                    K -= 1  # Reduce effective K (nodes no longer contributing)
            
            S += y  # Update sum of weights used so far
            W_total = w - S  # Remaining weight that can be freely assigned
            ans = 2 * S + W_total * K  # Compute final answer using formula derived
            output.append(str(ans))
        
        print(" ".join(output))

if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/