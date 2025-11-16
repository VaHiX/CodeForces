# Problem: CF 774 A - Amusement Park
# https://codeforces.com/contest/774/problem/A

"""
Problem: Amusement Park

Algorithm/Technique: Dynamic Programming with Enumeration
- The problem is to split n people (pupils and adults) into groups such that:
  - Each group has at least one adult.
  - Each person joins exactly one group.
  - The total cost is minimized.
- Cost for a group of x people: c1 + c2 * (x-1)^2
- We enumerate over the number of groups (k), and for each k, we try to distribute
  the extra people (non-adults) into k groups to minimize total cost.
- For each valid number of groups k (1 to A, where A is the number of adults):
  - Distribute (n - k) non-adult people into k groups.
  - Calculate how many groups will have (base + 1) people and how many will have base people.
  - Compute cost and track minimum.

Time Complexity: O(A), where A is the number of adults. Since there are at most n adults, and A <= n, this is efficient.
Space Complexity: O(1), as we only use a constant amount of extra space.
"""

n, c1, c2 = map(int, input().split())
s = input().strip()
A = s.count("1")  # Count number of adults

best = float("inf")  # Initialize best cost to infinity

# Try all possible numbers of groups from 1 to A (number of adults)
for k in range(1, A + 1):
    extra = n - k  # Number of non-adults to distribute
    base = extra // k  # Base number of people per group
    r = extra % k  # Number of groups that get one extra person
    
    # Compute the total cost for this group distribution:
    # k * c1 for k groups of 1 person each
    # c2 * [r * (base + 1)^2 + (k - r) * base^2] for the rest
    cost = k * c1 + c2 * (r * (base + 1) ** 2 + (k - r) * base**2)
    
    if cost < best:
        best = cost  # Update the minimum cost

print(best)


# https://github.com/VaHiX/CodeForces/