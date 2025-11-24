# Problem: CF 1999 B - Card Game
# https://codeforces.com/contest/1999/problem/B

"""
Algorithm/Techniques: Brute Force Enumeration
Time Complexity: O(1) - Since there are at most 4 * 4 = 16 combinations of card flips for each test case,
                     and the number of test cases is bounded by 10^4, the overall complexity is acceptable.
Space Complexity: O(1) - Only a constant amount of extra space is used regardless of input size.

This solution enumerates all possible ways the game can unfold:
1. Suneet chooses one of his two cards to flip first.
2. Slavic chooses one of his two cards to flip first.
3. For each of these 4 combinations, we simulate the two rounds.
4. We count how many times Suneet wins more rounds than Slavic.

The function `count_suneet_wins` computes the number of winning scenarios for Suneet.
"""

def count_suneet_wins(a1, a2, b1, b2):
    suneet_wins = 0
    # Iterate through all possible first card choices for Suneet
    for s1, s2 in [(a1, a2), (a2, a1)]:
        # Iterate through all possible first card choices for Slavic
        for sl1, sl2 in [(b1, b2), (b2, b1)]:
            suneet_rounds_won = 0
            slavic_rounds_won = 0
            # First round: compare Suneet's first card with Slavic's first card
            if s1 > sl1:
                suneet_rounds_won += 1
            elif s1 < sl1:
                slavic_rounds_won += 1
            # Second round: compare Suneet's second card with Slavic's second card
            if s2 > sl2:
                suneet_rounds_won += 1
            elif s2 < sl2:
                slavic_rounds_won += 1
            # If Suneet won more rounds than Slavic, increment the win count
            if suneet_rounds_won > slavic_rounds_won:
                suneet_wins += 1
    return suneet_wins


def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        a1 = int(data[index])
        a2 = int(data[index + 1])
        b1 = int(data[index + 2])
        b2 = int(data[index + 3])
        results.append(count_suneet_wins(a1, a2, b1, b2))
        index += 4
    sys.stdout.write("\n".join(map(str, results)) + "\n")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/