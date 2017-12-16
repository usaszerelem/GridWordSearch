#pragma once

class CWordSearch
{
public:
	CWordSearch(const string strMatrixData);
	~CWordSearch();
	bool SearchWord(const string & strToSearch);

private:
	class Cell
	{
	public:
		inline Cell(char chInit = '\0') { ch = chInit; bVisited = false; }
		char	ch;
		bool	bVisited;
	};
	// ---------------------------------------------------------------------------
	// This global 2D array is initialized with the matrix of letters

	Cell MasterGrid[4][4];

	// ---------------------------------------------------------------------------
	// Throughout the program we are going to look at adjacent cells. This enum
	// will provide clarity on which adjacent cell we are looking at.

	enum CellDirection
	{
		Up,
		Down,
		Right,
		Left,
		UpperRight,
		LowerRight,
		UpperLeft,
		LowerLeft
	};

private:
	bool HasNeighbor(CellDirection dir, int row, int col, int * pRow, int * pCol);
	void ClearVisited();
	bool CheckNeighbors(int row, int col, const char *pszToSearch);
	bool FindChar(int row, int col, const char *pszToSearch);
};

