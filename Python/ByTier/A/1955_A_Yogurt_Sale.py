# Problem: CF 1955 A - Yogurt Sale
# https://codeforces.com/contest/1955/problem/A

"""
Purpose: Calculate the minimum cost for Maxim to buy exactly n yogurts,
         considering both regular and promotional pricing.
         Promotion: buy 2 yogurts for b burles, regular price: a burles each.

Algorithms/Techniques: Greedy approach
    - Compare the cost of buying 2 yogurts at regular price (2*a) vs. promotion price (b)
    - If 2*a <= b, it's always better to buy pairs at regular price
    - Otherwise, buy as many pairs as possible at promotion price and remaining at regular price

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(t), to store the test cases
"""

def min_cost(t, cases):
    for case in cases:
        n, a, b = case
        # If buying 2 yogurts at regular price is cheaper than promotion, buy individually
        if a * 2 <= b:
            print(n * a)
        else:
            # Calculate number of pairs we can buy at promotion price
            pairs = n // 2
            # Calculate remaining yogurts that must be bought at regular price
            remaining = n % 2
            # Total cost: cost of pairs + cost of remaining yogurts
            print(pairs * b + remaining * a)


t = int(input())
cases = []
for _ in range(t):
    n, a, b = map(int, input().split())
    cases.append((n, a, b))
min_cost(t, cases)


# https://github.com/VaHiX/CodeForces/