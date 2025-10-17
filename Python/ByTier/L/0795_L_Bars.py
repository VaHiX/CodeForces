# Contest 795, Problem L: Bars
# URL: https://codeforces.com/contest/795/problem/L

n, k = map(int, input().split())
s = input().strip()

zeros = [i for i, c in enumerate(s) if c == "0"]


def is_possible(d, zeros, k):
    required = 1
    current = zeros[0]
    last = zeros[-1]
    i = 0
    while current != last:
        left = i + 1
        right = len(zeros) - 1
        best = -1
        while left <= right:
            mid = (left + right) // 2
            if zeros[mid] <= current + d + 1:
                best = mid
                left = mid + 1
            else:
                right = mid - 1
        if best == -1:
            return False
        current = zeros[best]
        required += 1
        i = best
        if required > k:
            return False
    return required <= k


low = 0
high = zeros[-1] - zeros[0] - 1
answer = high

while low <= high:
    mid = (low + high) // 2
    if is_possible(mid, zeros, k):
        answer = mid
        high = mid - 1
    else:
        low = mid + 1

print(answer)
