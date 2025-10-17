# Problem: CF 2144 D - Price Tags
# https://codeforces.com/contest/2144/problem/D

"""
D. Price Tags

Algorithm: 
- For each possible coefficient x > 1, compute the total income:
  - New price of item i is ceil(c_i / x)
  - Count how many items have each new price
  - Calculate total value minus cost of printing new tags
- Optimization using prefix sums to count occurrences efficiently

Time Complexity: O(n + max_c * log(max_c)) where max_c = 2*10^5
Space Complexity: O(max_c) for the prefix array

Approach:
1. Use a prefix sum array to quickly compute how many items fall into a range [a, b)
2. For each valid x (starting from 2), compute total income:
   - For each group of items with same ceil(c_i / x), calculate value and cost
   - Value is sum of all new prices
   - Cost is y * number of new tags needed

"""

for _ in range(int(input())):
    n, y = map(int, input().split())
    arr = list(map(int, input().split()))
    ans = -float("inf")
    pre = [0 for i in range(200100)]  # Prefix array to count items by their values
    
    # Count occurrences of each price
    for a in arr:
        pre[a] += 1
    
    # Build prefix sum array
    for i in range(1, 200100):
        pre[i] += pre[i - 1]
    
    # Try each possible x from 2 to a large number
    for x in range(2, 200100):
        curr = 0
        d = 1
        while (d - 1) * x < 200100:  # Ensure we don't go out of bounds
            # Compute count of items with ceil(c_i / x) = d
            count = pre[min(200010, d * x)] - pre[(d - 1) * x]
            
            # Add contribution to total value (d * count)
            curr += d * count
            
            # Subtract cost: y * [number of original tags not reused]
            # This equals: y * [count - min(count, count_of_items_with_price_d)]
            curr -= y * (count - min(count, pre[d] - pre[d - 1]))
            d += 1
        ans = max(ans, curr)
    print(ans)


# https://github.com/VaHiX/codeForces/