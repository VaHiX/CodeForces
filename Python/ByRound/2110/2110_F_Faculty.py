# Contest 2110, Problem F: Faculty
# URL: https://codeforces.com/contest/2110/problem/F


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
                    candidate_beauty = current_value
                else:
                    for prev_val in previous_values:
                        candidate_beauty = max(
                            candidate_beauty, prev_val + (current_value % prev_val)
                        )
            max_beauty = max(max_beauty, candidate_beauty)
            max_so_far = current_value
        elif current_value < max_so_far:
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
