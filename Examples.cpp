#include "LogRecord.h"

int main()
{
	// Test Status
	INFO_MSG("String", true);
	WARNING_MSG("String", true);
	ERROR_MSG("String", true);
	FATALERROR_MSG("String", true);
	REGISTER_MSG("String", true);
	INITIALIZATION_MSG("String", true);
	CLIENT_MSG("String", true);
	SERVER_MSG("String", true);
	EXCEPTION_MSG("String", true);

	// Test type
	INFO_MSG(L"WString", true);
	INFO_MSG(12345, true);
	INFO_MSG(3.14, true);

	// Test visible console
	INFO_MSG("String", false);

	system("pause");
	return 0;
}