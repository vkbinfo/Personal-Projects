#ifndef SUDOKU_GRID_H_
#define SUDOKU_GRID_H_

class sudoku_grid {

	public:
		void print();
		void fillGrid();
		void solve();
		// REQUIRES: All preset values already input to grid


	private:
		cell grid[9][9];

		bool rowCheck(int row, int val);
		// Returns false if val is already on row
		bool colCheck(int col, int val);
		// Returns false if val is already on col
		bool miniGridCheck(int row, int col, int val);
		// Returns false if val is already in miniGrid
		int returnPossibleValue(int row, int col);
		void solve_helper(int row, int col, bool backTrack);


};

void sudoku_grid::print() {
	std::cout << "\nGRID:\n";
	for (int i=0; i<9; i++) {
		for (int j=0; j<9; j++) {
			std::cout << "|" << grid[i][j].currentValue;
		}
		std::cout << "|\n";
	}
	std::cout << '\n';
}

void sudoku_grid::fillGrid() {
	std::cout << "Enter '-1' as row to exit\n";
	while (true) {
		int row, col, val;
		std::cout << "\nEnter row: ";
		std::cin >> row;
		if (row == -1) {
			break;
		}
		std::cout << "\nEnter column: ";
		std::cin >> col;
		std::cout << "\nEnter value: ";
		std::cin >> val;
		if ((val <= 0) || (val >= 10)) {
			std::cout << "Incorrect value entered. Please try again.\n";
		} else {
			grid[row][col].currentValue = val;
			grid[row][col].preset = true;
		}
	}
}

bool sudoku_grid::rowCheck(int row, int val) {
	for (int i=0; i < 9; i++) {
		if (grid[row][i].currentValue == val) {
			return false;
		}
	}
	return true;
}

bool sudoku_grid::colCheck(int col, int val) {
	for (int i=0; i < 9; i++) {
		if (grid[i][col].currentValue == val) {
			return false;
		}
	}
	return true;
}

bool sudoku_grid::miniGridCheck(int row, int col, int val) {
	for (int i = (row/3)*3; i < ((row/3)*3)+3; i++) {
		for (int j = (col/3)*3; j < ((col/3)*3)+3; j++) {
			if (grid[i][j].currentValue == val) {
				return false;
			}
		}
	}
	return true;
}

int sudoku_grid::returnPossibleValue(int row, int col) {
	for (int i=1; i < 10; i++) {
		if (rowCheck(row, i) && colCheck(col, i) && miniGridCheck(row, col, i) && i>grid[row][col].currentValue) {
			return i;
		}
	}
	return 0;
}

void sudoku_grid::solve_helper(int row, int col, bool backTrack) {
	// Below checks preset value in cell and either proceeds forward or backTracks if in backTracking mode
	// Print function used for testing
	if (grid[row][col].preset == true) {
		if (backTrack == true) {
			if (col == 0) {
				if (row == 0) {
					std::cout << "No Solution1\n";
					return;
				}
				return solve_helper(row-1, 8, true);
			}
			return solve_helper(row, col-1, true);
		}
		if (col == 8) {
			if (row == 8) {
				std::cout << "Complete\n";
				return;
			}
			return solve_helper(row+1, 0, false);
		}
		return solve_helper(row, col+1, false);
	}
	grid[row][col].currentValue = returnPossibleValue(row, col);
	if (grid[row][col].currentValue == 0) {
		if (col == 0) {
			if (row == 0) {
				std::cout << "No Solution\n";
				return;
			}
			return solve_helper(row-1, 8, true);
		}
		return solve_helper(row, col-1, true);
	}
	if (col == 8) {
		if (row == 8) {
			std::cout << "Complete\n";
			return;
		}
		return solve_helper(row+1, 0, false);
	}
	return solve_helper(row, col+1, false);
}

void sudoku_grid::solve() {
	solve_helper(0, 0, false);
	return;
}


#endif
