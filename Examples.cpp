#include "LogRecord.h"

int main()
{
	// Test Status
	INFO_LOG("String", true);
	WARNING_LOG("String", true);
	ERROR_LOG("String", true);
	FATALERROR_LOG("String", true);
	REGISTER_LOG("String", true);
	INITIALIZATION_LOG("String", true);
	CLIENT_LOG("String", true);
	SERVER_LOG("String", true);
	EXCEPTION_LOG("String", true);

	// Test type
	INFO_LOG(L"WString", true);
	INFO_LOG(12345, true);
	INFO_LOG(3.14, true);

	// Test visible console
	INFO_LOG("String", false);

	system("pause");
	return 0;
}