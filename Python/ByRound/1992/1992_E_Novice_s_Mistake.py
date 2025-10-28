# Problem: CF 1992 E - Novice's Mistake
# https://codeforces.com/contest/1992/problem/E

"""
Algorithm: Novice's Mistake
Purpose: Find all pairs (a, b) such that K1o0n's incorrect solution still gives the correct result for a given n.
The incorrect solution treats n as a string and performs string multiplication and substring removal.
Correct solution: n * a - b
Incorrect solution: (n repeated a times) - b characters from end -> result as integer should equal correct answer

Time Complexity: O(1) - Since n is bounded by 100, and we generate a fixed number of possible combinations.
Space Complexity: O(1) - Fixed memory usage due to bounded input.

Approach:
1. Handle special case when n == 1.
2. For other values of n, generate all possible repeated strings formed by repeating n and appending prefixes.
3. For each generated number, derive values of a and b using mathematical relations.
4. Validate a and b according to constraints.
5. Return all valid pairs (a, b).
"""

def find_correct_pairs(n):
    correct_pairs = []
    n_str = str(n)
    if n == 1:
        # Special case handling for n=1
        for a in range(1, 10001):
            b = a - 1
            if b >= 1 and b <= min(10000, a * n):
                correct_pairs.append((a, b))
        return correct_pairs
    possible_numbers = []
    # Generate all possible repeated strings of n up to length 6
    for i in range(1, 7):
        repeated_str = n_str * i
        possible_numbers.append(int(repeated_str))
        # Append prefixes of n to the repeated string
        for j in range(1, len(n_str)):
            partial_str = repeated_str + n_str[:j]
            possible_numbers.append(int(partial_str))
    # For each generated number, compute corresponding a and b
    for number in possible_numbers:
        len_number = len(str(number))
        len_n = len(str(n))
        a = (number - len_number) / (n - len_n)
        b = a * len_n - len_number
        # Validate if a and b are integers and within bounds
        if (
            a >= 1
            and a <= 10000
            and b >= 1
            and b <= min(10000, a * n)
            and a == int(a)
            and b == int(b)
        ):
            correct_pairs.append((int(a), int(b)))
    return correct_pairs


def main():
    import sys

    input = sys.stdin.read
    data = input().split()
    t = int(data[0])
    ns = list(map(int, data[1 : t + 1]))
    results = []
    for n in ns:
        correct_pairs = find_correct_pairs(n)
        results.append(f"{len(correct_pairs)}")
        for a, b in correct_pairs:
            results.append(f"{a} {b}")
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/