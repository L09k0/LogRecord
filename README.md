# LogRecord

LogRecord Это легковесная одна файловая библиотека для записи и вывода на экран "логирования" написанная мной для личных нужд и клана iwc 


# Спецификация

Библиотека имеет поддержку разных типов данных, разделение сообщений на категории и запись конкретного времяни сообщения
Вот пример использования
```
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
```

Последний же параметр это, будет ли отображаться сообщение на экране/консоли

<img width="446" height="270" alt="image" src="https://github.com/user-attachments/assets/e93bb693-d15e-4123-9a66-98574e47be49" />


_Как показано здесь_


# Результат
<img width="468" height="356" alt="image" src="https://github.com/user-attachments/assets/619894c8-aa07-4b3b-a0f9-690265822187" />



_Результат выполнения программы, в файле_

# Всем спасибо за внимание !

