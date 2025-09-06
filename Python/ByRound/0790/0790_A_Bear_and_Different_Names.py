# Contest 790, Problem A: Bear and Different Names
# URL: https://codeforces.com/contest/790/problem/A

# ---------------------------------------------------------------------------------------
# URL    : https://codeforces.com/contest/790/problem/A
# Title  : Bear and Different Names
# Tags   : tag-codeforces, tag-problem-A, tag-div-1, tag-difficulty-1500
# Notes  : constructive algorithms, greedy
# ---------------------------------------------------------------------------------------


import string


def list_to_string(_a):
    return " ".join(map(str, _a))


def solve():
    possible_names = list(string.ascii_uppercase)
    possible_names += list(map(lambda x: x[0] + x[1], zip(list(string.ascii_uppercase), list(string.ascii_lowercase))))

    n, k = map(int, input().split())
    a = list(input().split())

    result = possible_names[:n]

    for i in range(n - k + 1):
        if a[i] == "NO":
            result[i + k - 1] = result[i]

    return list_to_string(result)


if __name__ == "__main__":
    print(solve())
