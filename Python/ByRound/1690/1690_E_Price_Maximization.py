# Problem: CF 1690 E - Price Maximization
# https://codeforces.com/contest/1690/problem/E

"""
Purpose: To maximize the total revenue from packaging goods into pairs,
where the cost of a package is floor(weight / k). The key idea is to first
count the base cost from individual goods (floor(a[i]/k)), then pair the
remainders optimally to maximize the additional cost from combining goods.

Algorithm:
1. Compute initial revenue by summing floor(a[i]/k) for all goods.
2. Update each good's value to its remainder when divided by k.
3. Sort the updated values.
4. Use two pointers to greedily pair smallest and largest remainders
   to form new packages that contribute an additional unit of cost (when sum >= k).
5. Add these extra contributions to the base revenue.

Time Complexity: O(n log n) due to sorting, where n is the number of goods.
Space Complexity: O(1) if we ignore input/output space, as we modify the array in-place.
"""

for T in range(int(input())):
    n, k = map(int, input().split())
    a = [int(val) for val in input().split()]
    res = 0
    # Calculate base cost from individual goods
    for i in range(n):
        res += a[i] // k  # Add the floor division result to the total
        a[i] %= k  # Update the goods to their remainders
    a.sort()  # Sort the remainders
    l, r = 0, n - 1  # Two pointers for pairing
    # Greedily pair smallest and largest remainders
    while l < r:
        if a[l] + a[r] >= k:  # If combined remainder is sufficient to make one extra cost
            res += 1  # Add one more unit of cost
            r -= 1  # Move right pointer inward
        l += 1  # Move left pointer inward
    print(res)


# https://github.com/VaHiX/CodeForces/