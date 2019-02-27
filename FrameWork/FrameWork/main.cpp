#include "Headers.h"




//** 전역 변수
SCENEID SceneState = SCENEID_LOGO;

User* pPlayer = CreateUser();



//** SceneManager
void SceneManager();

//** InputManager
DWORD InputManager();

//** 커서 좌표를 이동시키고 이동한 위치에서 해당 컬러값으로 문자열을 출력.
void SetCursorPosition(const int _ix, const int _iy, const char* str, const int _Color);

//** 커서 숨김
void SetCursorHide();

//** 문자열 컬러 변경
void SetColor(int _Color);

//** 유저의 이름을 셋팅
char* SetName();

//** 객체를 생성하는 함수
User* CreateUser();




void SetPlayerPosition();


int main()
{
	SetCursorHide();

	pPlayer = CreateUser();

	//** GetTickCount = 1/1000 초
	DWORD dwTime = GetTickCount();


	while (true)
	{
		if (dwTime + 50 < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

			SceneManager();

		}
	}

	system("pause");
	return 0;
}


void SceneManager()
{
	DWORD dwKey = InputManager();

	switch (SceneState)
	{
	case SCENEID_LOGO:
		printf_s("SCENEID_LOGO\nKEY_ENTER\n");
		if (dwKey & KEY_ENTER)
		{
			SceneState = SCENEID_MENU;
		}
		break;
	case SCENEID_MENU:
		printf_s("SCENEID_MENU\nKEY_SPACE\n");
		if (dwKey & KEY_ENTER)
		{
			SceneState = SCENEID_STAGE;
		}
		break;
	case SCENEID_STAGE:
		printf_s("SCENEID_STAGE\n");
		
		//** 키 체크
		SetPlayerPosition();

		//** 출력
		SetCursorPosition(
			int(pPlayer->Position.x),
			int(pPlayer->Position.y),
			pPlayer->Name, 15);
		break;
	default:
		break;
	}


}


DWORD InputManager()
{
	DWORD dwKey = 0;

	//** 키 입력
	if (GetAsyncKeyState(VK_UP))
		dwKey |= KEY_UP;

	if (GetAsyncKeyState(VK_DOWN))
		dwKey |= KEY_DOWN;

	if (GetAsyncKeyState(VK_LEFT))
		dwKey |= KEY_LEFT;

	if (GetAsyncKeyState(VK_RIGHT))
		dwKey |= KEY_RIGHT;

	if (GetAsyncKeyState(VK_RETURN))
		dwKey |= KEY_ENTER;

	if (GetAsyncKeyState(VK_SPACE))
		dwKey |= KEY_SPACE;

	return dwKey;
}

//** 커서 좌표를 이동시키고 이동한 위치에서 해당 컬러값으로 문자열을 출력.
void SetCursorPosition(const int _ix, const int _iy, const char* str, const int _Color)
{
	//** 좌표를 갖는다.
	COORD Pos;
	Pos.X = _ix;	//* x 좌표 설정
	Pos.Y = _iy;	//* y 좌표 설정

	//** 콘솔창의 권한중 커서의 좌표 이동 권한을 갖는다.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	//** 함수 정의에서 설명....
	SetColor(_Color);

	//** 문자열 출력
	printf_s("%s", str);
}

//** 커서 숨김
void SetCursorHide()
{
	//** GetStdHandle(STD_OUTPUT_HANDLE) = 현재 콘솔창의 접근 권한을 갖는다.
	HANDLE hCursor = GetStdHandle(STD_OUTPUT_HANDLE);

	//** 커서의 정보를 담고있는 구조체
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 100;
	Info.bVisible = FALSE;

	//** 커서를 안보이게 설정.
	SetConsoleCursorInfo(hCursor, &Info);
}


void SetColor(int _Color)
{
	//** 콘솔창의 권한중 커서의 컬러값 변경 권한을 갖는다.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}


char* SetName()
{
	char str[128] = "";

	printf_s("입력 : ");
	scanf_s("%s", str, 128);

	char* pName = (char*)malloc(strlen(str) + 1);
	strcpy(pName, str);

	return pName;
}

//** 객체를 생성하는 함수
User* CreateUser()
{
	//** 동적 할당
	User* pUser = (User*)malloc(sizeof(User));

	//** Initialzie
	pUser->Name = (char*)"옷";// SetName();
	pUser->Position = Vector3(10.f, 10.f);

	//** 반환
	return pUser;
}


void SetPlayerPosition()
{
	DWORD dwKey = InputManager();

	if (dwKey & KEY_UP)
	{
		pPlayer->Position.y -= 1;
	}
	if (dwKey & KEY_DOWN)
	{
		pPlayer->Position.y += 1;
	}
	if (dwKey & KEY_LEFT)
	{
		pPlayer->Position.x -= 2;
	}
	if (dwKey & KEY_RIGHT)
	{
		pPlayer->Position.x += 2;
	}
}