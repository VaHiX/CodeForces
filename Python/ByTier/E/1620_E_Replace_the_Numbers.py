# Problem: CF 1620 E - Replace the Numbers
# https://codeforces.com/contest/1620/problem/E

"""
Algorithm: Reverse Processing with Map
Techniques: Hash Map (Dictionary), Reverse Iteration

Time Complexity: O(q), where q is the number of queries. Each query is processed in O(1) amortized time due to use of hash map.
Space Complexity: O(U), where U is the number of unique values in the array at any point in time.

The algorithm processes queries in reverse order. For type 1 queries, it records the value. For type 2 queries, it updates a mapping from old value to new value. 
When processing in reverse, we use the mapping to determine what value should be in the final array.
"""

n = int(input())
q = [list(map(int, input().split())) for i in range(n)]
d = {}  # Dictionary to store replacement mappings
ans = []  # List to store the result in reverse order

# Process queries in reverse
for i in range(n - 1, -1, -1):
    if len(q[i]) == 2:  # Type 1 query: add element
        x = q[i][1]
        # Get the final value of x, using mapping d, or x itself if not mapped
        ans.append(d.get(x, x))
    else:  # Type 2 query: replace all occurrences
        x, y = q[i][1:]  # x is the value to be replaced, y is the replacement
        # Update mapping: x will map to y (or y's final value if y is also mapped)
        d[x] = d.get(y, y)

# Print result in correct order (reverse the ans array)
print(*ans[::-1])


# https://github.com/VaHiX/CodeForces/