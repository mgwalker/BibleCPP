#include <stdio.h>
#include <iostream>
using namespace std;

class Bible
{
	public:
		Bible()
		{
			fp = fopen("Bible.dat","rb");
			if(fp == NULL)
			{
				cout << "Error opening file.  Quitting." << endl;
				return;
			}
			for(int i = 0; i < 66; i++)
			{
				char offset[4];
				fread(Books[i], 1, 20, fp);
				Books[i][20] = 0;
				fread(offset, 1, 4, fp);
				Offsets[i] = (((unsigned int)offset[0] & 0xff) << 24) | (((unsigned int)offset[1] & 0xff) << 16) | (((unsigned int)offset[2] & 0xff) << 8) | ((unsigned int)offset[3] & 0xff);
			}
		}
		~Bible()
		{
			fclose(fp);
		}
		
		char* getBookName(int id)
		{
			if(id < 1 || id > 66)
				return "No such book.";
			return Books[--id];
		}

		int getBookNum(char* name)
		{
			for(int i = 0; i < 66; i++)
			{
				if(strlen(name) == strlen(Books[i]))
				{
					int j = 0;
					for(; j < strlen(name); j++)
					{
						if((Books[i][j] | 0x20) != (name[j] | 0x20))
							break;
					}
					if(j == strlen(name))
						return i + 1;
				}
			}
			return -1;
		}

		int getNumChapters(int Book)
		{
			Book--;
			if(Book > 65 || Book < 0)
				return -1;

			char* buff = new char[1];
			fseek(fp, Offsets[Book], SEEK_SET);
			fread(buff, 1, 1, fp);
            return (((int)buff[0]) & 0xff);
		}

		char* getVerse(int Book, int Chapter, int Verse)
		{
			// Let the caller use 1-based indexing because
			// that's more logical.

			Book--;
			if(Book > 65 || Book < 0)
				return "No such book.";

			char* buff = new char[4];
			fseek(fp, Offsets[Book], SEEK_SET);
            fread(buff, 1, 1, fp);
			if(Chapter > (((int)buff[0]) & 0xff))
				return "No such chapter.";

			Chapter--;
			fseek(fp, Chapter * 3, SEEK_CUR);
			fread(buff, 1, 3, fp);
			int chOffset = (((unsigned int)buff[0] & 0xff) << 16) | (((unsigned int)buff[1] & 0xff) << 8) | ((unsigned int)buff[2] & 0xff);

            fseek(fp, Offsets[Book] + chOffset, SEEK_SET);
			fread(buff, 1, 1, fp);
			if(Verse > (((int)buff[0]) & 0xff))
				return "No such verse.";

			int verse = 1;
			fread(buff, 1, 2, fp);
			int len = (((unsigned int)buff[0] & 0xff) << 8) | ((unsigned int)buff[1] & 0xff);
			while(verse < Verse)
			{
				fseek(fp, len, SEEK_CUR);
				fread(buff, 1, 2, fp);
				len = (((unsigned int)buff[0] & 0xff) << 8) | ((unsigned int)buff[1] & 0xff);
				verse++;
			}
			buff = new char[len + 1];
			memset(buff, 0, len + 1);
			fread(buff, 1, len, fp);
			return buff;
		}

	private:
		FILE* fp;
		char Books[66][21];
		unsigned int Offsets[66];
	
/*
	char* buff = new char[10];
	for(int bookNum = 0; bookNum < 66; bookNum++)
	{
		cout << Books[bookNum] << " has ";
		fseek(fp, Offsets[bookNum], SEEK_SET);
		fread(buff, 1, 1, fp);
		int chapters = ((int)buff[0]) & 0xff;
		cout << chapters << " chapters" << endl;
		fread(buff, 1, 3, fp);
		int chapterOffset = (((unsigned int)buff[0] & 0xff) << 16) | (((unsigned int)buff[1] & 0xff) << 8) | ((unsigned int)buff[2] & 0xff);
		fseek(fp, Offsets[bookNum] + chapterOffset, SEEK_SET);
		cout << "Chapter 1 has ";
		fread(buff, 1, 1, fp);
		int verses = ((int)buff[0]) & 0xff;
		cout << verses << " verses" << endl;
		cout << Books[bookNum] << " 1:1 - ";
		fread(buff, 1, 2, fp);
		int len = (((int)buff[0] & 0xff) << 8) | ((int)buff[1] & 0xff);
		char* verse = new char[len + 1];
		memset(verse, 0, len + 1);
		fread(verse, 1, len, fp);
		cout << verse << endl << endl;
	}

	*/
};