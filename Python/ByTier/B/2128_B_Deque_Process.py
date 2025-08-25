# Contest 2128, Problem B: Deque Process
# URL: https://codeforces.com/contest/2128/problem/B


def appendToResult(result: list[str], reversed: bool | None):
    if not reversed:
        result.append("L")
        result.append("R")
    else:
        result.append("R")
        result.append("L")


def main(N: int, array: list[int]) -> str:
    result = ["L", "R"]
    left, right = 1, N - 2
    while left <= right:
        first = array[left - 1] if result[-2] == "L" else array[right + 1]
        second = array[right + 1] if result[-1] == "R" else array[left - 1]
        if second - first > 0:
            if array[left] >= array[right]:
                appendToResult(result, False)
            else:
                appendToResult(result, True)
        else:
            if array[left] >= array[right]:
                appendToResult(result, True)
            else:
                appendToResult(result, False)
        if left == right:
            result.pop()
        left += 1
        right -= 1
    return "".join(result)


for _ in range(int(input())):
    result = main(int(input()), list(map(int, input().split())))
    print(result)
