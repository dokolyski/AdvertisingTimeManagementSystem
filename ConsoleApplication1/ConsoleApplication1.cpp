// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.

#include "pch.h"
#include "Application.h"
#include <Windows.h>

int main()
{
	FreeConsole();
	Application a;
	a.doApplication();
	return 0;
}
