#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

typedef struct {
	int x, y;
}Pos;

typedef struct {
	char MonsterU;
	char MonsterI;
	char MonsterJ;
	char MonsterL;
	char player;
}Object;

// 커서 숨기기 or 두께조절
void RemoveCursor()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	// 1. 현재 커서 정보를 가져옴
	GetConsoleCursorInfo(hConsole, &cursorInfo);

	// 2. 가시성 옵션을 FALSE로 설정
	cursorInfo.bVisible = FALSE;

	// 3. 변경된 정보를 적용
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// 화면 초기화
void ClearScreen()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD topLeft = { 0, 0 }; // 시작점은 왼쪽 맨 위
	DWORD written;

	// 콘솔 창의 가로 x 세로 크기를 구해야 전체를 채울 수 있음.
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	DWORD size = csbi.dwSize.X * csbi.dwSize.Y;

	// 화면 전체를 공백(' ')으로 채우기
	FillConsoleOutputCharacter(hConsole, ' ', size, topLeft, &written);

	// 커서 위치도 다시 (0, 0)으로 되돌려주는 게 국룰
	SetConsoleCursorPosition(hConsole, topLeft);
}

// 위치
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { (short)x, (short)y };
	SetConsoleCursorPosition(hConsole, pos);
}

void GameRule(int x, int y)
{
	gotoxy(x, y);
	printf("===========================");
	gotoxy(x, y + 1);
	printf("|       Shooting Game     |");
	gotoxy(x, y + 2);
	printf("===========================");

	gotoxy(x - 8, y + 5);
	printf("움직임 : WASD");
	Sleep(1000);

	gotoxy(x - 8, y + 6);
	printf("슈팅 : U, I, J, K");
	Sleep(1000);

	gotoxy(x - 8, y + 8);
	printf("제한시간 안에 최대한 많은 몬스터를 죽여주세요! 목숨은 3개입니다!");
	Sleep(1000);

	gotoxy(x - 8, y + 10);
	printf("플레이어를 적의 위치까지 이동시켜 적절한 키를 입력하세요!");
	Sleep(1000);

	gotoxy(x - 8, y + 12);
	printf("틀릴경우 목숨이 줄어듭니다!");
	Sleep(1000);

	gotoxy(x - 8, y + 14);
	printf("그럼 슈팅게임 시작하겠습니다!");
	Sleep(1000);

	gotoxy(x - 8, y + 16);
	printf("아무키나 눌러주세요!");

	_getch();
	ClearScreen();
}



int main()
{
	Object object = { '!', '@', '#', '$', '+' };
	RemoveCursor();
	GameRule(48, 2);

}

// 게임적 기능
// 1. 랜덤으로 나오는 몬스터를 잡는 게임 목숨은 3개
// 2. 플레이어가 몬스터와 좌표가 겹친 상태로 몬스터에게 맞는 버튼을 누르면
// 3. 몬스터가 사라지고 다른 랜덤한 좌표에서 재생성
// 4. n초 안에 n번 성공하면 클리어

// 코드적 기능
// 1. SetConsoleCursorInfo를 사용해서 커서를 숨기고 SetConsoleCursorPosition을 사용해서 게임설명
// 2. 게임설명을 끝내면 FillConsoleOutputCharacter를 사용해서 화면을 지운 후에 본격적인 게임 코드 실행
// 3.
// 4.