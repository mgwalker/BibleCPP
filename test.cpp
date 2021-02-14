#include "Bible.h"
#include <iostream>
#include <string>
using namespace std;

enum BibleBooks{GENESIS=1,EXODUS,LEVITICUS,NUMBERS,DEUTERONOMY,JOSHUA,JUDGES,RUTH,SAMUEL1,
                SAMUEL2,KINGS1,KINGS2,CHRONICLES1,CHRONICLES2,EZRA,NEHEMIA,ESTHER,JOB,
				PSALMS,PROVERBS,ECCLESIASTES,SONG_OF_SONGS,ISAIAH,JEREMIAH,LAMENTATIONS,
				EZEKIEL,DANIEL,HOSEA,JOEL,AMOS,OBADIAH,JONAH,MICAH,NAHUM,HABAKKUK,
				ZEPHANIAH,HAGGAI,ZECHARIAH,MALACHI,MATTHEW,MARK,LUKE,JOHN,ACTS,ROMANS,
				CORINTHIANS1,CORINTHIANS2,GALATIANS,EPHESIANS,PHILIPPIANS,COLOSSIANS,
				THESSALONIANS1,THESSALONIANS2,TIMOTHY1,TIMOTHY2,TITUS,PHILEMON,HEBREWS,
				JAMES,PETER1,PETER2,JOHN1,JOHN2,JOHN3,JUDE,REVELATION};

int main()
{
	Bible myBible;

	char* input = new char[20];
	char* buffr = new char[512];
	int book, chapter, verse;

	while(true)
	{
		cout << "Enter a book name, or QUIT to exit: ";
		cin.getline(input, 20);
		if(strcmp(input,"QUIT") == 0)
			break;
		book = myBible.getBookNum(input);
		cout << "  Chapter: ";
		cin >> chapter;
		cout << "    Verse: ";
		cin >> verse;
		cout << myBible.getBookName(book) << " " << chapter << ":" << verse << " - ";
		cout << myBible.getVerse(book, chapter, verse) << endl << endl;
		cin.get();
	}

	return 0;
}