// Problem: CF 2123 B - Tournament
// https://codeforces.com/contest/2123/problem/B

/*
B. Tournament

Purpose:
This program determines whether a specific player j can be among the last k players in a tournament,
where players are eliminated based on strength comparisons.

Algorithms/Techniques:
- Simulation of a tournament process with greedy selection
- Optimization using max element check

Time Complexity: O(n) per test case
Space Complexity: O(n) due to storing array elements

The solution works under the observation that if k=1, player j can win only if its strength is maximum.
Otherwise, as long as the tournament continues for more than k players, any player can potentially remain,
but when k=1, we just need to verify if the player's strength is max among all.

*/

fun main(){
    for ( i in 1..readln().toInt()) {
        val input = readln().split(" ").map { it.toInt() }
        val n = input[0]
        val j = input[1]
        val k = input[2]
        var a =readln().split(" ").map { it.toInt() }
        val element=a[j-1] // Get the strength of player j (1-indexed)
        if (k!=1){
            println("YES") // If k > 1, player j can always be in last k players
            continue
        }
        if (element==a.max()){
            println("YES") // If k=1, player j is valid only if it has max strength
        }
        else{
            println("NO")
        }
    }
}


// https://github.com/VaHiX/CodeForces/