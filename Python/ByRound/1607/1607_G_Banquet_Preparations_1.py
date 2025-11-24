# Problem: CF 1607 G - Banquet Preparations 1
# https://codeforces.com/contest/1607/problem/G

"""
Problem: Banquet Preparations 1
Algorithm: Greedy approach to minimize balance between total fish and meat consumption
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing dish information

The problem asks us to minimize the absolute difference between total fish and meat consumed
by distributing exactly m grams of food from each dish, where each dish contains a_i fish and b_i meat.
We use a greedy approach where we decide how to distribute the m grams optimally.

Key idea: 
- Calculate the initial balance (sum of (a_i - b_i))
- For each dish, we can consume at most m grams, so we can choose any combination of fish and meat
  such that fish consumed + meat consumed = m
- We want to minimize the final balance, so we strategically decide how much fish to consume
  from each dish to get the minimum final balance.

Approach:
1. Analyze the possible consumption from each dish to determine how much fish we should consume overall
2. Calculate optimal fish consumption based on the current balance
3. Distribute the consumption across dishes greedily
"""

for t in range(int(input())):
    input() # Skip blank line
    n, m = map(int, input().split())
    nm = n * m
    mass = [list(map(int, input().split())) for i in range(n)]
    balance = max_a = max_b = 0
    for i in mass:
        balance += i[0] - i[1]  # Calculate initial balance (sum of (fish - meat) for each dish)
        max_a += min(m, i[0])   # Maximum fish we can consume from all dishes
        max_b += min(m, i[1])   # Maximum meat we can consume from all dishes
    
    min_a = nm - max_b  # Minimum fish consumption possible (when we consume maximum meat)
    
    # Determine how much fish consumption we want in total
    if balance < nm - 2 * max_b:  # If current balance is too negative
        eat_a = min_a  # Consume minimum fish
    elif balance > 2 * max_a - nm:  # If current balance is too positive
        eat_a = max_a  # Consume maximum fish
    else:  # Balance is within acceptable range
        # Use formula to find optimal fish consumption to minimize balance
        eat_a = (nm + balance + 1) // 2
    
    print(abs(balance - 2 * eat_a + nm))  # Print the minimum achievable balance
    
    rest_a = eat_a - min_a  # Remaining fish consumption to allocate
    for i in mass:
        cur_a = max(m - i[1], 0)  # Current fish consumption from this dish (minimum needed to consume at least m total)
        add = min(rest_a, min(m - cur_a, i[0] - cur_a))  # How much more fish can we consume?
        cur_a += add  # Update current fish consumption
        rest_a -= add  # Update remaining fish to distribute
        print(f"{cur_a } {m -cur_a }")  # Print fish and meat consumption for this dish


# https://github.com/VaHiX/CodeForces/