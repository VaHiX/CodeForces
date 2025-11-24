# Problem: CF 1672 D - Cyclic Rotation
# https://codeforces.com/contest/1672/problem/D
 
"""
Algorithm: Simulation with Delay Tracking
Techniques: Two-pointer technique, frequency tracking using array
 
Time Complexity: O(n) - Each element is processed at most twice (once in main loop, once in inner loop)
Space Complexity: O(n) - Extra space for delay array of size n+1
 
The problem allows rotating a subarray where first and last elements are equal.
This operation effectively moves the first element to the end of the subarray.
We simulate the transformation by matching elements from array b to array a,
tracking how many times each element "waits" to be matched (delay).
"""
 
def li():
    return [int(i) for i in input().split()]
 
 
def sol(a, b, n):
    # Initialize delay array to track how many times each element is delayed
    delay = [0] * (n + 1)
    # Append sentinel values to simplify boundary checks
    a += [-1]
    b += [-2]
    x, y = 0, 0  # Pointers for arrays a and b
    
    # Process each element in array b to match with array a
    while x < n:
        # If current elements match, advance both pointers
        if a[x] == b[y]:
            x, y = x + 1, y + 1
        # If current element in a matches previous element and we have a delay for it
        elif a[x] == a[x - 1] and delay[a[x]]:
            delay[a[x]] -= 1
            x += 1
        else:
            # Try to find a matching element for a[x] in b[y...]
            # For each element in b that doesn't match, increment its delay
            while y < n and b[y] != a[x]:
                delay[b[y]] += 1
                y += 1
            # If we couldn't find a match, transformation is impossible
            if y == n:
                return "NO"
            x, y = x + 1, y + 1
 
    return "YES"
 
 
for _ in range(int(input())):
    (n,) = li()
    a = li()
    b = li()
    print(sol(b, a, n))
 
 
# https://github.com/VaHiX/CodeForces/