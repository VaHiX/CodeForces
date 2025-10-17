# Problem: CF 1954 C - Long Multiplication
# https://codeforces.com/contest/1954/problem/C

"""
Algorithm: Greedy
Time Complexity: O(n) where n is the length of the strings x and y
Space Complexity: O(n) for storing the lists of characters

Approach:
- We iterate through each digit position i from left to right.
- At each position, we decide whether swapping the digits at position i will increase the product.
- To maximize the product, we want both numbers to be as large as possible.
- If we have two digits a and b at a given position, we should consider swapping if it helps
  make both numbers larger in value.
- Greedily try to ensure that at each position, we either:
  - Keep them as they are if swapping doesn't help.
  - Swap them such that we end up with a larger first number at this position, if possible.
"""

def pow(x, y, m=10**9 + 7):
    ans = 1
    x %= m
    while y:
        if y & 1:
            ans = (ans * x) % m
        x = (x * x) % m
        y >>= 1
    return ans


def solve():
    x = input()
    y = input()
    f = False  # Flag to track if any swaps have been performed
    x = list(x)  # Convert string to list for mutability
    y = list(y)
    for i in range(len(x)):
        # If we're in a state where previous swap was beneficial (f=True),
        # and current digit of x is greater than y's digit,
        # then swap to make x smaller and y larger (or vice versa)
        if (x[i] > y[i]) == f:
            x[i], y[i] = y[i], x[i]
        # Update flag - if digits at current position are not equal, set flag to True
        f |= x[i] != y[i]
    print("".join(x))
    print("".join(y))


def main():
    TC = 1
    TC = int(input())
    for _ in range(TC):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/