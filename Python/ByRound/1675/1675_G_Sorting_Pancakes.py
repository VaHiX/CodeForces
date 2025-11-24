# Problem: CF 1675 G - Sorting Pancakes
# https://codeforces.com/contest/1675/problem/G
 
"""
Algorithm: Dynamic Programming with Cumulative Sum Optimization
Time Complexity: O(n * m^2) where n is number of dishes and m is number of pancakes
Space Complexity: O(m^2) for the DP table
 
The problem is about making an array non-increasing with minimum moves,
where each move redistributes one pancake to an adjacent dish.
 
Approach:
1. Convert the problem into a dynamic programming task by tracking how many pancakes
   are placed at each position and how much cost it takes to reach that state.
2. Use a cumulative sum technique to compute costs quickly for ranges.
3. For each dish from right to left, calculate the minimum moves needed to distribute
   the pancakes to form a non-increasing sequence.
 
Key steps:
- Reverse the array to process from right to left (more intuitive for DP).
- Precompute positions of all pancakes.
- Use DP to track minimum cost to place k pancakes at the last i dishes.
- Use cumulative sums to speed up cost calculations.
"""
 
n, m = map(int, input().split())
a = list(map(int, input().split()))[::-1] # Reverse the array for easier processing from right to left
 
# Create list of positions for all pancakes (0-indexed from right)
id = []
for i in range(n):
    for _ in range(a[i]):
        id.append(i)
 
inf = 10**5
# dp[j][k] represents minimum moves to place j pancakes in last k dishes
dp = [[inf] * (m + 1) for i in range(m + 1)]
dp[0][0] = 0 # Base case: 0 pancakes, 0 dishes used = 0 moves
 
for i in range(n):
    # Compute cost for moving all pancakes to position i
    cost = []
    for j in id:
        cost.append(abs(i - j))
    
    # Build cumulative sum array for cost
    cum = [0]
    tmp = 0
    for j in cost:
        tmp += j
        cum.append(tmp)
 
    # Create new DP table for next iteration
    dp_new = [[inf] * (m + 1) for i in range(m + 1)]
    for j in range(m + 1):
        # Maximum number of pancakes that can be placed in remaining dishes
        mx = (m - j) // (n - i)
        for k in range(mx + 1):
            if dp[j][k] == inf:
                continue
 
            # Try placing l pancakes in current dish (from k to mx)
            for l in range(k, mx + 1):
                # Calculate cost of moving 'l' pancakes from previous state to current
                c = cum[l + j] - cum[j]
                dp_new[j + l][l] = min(dp_new[j + l][l], dp[j][k] + c)
    dp = dp_new
 
# Return minimum moves to place all pancakes
print(min(dp[-1]))
 
 
# https://github.com/VaHiX/CodeForces/