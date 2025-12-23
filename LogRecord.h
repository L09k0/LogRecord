#pragma once

#pragma warning(disable : 4996)

#include <fstream>
#include <string>
#include <chrono>
#include <iomanip> 
#include <mutex>
#include <iostream>
#include <filesystem>

class LogRecord
{
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

	void msg(std::string msg, StatusMsg _statusmsg, bool print);
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
		// f
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

LogRecord* LogRecord::GetInstance()
{
	static LogRecord instance;
	return& instance;
}

inline void LogRecord::msg(std::string msg, StatusMsg _statusmsg, bool print)
{
	std::lock_guard<std::mutex> lock(logMut);
	std::string statusmsg;
	switch (_statusmsg)
	{
	case LogRecord::StatusMsg::_INFO:
		statusmsg = "[INFO]";
		break;
	case LogRecord::StatusMsg::_WARNING:
		statusmsg = "[WARNING]";
		break;
	case LogRecord::StatusMsg::_ERROR:
		statusmsg = "[ERROR]";
		break;
	case LogRecord::StatusMsg::_FATALERROR:
		statusmsg = "[FATALERROR]";
		break;
	case LogRecord::StatusMsg::_REGISTER:
		statusmsg = "[REGISTER]";
		break;
	case LogRecord::StatusMsg::_INITIALIZATION:
		statusmsg = "[INITIALIZATION]";
		break;
	case LogRecord::StatusMsg::_CLIENT:
		statusmsg = "[CLIENT]";
		break;
	case LogRecord::StatusMsg::_SERVER:
		statusmsg = "[SERVER]";
		break;
	case LogRecord::StatusMsg::_EXCEPTION:
		statusmsg = "[EXCEPTION]";
		break;
	default:
		statusmsg = "[INFO]";
		break;
	}

	if (print != false)
		std::cout << statusmsg << "[" << GetTime("%H:%M:%S") << "]: " << msg << "\n";

	file.open(getFileName(), std::ios::app);
	if (file.is_open())
		file << statusmsg << "[" << GetTime("%H:%M:%S") << "]: " << msg << /*" adrr \"" << GetInstance() <<*/ "\n";
	else
		std::cerr << "Log file not open !\n";

	file.close();
}
