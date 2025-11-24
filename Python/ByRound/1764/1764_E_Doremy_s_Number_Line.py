# Problem: CF 1764 E - Doremy's Number Line
# https://codeforces.com/contest/1764/problem/E

"""
Algorithm: Greedy approach with sorting
Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing the array of tuples

The problem involves determining if a specific point k can be colored with color 1,
given a permutation of operations. The key insight is to simulate the process in reverse
by sorting the operations in a specific way and using a greedy approach to check
if k can be reached with the first operation (color 1).

The core idea:
1. Determine whether k can be colored with color 1 using a greedy approach.
2. Preprocess operations to sort and transform them for efficient checking.
3. Simulate the process in reverse order to check reachability.

Key transformations:
- For each operation (a_i, b_i), transform it to (-a_i - b_i, a_i)
- Sort the transformed list
- Use greedy checking with updated k value.

The condition k <= -t[0] checks if current k can be reached by the operation,
and if so, update k accordingly.
"""

t = int(input())
for cs in range(t):
    n, k = map(int, input().split())
    ab1 = tuple(map(int, input().split()))
    ab = [input() for _ in range(n - 1)]

    # If k is <= a_1, then we can color it directly with color 1
    if k <= ab1[0]:
        print("YES")
        continue
    
    # If the sum of a_1 and b_1 is less than k, it's impossible to reach k
    if sum(ab1) < k:
        print("NO")
        continue

    # Parse remaining operations
    ab = [tuple(map(int, s.split())) for s in ab]

    # Update k, transform operations
    k -= ab1[1]  # Subtract b_1 from k since we're moving backward
    ab = [(-t[0] - t[1], t[0]) for t in ab]  # Transform each (a_i, b_i) to (-a_i - b_i, a_i)
    ab.sort()  # Sort by the first element of transformed tuple

    f = False
    for i, t in enumerate(ab):
        # Check if k can be colored with current operation
        if k <= t[1] or i < n - 2 and k <= -ab[i + 1][0]:
            f = True
            break
        # If k can be reached, update k
        if k <= -t[0]:
            k += t[0] + t[1]

    print("YES" if f else "NO")


# https://github.com/VaHiX/CodeForces/