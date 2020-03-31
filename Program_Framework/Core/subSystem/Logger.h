#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

#include "ISubSystem.h"

enum class LoggerType { ERR, WAR, INF, DEB };

class Logger final : public ISubSystem {
public:
	static Logger& GetInstance() {
		static Logger* _instance = new Logger();
		return *_instance;
	}

	bool initLogService(const std::wstring& _filepath) {
		fid.open(_filepath);
		if (fid.is_open()) isFileOpen = true;
	}
	void info(const std::wstring& _msg) { writeLog(LoggerType::INF, _msg); }

	template<typename ...Args>
	void info(const std::wstring& _format, const Args&... args) {
		wchar_t buf[256];
		swprintf_s(buf, 256, _format.data(), args...);
		info(buf);
	}

	void warn(const std::wstring& _msg) { writeLog(LoggerType::WAR, _msg); }
	void warn(const std::wstring& _msg, const std::exception* _ex) {
		writeLog(LoggerType::WAR, _msg, _ex);
	}

	void error(const std::wstring& _msg) { writeLog(LoggerType::ERR, _msg); }
	void error(const std::wstring& _msg, const std::exception* _ex) {
		writeLog(LoggerType::ERR, _msg, _ex);
	}

	void debug(const std::wstring& _msg) { writeLog(LoggerType::DEB, _msg); }
	void debug(const std::wstring& _msg, const std::exception* _ex) {
		writeLog(LoggerType::DEB, _msg, _ex);
	}

private:
	bool isFileOpen;
	std::wofstream fid;
	std::wstring logFormat = L"%s [%s] : %s";

	Logger() : isFileOpen(false) {};
	virtual ~Logger() {
		if (isFileOpen) fid.close();
	}

	void writeLog(const LoggerType& _type, const std::wstring& _msg,
		const std::exception* _ex = nullptr) {
		time_t now = time(0);
		tm ltm;
		localtime_s(&ltm, &now);

		wchar_t buf[256];
		wcsftime(buf, 256, L"%F %T", &ltm);

		std::wstring logType;
		switch (_type) {
		case LoggerType::ERR:
			logType = L"ERROR";
			break;

		case LoggerType::WAR:
			logType = L"WARNING";
			break;

		case LoggerType::INF:
			logType = L"INFO";
			break;

		case LoggerType::DEB:
			logType = L"DEBUG";
			break;
		}
		wchar_t logMsgBuf[256];
		swprintf_s(logMsgBuf, 256, logFormat.data(), buf, logType.data(), _msg.data());
		std::wcout << logMsgBuf << std::endl;
		if (_ex) std::wcout << _ex->what() << std::endl;
		if (isFileOpen) {
			fid << logMsgBuf << std::endl;
			if (_ex) fid << _ex->what() << std::endl;
		}
	}
};

#define _Logger Logger::GetInstance()