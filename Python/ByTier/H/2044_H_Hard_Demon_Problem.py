# Contest 2044, Problem H: Hard Demon Problem
# URL: https://codeforces.com/contest/2044/problem/H

from collections.abc import Iterable
import sys

input = sys.stdin.readline


def read_int() -> int:
    return int(input())


def read_ints() -> map:
    return map(int, input().split())


def write_ints(ints: Iterable[int], sep: str = " "):
    print(sep.join(map(str, ints)))


def roundup_division(dividend: int, divisor: int) -> int:
    return (dividend - 1) // divisor + 1


def matrix_integral(matrix: list[list[int]]) -> list[list[int]]:
    integral = [[0 for _ in range(len(matrix[0]) + 1)] for _ in range(len(matrix) + 1)]
    for i in range(1, len(matrix) + 1):
        for j in range(1, len(matrix[i - 1]) + 1):
            integral[i][j] = (
                matrix[i - 1][j - 1]
                + integral[i][j - 1]
                + integral[i - 1][j]
                - integral[i - 1][j - 1]
            )
    return integral


def rect_sum(
    integral: list[list[int]], top: int, left: int, bottom: int, right: int
) -> int:
    return (
        integral[bottom][right]
        - integral[bottom][left - 1]
        - integral[top - 1][right]
        + integral[top - 1][left - 1]
    )


def main():
    n_tests = int(input())
    for _ in range(n_tests):
        n, q = read_ints()
        matrix = [list(read_ints()) for _ in range(n)]
        i_matrix = [[(i + 1) * matrix[i][j] for j in range(n)] for i in range(n)]
        j_matrix = [[(j + 1) * matrix[i][j] for j in range(n)] for i in range(n)]
        integral, i_integral, j_integral = map(
            matrix_integral, (matrix, i_matrix, j_matrix)
        )
        answers = [0 for _ in range(q)]
        for i in range(q):
            top, left, bottom, right = read_ints()
            sum, i_sum, j_sum = map(
                lambda integral: rect_sum(integral, top, left, bottom, right),
                (integral, i_integral, j_integral),
            )
            width = right - left + 1
            answers[i] = width * i_sum + j_sum - (width * top + left - 1) * sum
        write_ints(answers)


if __name__ == "__main__":
    main()
