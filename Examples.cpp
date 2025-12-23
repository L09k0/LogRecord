#include <locale>
#include <iostream>

#include "LogRecord.h"

int main()
{
	setlocale(NULL, "Russian");

	LogRecord::GetInstance()->msg("std::string", LogRecord::StatusMsg::_INFO, true);
	LogRecord::GetInstance()->msg(L"std::wstring", LogRecord::StatusMsg::_INFO, true);
	LogRecord::GetInstance()->msg(1, LogRecord::StatusMsg::_INFO, true);
	LogRecord::GetInstance()->msg(1.1, LogRecord::StatusMsg::_INFO, true);

	system("pause");
	return 0;
}