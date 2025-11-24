# Problem: CF 1762 G - Unequal Adjacent Elements
# https://codeforces.com/contest/1762/problem/G

"""
Algorithm: Segmentation and Greedy Pairing
Time Complexity: O(n)
Space Complexity: O(n)

This solution attempts to construct a permutation of indices such that:
1. For any three consecutive elements in the permutation, the first and third are not equal.
2. For any two consecutive elements in the permutation, the corresponding array values are not equal.

The approach involves:
1. Identifying frequency of each value in the input array.
2. Checking if a valid permutation is possible (no value occurs more than ⌈n/2⌉ times).
3. Constructing segments of pairs of indices that satisfy the constraints.
4. Handling remaining indices by placing them appropriately to avoid conflicts.
5. Adjusting adjacent segments to ensure compatibility between them.
"""

import sys

input_data: list[str] = sys.stdin.read().strip().split()
data_index: int = 0


def input() -> str:
    """
    Read the next token from the pre-read input data.

    :return: A single token (string) from the input data.
    """
    global data_index
    val = input_data[data_index]
    data_index += 1
    return val


def solve_one_case() -> None:
    """
    Solve a single test case.

    This function reads an integer n, then reads an array of n elements.
    It constructs segments by pairing indices of distinct values under
    certain frequency constraints. If it is impossible to satisfy the
    constraints (i.e., one value appears more than half the time, rounded up),
    it prints "NO". Otherwise, it prints "YES" followed by the segments.
    """

    n: int = int(input())

    arr: list[int] = [0] * (n + 1)
    freq: list[int] = [0] * (n + 1)
    bucket: list[int] = [0] * (n + 1)
    visited: list[bool] = [False] * (n + 1)

    segments: list[list[int]] = []

    mx_value: int = 0

    for i in range(1, n + 1):
        arr[i] = int(input())

    for i in range(1, n + 1):
        freq[arr[i]] += 1

    for i in range(1, n + 1):
        mx_value = max(mx_value, freq[i])
        bucket[freq[i]] += 1

    if mx_value > (n + 1) // 2:
        print("NO")
        return

    def get_max() -> int:
        """
        Return the current maximum frequency for which the bucket count is non-zero.

        :return: The maximum frequency that still has a positive count.
        """
        nonlocal mx_value
        while mx_value > 0 and bucket[mx_value] == 0:
            mx_value -= 1
        return mx_value

    def reduce_freq(x: int) -> None:
        """
        Decrease the frequency of the given value x by one. The bucket data structure
        and freq array are updated accordingly.

        :param x: The value whose frequency should be reduced by one.
        """
        old_f = freq[x]
        bucket[old_f] -= 1
        freq[x] = old_f - 1
        bucket[freq[x]] += 1

    def adjust_even_pairs(vec: list[int]) -> None:
        """
        Swap elements in the list in pairs. That is, for indices (0,1), (2,3), etc.

        :param vec: The list of indices to be rearranged in-place.
        """
        for i in range(0, len(vec), 2):
            vec[i], vec[i ^ 1] = vec[i ^ 1], vec[i]

    r: int = 0
    j: int = 2
    for i in range(1, n + 1):
        if i == r + 1:
            segments.append([])

        if get_max() == ((n - r) + 1) // 2:
            break

        if not visited[i]:
            while j <= n and arr[j] == arr[i]:
                j += 1
            if j > n:
                print("NO")
                return

            visited[i] = True
            visited[j] = True

            reduce_freq(arr[i])
            reduce_freq(arr[j])

            r += 2
            segments[-1].append(j)
            segments[-1].append(i)

            j += 1

    max_position: int = max(range(1, n + 1), key=lambda x: freq[x])
    group_0: list[int] = []
    group_1: list[int] = []

    for i in range(1, n + 1):
        if not visited[i]:
            if arr[i] != max_position:
                group_1.append(i)
            else:
                group_0.append(i)

    total_left: int = len(group_0) + len(group_1)
    for i in range(total_left):
        if (i & 1) == 0:
            segments[-1].append(group_0[i >> 1])
        else:
            segments[-1].append(group_1[i >> 1])

    for idx in range(len(segments) - 1, 0, -1):
        first_in_current = segments[idx][0]
        last_in_previous = segments[idx - 1][-1]
        if arr[first_in_current] == arr[last_in_previous]:
            adjust_even_pairs(segments[idx - 1])

    print("YES")
    for seg in segments:
        for x in seg:
            print(x, end=" ")
    print()


def main() -> None:
    """
    Orchestrate the solution by reading the number of test cases,
    then solve each one by calling solve_one_case.
    """
    t: int = int(input())
    for _ in range(t):
        solve_one_case()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/