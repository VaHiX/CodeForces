# Problem: CF 2146 D1 - Max Sum OR (Easy Version)
# https://codeforces.com/contest/2146/problem/D1

"""
D1. Max Sum OR (Easy Version)

Algorithm:
This problem involves maximizing the sum of bitwise ORs between elements of two arrays,
where one array 'a' is reordered to maximize the result.

The key idea is based on bit manipulation and greedy approach:
- For each bit position, we want to pair numbers such that they contribute maximally to the OR.
- We process bits from highest to lowest.
- The optimal way is to use a specific reordering pattern based on powers of 2 (similar to a "binary tree" style arrangement).

Time Complexity: O(n log n), where n = r - l + 1. This accounts for sorting and bit processing.

Space Complexity: O(n), to store the arrays 'a' and 'b'.

Approach:
1. Initialize array 'a' with values [l, l+1, ..., r].
2. Perform a complex reordering operation involving powers of 2.
3. Compute the final result and reconstruct array 'a' accordingly.

Techniques:
- Bit manipulation
- Greedy reordering using powers of two
"""

for t in range(int(input())):
    l, r = map(int, input().split())
    n = r - l + 1
    a = list(range(l, r + 1))  # Create initial array from l to r
    b = []
    while n:
        k = 1  # Find the largest power of 2 that is <= n
        while k * 2 <= n:
            k *= 2
        # Reorder a: take the last k elements, middle part, and first part in new order
        a = a[k:] + a[n - k : k] + a[: n - k]
        # Add reversed portion of current a to b (elements from index k-1 to end)
        b += a[k - 1 :: -1]
        # Update a to the remaining elements after the last k
        a = a[k:]
        n = len(a)  # Update remaining length
            
    n = len(b)
    # Print maximum sum of ORs and the reordered array a
    print(sum(i | b[i] for i in range(n)))
    print(*b)



# https://github.com/VaHiX/CodeForces/