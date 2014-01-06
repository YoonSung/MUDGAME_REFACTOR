#include "stdafx.h"
#include "Log.h"

CLog* g_Logger = nullptr;

CLog::CLog(void)
{
}

void CLog::AddLogBuffer(std::string logString)
{
	for ( int i = 1 ; i < MAX_LOG_NUM; ++i )
	{
		m_LogBuffer[i-1] = m_LogBuffer[i];
	}

	m_LogBuffer[MAX_LOG_NUM - 1] = logString;
}

std::string CLog::getLogView()
{
	std::string view;

	view.append("旨");

	for(int i = 0; i < MAX_LOG_LENGTH-35; ++i) {
		view.append("收");
	}
	view.append("旬");
	view.append( NEWLINE );

	for ( int i = 0 ; i < MAX_LOG_NUM ; ++i )
	{
		view.append("早");

		int size = m_LogBuffer[i].length();

		std::string temp;

		for ( int j = 0 ; j < MAX_LOG_LENGTH-size ; ++j)
		{
			temp.append(" ");
		}

		view.append(m_LogBuffer[i]);
		view.append(temp);
		view.append("早");
		view.append( NEWLINE );
	}

	view.append("曲");
	for(int i = 0; i < MAX_LOG_LENGTH-35; ++i) {
		view.append("收");
	}
	view.append("旭");

	return view;
}


CLog::~CLog(void)
{
}
