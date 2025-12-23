#include "LogRecord.h"

#include <locale>
#include <iostream>


int main()
{
	setlocale(NULL, "Russian");

	LogRecord::GetInstance()->msg("Launch Run !", LogRecord::StatusMsg::_INFO, true);

	return 0;
}