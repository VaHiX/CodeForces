# Problem: CF 2139 B - Cake Collection
# https://codeforces.com/contest/2139/problem/B

"""
B. Cake Collection
Algorithm: Greedy approach with sorting
- Sort ovens by baking rate in descending order
- For each of the first m seconds, select the oven with highest remaining cake count
- The contribution of an oven at second i is a[i] * (m - i), where i is the index of selection
- Time Complexity: O(n log n) per test case due to sorting
- Space Complexity: O(1) excluding input storage
Techniques:
- Greedy selection: Always pick the oven that will yield maximum cakes in remaining time
- Sorting to prioritize high-yield ovens
"""

for _ in range(int(input())):  # Read number of test cases
    n, m = map(int, input().split())  # Read n (ovens) and m (seconds)
    arr = sorted(map(int, input().split()), reverse=True)  # Sort baking rates in descending order
    ans = 0  # Initialize total cakes collected
    for i in range(min(n, m)):  # Iterate through the first min(n, m) seconds
        ans += arr[i] * (m - i)  # Add contribution of oven i at second i
    print(ans)  # Print maximum cakes collected


# https://github.com/VaHiX/codeForces/