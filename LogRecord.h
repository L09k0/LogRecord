#pragma once

#pragma warning(disable : 4996)

//#define LOGINFO(MSG, ...) LOGINFO_BOOL(##__VA_ARGS__)
//
//#define LOGINFO_BOOL(PRINT) \
//	LogRecord::GetInstance()->msg(PRINT, LogRecord::StatusMsg::_INFO, true)
//
//#define WRITELOG_INFO(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INFO, PRINT)
//#define WRITELOG_WARNING(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_WARNING, PRINT)
//#define WRITELOG_ERROR(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_ERROR, PRINT)
//#define WRITE_FATALERROR(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_FATALERROR, PRINT)
//#define WRITE_REGISTER(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_REGISTER, PRINT)
//#define WRITE_INITIALIZATION(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INITIALIZATION, PRINT)
//#define WRITE_CLIENT(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_CLIENT, PRINT)
//#define WRITE_SERVER(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_SERVER, PRINT)
//#define WRITE_EXCEPTION(MSG, PRINT) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_EXCEPTION, PRINT)
//
////#define PRINT_INFO_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INFO, false)
//#define PRINT_WARNING_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_WARNING, false)
//#define PRINT_ERROR_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_ERROR, false)
//#define PRINT_FATALERROR_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_FATALERROR, false)
//#define PRINT_REGISTER_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_REGISTER, false)
//#define PRINT_INITIALIZATION_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_INITIALIZATION, false)
//#define PRINT_CLIENT_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_CLIENT, false)
//#define PRINT_SERVER_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_SERVER, false)
//#define PRINT_EXCEPTION_LOG(MSG) LogRecord::GetInstance()->msg(MSG, LogRecord::StatusMsg::_EXCEPTION, false)


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
		_INIT,
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

template<class T>
constexpr auto LOGINFO(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_INFO, false);
}

template<class T1, class T2>
constexpr auto LOGINFO(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_INFO, PRINT);
}

template<class T>
constexpr auto LOGWARNING(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_WARNING, false);
}

template<class T1, class T2>
constexpr auto LOGWARNING(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_WARNING, PRINT);
}

template<class T>
constexpr auto LOGERROR(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_ERROR, false);
}

template<class T1, class T2>
constexpr auto LOGERROR(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_ERROR, PRINT);
}

template<class T>
constexpr auto LOGFATALERROR(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_FATALERROR, false);
}

template<class T1, class T2>
constexpr auto LOGFATALERROR(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_FATALERROR, PRINT);
}

template<class T>
constexpr auto LOGREGISTER(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_REGISTER, false);
}

template<class T1, class T2>
constexpr auto LOGREGISTER(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_REGISTER, PRINT);
}

template<class T>
constexpr auto LOGINIT(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_INIT, false);
}

template<class T1, class T2>
constexpr auto LOGINIT(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_INIT, PRINT);
}

template<class T>
constexpr auto LOGCLIENT(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_CLIENT, false);
}

template<class T1, class T2>
constexpr auto LOGCLIENT(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_CLIENT, PRINT);
}

template<class T>
constexpr auto LOGSERVER(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_SERVER, false);
}

template<class T1, class T2>
constexpr auto LOGSERVER(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_SERVER, PRINT);
}

template<class T>
constexpr auto LOGEXCEPTION(T&& MSG) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T>(MSG), LogRecord::StatusMsg::_EXCEPTION, false);
}

template<class T1, class T2>
constexpr auto LOGEXCEPTION(T1 MSG, T2 PRINT) -> decltype(auto)
{
	return LogRecord::GetInstance()->msg(std::forward<T1>(MSG), LogRecord::StatusMsg::_EXCEPTION, PRINT);
}

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
