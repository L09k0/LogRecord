# LogRecord

LogRecord Это легковесная одна файловая библиотека для записи и вывода на экран "логирования" написанная мной для личных нужд и клана iwc 


# Спецификация

Библиотека имеет поддержку пись разных типов данных, разделение сообщений на категории и запись конкретного времяни сообщения
Вот пример использования
```
#include <iostream>
#include "LogRecord.h"

int main()
{
	LogRecord::GetInstance()->msg("String", LogRecord::StatusMsg::_INFO, true); // Запись типа std::string
	LogRecord::GetInstance()->msg(L"String", LogRecord::StatusMsg::_INFO, true); // Запись типа std::wstring
	LogRecord::GetInstance()->msg(12345, LogRecord::StatusMsg::_INFO, true); // Запись типа int
	LogRecord::GetInstance()->msg(3.14, LogRecord::StatusMsg::_INFO, true); // Запись типа double

	return 0;
}
```
Первый параметр передаваемый в метод msg сама строка, второй ее категория, категорий есть 6 видов
```
		INFO,
		WARNING,
		ERROR,
		FATALERROR,
		REGISTER,
		INITIALIZATION,
		CLIENT,
		SERVER,
		EXCEPTION
```


Последний же параметр это, будет ли отображаться сообщение на экране/консоли

<img width="462" height="166" alt="image" src="https://github.com/user-attachments/assets/49245d7b-1460-4d33-b206-2e5a68b670d3" />

_Как показано здесь_


# Результат
<img width="449" height="200" alt="image" src="https://github.com/user-attachments/assets/0bc1574c-807d-4d9f-8c0c-bb307f5737e6" />

_Результат выполнения программы, в файле_

Всем спасибо за внимание !

