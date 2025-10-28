// Problem: CF 2011 E - Rock-Paper-Scissors Bot
// https://codeforces.com/contest/2011/problem/E

/*
E. Rock-Paper-Scissors Bot
Algorithms/Techniques: Greedy algorithm with string matching and simulation

Time Complexity: O(n) where n is the length of string s, since each character is processed once in the main loop.
Space Complexity: O(n) for storing the input string and auxiliary arrays.

Problem Summary:
Monocarp wants to play rock-paper-scissors against a predictable bot. The bot's behavior is:
- First round: bot chooses Rock (R)
- In subsequent rounds: bot chooses the move that beats Monocarp's previous move.
Goal:
Find minimum number of rounds such that:
1. Monocarp wins more rounds than the bot.
2. The string s appears as a substring in the bot's sequence of moves.

Approach:
We simulate the bot moves and try to optimize Monocarp's moves to meet both conditions with minimal rounds.
We construct a strategy where we try to build a sequence that satisfies the constraints efficiently,
and adjust for the score required to make Monocarp win.
*/

val reader = System.`in`.bufferedReader()
fun readLn() = reader.readLine()
fun readInt() = readLn().toInt()
fun readDouble() = readLn().toDouble()
fun readLong() = readLn().toLong()
fun readStrings() = readLn().split(" ")
fun readInts() = readStrings().map { it.toInt() }
fun readDoubles() = readStrings().map { it.toDouble() }
fun readLongs() = readStrings().map { it.toLong() }

fun calc(a: Char, b: Char): Int {
    if (a == b) {
        return 0
    }
    if (a == 'R' && b == 'S') {
        return 1
    }
    if (a == 'S' && b == 'P') {
        return 1
    }
    if (a == 'P' && b == 'R') {
        return 1
    }
    return -1
}

fun runcase() {
    var s = readLn()
    var n = s.length
    var a = s.toCharArray()
    var b = CharArray(n - 1) // Precomputed bot moves for the sequence

    // Predict next bot move based on the following rule:
    // if a[i+1] == 'R' then bot chooses 'S',
    // if a[i+1] == 'S' then bot chooses 'P',
    // if a[i+1] == 'P' then bot chooses 'R'
    for (i in 0 until n - 1) {
        if (a[i + 1] == 'R') {
            b[i] = 'S'
        }
        if (a[i + 1] == 'S') {
            b[i] = 'P'
        }
        if (a[i + 1] == 'P') {
            b[i] = 'R'
        }
    }

    var score = 1 // Initial score: Monocarp wins the first round (bot starts with R, we can beat it)

    // Calculate expected score based on our chosen strategy
    for (i in 0 until n - 1) {
        score += calc(b[i], a[i]) // We use our move a[i] against bot's predicted b[i]
    }

    var score2 = score // A second strategy option

    var ans = n // Base number of rounds needed to include s as substring
    var ans2 = 100000000

    // Adjust for different starting moves
    if (a[0] == 'P') {
        ans++ // If we start with P, add one more round to get extra win chance
        ans2 = n + 2 // Alternative strategy with even more rounds
        score2 += 2 // Winning score increases for this case
    }
    if (a[0] == 'S') {
        ans++
        score++
    }

    // Compute extra rounds needed if score is zero or negative
    if (score <= 0) {
        ans += 1 - score
    }
    if (score2 <= 0) {
        ans2 += 1 - score2
    }

    println(minOf(ans, ans2))
}

fun main() {
    var t = readInt()
    repeat(t) { runcase() }
}


// https://github.com/VaHiX/codeForces/