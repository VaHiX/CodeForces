// Problem: CF 2141 B - Games
// https://codeforces.com/contest/2141/problem/B

/*
B. Games

Purpose:
This program computes the maximum number of suggestions Alice and Bob will make while choosing a game to play.
The process alternates between Alice and Bob suggesting games from their respective lists until a mutual favorite is found.

Algorithm/Techniques:
- Set-based lookup for efficient intersection detection.
- Greedy simulation of turn-based suggestion with early termination when a common game is found.

Time Complexity: O(n + m) per test case, where n and m are the lengths of the two lists.
Space Complexity: O(m) for storing Bob's list as a set.

Input:
- t: Number of test cases
- n, m: Sizes of Alice's and Bob's game lists
- aList: Alice's list of games (sorted)
- bSet: Bob's list of games (as a set for fast lookup)

Output:
- Maximum number of suggestions before finding a mutual favorite.
*/

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val (n, m) = readLine()!!.split(" ").map { it.toInt() } // Read n and m
        val aList = readLine()!!.split(" ").map { it.toInt() } // Read Alice's list
        val bSet = readLine()!!.split(" ").map { it.toInt() }.toSet() // Read Bob's list as a set for fast lookup
        
        // Count how many games in Alice's list are also in Bob's list
        val common = aList.count { it in bSet }
        
        // Calculate number of unique games each has (excluding common ones)
        val x = n - common // Games only Alice has
        val y = m - common // Games only Bob has
        
        // Determine the maximum turns based on who runs out of unique games first
        println(if (x > y) 2 * y + 2 else 2 * x + 1)
    }
}


// https://github.com/VaHiX/codeForces/