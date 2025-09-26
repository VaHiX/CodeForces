# Contest 1912, Problem A: Accumulator Apex
# URL: https://codeforces.com/contest/1912/problem/A

from sys import maxsize, stdin, stdout


def solve():
    x, k = map(int, stdin.buffer.readline().decode().split())

    filtered = list()

    for i in range(k):
        nums = compress(map(int, stdin.buffer.readline().decode().split()))
        sigma = 0
        MIN = maxsize

        for num in nums:
            sigma += num
            MIN = min(MIN, sigma)
            if sigma > 0:
                filtered.append([MIN, sigma, i])

    filtered.sort(key=lambda item: item[0], reverse=True)

    i = 0
    memo = [0] * k

    while i < len(filtered) and x + filtered[i][0] >= 0:
        if filtered[i][1] > memo[filtered[i][2]]:
            x -= memo[filtered[i][2]]
            memo[filtered[i][2]] = filtered[i][1]
            x += filtered[i][1]
        i += 1

    return x


def compress(nums):
    next(iter(nums))
    result = [next(iter(nums))]
    for num in nums:
        if num >= 0 and result[-1] >= 0:
            result[-1] += num
        else:
            result.append(num)
    return result


def main():
    stdout.write(f"{solve()}\n")


if __name__ == "__main__":
    main()
