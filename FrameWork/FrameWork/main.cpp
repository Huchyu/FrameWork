#include "Headers.h"






//** Ŀ�� ��ǥ�� �̵���Ű�� �̵��� ��ġ���� �ش� �÷������� ���ڿ��� ���.
void SetCursorPosition(const int _ix, const int _iy, const char* str, const int _Color);

//** Ŀ�� ����
void SetCursorHide();

//** ���ڿ� �÷� ����
void SetColor(int _Color);

//** ������ �̸��� ����
char* SetName();

//** ��ü�� �����ϴ� �Լ�
User* CreateUser();

//** InputManager
DWORD InputManager();


const int MAX = 10;


int main()
{
	User* pObjList[OBJECT_MAX];

	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		pObjList[i] = (User*)malloc(sizeof(User));
		pObjList[i]->Name = SetName();
		pObjList[i]->Position = Vector3(0.f, 0.f);
	}

	for (int i = 0; i < OBJECT_MAX; ++i)
	{
		printf_s("%s\n", pObjList[i]->Name);
	}
	printf_s("\n");

	printf_s("%s\n", pObjList[OBJECT_PLAYER]->Name);
	printf_s("%s\n", pObjList[OBJECT_MONSTER]->Name);
	printf_s("%s\n", pObjList[OBJECT_BULLET]->Name);


	system("pause");




	SetCursorHide();

	User* pPlayer = CreateUser();

	//** GetTickCount = 1/1000 ��
	DWORD dwTime = GetTickCount();


	while (true)
	{
		if (dwTime + 50 < GetTickCount())
		{
			dwTime = GetTickCount();
			system("cls");

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


			//** ���
			SetCursorPosition(
				int(pPlayer->Position.x),
				int(pPlayer->Position.y),
				pPlayer->Name, 15);
		}
	}

	system("pause");
	return 0;
}




//** Ŀ�� ��ǥ�� �̵���Ű�� �̵��� ��ġ���� �ش� �÷������� ���ڿ��� ���.
void SetCursorPosition(const int _ix, const int _iy, const char* str, const int _Color)
{
	//** ��ǥ�� ���´�.
	COORD Pos;
	Pos.X = _ix;	//* x ��ǥ ����
	Pos.Y = _iy;	//* y ��ǥ ����

	//** �ܼ�â�� ������ Ŀ���� ��ǥ �̵� ������ ���´�.
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);

	//** �Լ� ���ǿ��� ����....
	SetColor(_Color);

	//** ���ڿ� ���
	printf_s("%s", str);
}

//** Ŀ�� ����
void SetCursorHide()
{
	//** GetStdHandle(STD_OUTPUT_HANDLE) = ���� �ܼ�â�� ���� ������ ���´�.
	HANDLE hCursor = GetStdHandle(STD_OUTPUT_HANDLE);

	//** Ŀ���� ������ ����ִ� ����ü
	CONSOLE_CURSOR_INFO Info;
	Info.dwSize = 100;
	Info.bVisible = FALSE;

	//** Ŀ���� �Ⱥ��̰� ����.
	SetConsoleCursorInfo(hCursor, &Info);
}


void SetColor(int _Color)
{
	//** �ܼ�â�� ������ Ŀ���� �÷��� ���� ������ ���´�.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _Color);
}


char* SetName()
{
	char str[128] = "";

	printf_s("�Է� : ");
	scanf_s("%s", str, 128);

	char* pName = (char*)malloc(strlen(str) + 1);
	strcpy(pName, str);

	return pName;
}

//** ��ü�� �����ϴ� �Լ�
User* CreateUser()
{
	//** ���� �Ҵ�
	User* pUser = (User*)malloc(sizeof(User));

	//** Initialzie
	pUser->Name = (char*)"��";// SetName();
	pUser->Position = Vector3(10.f, 10.f);

	//** ��ȯ
	return pUser;
}


DWORD InputManager()
{
	DWORD dwKey = 0;

	//** Ű �Է�
	if (GetAsyncKeyState(VK_UP))
	{
		dwKey |= KEY_UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		dwKey |= KEY_DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		dwKey |= KEY_LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		dwKey |= KEY_RIGHT;
	}

	return dwKey;
}