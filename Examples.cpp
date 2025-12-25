#include "LogRecord.h"

int main()
{
	// Test Args
	LOGINFO("Test no args");
    LOGINFO("Test args \"true\"", true);
    LOGINFO("Test args \"false\"", false);

	// Test status
	LOGINFO("LOGINFO");
	LOGWARNING("LOGWARNING");
	LOGERROR("LOGERROR");
	LOGFATALERROR("LOGFATALERROR");
	LOGREGISTER("LOGREGISTER");
	LOGINITIALIZATION("LOGINITIALIZATION");
	LOGCLIENT("LOGCLIENT");
	LOGSERVER("LOGSERVER");
	LOGEXCEPTION("LOGEXCEPTION");

	// Test type
	LOGINFO("std::string");
	LOGINFO(L"std::wstring");
	LOGINFO(12345);
	LOGINFO(3.14);

	system("pause");
	return 0;
}