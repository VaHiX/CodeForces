// Problem: CF 2104 C - Card Game
// https://codeforces.com/contest/2104/problem/C

/**
 * Card Game Problem
 * 
 * Purpose:
 * This code determines the winner of a game between Alice and Bob where they play cards,
 * following special rules of beat relationships: card i beats card j if i > j, except for
 * card 1 which beats card n.
 * 
 * Algorithm:
 * For each test case:
 * 1. Parse input to assign cards to Alice (A) and Bob (B)
 * 2. For each of Alice's cards, check if there exists a Bob card that can beat it.
 *    If no such card exists for any of Alice's cards, Alice wins (she can always find
 *    a counter).
 * 3. Otherwise, Bob wins.
 *
 * Time Complexity: O(n^2) per test case due to nested loops checking all combinations.
 * Space Complexity: O(n) for storing the lists of cards for Alice and Bob.
 */

fun beats(m1: Int, m2: Int, n: Int): Boolean {
    // m1 beats m2 if m1 > m2 unless it's (1, n) case
    if (m1 == 1 && m2 == n) {
        return true
    }
    return m1 > m2 && !(m1 == n && m2 == 1)
}

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val vecA = readLine()!!
        val __aa__ = mutableListOf<Int>() // Alice's cards
        val bobCards = mutableListOf<Int>() // Bob's cards
        for (i in 0 until n) {
            if (vecA[i] == 'A') {
                __aa__.add(i + 1)
            } else {
                bobCards.add(i + 1)
            }
        }
        var ktra = false // flag to determine Alice wins
        for (m2 in __aa__) { // for each of Alice's cards
            var res = false
            for (m1 in bobCards) { // check if any of Bob's cards beats it
                if (beats(m1, m2, n)) {
                    res = true
                    break
                }
            }
            if (!res) { // if none of Bob's cards beats Alice's card
                ktra = true
                break
            }
        }
        if (ktra) {
            println("Alice")
        } else {
            println("Bob")
        }
    }
}


// https://github.com/VaHiX/CodeForces/