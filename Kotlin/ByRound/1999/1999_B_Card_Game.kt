// Problem: CF 1999 B - Card Game
// https://codeforces.com/contest/1999/problem/B

/*
 * Problem: Card Game
 * 
 * Purpose: Calculate the number of ways Suneet can win a card game against Slavic,
 *          given that both players have two face-down cards each and the game consists
 *          of two turns where players flip one card each turn.
 * 
 * Approach:
 * - For each possible sequence of card flips (4 total combinations since each player
 *   has 2 cards), determine the outcome of both rounds.
 * - A player wins a round if their flipped card value is strictly greater than
 *   the opponent's.
 * - A player wins the game if they win more than half the rounds (i.e., 2 out of 2).
 * - Since we must enumerate all valid scenarios, we consider all combinations of
 *   which card each player flips in each round.
 * 
 * Time Complexity: O(1) - The number of test cases is bounded and the logic is constant.
 * Space Complexity: O(1) - Only constant extra space used.
 */

fun main() {
    val t = readLine()!!.toInt()
    for (test in 1..t) {
        val (a, b, c, d) = readLine()!!.split(' ').map { it.toInt() }
        var ways = 0
        // Check all valid combinations for Suneet to win the game
        // Case 1: Suneet flips a first, Slavic flips c first; Suneet flips b second, Slavic flips d second
        // If Suneet wins both rounds, increment ways by 2 (for a > c and b > d)
        if ((a > c && b >= d) || (a >= c && b > d))
            ways += 2
        // Case 2: Suneet flips a first, Slavic flips d first; Suneet flips b second, Slavic flips c second
        // If Suneet wins both rounds, increment ways by 2 (for a > d and b > c)
        if ((a > d && b >= c) || (a >= d && b > c))
            ways += 2
        print("$ways\n")
    }
}


// https://github.com/VaHiX/CodeForces/