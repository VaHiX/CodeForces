# Problem: CF 1931 D - Divisible Pairs
# https://codeforces.com/contest/1931/problem/D

"""
Algorithm: 
- For each element in the array, we compute its remainder when divided by x and y.
- We store the count of elements with the same (remainder_x, remainder_y) pair in a map.
- For each element, we check how many previous elements satisfy the condition for being "beautiful":
  - If a[i] + a[j] is divisible by x, then (a[i] % x) + (a[j] % x) ≡ 0 (mod x).
  - If a[i] - a[j] is divisible by y, then (a[i] % y) = (a[j] % y).
- For the current element a[j], we look for elements a[i] such that:
  - (a[i] % x) + (a[j] % x) ≡ 0 (mod x) → a[i] % x ≡ (x - a[j] % x) (mod x)
  - (a[i] % y) = (a[j] % y)
  - So we look up (x - a[j] % x, a[j] % y) in the map.
- After processing current element, we update the map with its (remainder_x, remainder_y).

Time Complexity: O(n) - Each element is processed once
Space Complexity: O(min(n, x * y)) - Hash map stores at most n entries of pairs (remainder_x, remainder_y)
"""

def solve(test_cases):
    for _ in range(test_cases):
        n, x, y = map(int, input().split())
        arr = list(map(int, input().split()))
        m = {}
        ans = 0
        for a in arr:
            p = a % x      # remainder when divided by x
            q = a % y      # remainder when divided by y
            # Look up for valid previous elements that form a beautiful pair with current element
            ans += m.get((x - p, q), 0)
            # Adjust p to be in [1, x] instead of [0, x-1] for consistency in lookup
            if p == 0:
                p = x
            # Add current element to the map for future lookups
            m[(p, q)] = m.get((p, q), 0) + 1
        print(ans)


test_cases = int(input())
solve(test_cases)


# https://github.com/VaHiX/CodeForces/