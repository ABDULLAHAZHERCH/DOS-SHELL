
#include"DOS.h"

using namespace std;

int main()
{
	DOS Shell;
	system("cls");
	Shell.CopyRight();
	while (true)
	{
		Shell.Execute();
	}

	return 0;
}