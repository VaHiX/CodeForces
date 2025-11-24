# Problem: CF 1735 D - Meta-set
# https://codeforces.com/contest/1735/problem/D

"""
Purpose: This code solves the "Meta-set" problem where we need to count the number of 5-card groups (meta-sets)
         such that there are more than one valid SET among the 5 cards. A SET is a group of 3 cards where each 
         feature is either all the same or all different across the cards.

Algorithms/Techniques:
- Brute-force approach over all possible 5-card combinations
- For each 5-card group, determine how many valid SETs exist among them
- Use a set for O(1) lookup of cards
- For each card in a 5-card group, count how many other cards form a valid SET with it (using the third card rule)
- Then compute how many 3-card combinations from that count contribute to valid SETs

Time Complexity: O(n^2 * k), where n is the number of cards and k is the number of features
Space Complexity: O(n * k), to store all cards in a set for fast lookup

"""

def solve(n, k, c):
    S = set(c)  # Convert list of cards to a set for fast lookup
    tot = 0     # Total number of meta-sets

    # For each card in the collection
    for i in range(n):
        # Count how many valid third cards can form a SET with card i
        # For each j from 0 to n-1 (another card), compute what card k would complete the SET
        # This is done by ensuring that for each of the k features, the three values
        # are either all same or all different. So (a + b + k) % 3 == 0 for each feature.
        count = (
            sum(
                tuple((6 - c[i][p] - c[j][p]) % 3 for p in range(k)) in S
                for j in range(n)
            )
            - 1  # Subtract one to exclude the case when i == j (same card)
        ) // 2  # Divide by 2 to avoid double-counting (a,b) and (b,a)
        # count represents how many sets include card i
        # Now we compute the number of ways to choose 2 cards from these count cards to form a SET
        tot += count * (count - 1) // 2  # This is C(count, 2) times the number of such sets

    return tot


# Read input
n, k = [int(_) for _ in input().split()]
c = []
for i in range(n):
    c.append(tuple(int(_) for _ in input().split()))

# Output the result
print(solve(n, k, c))


# https://github.com/VaHiX/CodeForces/