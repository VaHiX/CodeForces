# Contest 2089, Problem D: Conditional Operators
# URL: https://codeforces.com/contest/2089/problem/D


def inter(S):
    ans = []
    for i in range(0, len(S) - 1, 2):
        ans.append(f"{S[i]}?{S[i + 1]}:")
    if len(S) & 1:
        ans.append(S[-1])
    return "".join(ans)


def solve(n, s):
    if s[-1] == "1":
        if s == "101":
            return None
        if s[0] == "0":
            return f"0?({inter(s[1:-1])}):1"
        if s.startswith("11"):
            return f"1?1:({inter(s[2:])})"
        return f"(1?0:{s[2]})?({inter(s[3:-1])}):1"

    i = 0
    while i < n and s[i] == "0":
        i += 2
    if i < n:
        j = i + 1
        while j < n and s[j] == "0":
            j += 2
        if j < n:
            return f"{inter(s[:i])}(1?({inter(s[i + 1 : j])}1):{inter(s[j + 1 : -1])}0)"


for tc in range(int(input())):
    ans = solve(2 * int(input()) + 1, input())
    print(f"Yes\n{ans}" if ans else "No")
