// Problem: CF 2123 B - Tournament
// https://codeforces.com/contest/2123/problem/B

/*
B. Tournament
Algorithms/Techniques: Greedy approach with maximum element comparison.

Time Complexity: O(n) per test case, where n is the number of players.
Space Complexity: O(n) for storing the array of player strengths.

The problem asks whether a specific player j can be among the last k players after a tournament
where players are eliminated based on strength comparisons. The key insight is:
- If k > 1, then at least one player is guaranteed to be in the final k players (this is not always true,
  but we can deduce this from game rules in terms of elimination process)
- If k = 1, only the strongest player can be left; we need to check if player j has the maximum strength.
- However, for k > 1, since there are multiple players selected and eliminated randomly, it's generally possible
  that any player (except those with lowest strengths) could make it into last k unless some specific
  conditions prevent it.
*/
import java.util.Scanner;
final public class B_Tournament{
    public static void main(String ak[]){
        Scanner s=new Scanner(System.in);
        int x=s.nextInt(); // number of test cases
        while(x-->0){
            int n=s.nextInt(); // number of players
            int c=s.nextInt(); // target player index (1-based)
            int k=s.nextInt(); // number of players to remain at the end
            int ar[]=new int[n]; // array to store player strengths
            int max=0; // track maximum strength in current test case
            for(int i=0;i<n;i++){
                ar[i]=s.nextInt(); // read player strength
                max = Math.max(max, ar[i]); // update maximum strength
            }
            // If k > 1 OR if the target player has the maximum strength,
            // then it is possible for the player to be in the last k players
            System.out.println(k>1 || ar[c-1]==max ? "YES" : "NO");
        }
    }
}


// https://github.com/VaHiX/CodeForces/