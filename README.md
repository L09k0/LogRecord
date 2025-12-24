# LogRecord

LogRecord Это легковесная одна файловая библиотека для записи и вывода на экран "логирования" написанная мной для личных нужд и клана iwc 


# Спецификация

Библиотека имеет поддержку разных типов данных, разделение сообщений на категории и запись конкретного времяни сообщения
Вот пример использования
```
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
```

Последний же параметр это, будет ли отображаться сообщение на экране/консоли

<img width="446" height="270" alt="image" src="https://github.com/user-attachments/assets/e93bb693-d15e-4123-9a66-98574e47be49" />


_Как показано здесь_


# Результат
<img width="501" height="365" alt="image" src="https://github.com/user-attachments/assets/269feb31-a435-4825-9b5a-639e7ba1f573" />


_Результат выполнения программы, в файле_

# Всем спасибо за внимание !

