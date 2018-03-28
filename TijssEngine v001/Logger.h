#pragma once
#include "_DLLExport.h"

#include <iostream>

using namespace std;

namespace Tijss
{
	class TIJSSEN_DECLSPEC Log
	{
	public:
		Log();
		~Log();

		void EnableLog(bool enable);
		void Separator();

		static void Info(const char* msg);
		static void Error(const char* msg);
		static void Warning(const char* msg);
		static void Success(const char* msg);
		static void WriteText(const char* msg);

		bool operator !();
		Log& operator << (int i);
		Log& operator << (float i);
		Log& operator << (const char* msg);

	private:
		static bool m_ConsoleLogging;
		static Log* m_Instance;
		char m_FileName[32];
		FILE* m_File;

		void Init();
		void Release();
		void WriteAll(const char* result);
	};
}