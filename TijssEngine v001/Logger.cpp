#include "Logger.h"
#include <string>
#include "EngineDefines.h"

namespace Tijss
{
	Log* Log::m_Instance = NULL;
	bool Log::m_ConsoleLogging = true;

	Log::Log()
	{
		if (m_Instance == NULL)
		{
			strcpy(m_FileName, "Log.txt");
			m_Instance = this;
			m_Instance->Init();
		}
		else
		{
			Warning("Log already created");
		}
	}

	Log::~Log()
	{
		Release();
	}

	void Log::Release()
	{
		Separator();
		Info("Logger stopped");
		Separator();
		fclose(m_File);
		m_Instance = NULL;
	}

	void Log::EnableLog(bool enable)
	{
		m_ConsoleLogging = enable;
	}

	void Log::Init()
	{
		m_File = fopen(m_FileName, "w");

		if (m_File != 0)
		{
			WriteText("TijssEngine Output Log");
#ifdef _DEBUG
			WriteText("In Debug Mode\n");
#else
			WriteText("In Release Mode\n");
#endif
			Separator();
			Info("Info: Logging started");
			Separator();
		}
	}

	void Log::Info(const char* msg)
	{
		string Message = msg;
		if (m_Instance)
		{
			Message.insert(0, "INFO: ");
			Message.append("\n");
			m_Instance->WriteAll(Message.c_str());
		}
	}


	void Log::WriteText(const char* msg)
	{
		if (m_Instance)
		{
			m_Instance->WriteAll(msg);
		}
	}


	void Log::Separator()
	{
		if (m_Instance)
		{
			string Message = "-------------------------------------------------------------------------------\n";
			if (m_File)
				fwrite(Message.c_str(), 1, Message.size(), m_Instance->m_File);
			if (m_ConsoleLogging) cout << Message.c_str();
		}
	}


	void Log::Error(const char* msg)
	{
		string Message = msg;

		if (m_Instance)
		{
			Message.insert(0, "ERROR: ");
			Message.append("\n");
			m_Instance->WriteAll(Message.c_str());
			m_Instance->Release();
		}
		MessageBoxA(0, Message.c_str(), "Error", 0);
		throw Message.c_str();
	}


	void Log::Warning(const char* msg)
	{
		string Message = msg;
		if (m_Instance)
		{
			Message.insert(0, "WARNING: ");
			Message.append("\n");
			m_Instance->WriteAll(Message.c_str());
		}
	}


	void Log::Success(const char* msg)
	{
		string Message = msg;
		if (m_Instance)
		{
			Message.insert(0, "SUCCESS: ");
			Message.append("\n");
			m_Instance->WriteAll(Message.c_str());
		}
	}


	bool Log::operator ! ()
	{
		return m_Instance == nullptr;
	}


	Log& Log::operator<<(int i)
	{
		if (m_Instance)
		{
			string Message = std::to_string(i);
			m_Instance->WriteAll(Message.c_str());
		}
		return *this;
	}


	Log& Log::operator<<(float i)
	{
		if (m_Instance)
		{
			string Message = std::to_string(i);
			m_Instance->WriteAll(Message.c_str());
		}

		return *this;
	}


	Log& Log::operator<<(const char* Message)
	{
		if (m_Instance)
		{
			m_Instance->WriteAll(Message);
		}
		return *this;
	}


	void Log::WriteAll(const char* ResultMessage)
	{
		if (m_File)
		{
			fwrite(ResultMessage, 1, strlen(ResultMessage), m_File);
		}
		if (m_ConsoleLogging) cout << ResultMessage;
	}

}