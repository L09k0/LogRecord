#pragma once

#pragma warning(disable : 4996)

#define INFO_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INFO, PRINT)
#define WARNING_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_WARNING, PRINT)
#define ERROR_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_ERROR, PRINT)
#define FATALERROR_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_FATALERROR, PRINT)
#define REGISTER_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_REGISTER, PRINT)
#define INITIALIZATION_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INITIALIZATION, PRINT)
#define CLIENT_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_CLIENT, PRINT)
#define SERVER_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_SERVER, PRINT)
#define EXCEPTION_LOG(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_EXCEPTION, PRINT)

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip> 
#include <mutex>
#include <iostream>
#include <filesystem>
#include <codecvt>

class LogRecord
{
public:
	static LogRecord* GetInstance();
	LogRecord(const LogRecord&) = delete;
	LogRecord& operator=(const LogRecord&) = delete;

	enum class StatusMsg : int
	{
		_INFO,
		_WARNING,
		_ERROR,
		_FATALERROR,
		_REGISTER,
		_INITIALIZATION,
		_CLIENT,
		_SERVER,
		_EXCEPTION
	};

	void msg(const std::string& _msg, StatusMsg _statusmsg, bool print);
	void msg(const std::wstring& _msg, StatusMsg _statusmsg, bool print);
	void msg(const char* _msg, StatusMsg _statusmsg, bool print);
	void msg(const wchar_t* _msg, StatusMsg _statusmsg, bool print);

	template<class T>
	void msg(T msg, StatusMsg _statusmsg, bool print);

private:
	std::string filename;
	std::mutex logMut;
	std::ofstream file;

	explicit LogRecord();
	//LogRecord();
	~LogRecord();

	bool ExistLog();
	std::string GetTime(const char* format);
	std::string getFileName();
	std::string GetStatusString(StatusMsg status);

};

inline LogRecord::LogRecord()
{
	if (ExistLog())
	{
		file.open(getFileName(), std::ios::app);
		if (!file.is_open())
			std::cerr << "Failed to open log file!\n";

		if (std::filesystem::file_size(getFileName()) != 0)
			file << "\nStart log recording (" << GetTime("%H:%M:%S %Y-%m-%d") << ")\n";
		else
			file << "Start log recording (" << GetTime("%H:%M:%S %Y-%m-%d") << ")\n";

		file.close();
	}
}

inline LogRecord::~LogRecord()
{
	if (file.is_open())
		this->file.close();
}

inline bool LogRecord::ExistLog()
{
	try
	{
		if (!std::filesystem::is_directory("logs\\"))
			std::filesystem::create_directory("logs\\");

		if (!std::filesystem::exists(getFileName()))
		{
			std::ofstream file(getFileName(), std::ios::app);
			if (!file)
				std::cerr << "Log file not open!\n";

			file.close();
		}

		return true;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error in ExistLog: " << e.what() << "\n";
		return false;  
	}
}

inline std::string LogRecord::GetTime(const char* format)
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);
	std::tm tm = *std::localtime(&in_time_t);

	std::ostringstream ss;
	ss << std::put_time(&tm, format);
	return ss.str();
}

inline std::string LogRecord::getFileName()
{
	std::string filename
		= "logs\\"
		+ GetTime("%d-%m-%Y")
		+ ".log";

	return filename;
}

inline std::string LogRecord::GetStatusString(StatusMsg status)
{
	switch (status)
	{
	case LogRecord::StatusMsg::_INFO:
		return "[INFO]";
		break;
	case LogRecord::StatusMsg::_WARNING:
		return "[WARNING]";
		break;
	case LogRecord::StatusMsg::_ERROR:
		return "[ERROR]";
		break;
	case LogRecord::StatusMsg::_FATALERROR:
		return "[FATALERROR]";
		break;
	case LogRecord::StatusMsg::_REGISTER:
		return "[REGISTER]";
		break;
	case LogRecord::StatusMsg::_INITIALIZATION:
		return "[INITIALIZATION]";
		break;
	case LogRecord::StatusMsg::_CLIENT:
		return "[CLIENT]";
		break;
	case LogRecord::StatusMsg::_SERVER:
		return "[SERVER]";
		break;
	case LogRecord::StatusMsg::_EXCEPTION:
		return "[EXCEPTION]";
		break;
	default:
		return "[INFO]";
		break;
	}
}

LogRecord* LogRecord::GetInstance()
{
	static LogRecord instance;
	return& instance;
}

inline void LogRecord::msg(const std::string& msg, StatusMsg _statusmsg, bool print)
{
	std::lock_guard<std::mutex> lock(logMut);

	std::string statusMsg = GetStatusString(_statusmsg);
	std::string times = GetTime("%H:%M:%S");
	std::string engMsg = statusMsg + "[" + times + "]: " + msg + "\n";

	if (print)
		std::cout << engMsg;

	try
	{
		if (!file.is_open())
		{
			file.open(getFileName(), std::ios::app);
			if (!file.is_open())
			{
				std::cerr << "Failed to open log file for writing!\n";
				return;
			}
		}

		file << engMsg;
		file.flush();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to write to log file" << e.what() << "\n";
		if (file.is_open())
			file.close();
	}
}

inline void LogRecord::msg(const std::wstring& msg, StatusMsg _statusmsg, bool print)
{
	std::lock_guard<std::mutex> lock(logMut);

	std::string statusMsg = GetStatusString(_statusmsg);
	std::string times = GetTime("%H:%M:%S");

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string convertMsg = converter.to_bytes(msg);

	std::string engMsg = statusMsg + "[" + times + "]: " + convertMsg + "\n";

	if (print)
		std::wcout << statusMsg.c_str() << L"[" << times.c_str() << L"]: " << msg << L"\n";

	try
	{
		if (!file.is_open())
		{
			file.open(getFileName(), std::ios::app);
			if (!file.is_open())
			{
				std::cerr << "Failed to open log file for writing!\n";
				return;
			}
		}

		file << engMsg;
		file.flush();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Failed to write to log file" << e.what() << "\n";
		if (file.is_open())
			file.close();
	}
}

inline void LogRecord::msg(const char* _msg, StatusMsg _statusmsg, bool print)
{
	this->msg(std::string(_msg), _statusmsg, print);
}

inline void LogRecord::msg(const wchar_t* _msg, StatusMsg _statusmsg, bool print)
{
	this->msg(std::wstring(_msg), _statusmsg, print);
}

template<class T>
inline void LogRecord::msg(T msg, StatusMsg _statusmsg, bool print)
{
	std::lock_guard<std::mutex> lock(logMut);
	std::string statusMsg = GetStatusString(_statusmsg);
	std::string times = GetTime("%H:%M:%S");

	std::ostringstream oss;
	oss << msg;
	std::string msgStr = oss.str();

	std::string engMsg = statusMsg + "[" + times + "]: " + msgStr + "\n";

	if (print)
		std::cout << engMsg;

	try
	{
		if (!file.is_open())
		{
			file.open(getFileName(), std::ios::app);
			if (!file.is_open())
			{
				std::cerr << "Failed to open log file for writing!\n";
				return;
			}
		}

		file << engMsg;
		file.flush();
	}
	catch (const std::exception&)
	{
		std::cerr << "Failed to write to log file\n";
		if (file.is_open())
			file.close();
	}
}
