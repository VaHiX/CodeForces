# Problem: CF 795 A - Amusement Park
# https://codeforces.com/contest/795/problem/A

"""
Problem: Amusement Park
Algorithm: Dynamic Programming / Greedy
Time Complexity: O(A), where A is the number of adults
Space Complexity: O(1)

Approach:
- We have n visitors, each either a pupil (0) or an adult (1).
- We must group them such that each group has at least one adult.
- Group cost is calculated as: c1 + c2 * (x - 1)^2 where x is the group size.
- We try all possible numbers of groups (k) from 1 to A (number of adults).
- For each k (number of groups), we distribute remaining (n - k) pupils among k groups.
- Use greedy to minimize the total cost:
    - Distribute extra pupils (r = (n - k) % k) to some groups (they get one more person)
    - Others get base count (base = (n - k) // k).
- Compute total cost for that grouping and keep track of minimum.

Key Observations:
- Each group must include at least one adult.
- Therefore, number of groups <= number of adults.
- The optimal grouping can be determined by iterating over possible numbers of groups.
"""

n, c1, c2 = map(int, input().split())
s = input().strip()
A = s.count("1")  # Count the number of adults

best = float("inf")

for k in range(1, A + 1):  # Try all valid numbers of groups
    extra = n - k  # Number of pupils to distribute into k groups
    base = extra // k  # Base number of pupils per group
    r = extra % k  # Number of groups that get one extra pupil
    # Calculate total cost for this group distribution:
    # Each group has either 'base' or 'base + 1' pupils + one adult
    cost = k * c1 + c2 * (r * (base + 1) ** 2 + (k - r) * base**2)
    if cost < best:
        best = cost

print(best)


# https://github.com/VaHiX/CodeForces/