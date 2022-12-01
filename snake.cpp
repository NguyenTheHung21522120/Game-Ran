
#include<iostream>
using namespace std;

#include <vector>
#include <windows.h>
#include <conio.h>
#include <cstring>
#include <time.h>
#define WIDTH 40
#define HEIGHT 20
#define BODY '*'
#define APPLE "0"

enum class Direction
{
	up,
	right,
	down,
	left
};

struct Point
{
	int x;
	int y;
};
//vector snake
vector<Point> snake = {
	Point{ WIDTH / 2 + 2, HEIGHT / 2 },
	Point{ WIDTH / 2 + 1, HEIGHT / 2 },
	Point{ WIDTH / 2, HEIGHT / 2 },
	Point{ WIDTH / 2 - 1, HEIGHT / 2 },
	Point{ WIDTH / 2 - 2, HEIGHT / 2 }
};
Direction direction = Direction::right;
Point apple;
Point prevTail;
int score = 0;
int speed = 300;
int level;
void drawSnakePart(Point);
void drawSnake();
void genApple();
void gotoxy(int, int);
void ShowConsoleCursor(bool);
void move();
void drawBox();
void drawHeadnTail();
bool isBiteItself();
bool isHitWall();
bool isAteApple();
void displayScore();
void showEndMenu();
void startGame();
void resetSnake();
void showStartMenu();
int levelacdtospeed();



int main()
{
	showStartMenu();
	return 0;
}
void drawBox() // ve khung
{
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	gotoxy(0, HEIGHT);
	for (size_t i = 0; i < WIDTH; i++)
		cout << '=';
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(0, i);
		cout << '|';
	}
	for (size_t i = 1; i < HEIGHT; i++)
	{
		gotoxy(WIDTH, i);
		cout << '|';
	}
}



bool isHitWall() //dam tuong
{
	return snake[0].x == 0 || snake[0].y == 0 || snake[0].x == WIDTH || snake[0].y == HEIGHT;
}

void showEndMenu()
{
	system("cls");
	gotoxy(0, 0);
	cout << "Game over!" << endl;
	cout << "Diem : " << score << endl;
	cout << "ban muon choi lai khong ([y]/[n]): ";
	char option;
	cin >> option;
	option = tolower(option);
	if (option == 'y')
	{
		resetSnake();
		startGame();
	}
	else if (option == 'n')
		exit(1);

}

void startGame() // bat dau game
{
	system("cls");
	ShowConsoleCursor(false);//An con tro chuot
	drawBox();
	drawSnake();//ve con ran
	genApple(); 
	level = levelacdtospeed();
	displayScore();
	while (true)//dinh nghia di chuyen ran
	{
		if (_kbhit())
		{
			char ch = _getch();
			ch = tolower(ch);
			if (ch == 'a' && direction != Direction::right)
				direction = Direction::left;
			else if (ch == 'w' && direction != Direction::down)
				direction = Direction::up;
			else if (ch == 's' && direction != Direction::up)
				direction = Direction::down;
			else if (ch == 'd' && direction != Direction::left)
				direction = Direction::right;
			else if (ch == 'u')
			{
				if (speed > 100)
					speed -= 100;
				else if (speed == 100)
				{
					gotoxy(WIDTH / 4 - 1, HEIGHT + 1);
					cout << "You hav gained max level";
					Sleep(1000);
					gotoxy(WIDTH / 4 - 1, HEIGHT + 1);
					cout << "\b                         ";

				}
			}
			else if (ch == 'i')
			{
				if (speed < 500)
					speed += 100;
				else if (speed == 500)
				{
					gotoxy(WIDTH / 4 - 1, HEIGHT + 1);
					cout << "You hav gained min level";
					Sleep(1000);
					gotoxy(WIDTH / 4 - 1, HEIGHT + 1);
					cout << "\b                         ";

				}
			}
			level = levelacdtospeed();
			displayScore();
		}
		move();//di chuyen ran
		drawHeadnTail();//set lai ran moi
		if (isAteApple())//An tao thi ran lon
		{
			score++;
			displayScore();
		}
		if (isHitWall())//dam tuong thi thoat
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		if(isBiteItself())
		{
			ShowConsoleCursor(true);
			showEndMenu();
			break;
		}
		Sleep(speed);
	}

}
void resetSnake()
{
	score = 0;
	direction = Direction::right;
	snake = {
		Point{ WIDTH / 2 + 2, HEIGHT / 2 },
		Point{ WIDTH / 2 + 1, HEIGHT / 2 },
		Point{ WIDTH / 2, HEIGHT / 2 },
		Point{ WIDTH / 2 - 1, HEIGHT / 2 },
		Point{ WIDTH / 2 - 2, HEIGHT / 2 }
	};
}
	
void showStartMenu()
{
		system("cls");
		cout << "Welcome to snake game!" << endl;
		cout << "Team : 5 Anh em sieu nhan " << endl;
		cout << "  ==============" << endl;
		cout << "Menu :" << endl;
	black:
		cout << "1. Start" << endl;
		cout << "2. Exit" << endl;
		cout << "Your choice: ";
		int option;
		cin >> option;

		if (option == 1)
		{
			system("cls");
			cout << "Choose your level (1 - 5): ";
			int t;
			cin >> t;
			while (t < 1 || t > 5)
			{
				system("cls");
				cout << "Your level is not exsist !! Choose again (1 - 5) : ";
				cin >> t;
			}
			speed = 600 - t * 100;
			level = speed / 100;
			system("cls");
			cout << "Tip: While playing game, you can press 'e' to exit";
			gotoxy(0, 3);
			cout << "Ready!";
			Sleep(1000);
			for (size_t i = 3; i > 0; i--)
			{
				gotoxy(0, 3);
				cout << i << "         ";
				Sleep(1000);
			}
			gotoxy(0, 3);
			cout << "Bat dau!";
			Sleep(1000);
			startGame();
		}
		else if (option == 2)
			exit(1);
		else
		{
			system("cls");
			cout << "Khong ton tai lua chon nay`. Vui long nhap lai !!" << endl;
			goto black;
		}
}
void drawSnakePart(Point p)//ve 1 diem tren than ran
{
	gotoxy(p.x, p.y);
	cout << BODY;
}

void drawSnake()//ve con ran
{
	for (size_t i = 0; i < snake.size(); i++)
		drawSnakePart(snake[i]);
}

void move()//di chuyen ran
{
	prevTail = snake.back();
	for (size_t i = snake.size() - 1; i > 0; i--)
		snake[i] = snake[i - 1];
	if (direction == Direction::up)
		snake[0].y -= 1;
	else if (direction == Direction::down)
		snake[0].y += 1;
	else if (direction == Direction::left)
		snake[0].x -= 1;
	else if (direction == Direction::right)
		snake[0].x += 1;
}

bool isBiteItself()
{
    Point head = snake[0];
    for (size_t i = 1; i < snake.size(); i++)
        if (head.x == snake [i].x && head.y == snake[i].y)
        return true;
    return false;
}

void drawHeadnTail()//tao vi tri moi, xoa vi tri cu khi di chuyen
{
	gotoxy(snake[0].x, snake[0].y);
	cout << BODY;
	gotoxy(prevTail.x, prevTail.y);
	cout << ' ';
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}
void ShowConsoleCursor(bool showFlag)// an con tro chuot
{
	HANDLE out =GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}


//them tao
void genApple()
{
	srand(time(0));
	int x = rand() % (WIDTH - 1) + 1;
	int y = rand() % (HEIGHT - 1) + 1;
	apple = {
		x,
		y,
	};
	gotoxy(x, y);
	cout << "\033[1;31m" << APPLE << "\033[0m";
}
//An Tao
bool isAteApple()
{
	return snake[0].x == apple.x && snake[0].y == apple.y;
}
//Tinh diem 
void displayScore()
{
	gotoxy(WIDTH + 5, 2);
	cout << "Your score: " << score << endl;
	gotoxy(WIDTH + 5, 4);
	cout << "-- Guide --" << endl;
	gotoxy(WIDTH + 5, 5);
	cout << "UP : W" << endl;
	gotoxy(WIDTH + 5, 6);
	cout << "DOWN : S" << endl;
	gotoxy(WIDTH + 5, 7);
	cout << "LEFT : A" << endl;
	gotoxy(WIDTH + 5, 8);
	cout << "RIGHT : D" << endl;
	gotoxy(WIDTH + 5, 9);
	cout << "-- Option --" << endl;
	gotoxy(WIDTH + 5, 10);
	cout << "EXIT : E" << endl;
	gotoxy(WIDTH + 5, 11);
	cout << "Up level : U" << endl;
	gotoxy(WIDTH + 5, 12);
	cout << "Down level : I" << endl;
	gotoxy(WIDTH + 5, 15);
	cout << "Your Level : " << level;
}

int levelacdtospeed() {
	if (speed == 100)
	{
		return 5;

	}
	else if (speed == 200)
	{
		return 4;
	}
	else if (speed == 300)
	{
		return 3;
	}
	else if (speed == 400)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}


