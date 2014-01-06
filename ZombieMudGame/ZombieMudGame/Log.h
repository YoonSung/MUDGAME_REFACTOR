#pragma once

#define MAX_LOG_LENGTH		70
#define NEWLINE			"\n"
#define MAX_LOG_NUM 10

class CLog
{
public:
	CLog(void);
	~CLog(void);
	std::string m_LogBuffer[10];
	std::string CLog::getLogView();
	void AddLogBuffer(std::string logString);
};

extern CLog* g_Logger;