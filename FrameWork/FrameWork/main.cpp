#include "Headers.h"




//** ���� ����
SCENEID SceneState = SCENEID_LOGO;

Object* pPlayer = NULL;
Object* pBullet[BULLET_MAX] = { NULL };
Object* pMonster[MONSTER_MAX] = { NULL };

//** SceneManager
void SceneManager();

//** InputManager
DWORD InputManager();

//** Ŀ�� ��ǥ�� �̵���Ű�� �̵��� ��ġ���� �ش� �÷������� ���ڿ��� ���.
void SetCursorPosition(const int _ix, const int _iy, const char* str, const int _Color);

//** Ŀ�� ����
void SetCursorHide();

//** ���ڿ� �÷� ����
void SetColor(int _Color);

//** ������ �̸��� ����
char* SetName();

//** ��ü�� �����ϴ� �Լ�
Object* CreateObject();

//** ��ü�� �ʱ�ȭ�ϴ� �Լ�
void Initialize(Object* _pUser);

//** �÷��̾��� ��ġ�� �����ϴ� �Լ�
void SetPlayerPosition();

//** SetPosition(���� ���, ������ ��)
void SetPosition(Vector3* _vPos, Vector3 _point);


int main()
{
	SetCursorHide();

	pPlayer = CreateObject();

	//** GetTickCount = 1/1000 ��
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
	DWORD dwTime = GetTickCount();

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
		if (dwKey & KEY_SPACE)
		{
			SceneState = SCENEID_STAGE;
		}
		break;
	case SCENEID_STAGE:
		printf_s("SCENEID_STAGE\n");
		
		//** Ű üũ
		SetPlayerPosition();

		//** ���
		SetCursorPosition(
			int(pPlayer->Position.x),
			int(pPlayer->Position.y),
			pPlayer->Name, 15);

		for (int i = 0; i < BULLET_MAX; ++i)
		{
			if (pBullet[i])
			{
				pBullet[i]->Position.x += 2;

				SetCursorPosition(
					int(pBullet[i]->Position.x),
					int(pBullet[i]->Position.y),
					pPlayer->Name, 15);

				if (pBullet[i]->Position.x > 100)
				{
					free(pBullet[i]);
					pBullet[i] = NULL;
				}
			}

		}
		if (dwTime + 1000 < GetTickCount())
		{
			dwTime = GetTickCount();

			for (int i = 0; i < MONSTER_MAX; ++i)
			{
				if (!pMonster[i])
				{
					pMonster[i] = CreateObject();
					SetPosition(&pMonster[i]->Position, Vector3(100, pPlayer->Position.y, 0));
					break;
				}

				if (pMonster[i])
				{
					pMonster[i]->Position.x -= 2;

					SetCursorPosition(
						int(pMonster[i]->Position.x),
						int(pMonster[i]->Position.y),
						"��", 15);

					if (pMonster[i]->Position.x < 0)
					{
						free(pMonster[i]);
						pMonster[i] = NULL;
					}
				}
			}
		}
		break;
	default:
		break;
	}


}


DWORD InputManager()
{
	DWORD dwKey = 0;

	//** Ű �Է�
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
Object* CreateObject()
{
	//** ���� �Ҵ�
	Object* pUser = (Object*)malloc(sizeof(Object));

	//** Initialzie
	pUser->Name = (char*)"��";// SetName();
	pUser->Position = Vector3(10.f, 10.f);

	//** ��ȯ
	return pUser;
}

void Initialize(Object* _pUser)
{
	_pUser->Name = (char*)"��"; // SetName();
	_pUser->Position = Vector3(0.f, 0.f);
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
	if (dwKey & KEY_SPACE)
	{
		for (int i = 0; i < BULLET_MAX; ++i)
		{
			if (!pBullet[i])
			{
				pBullet[i] = CreateObject();
				SetPosition(&pBullet[i]->Position, pPlayer->Position);
				break;
			}
		}
	}
}

void SetPosition(Vector3* _vPos, Vector3 _point)
{
	_vPos->x = _point.x;
	_vPos->y = _point.y;
}