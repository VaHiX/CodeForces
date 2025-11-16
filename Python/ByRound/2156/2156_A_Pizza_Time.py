# Problem: CF 2156 A - Pizza Time
# https://codeforces.com/contest/2156/problem/A

"""
Algorithm: Greedy approach with mathematical optimization
Approach:
- At each step, we want to maximize the number of slices Hao eats.
- Since Hao eats the smallest group (m1), and Alex eats the middle group (m2),
  we want to minimize m1 and m2 as much as possible.
- To do this optimally, we split n into three groups where:
  - m1 = floor(n/3) (smallest possible group)
  - m2 = floor(n/3) (middle group)
  - m3 = n - m1 - m2 (largest group)
- But we also need to ensure that m1 <= m2 <= m3.
- However, we can simplify since if we always split as evenly as possible,
  we will get m1 = floor(n/3), m2 = floor((n + 1)/3), and m3 = ceil(n/3).
- But the greedy way is to try to reduce n quickly:
  - If n % 3 == 0, we can split into 1,1,n-2 (but that's not optimal).
  - Instead, the key insight is that we split n = m1 + m2 + m3 where m1 <= m2 <= m3.
  - If n = 3k, split as 1,1,3k-2 → Hao eats 1, Alex eats 1, carry over 3k-2 = 3(k-1).
  - If n = 3k + 1, split as 1,1,3k-1 → Hao eats 1, Alex eats 1, carry over 3k-1 = 3k-1.
  - If n = 3k + 2, split as 1,2,3k-1 → Hao eats 1, Alex eats 2, carry over 3k-1.
- A simpler method:
  - We can observe that we are always doing n = n/3 (rounded down) and adding remainder,
    effectively reducing n by 2/3 every time.
  - We keep doing this until n <= 2, which means Alex eats all remaining slices.
  - In the total sum, we add the floor(n/3) to the result (this is number of slices Hao eats).

Time Complexity: O(log n) - Each iteration reduces n by approximately 2/3.
Space Complexity: O(1) - Only using a few variables.
"""

def solve():
    n = int(input())
    res = 0
    while n > 2:
        div = n // 3  # Number of slices Hao eats (smallest group)
        rem = n % 3   # Remainder after splitting
        n = rem + div # Update n for next iteration
        res += div    # Accumulate Hao's slices
    print(res)


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/