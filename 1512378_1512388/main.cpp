// 1512378_1512388.cpp : Defines the entry point for the console application.
//
#pragma once
#include "QInt.h"
#include "FileHandler.h"


int main(int argc, char* argv[])
{
	if (argc == 3)
	{
		ProcessedFile(argv[1], argv[2]);
	}
	system("pause");
	return 0;
}

