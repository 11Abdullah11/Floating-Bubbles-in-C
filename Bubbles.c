#include <stdio.h>
#include <windows.h>
#include <conio.h>


void gotoXY(int, int);   
void bubble(char c[][140], int, int, int, int);
void hidecursor();


int main(void) {
	hidecursor();
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	system("color F2");
	char a[30][140]; 
	int row = 26, column,no_of_bubbles;
	gotoXY(25, 10);
	printf("Enter no. of bubbles:");
	gotoXY(25, 11);
	scanf_s("%d", &no_of_bubbles);
	int var = 10, up = 3, down = 3;
	char q = '1';
	gotoXY(90,37);
	printf("Press Up/Down to change size");
	while (1) {
		hidecursor();
		memset(a, ' ', 140*30 * sizeof(a[0][0]));

		srand(var);
		int temp_bubbles = no_of_bubbles;
		for (temp_bubbles; temp_bubbles > 0; temp_bubbles--) {
			column = rand() % 120 - up;
			bubble(a, row, column, up, down);
		}
		row--;


		if (_kbhit()) {
			if (GetAsyncKeyState(VK_UP) && up<7) {
				up++;
				down++;
			}
			if (GetAsyncKeyState(VK_DOWN) && up>2) {
				up--;
				down--;
			}
			q = _getch();
			if (q == '0') {
				break;
			}
		}

		if (row == 0 + up) {
			row = row + 26;
		}
		if (row == 26 + up) {
			var = var + 10;
		}

		for (int i = 0; i < 30; i++) {
			gotoXY(10, 7 + i);
			for (int j = 0; j < 140; j++) {
				printf("%c", a[i][j]);
			}
		}

	}
}


/*
Function taken from https://cboard.cprogramming.com/
to set cursor poistion
*/
void gotoXY(int x, int y) {
	COORD coord = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}

/*
Function to hide cursor 
taken from https://stackoverflow.com/questions/30126490/how-to-hide-console-cursor-in-c
*/
void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 10;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}
/*
Function to create bubble at given row and column
with width a and length b
*/
void bubble(char c[][140], int row, int column, int a, int b) {

	for (int r = column; r <= (column + a); r++)
	{
		for (int s = row; s >= (row - b); s--) {
			if (s<row && s>(row - b)) {
				if (r == column || r == (column + a))
					c[s][r] = '.';
			}
			if (s == row || s == (row - b))
			{
				if (r > column && r < (column + a))
					c[s][r] = '.';
			}
		}
	}

}
