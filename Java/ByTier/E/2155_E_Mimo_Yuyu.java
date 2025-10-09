// Problem: CF 2155 E - Mimo & Yuyu
// https://codeforces.com/contest/2155/problem/E

/**
 * Problem: Mimo & Yuyu
 * 
 * Game on an n x m grid where players move tokens according to specific rules.
 * The game ends when a player cannot make a move. The player who cannot make a move loses.
 * 
 * Key Concepts:
 * - Tokens are moved along valid paths that go downward and leftward in the grid,
 *   ending in column 1.
 * - The state of the game can be determined using parity of token counts in each column.
 * 
 * Algorithm:
 * - For each token, we track which column it's in.
 * - Use a ParityMap to count how many tokens exist in each column (parity-wise).
 * - Based on the parity of columns, determine if there is a winning strategy for Mimo:
 *   - If n == 1, check if column 2 has an odd number of tokens.
 *   - Otherwise, check if any column >= 2 has an odd count of tokens.
 *
 * Time Complexity: O(k) where k is the number of tokens (for processing all inputs per test case)
 * Space Complexity: O(m) for storing column parities in the map (in worst case, m columns)
 */
import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc= new Scanner(System.in);
        int t= sc.nextInt();
        while(t-->0) solve(sc);
        sc.close();
    }
    static class ParityMap{
        Map<Integer, Integer> internalMap;
        public ParityMap(){
            this.internalMap= new HashMap<>();
        }
        public void flip(int key){
            this.internalMap.put(key, this.internalMap.getOrDefault(key, 0)^1); // XOR with 1 toggles parity
        }
        public int getParity(int key){
            return this.internalMap.getOrDefault(key, 0); // Returns 0 if key not present (even parity)
        }
        public Set<Map.Entry<Integer, Integer>> getEntries(){
            return this.internalMap.entrySet(); // Returns all entries to iterate over
        }
    }
    public static ParityMap getColumnParity(Scanner sc, int k){
        ParityMap map= new ParityMap();
        for(int i=0; i<k; i++){
            int x= sc.nextInt(); // Row coordinate (not used in computation)
            int y= sc.nextInt(); // Column coordinate - used to compute parity
            map.flip(y); // Toggle the parity count for that column
        }
        return map;
    }
    public static boolean isMimoWinner(long n, ParityMap map){
        if(n==1) return map.getParity(2)==1; // For single row, only column 2 matters
        else{
            // Check all columns >= 2 for odd parity (indicating a winning move exists)
            for(Map.Entry<Integer, Integer> pair:map.getEntries()){
                if(pair.getKey()>=2 && (pair.getValue()&1)==1) return true;
            }
        }
        return false; // No winning move possible for Mimo
    }
    public static void solve(Scanner sc){
        long n= sc.nextLong();
        long m= sc.nextLong();
        int k= sc.nextInt();
        ParityMap map= getColumnParity(sc, k); // Process all tokens and compute column parities
        boolean mimoWins= isMimoWinner(n, map); // Determine if Mimo wins based on parity
        if(mimoWins) System.out.println("Mimo");
        else System.out.println("Yuyu");
    }
}


// https://github.com/VaHiX/CodeForces/