namespace Problems
{
    public class P2136A
    {
        public static void Main(string[] args)
        {
            var numberOfTests = int.Parse(Console.ReadLine());

            for (int i = 0; i < numberOfTests; i++)
            {
                var inputs = Console.ReadLine()
                    .Split(' ')
                    .Select(int.Parse)
                    .ToArray();

                var a = inputs[0];
                var b = inputs[1];
                var c = inputs[2];
                var d = inputs[3];

                var result = IsScorePossible(a, b, c, d);
                Console.WriteLine(result ? "YES" : "NO");
            }
        }

        public static bool IsScorePossible(int a, int b, int c, int d)
        {
            // The score of the 1st half isn't relevant for checking the score of the 2nd half.
            return IsScorePossible(a, b) && IsScorePossible(c - a, d - b);
        }

        public static bool IsScorePossible(int a, int b)
        {
            // Ensure biggest number is in a
            if (b > a)
                (a, b) = (b, a); // swap

            // Don't divide by zero
            if (b == 0)
            {
                return a <= 2; // 0:0, 1:0 and 2:0 are ok
            }

            return (a - 2) <= (2 * b);
        }
    }
}
