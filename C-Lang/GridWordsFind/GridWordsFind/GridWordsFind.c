#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <tchar.h>
#include <stdlib.h>  
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0

// ---------------------------------------------------------------------------
// I decided to use ANSI C notation, but in one case I need this Kerningham
// and Richie forward declaraction because the logic uses recursive calls.

BOOL FindChar(int row, int col, const char *pszToSearch);

// ---------------------------------------------------------------------------
// This definition holds one grid cell and the 4x4 grid is made up of this
// data definition type.

typedef struct tagCELL
{
	char ch;
	BOOL bVisited;
} CELL, *PCELL;

// ---------------------------------------------------------------------------
// This global 2D array is initialized with the matrix of letters

CELL MasterGrid[4][4];

// ---------------------------------------------------------------------------
// Throughout the program we are going to look at adjacent cells. This enum
// will provide clarity on which adjacent cell we are looking at.

typedef enum
{
	Up,
	Down,
	Right,
	Left,
	UpperRight,
	LowerRight,
	UpperLeft,
	LowerLeft
} CellDirection;

// ---------------------------------------------------------------------------
// This function checks relative from the provided cell in row, col has an
// adjacent cell. If it has then 'true' is returned an pRow and pCol is filled
// with that cell's location

BOOL HasNeighbor(CellDirection dir, int row, int col, int * pRow, int * pCol)
{
	BOOL Success = FALSE;

	switch (dir)
	{
	case Up:
		if (row > 0)
		{
			*pRow = row - 1;
			*pCol = col;
			Success = TRUE;
		}
		break;

	case Down:
		if (row < 3)
		{
			*pRow = row + 1;
			*pCol = col;
			Success = TRUE;
		}
		break;

	case Right:
		if (col < 3)
		{
			*pRow = row;
			*pCol = col + 1;
			Success = TRUE;
		}
		break;

	case Left:
		if (col > 0)
		{
			*pRow = row;
			*pCol = col - 1;
			Success = TRUE;
		}
		break;

	case UpperRight:
		if (row > 0 && col < 3)
		{
			*pRow = row - 1;
			*pCol = col + 1;
			Success = TRUE;
		}
		break;

	case LowerRight:
		if (row < 3 && col < 3)
		{
			*pRow = row + 1;
			*pCol = col + 1;
			Success = TRUE;
		}
		break;

	case UpperLeft:
		if (row > 0 && col > 0)
		{
			*pRow = row - 1;
			*pCol = col - 1;
			Success = TRUE;
		}
		break;

	case LowerLeft:
		if (col > 0 && row < 3)
		{
			*pRow = row + 1;
			*pCol = col - 1;
			Success = TRUE;
		}
		break;

	default:
		Success = FALSE;
		break;
	}

	return(Success);
}

// ---------------------------------------------------------------------------
// The 4 x 4 matrix is initiated with the provided list of characters.

BOOL InitMasterGrid(const char * pszCharList)
{
	BOOL bSuccess = TRUE;

	if (strlen(pszCharList) == 16)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				PCELL pCell = &MasterGrid[i][j];
				pCell->bVisited = FALSE;
				pCell->ch = *pszCharList++;
			}
		}
	}
	else
	{
		// Invalid Grid Size
		bSuccess = FALSE;
	}

	return(bSuccess);
}

// ---------------------------------------------------------------------------
// After a word was found, we need to clear the visited cells before searching
// for another word.

void ClearVisited()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			MasterGrid[i][j].bVisited = FALSE;
		}
	}
}

// ---------------------------------------------------------------------------
// Check whether the specified cell has a neighbor cell that matches the first
// character is the provided pszToSearch string. If there is a neighbor cell
// then call recursively the FindChar function to see if the neightboring
// character matches.

BOOL CheckNeighbors(int row, int col, const char *pszToSearch)
{
	BOOL Found = FALSE;
	int nNeighborCellRow, nNeighborCellCol;

	if (HasNeighbor(Up, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(Down, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(Left, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(Right, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(UpperLeft, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(UpperRight, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(LowerLeft, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	if (Found == FALSE && HasNeighbor(LowerRight, row, col, &nNeighborCellRow, &nNeighborCellCol) == TRUE)
	{
		Found = FindChar(nNeighborCellRow, nNeighborCellCol, pszToSearch);
	}

	// ------------------------------------------------------------------
	// If nothing was found surrounding this cell then we are backing
	// up, and this implies that the current cell path is not valid.
	// Therefore we clear the visited cell.
	// ------------------------------------------------------------------

	if (Found == FALSE)
	{
		MasterGrid[row][col].bVisited = FALSE;
	}

	return(Found);
}

// ---------------------------------------------------------------------------
// Determines whether the first charcter in *pszToSearch string matches the
// character at the matrix row and col position. There is also a need to check
// whether the character has been visited before.

BOOL FindChar(int row, int col, const char *pszToSearch)
{
	BOOL Found = FALSE;

	if (MasterGrid[row][col].bVisited == FALSE)
	{
		if (MasterGrid[row][col].ch == *pszToSearch)
		{
			MasterGrid[row][col].bVisited = TRUE;

			if (pszToSearch[1])
				Found = CheckNeighbors(row, col, pszToSearch + 1);
			else
				Found = TRUE;
		}
	}

	return(Found);
}

// ---------------------------------------------------------------------------
// This is the main function that is called to determine whether the provided
// string matches any pattern within the provided 4 x 4 array of characters.

BOOL SearchWord(const char * pszToSearch)
{
	BOOL Found = FALSE;

	for (size_t nIdx = 0; nIdx < strlen(pszToSearch) && Found == FALSE; nIdx++)
	{
		for (int row = 0; row < 4 && Found == FALSE; row++)
		{
			for (int col = 0; col < 4 && Found == FALSE; col++)
			{
				ClearVisited();
				Found = FindChar(row, col, pszToSearch);
			}
		}
	}

	return(Found);
}

// ---------------------------------------------------------------------------
// Method used to trim whitespace from a word. White spaces can be found in
// words read from a word text file.

static void TrimWhiteSpace(char * pszWord)
{
	unsigned int uStartIndex = 0;
	unsigned int uEndIndex = strlen(pszWord);

	// This should be valid or we have a programmer error.
	// I intentionally want this to burn during development
	// so that we catch programmer errors. Validation should
	// have been done higher up.

	assert(uEndIndex > 0);

	size_t CharsToMove = 0;

	// Leading
	while (isspace(pszWord[uStartIndex]))
	{
		uStartIndex++;
	}

	// Trailing
	while (isspace(pszWord[uEndIndex - 1]))
	{
		uEndIndex--;
	}

	if (uStartIndex != uEndIndex)
	{
		unsigned int uEndOffset = uEndIndex - uStartIndex;
		memmove(pszWord, &pszWord[uStartIndex], uEndOffset);
		pszWord[uEndOffset] = '\0';
	}
}

// ---------------------------------------------------------------------------
// Main entry point. The first argument to be passed is a word file to parse
// where each word is on a separate line. The second argument should be 16
// characters that will compose the 4 x 4 matrix to match the words in.

int main(int argc, char *argv[])
{
#ifdef TEST
	InitMasterGrid("zzzigznznnzzinzz");

	if (SearchWord("inning") == true)
		printf("Match: %s\n", "inning");

#endif // 

#define MAX_ONE_LINE 1024

	char * pszWordFile = argv[1];
	InitMasterGrid(argv[2]);

	FILE * hFile;

	if (!fopen_s(&hFile, pszWordFile, "r"))
	{
		// must have one extra character reserved for the EOL
		char * pszOneLine = (char *)malloc(MAX_ONE_LINE + 1);

		while (fgets(pszOneLine, MAX_ONE_LINE, hFile))
		{
			TrimWhiteSpace(pszOneLine);

			if (strlen(pszOneLine) > 2)
			{
				if (SearchWord(pszOneLine) == TRUE)
					printf("Match: %s\n", pszOneLine);
			}
		}

		free(pszOneLine);
		fclose(hFile);
	}
	else
	{
		printf("File not found: %s", pszWordFile);
	}

	return 0;
}
