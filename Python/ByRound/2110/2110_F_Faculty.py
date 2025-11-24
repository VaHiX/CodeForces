# Problem: CF 2110 F - Faculty
# https://codeforces.com/contest/2110/problem/F

"""
F. Faculty
Time Complexity: O(n * sqrt(max_value)) per test case, where n is the size of the array and max_value is the maximum element in the array.
Space Complexity: O(n) for storing the input and intermediate results.

Algorithms/Techniques:
- Prefix-based computation with optimization using previous values
- For each new element, we compute the beauty of the prefix up to that point by comparing:
  - Current element with max_so_far (if current > max_so_far)
  - Pairwise computations using mod operation between current and past elements

The key insight is to maintain a running maximum (`max_so_far`) and store previously seen values (`previous_values`) to avoid recomputing all pairs from scratch.
"""

def solve():
    n = int(input())
    values = list(map(int, input().split()))
    answer_list = [0] * n
    previous_values = []
    max_so_far = 0
    max_beauty = 0
    for i in range(n):
        current_value = values[i]
        if current_value > max_so_far:
            candidate_beauty = 0
            if previous_values:
                if 2 * max_so_far > current_value:
                    # Optimization: if 2 * max_so_far > current_value,
                    # we can directly consider current_value as a valid candidate
                    candidate_beauty = current_value
                else:
                    # Otherwise, try pair-wise mod computations with previous values
                    for prev_val in previous_values:
                        candidate_beauty = max(
                            candidate_beauty, prev_val + (current_value % prev_val)
                        )
            max_beauty = max(max_beauty, candidate_beauty)
            max_so_far = current_value
        elif current_value < max_so_far:
            # If current value is less than max_so_far,
            # we compute mod between max_so_far and current_value
            max_beauty = max(max_beauty, current_value + (max_so_far % current_value))
        answer_list[i] = max_beauty
        previous_values.append(current_value)
    print(" ".join(map(str, answer_list)))


def main():
    T = int(input())
    for _ in range(T):
        solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/