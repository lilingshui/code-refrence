#include <iostream>
#include <stdio.h>
#include "logexport.h"

int main(int argc, char** argv)
{
	SetLogLevel(LEVEL_DEBUG);
	LogD("Hello World!");
	return 0;
}
