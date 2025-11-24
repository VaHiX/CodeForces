// Problem: CF 2126 D - This Is the Last Time
// https://codeforces.com/contest/2126/problem/D

/*
 * Problem: D. This Is the Last Time
 * Purpose: Given n casinos with play requirements and rewards, find the maximum coins achievable starting with k coins.
 * Algorithm: Greedy approach using a priority queue to always choose the best available casino based on reward.
 *            - Sort casinos by left bound (l)
 *            - Use a max-heap (priority queue) to track playable casinos by their real reward
 *            - Iterate through all possible plays, updating current coins and tracking maximum
 *
 * Time Complexity: O(n log n + n) = O(n log n), where n is the number of casinos.
 * Space Complexity: O(n), for storing casino data and the priority queue.
 */

import java.util.PriorityQueue

data class Casino(val l: Long, val r: Long, val real: Long)

fun main() {
    val t = readln().toInt()
    repeat(t) {
        solve()
    }
}

fun solve() {
    val (nStr, kStr) = readln().split(" ")
    val n = nStr.toInt()
    val k = kStr.toLong()
    val casinos = mutableListOf<Casino>()
    
    // Read casino data
    for (i in 0 until n) {
        val (l, r, real) = readln().split(" ").map { it.toLong() }
        casinos.add(Casino(l, r, real))
    }
    
    // Sort casinos by left bound to process them in order
    casinos.sortBy { it.l }
    
    // Priority queue to keep track of playable casinos based on reward (real)
    val playableCasinosPQ = PriorityQueue<Casino>(compareBy { it.real })
    
    var currentCoins = k
    var maxCoins = k
    var casinoIndex = 0
    
    while (true) {
        // Add all casinos that can currently be played (l <= currentCoins) to the heap
        while (casinoIndex < n && casinos[casinoIndex].l <= currentCoins) {
            playableCasinosPQ.add(casinos[casinoIndex])
            casinoIndex++
        }
        
        // Remove all casinos from heap that are no longer playable (r < currentCoins)
        while (playableCasinosPQ.isNotEmpty() && playableCasinosPQ.peek().r < currentCoins) {
            playableCasinosPQ.poll()
        }
        
        // If no playable casino left, end simulation
        if (playableCasinosPQ.isEmpty()) {
            break
        }
        
        // Play the best available casino (highest reward)
        val bestCasinoToPlay = playableCasinosPQ.poll()
        currentCoins = bestCasinoToPlay.real
        maxCoins = maxOf(maxCoins, currentCoins)
    }
    
    println(maxCoins)
}


// https://github.com/VaHiX/CodeForces/