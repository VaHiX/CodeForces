# Problem: CF 1978 B - New Bakery
# https://codeforces.com/contest/1978/problem/B

"""
Code Purpose:
This code calculates the maximum profit Bob can obtain by selling n buns,
considering a promotional pricing strategy where the first k buns are sold at
decreasing prices (from b down to b - k + 1), and the remaining buns are sold
at the regular price a.

Algorithms/Techniques:
- Mathematical optimization to find the optimal k value.
- Use of arithmetic series sum formula for efficient calculation of modified price portion.

Time Complexity:
O(1) - Each test case is processed in constant time, as all operations are basic arithmetic or simple min/max calculations.

Space Complexity:
O(1) - Only a constant amount of extra space is used regardless of input size.
"""

def max_profit(n, a, b):
    # If regular price is higher than or equal to the initial modified price,
    # sell all at regular price for maximum profit
    if a >= b:
        return n * a
    else:
        # Calculate optimal k value using mathematical insight:
        # k should be the minimum of n, b, and (b - a + 1)
        # This ensures k is within bounds and maximizes profit
        k = min(n, b, b - a + 1)

        # Compute profit from first k buns using arithmetic series sum:
        # Sum = k * (first_term + last_term) / 2
        # first_term = b, last_term = b - k + 1
        profit_k = k * (b + (b - k + 1)) // 2

        # Profit from remaining (n - k) buns at regular price
        profit_remaining = (n - k) * a
        return profit_k + profit_remaining


def main():
    import sys

    input = sys.stdin.read
    data = input().split()

    t = int(data[0])
    index = 1
    results = []

    for _ in range(t):
        n = int(data[index])
        a = int(data[index + 1])
        b = int(data[index + 2])
        index += 3
        results.append(max_profit(n, a, b))

    for result in results:
        print(result)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/