# Problem: CF 1835 E - Old Mobile
# https://codeforces.com/contest/1835/problem/E

"""
Algorithm: Dynamic Programming with Modular Arithmetic
Time Complexity: O(n * log MODULO) where n is the length of the number
Space Complexity: O(m) where m is the base of the numerical system

The problem involves calculating the expected number of button presses for a
teleporting captain to type a number on a worn-out keypad with m+1 buttons:
digits 0 to m-1 and a backspace button. The buttons are indistinguishable
until pressed. The solution uses dynamic programming to compute expected
values considering the probability of hitting the correct digit or backspace.

The approach calculates the expected number of presses based on how many
unique digits need to be pressed and how the backspace button affects
the total count.
"""

import sys

MODULO = 1000000007


def modular_exponentiation(base: int, exponent: int) -> int:
    """
    Computes the modular exponentiation using binary exponentiation.
    :param base: The base integer.
    :param exponent: The exponent integer.
    :return: The result of (base^exponent) % MODULO.
    """
    result = 1
    while exponent:
        if exponent & 1:
            result = (result * base) % MODULO
        exponent >>= 1
        base = (base * base) % MODULO
    return result


def compute_result(num_digits: int, num_buttons: int) -> int:
    """
    Computes the desired result based on given constraints.
    :param num_digits: The total number of elements.
    :param num_buttons: The maximum possible value of an element.
    :return: Computed result as per the problem's requirements.
    """
    is_visited = [False] * (num_buttons + 1)  # Track visited digits
    unique_count = 0  # Count of unique digits in the target number
    elements = list(map(int, sys.stdin.readline().split()))

    # Count how many unique digits are in the target number
    for element in elements:
        if not is_visited[element]:
            unique_count += 1
            is_visited[element] = True

    # Calculate probability factor for expected value calculation
    probability_factor = 1
    for i in range(1, unique_count + 1):
        # Modular inverse of (num_buttons + 2 - i) is computed using Fermat's little theorem
        probability_factor = (
            probability_factor * modular_exponentiation(num_buttons + 2 - i, MODULO - 2)
        ) % MODULO
        # Update num_digits based on expected values
        num_digits = (
            num_digits
            + 2 * i * modular_exponentiation(i + 1, MODULO - 2)
            + (MODULO - probability_factor) * 2
        ) % MODULO

    # Adjust for remaining digits that were not in initial set
    num_digits = (
        num_digits
        + (num_buttons - unique_count)
        * (
            2
            * (unique_count + 1)
            * modular_exponentiation(unique_count + 2, MODULO - 2)
            - probability_factor
            + MODULO
        )
    ) % MODULO
    probability_factor = 1

    # Final adjustments for expected value
    for i in range(1, unique_count + 1):
        # Again, compute modular inverse for probability factor
        probability_factor = (
            probability_factor * modular_exponentiation(num_buttons + 2 - i, MODULO - 2)
        ) % MODULO
        # Add contribution from each digit
        num_digits = (num_digits + (1 + (i != 1)) * probability_factor) % MODULO

    return num_digits


def main():
    num_digits, num_buttons = map(int, sys.stdin.readline().split())
    print(compute_result(num_digits, num_buttons))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/