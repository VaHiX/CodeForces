# Problem: CF 1932 D - Card Game
# https://codeforces.com/contest/1932/problem/D

"""
Card Game Solution

Algorithm:
- The problem involves reconstructing a valid sequence of card plays in a card game.
- We need to pair up cards such that each pair represents a valid play (first player's card, second player's card).
- A card can beat another if:
    1. Same suit and higher rank, or
    2. Trump card beats non-trump card
- Strategy:
    1. Sort suits so that trump suit comes last.
    2. Group all cards by suit.
    3. For each non-trump suit, pair up cards by rank (higher rank card beats lower).
    4. Handle trump suit separately:
        - Pair up trump cards with non-trump cards (if possible).
        - If no non-trump left, pair trump cards among themselves.
    5. If not all cards can be paired, return "IMPOSSIBLE".

Time Complexity: O(n log n) - due to sorting and processing steps.
Space Complexity: O(n) - for storing sorted cards and result.
"""

MULTI_TEST = True
PRINT_RETURN_VALUES = True


def solve():
    int(input())
    trump_suit = input()
    cards = input().split()

    # Sort suits to ensure trump suit is last
    suits = sorted("CDHS", key=lambda x: x == trump_suit)

    # Group cards by suit
    sorted_cards = [[] for _ in range(4)]
    for c in cards:
        sorted_cards[suits.index(c[1])].append(c[0])  # Store only ranks

    res = []
    # Process each non-trump suit
    for i in range(3):
        # While we have more than one card in the suit
        while len(sorted_cards[i]) > 1:
            # Take two cards
            a = sorted_cards[i].pop()
            b = sorted_cards[i].pop()
            # Ensure a >= b for simplicity in comparison
            if b < a:
                a, b = b, a
            # Add the play to result: a (first player) beats b (second player)
            res.append(f"{a + suits[i]} {b + suits[i]}")

    # Process trump suit
    for i in range(3):
        # If there are cards left in non-trump suit
        if sorted_cards[i]:
            # If there are any trump cards left
            if sorted_cards[3]:
                # Play trump card against non-trump
                a = sorted_cards[i].pop()
                b = sorted_cards[3].pop()
                res.append(f"{a + suits[i]} {b + suits[3]}")
            else:
                # No trump cards left to beat, impossible to proceed
                return "IMPOSSIBLE"

    # Pair up remaining trump cards
    while len(sorted_cards[3]) > 1:
        a = sorted_cards[3].pop()
        b = sorted_cards[3].pop()
        if b < a:
            a, b = b, a
        res.append(f"{a + suits[3]} {b + suits[3]}")

    return "\n".join(res)


def main():
    t = int(input()) if MULTI_TEST else 1
    if PRINT_RETURN_VALUES:
        output = []
        for _ in range(t):
            ans = solve()
            output.append(ans)

        print_lines(output)
    else:
        for _ in range(t):
            solve()


def input():
    return next(test).strip()


def read_ints():
    return [int(c) for c in input().split()]


def print_lines(lst):
    print("\n".join(map(str, lst)))


if __name__ == "__main__":
    import sys
    from os import environ as env

    if "COMPUTERNAME" in env and "L2A6HRI" in env["COMPUTERNAME"]:
        sys.stdout = open("out.txt", "w")
        sys.stdin = open("in.txt", "r")

    test = iter(sys.stdin.readlines())

    main()


# https://github.com/VaHiX/CodeForces/