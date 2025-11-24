# Problem: CF 1991 G - Grid Reset
# https://codeforces.com/contest/1991/problem/G

class GridResetSolver:
    """A solver for the Grid Reset problem, processing operations on a grid.

    This class handles multiple test cases, each involving an n x m grid with q
    operations (horizontal 'H' or vertical 'V'). Each operation selects a 1xk or
    kx1 rectangle, and the solver outputs the top-left coordinates. It assumes
    operations are always possible, as per the original logic, without tracking
    the grid state or handling impossible cases.

    Algorithms/Techniques: 
    - Greedy placement strategy based on grid dimensions and operation types
    - Special cases handling for square grids, and grids with dimensions equal to k
    - State tracking for row/column indices to simulate operation sequence

    Time Complexity: O(q) where q is the number of operations, as each operation
    is processed in constant time with no nested loops.

    Space Complexity: O(q) for storing operation coordinates and intermediate state.
    """

    def __init__(self):

        self.row_count = 0

        self.column_count = 0

        self.rectangle_size = 0

        self.operation_count = 0

        self.operation_sequence = ""

        self.operation_coordinates = []

    def read_test_case_count(self):
        """Reads the number of test cases.

        Returns:
            int: The number of test cases.
        """
        return int(input())

    def read_test_case(self):
        """Reads parameters and operations for a single test case.

        Updates the instance variables with the grid dimensions, rectangle size,
        operation count, and operation sequence.
        """

        params = input().split()
        self.row_count = int(params[0])
        self.column_count = int(params[1])
        self.rectangle_size = int(params[2])
        self.operation_count = int(params[3])

        self.operation_sequence = input().strip()

        self.operation_coordinates = []

    def process_square_grid(self):
        """Handles the case where row_count == rectangle_size and column_count == rectangle_size.

        For a square grid where both dimensions equal the rectangle size, every
        operation uses the top-left corner (1, 1), as the entire row or column is
        covered and reset.
        """
        for _ in range(self.operation_count):
            self.operation_coordinates.append((1, 1))

    def process_rows_equal_size(self):
        """Handles the case where row_count == rectangle_size.

        Horizontal operations cycle through rows starting from 1, while vertical
        operations always use the last column.
        """

        current_row = 0
        for op in self.operation_sequence:
            if op == "H":
                current_row = (current_row % self.row_count) + 1
                self.operation_coordinates.append((current_row, 1))
            else:
                self.operation_coordinates.append((1, self.column_count))

    def process_columns_equal_size(self):
        """Handles the case where column_count == rectangle_size.

        Vertical operations cycle through columns starting from 1, while horizontal
        operations always use the last row.
        """

        current_column = 0
        for op in self.operation_sequence:
            if op == "V":
                current_column = (current_column % self.column_count) + 1
                self.operation_coordinates.append((1, current_column))
            else:
                self.operation_coordinates.append((self.row_count, 1))

    def process_general_case(self):
        """Handles the general case where row_count != rectangle_size and column_count != rectangle_size.

        Uses a strategy to select rows and columns, adjusting indices based on the
        original logic with reset points for rows and columns.
        """

        next_row_index = self.row_count

        next_column_index = self.column_count

        kResetRow = self.rectangle_size

        kResetColumn = self.rectangle_size

        kInitialRow = self.rectangle_size
        kInitialColumn = self.rectangle_size

        for op in self.operation_sequence:
            if op == "H":
                self.operation_coordinates.append((next_row_index, 1))
                next_row_index -= 1
                if next_row_index == 0:
                    if next_column_index <= self.rectangle_size:
                        kResetColumn = next_column_index
                        next_column_index = self.column_count
                        next_row_index = kInitialRow
                    else:
                        next_row_index = self.row_count
                elif next_row_index == self.rectangle_size:
                    next_row_index = kResetRow
                    kResetRow = kInitialRow
            else:
                self.operation_coordinates.append((1, next_column_index))
                next_column_index -= 1
                if next_column_index == 0:
                    if next_row_index <= self.rectangle_size:
                        kResetRow = next_row_index
                        next_row_index = self.row_count
                        next_column_index = kInitialColumn
                    else:
                        next_column_index = self.column_count
                elif next_column_index == self.rectangle_size:
                    next_column_index = kResetColumn
                    kResetColumn = kInitialColumn

    def process_test_case(self):
        """Processes a single test case by selecting the appropriate case handler.

        Determines the case based on grid dimensions and rectangle size, then
        calls the corresponding method to compute coordinates.
        """
        self.read_test_case()
        if (
            self.row_count == self.rectangle_size
            and self.column_count == self.rectangle_size
        ):
            self.process_square_grid()
        elif self.row_count == self.rectangle_size:
            self.process_rows_equal_size()
        elif self.column_count == self.rectangle_size:
            self.process_columns_equal_size()
        else:
            self.process_general_case()

    def print_results(self):
        """Prints the coordinates for all operations in the current test case.

        Outputs each coordinate pair on a new line in the format 'row col'.
        """
        for row, col in self.operation_coordinates:
            print(f"{row } {col }")

    def run(self):
        """Runs the solver for all test cases.

        Reads the number of test cases, processes each one, and outputs results.
        """
        test_case_count = self.read_test_case_count()
        for _ in range(test_case_count):
            self.process_test_case()
            self.print_results()


if __name__ == "__main__":

    solver = GridResetSolver()
    solver.run()


# https://github.com/VaHiX/CodeForces/