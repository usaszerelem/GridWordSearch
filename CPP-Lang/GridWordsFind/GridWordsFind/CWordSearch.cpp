#include "stdafx.h"
using namespace std;

// ---------------------------------------------------------------------------

//CWordSearch::CWordSearch(const char * pszMatrixPrimeData)
CWordSearch::CWordSearch(const string strMatrixData)
{
	if (strMatrixData.length() != 16)
	{
		throw new CAppException("Ensure to provide 16 characters for the 4x4 matrix.");
	}

	const char * pszMatrixPrimeData = strMatrixData.c_str();

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Cell * pCell = &MasterGrid[i][j];
			pCell->ch = *pszMatrixPrimeData++;
		}
	}
}

// ---------------------------------------------------------------------------

CWordSearch::~CWordSearch()
{
}

// ---------------------------------------------------------------------------
// This is the main function that is called to determine whether the provided
// string matches any pattern within the provided 4 x 4 array of characters.

bool CWordSearch::SearchWord(const string & strToSearch)
{
	bool Found = false;
	ClearVisited();

	for (size_t nIdx = 0; nIdx < strToSearch.length() && Found == false; nIdx++)
	{
		for (int row = 0; row < 4 && Found == false; row++)
		{
			for (int col = 0; col < 4 && Found == false; col++)
			{
				Found = FindChar(row, col, strToSearch.c_str());
			}
		}
	}

	return(Found);
}

// ---------------------------------------------------------------------------
// After a word was found, we need to clear the visited cells before searching
// for another word.

void CWordSearch::ClearVisited()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MasterGrid[i][j].bVisited = false;
		}
	}
}

// ---------------------------------------------------------------------------
// This function checks relative from the provided cell in row, col has an
// adjacent cell. If it has then 'true' is returned an pRow and pCol is filled
// with that cell's location

bool CWordSearch::HasNeighbor(CellDirection dir, int row, int col, int * pRow, int * pCol)
{
	bool Success = false;

	switch (dir)
	{
	case Up:
		if (row > 0)
		{
			*pRow = row - 1;
			*pCol = col;
			Success = true;
		}
		break;

	case Down:
		if (row < 3)
		{
			*pRow = row + 1;
			*pCol = col;
			Success = true;
		}
		break;

	case Right:
		if (col < 3)
		{
			*pRow = row;
			*pCol = col + 1;
			Success = true;
		}
		break;

	case Left:
		if (col > 0)
		{
			*pRow = row;
			*pCol = col - 1;
			Success = true;
		}
		break;

	case UpperRight:
		if (row > 0 && col < 3)
		{
			*pRow = row - 1;
			*pCol = col + 1;
			Success = true;
		}
		break;

	case LowerRight:
		if (row < 3 && col < 3)
		{
			*pRow = row + 1;
			*pCol = col + 1;
			Success = true;
		}
		break;

	case UpperLeft:
		if (row > 0 && col > 0)
		{
			*pRow = row - 1;
			*pCol = col - 1;
			Success = true;
		}
		break;

	case LowerLeft:
		if (col > 0 && row < 3)
		{
			*pRow = row + 1;
			*pCol = col - 1;
			Success = true;
		}
		break;

	default:
		Success = false;
		break;
	}

	return(Success);
}

// ---------------------------------------------------------------------------
// Check whether the specified cell has a neighbor cell that matches the first
// character is the provided pszToSearch string. If there is a neighbor cell
// then call recursively the FindChar function to see if the neightboring
// character matches.

bool CWordSearch::CheckNeighbors(int row, int col, const char *pszToSearch)
{
	bool Found = false;
	int nNeighborCellRow, nNeighborCellCol;

	if (HasNeighbor(Up, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(Down, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(Left, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(Right, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(UpperLeft, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(UpperRight, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(LowerLeft, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == false && HasNeighbor(LowerRight, row, col, &nNeighborCellRow, &nNeighborCellCol) == true)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	// ------------------------------------------------------------------
	// If nothing was found surrounding this cell then we are backing
	// up, and this implies that the current cell path is not valid.
	// Therefore we clear the visited cell.
	// ------------------------------------------------------------------

	if (Found == false)
	{
		MasterGrid[row][col].bVisited = false;
	}

	return(Found);
}

// ---------------------------------------------------------------------------
// Determines whether the first charcter in *pszToSearch string matches the
// character at the matrix row and col position. There is also a need to check
// whether the character has been visited before.

bool CWordSearch::FindChar(int row, int col, const char *pszToSearch)
{
	bool Found = false;

	if (MasterGrid[row][col].bVisited == false)
	{
		if (MasterGrid[row][col].ch == *pszToSearch)
		{
			MasterGrid[row][col].bVisited = true;

			if (pszToSearch[1])
				Found = CheckNeighbors(row, col, pszToSearch + 1);
			else
				Found = true;
		}
	}

	return(Found);
}


