// GridWordsFind.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// ---------------------------------------------------------------------------
// Main entry point to our little command line application

int main(int argc, char *argv[])
{
	try
	{
		CWordSearch WordSearch(CHelper::ToLower(string(argv[2])));

		string strOneWord;

		ifstream WordFile(argv[1]);

		if (WordFile.is_open())
		{
			while (getline(WordFile, strOneWord))
			{
				if (strOneWord.length() <= 2)
					continue;

				if (WordSearch.SearchWord(CHelper::ToLower(strOneWord)) == true)
				{
					cout << "Match: " << strOneWord << endl;
				}
			}

			WordFile.close();
		}
		else
		{
			throw new CAppException("File not found");
		}
	}
	catch (CAppException * pEx)
	{
		cout << pEx->what() << endl;
		delete pEx;

		cout << "Ensure to provide 16 characters for the 4x4 matrix." << endl;
		cout << "Syntax: GridWords.exe <WordFile.txt> <16 characters>" << endl;
	}

    return 0;
}

