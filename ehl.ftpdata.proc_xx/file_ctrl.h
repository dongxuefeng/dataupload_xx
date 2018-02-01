#ifndef _file_ctrl__
#define _file_ctrl__

#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

class _run_station
	{
	private:
		CRITICAL_SECTION m_criticalSection;
		string m_thread_name;
		int count;
		bool bwork;
	public:
		_run_station(const char * thread_name)
			{
			count = 0;
			m_thread_name = thread_name;
			bwork = true;
			InitializeCriticalSection(&m_criticalSection);
			};
		~_run_station()
			{
			DeleteCriticalSection(&m_criticalSection);//保证对象被析构时候能够删除临界区
			};
		void set_work(bool value)
			{
			    EnterCriticalSection(&m_criticalSection);
				bwork = value;
				LeaveCriticalSection(&m_criticalSection);
			}
		bool get_work()
			{
				EnterCriticalSection(&m_criticalSection);
				count++ ;
				cout << m_thread_name.c_str() << " run time " << count << endl; 
				LeaveCriticalSection(&m_criticalSection);
				return bwork;
			}
	};

unsigned int __stdcall thread_send_datafile(void * param);

unsigned int __stdcall thread_down_load_request_info(void * param);

unsigned int __stdcall thread_send_imgthread(void * param);

#endif