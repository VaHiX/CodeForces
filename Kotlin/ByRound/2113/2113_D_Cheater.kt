// Problem: CF 2113 D - Cheater
// https://codeforces.com/contest/2113/problem/D

/**
 * Problem: D. Cheater
 * Purpose: Maximize the number of points in a card game by strategically swapping at most one pair of cards in the player's hand.
 *
 * Algorithm:
 * - Precompute suffix minimums for dealer's hand to quickly determine the smallest value that can beat current round.
 * - Use two TreeSets to maintain increasing and decreasing order of played cards.
 * - For each round, simulate playing a card from player's hand and check if it beats the minimum required value.
 * - If not, try swapping one pair of cards in the player's hand.
 *
 * Time Complexity: O(n log n) per test case due to TreeSet operations (insert/delete/lookup).
 * Space Complexity: O(n) for storing arrays and TreeSets.
 */
@file:OptIn(ExperimentalStdlibApi::class)
import java.util.TreeSet
import kotlin.math.absoluteValue

fun readInt() = readln().toInt()
fun readLong() = readln().toLong()
fun readInts() = readln().split(" ").map { it.toInt() }
fun readLongs() = readln().split(" ").map { it.toLong() }

val Int.abs get() = absoluteValue
val Long.abs get() = absoluteValue

fun yes() = println("Yes")
fun no() = println("No")

val INF = 1_000_000_000

fun solve() {
    val n = readInt()
    val a = readInts() // Player's hand
    val b = readInts() // Dealer's hand
    
    // Precompute suffix minimums for dealer's hand: bMins[i] represents the minimum card in b[i..n-1]
    val bMins = buildList {
        repeat(n + 1) {
            if (it == 0) add(INF) else add(minOf(this[it - 1], b[it - 1]))
        }
    }

    // TreeSet to efficiently manage increasing and decreasing orders of played cards
    val setIncr = TreeSet<Int>() // tracks sorted increasing cards played so far
    val setDecr = TreeSet<Int>() // tracks sorted decreasing cards played so far

    // Initially add all player's cards to setDecr (as they haven't been played yet)
    for (i in 0 until n) setDecr.add(a[i])

    // Process each round
    for (i in 0 until n) {
        // Move the current card from setDecr to setIncr, indicating it's now played
        setIncr.add(a[i])
        setDecr.remove(a[i])

        // Get the smallest card in the increasing set (the next best card we can play now)
        val iterator = setIncr.iterator()
        val minIncr = iterator.next()

        // If the minimum card from increasing set is >= required threshold, skip
        if (minIncr >= bMins[n - i]) continue

        // If either:
        // 1. No cards left in decreasing set (setDecr)
        // 2. Last element of decreasing set < threshold (can't beat it)
        // 3. Next card in increasing set can beat the threshold
        // Then we need to swap at this point i
        if (setDecr.isEmpty() || setDecr.last() < bMins[n - i] || (iterator.hasNext() && iterator.next() < bMins[n - i])) {
            println(i)
            return
        }
    }

    // If no swap was needed, we win all rounds
    println(n)
}

fun main() {
    var t: Int = 1
    t = readInt()
    repeat(t) { solve() }
}


// https://github.com/VaHiX/CodeForces/