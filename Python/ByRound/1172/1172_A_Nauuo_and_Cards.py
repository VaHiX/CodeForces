# Problem: CF 1172 A - Nauuo and Cards
# https://codeforces.com/contest/1172/problem/A

"""
Problem: Nauuo and Cards
Algorithm: Greedy approach with verification
Time Complexity: O(n)
Space Complexity: O(1)

Task: Determine minimum number of operations to arrange cards in pile in increasing order.
Each operation allows playing a card from hand to bottom of pile, then drawing top card.
"""

n = int(input())
hand = list(map(int, input().split()))
deck = list(map(int, input().split()))
flg = True

# If the last card in deck is 0, it's impossible to arrange properly
if deck[-1] == 0:
    flg = False

# If the last card in deck is not 0, try to verify if arrangement is possible
if deck[-1] != 0:
    num = deck[-1]  # Get the value of last card in pile (should be n)
    
    # Check if the last 'num' cards in pile are consecutive descending from 'num'
    for i in range(num):
        if deck[-i - 1] != num - i:
            flg = False
    
    # Check remaining cards in pile
    for i in range(n - num):
        if deck[i] != 0:
            if num + i + 2 > deck[i]:  # If position constraint is violated
                flg = False

    # If all checks passed, compute the result
    if flg:
        print(n - num)

# If arrangement is not possible with above logic, fall back to brute force approach
if not flg:
    ans = n
    for i in range(n):
        if deck[i] != 0:
            # Compute maximum operations needed using current card at position i
            ans = max(ans, i - deck[i] + n + 2)
    print(ans)


# https://github.com/VaHiX/codeForces/