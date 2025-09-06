# Contest 2057, Problem H: Coffee Break
# URL: https://codeforces.com/contest/2057/problem/H

from typing import List


def get_right_out(a: List[int], res: List[int]) -> List[int]:
    n = len(a)
    st = []
    res = [0] * (n + 1)

    for i in range(n):
        x = a[i] + res[i]
        st.append(i)

        while x != 0:
            if not st:
                length = i + 1
                cnt = x // (length + 1)
                res[i + 1] += cnt * length
                x -= cnt * (length + 1)

                if x != 0:
                    res[i + 1] += x
                    st.append(x - 1)
                    x = 0
            else:
                j = st[-1]
                if x > i - j:
                    res[i + 1] += i - j
                    st.pop()
                    x -= i - j + 1
                else:
                    res[i + 1] += x
                    st[-1] += x
                    x = 0

    return res


def get_left_out(a: List[int], b: List[int]) -> List[int]:
    a = a[::-1]  # Reverse the input array
    b = get_right_out(a, b)
    b = b[::-1]  # Reverse the result
    a = a[::-1]  # Restore the input array
    return b


def solve():
    n = int(input())
    a = list(map(int, input().split()))

    # Initialize empty lists for left and right results
    lhs = []
    rhs = []

    # Get left and right outputs
    lhs = get_right_out(a, lhs)
    rhs = get_left_out(a, rhs)

    # Calculate and print the final result
    result = [lhs[i] + a[i] + rhs[i + 1] for i in range(n)]
    print(*result)


def main():
    t = int(input())  # Number of test cases
    for _ in range(t):
        solve()


if __name__ == "__main__":
    main()
