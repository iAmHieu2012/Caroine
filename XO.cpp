#include "Data.h"

void CreateConsoleWindow(int pWidth, int pHeight)
{
	// Tao console
	HWND consoleWindow = GetConsoleWindow(); // tra ve con tro thao tac console
	RECT r;									 // cau truc xac dinh hinh chu nhat goc tren ben phai va goc duoi ben trai.
	HANDLE hConsole;						 // khai bao bien hConsole kieu HANDLE

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);				// lay quyen dieu khien output tieu chuan
	SetConsoleTextAttribute(hConsole, 15 * 16 + 1);			// set thuoc tinh cua text, 240 là nen trang chu den
	GetWindowRect(consoleWindow, &r);						// truy xuat kich thuoc gioi han cua console
	MoveWindow(consoleWindow, 0, 0, pWidth, pHeight, TRUE); // di chuyen con tro toi toa do (0;0) va set kich thuoc window
}
void FixConsoleWindow()
{
	// disable maximize, resize, minimize
	HWND consoleWindow = GetConsoleWindow();			  // tra ve con tro thao tac console
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE); // truy xuat kieu cua console: dien mao, hanh vi...

	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME) & ~(WS_MINIMIZEBOX);
	/*
	dong nay sua doi bien style de vo hieu hoa phong to, thu nho, khung day (cho phep resize) cua cua so.
	toan tu bitwise AND (&) va  NOT (~) dung de xoa cac bit WS_MAXIMIZEBOX, WS_MINIMIZEBOX va WS_THICKFRAME theight bien style.
	*/
	SetWindowLong(consoleWindow, GWL_STYLE, style); // ap dung style vao window
}
void HideCursor(bool visible)
{
	// disappear con tro
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100; // lap day o con tro
	info.bVisible = visible;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void GotoXY(int x, int y)
{
	// di chuyen toi toa do (x,y)
	COORD coord;

	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void SetColor(int color)
{
	// set color tai o ma con tro dang dung
	HANDLE hConsole;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	// color your text in Windows console mode
	//  colors are 0=black 1=blue 2=green and so on to 15=white
	//  colorattribute = foreground + background * 16
}
_BufferInfo GetConsoleSize()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreen_BufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	_BufferInfo bf = {columns, rows};
	return bf;
}

vector<string> ReadFile(string filename)
{
	// doc file ghi vao vector
	std::fstream textFile;
	textFile.open(filename.c_str(), std::fstream::in);
	string line;
	std::vector<std::string> line1;
	while (getline(textFile, line))
		line1.push_back(line);
	textFile.close();
	return line1;
}

void DrawBox(int color, int width, int height, int x, int y, int delay)
{
	// ve box co vien theo mau
	SetColor(color);
	GotoXY(x, y);

	// Ve canh tren
	for (int i = 0; i < width; i++)
	{
		cout << " ";
	}
	// ve phan giua
	for (int i = 1; i <= height; i++)
	{
		Sleep(delay);
		GotoXY(x, y + i);
		cout << " ";
		SetColor(14 * 16 + 14);
		for (int j = 0; j < width - 2; j++)
		{
			cout << " ";
		}
		SetColor(color);
		cout << " ";
		SetColor(8 * 16 + 2);
		cout << " ";
		SetColor(color);
	}
	SetColor(color);
	GotoXY(x, y + height + 1);
	Sleep(delay);
	for (int i = 0; i < width; i++)
	{
		cout << " ";
	}
	SetColor(8 * 16 + 2);
	cout << " ";
	for (int i = 1; i <= width; i++)
	{
		GotoXY(x + i, y + height + 2);
		cout << " ";
	}
	SetColor(240);
}
void PrintText(string text, int color, int x, int y)
{
	// in text theo mau va nen
	GotoXY(x, y);
	SetColor(color);
	cout << text;
	SetColor(240);
}
void DrawFromFile(string filename, int color, int x, int y)
{
	int tempY = y;
	vector<string> line1 = ReadFile(filename);

	if (filename == "XWin.txt" || filename == "OWin.txt" || filename == "Draw.txt" || filename == "PWin.txt" || filename == "PLose.txt")
	{
		int turn = 0;
		while (1)
		{
			// Do file text animation co 4 frames nen moi co /4 ,%4...
			turn = turn % 4;
			for (int i = 0; i < line1.size() / 4; i++)
				PrintText(line1[i + 9 * turn], color + turn % 15, x, y++);
			y = tempY;
			Sleep(500);
			/*
			// Day la code nhap nhay text

			for (int i = 0; i < line1.size() / 4; i++)
			{
				string templine = "";
				for (int j = 0; j < line1[i + 9 * turn].length(); j++)
					templine += ' ';
				PrintText(templine, 240, x, y++);
			}
			Sleep(500);
			y = tempY;*/
			turn++;
			GotoXY(0, y);
			PrintText("Press any key to skip...", 240, x + 40, y + 10);
			if (_kbhit())
			{
				int kb = _getch();
				system("cls");
				break;
			};
		}
	}
	else
	{
		for (int i = 0; i < line1.size(); i++)
		{
			PrintText(line1[i], color, x, y);
			y++;
		}
	}
}


_Menu GetMenuProperties(int items, int color) {
	_Menu menu;
	menu.items = items;
	menu.color = color;
	return menu;
}
void MenuHighlight(int k)
{
	_BufferInfo bf = GetConsoleSize();
	switch (k)
	{
	case 1:
		DrawFromFile("NewGame.txt", 252, (bf.col - (int)ReadFile("NewGame.txt")[1].length()) / 2, bf.row - 30);
		DrawFromFile("LoadGame.txt", 240, (bf.col - (int)ReadFile("LoadGame.txt")[1].length()) / 2, bf.row - 25);
		break;
	case 2:
		DrawFromFile("NewGame.txt", 240, (bf.col - (int)ReadFile("NewGame.txt")[1].length()) / 2, bf.row - 30);
		DrawFromFile("LoadGame.txt", 252, (bf.col - (int)ReadFile("LoadGame.txt")[1].length()) / 2, bf.row - 25);
		DrawFromFile("About.txt", 240, (bf.col - (int)ReadFile("About.txt")[1].length()) / 2, bf.row - 20);
		break;
	case 3:
		DrawFromFile("LoadGame.txt", 240, (bf.col - (int)ReadFile("LoadGame.txt")[1].length()) / 2, bf.row - 25);
		DrawFromFile("About.txt", 252, (bf.col - (int)ReadFile("About.txt")[1].length()) / 2, bf.row - 20);
		DrawFromFile("Exit.txt", 240, (bf.col - (int)ReadFile("Exit.txt")[1].length()) / 2, bf.row - 15);
		break;
	case 4:
		DrawFromFile("About.txt", 240, (bf.col - (int)ReadFile("About.txt")[1].length()) / 2, bf.row - 20);
		DrawFromFile("Exit.txt", 252, (bf.col - (int)ReadFile("Exit.txt")[1].length()) / 2, bf.row - 15);
		break;
	}
}
int MenuAction()
{
	_BufferInfo bf = GetConsoleSize();
	int k = 1;
	DrawFromFile("NewGame.txt", 252, (bf.col - (int)ReadFile("NewGame.txt")[1].length()) / 2, bf.row - 30);
	do
	{
		int cmd = toupper(_getch());
		if ((cmd == 'S' || cmd == ARROW_DOWN) && k < 4)
		{
			k++;
			MenuHighlight(k);
		}
		else if ((cmd == 'W' || cmd == ARROW_UP) && k > 1)
		{
			k--;
			MenuHighlight(k);
		}
		else if ((cmd == KEY_ENTER))
		{
			return k;
		}
	} while (1);
}
int MainMenu()
{
	_BufferInfo bf = GetConsoleSize();
	DrawFromFile("Logo.txt", 240, (bf.col - (int)ReadFile("Logo.txt")[1].length()) / 2, 0);
	DrawFromFile("NewGame.txt", 240, (bf.col - (int)ReadFile("NewGame.txt")[1].length()) / 2, bf.row - 30);
	DrawFromFile("LoadGame.txt", 240, (bf.col - (int)ReadFile("LoadGame.txt")[1].length()) / 2, bf.row - 25);
	DrawFromFile("About.txt", 240, (bf.col - (int)ReadFile("About.txt")[1].length()) / 2, bf.row - 20);
	DrawFromFile("Exit.txt", 240, (bf.col - (int)ReadFile("Exit.txt")[1].length()) / 2, bf.row - 15);
	int k = MenuAction();
	return k;
}
void DrawTableLine(int ColNum, char mainSym, char subSym, int width)
{
	for (int i = 0; i < ColNum - 1; i++)
	{
		for (int i = 0; i < width; i++)
			cout << mainSym;
		cout << subSym;
	}
	for (int i = 0; i < width; i++)
		cout << mainSym;
}
void DrawBoard(int row, int col, int width, int height, int x, int y)
{
	system("cls");
	GotoXY(x, y);
	cout << TOP_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, TOP_CROSS, width);
	cout << TOP_RIGHT;

	for (int i = 0; i < (row - 1) * (height + 1); i++)
	{
		GotoXY(x, y + i + 1);
		if ((i + 1) % (height + 1) != 0)
		{
			cout << VERTICAL_LINE;
			DrawTableLine(col, SPACE, VERTICAL_LINE, width);
			cout << VERTICAL_LINE;
		}
		else
		{
			cout << LEFT_CROSS;
			DrawTableLine(col, HORIZONTAL_LINE, CROSS, width);
			cout << RIGHT_CROSS;
		}
	}
	for (int i = 0; i < height; i++)
	{
		GotoXY(x, y + (row - 1) * (height + 1) + 1 + i);
		cout << VERTICAL_LINE;
		DrawTableLine(col, SPACE, VERTICAL_LINE, width);
		cout << VERTICAL_LINE;
	}

	GotoXY(x, y + (row - 1) * (height + 1) + 1 + height);
	cout << BOTTOM_LEFT;
	DrawTableLine(col, HORIZONTAL_LINE, BOTTOM_CROSS, width);
	cout << BOTTOM_RIGHT;
}
void NewGame()
{
	// char a[16], b[16];

	// printf("Nhap ten nguoi choi thu nhat (2 - 16 ki tu)");
	// scanf_s("%s", &a);
	// system("cls");
	// printf("Nhap ten nguoi choi thu nhat (2 - 16 ki tu)");
	// scanf_s("%s", &b);
	// system("cls");
	DrawBoard(10, 10, 7, 3, 0, 0);
}
void RunMenu()
{
	int Player_choice = MainMenu();
	switch (Player_choice)
	{
	case 1:
		system("cls");
		NewGame();
		break;
	}
}

void YesNoHighlight(int k)
{
	_BufferInfo bf = GetConsoleSize();
	switch (k)
	{
	case 1:
		DrawFromFile("Yes.txt", 7 * 16 + 12, (bf.col - 60) / 2, (bf.row - 20));
		DrawFromFile("No.txt", 14 * 16 + 0, (bf.col + 15) / 2, (bf.row - 20));
		break;
	case 2:
		DrawFromFile("Yes.txt", 14 * 16 + 0, (bf.col - 60) / 2, (bf.row - 20));
		DrawFromFile("No.txt", 7 * 16 + 12, (bf.col + 15) / 2, (bf.row - 20));
		break;
	}
}
int AskContinueAction()
{
	_BufferInfo bf = GetConsoleSize();
	DrawFromFile("Yes.txt", 7 * 16 + 12, (bf.col - 60) / 2, (bf.row - 20));
	fflush(stdin);
	int k = 1;
	do
	{
		int cmd = toupper(_getch());
		if ((cmd == 'D' || cmd == ARROW_RIGHT) && k < 2)
		{
			k++;
			YesNoHighlight(k);
		}
		else if ((cmd == 'A' || cmd == ARROW_LEFT) && k > 1)
		{
			k--;
			YesNoHighlight(k);
		}
		else if (cmd == KEY_ENTER)
		{
			return k;
			break;
		}
	} while (1);
}
void AskContinueBox()
{
	_BufferInfo bf = GetConsoleSize();
	DrawBox(16, 100, 15, (bf.col - 100) / 2, (bf.row - 15) / 2, 50);

	DrawFromFile("Continue.txt", 14 * 16 + 5, (bf.col - 80) / 2, (bf.row - 28));
	DrawFromFile("Yes.txt", 14 * 16 + 0, (bf.col - 60) / 2, (bf.row - 20));
	DrawFromFile("No.txt", 14 * 16 + 0, (bf.col + 15) / 2, (bf.row - 20));
	int Action = AskContinueAction();
	if (Action == 1)
		printf("Tiep tuc");
	else if (Action == 2)
		printf("Nghi choi");
}

void End_game(int kq)
{
	_BufferInfo bf = GetConsoleSize();

	switch (kq)
	{
	case 1:
		system("cls");
		DrawFromFile("XWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
		AskContinueBox();
		break;
	case 0:
		system("cls");
		DrawFromFile("Draw.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
		AskContinueBox();
		break;
	case 2:
		system("cls");
		DrawFromFile("OWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
		AskContinueBox();
		break;
	case -1:
		system("cls");
		DrawFromFile("PWin.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
		AskContinueBox();
		break;
	case -2:
		system("cls");
		DrawFromFile("PLose.txt", 240, bf.col / 2 - 30, bf.row / 2 - 10);
		AskContinueBox();
		break;
	default:
		break;
	}
}
//#include <iostream>
//#include <Windows.h>
//#include <iostream>
//
//
//using namespace std;
//
//
//void main() {
//	HWND consoleWindow = GetConsoleWindow();
//	HANDLE hConsole;
//	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);	// lay quyen dieu khien output tieu chuan
//	for (int k = 0; k <= 255; k++) {
//		SetConsoleTextAttribute(hConsole, k);
//		cout <<k << " HELLO\n" << endl;
//	}
//}

int main()
{
	CreateConsoleWindow(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	FixConsoleWindow();
	system("cls");
	printf("p\np\np\np\np\np\np\np\np\np\np\np\np\np\np\n");
	HideCursor(false);
	// RunMenu();
	End_game(-1);
	system("pause");
	return 0;
}