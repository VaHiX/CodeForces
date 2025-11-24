# Problem: CF 2022 A - Bus to Pénjamo
# https://codeforces.com/contest/2022/problem/A

"""
Problem: Maximize happy people on a bus
Algorithm/Techniques: Greedy, Mathematical Optimization

Time Complexity: O(n) per test case
Space Complexity: O(1)

The problem involves seating families on a bus with r rows and 2 seats each.
A person is happy if:
- They sit with another family member in the same row, or
- They sit alone in their row with an empty adjacent seat.

Approach:
1. For each family of size `a[i]`, we can seat at most `a[i] // 2` pairs in a row (each pair takes 2 seats)
2. We also count how many people (`a[i] % 2`) cannot be paired in any row they're assigned to.
3. After assigning all possible pairs, we have excess unpaired people (cm).
4. The remaining rows `m = r - ans` can be used to maximize happiness:
   - If we assign the unpaired people optimally, then the best we can do is:
     - Pair up as many of them as possible in the remaining rows.
     - Each such pair gives 2 happy people.
   - We aim to maximize the contribution from unpaired people using available space.

The solution uses a greedy approach:
- First compute all possible pairs that fit into the bus
- Then compute how many unpaired individuals remain
- Allocate remaining rows optimally for maximum happiness
"""

for _ in range(int(input())):
    n, r = map(int, input().split())
    (*a,) = map(int, input().split())
    ans = 0  # Total number of pairs (each pair contributes 2 happy people)
    cm = 0   # Count of all unpaired people across families
    for x in a:
        ans += x // 2  # Add number of complete pairs from family x
        cm += x % 2    # Add remainder people who could not be paired
    m = r - ans        # Remaining rows that are not occupied by complete pairs
    print(2 * ans + min(2 * m - cm, cm))  # Output total happy people


# https://github.com/VaHiX/codeForces/