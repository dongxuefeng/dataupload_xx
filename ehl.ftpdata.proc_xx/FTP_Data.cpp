// FTP_Data.cpp : 定义控制台应用程序的入口点。
//


#include <iostream>
using namespace std;

#include "file_ctrl.h"
#include <windows.h>
#include <process.h>
#include "xxlib\c_windows_service.h"

void DoTask()
//int main(int argc, char * argv[])
{

	//uintptr_t uhand[3] = {0};
	uintptr_t uhand[1] = { 0 };

	//begin send data thread
	//begin down_load request_datafile thread
	//begin send_img

	_run_station send_datafile("send datafile");
		//,download_request_info("download request img list")
		//,send_img("send img list");
	send_datafile.set_work(true);
	//download_request_info.set_work(true);
	//send_img.set_work(true);


	cout << "启动传输线程" << endl;

	uhand[0] = _beginthreadex(NULL, 0, thread_send_datafile, &send_datafile, 0, NULL);	
	//uhand[1] = _beginthreadex(NULL, 0, thread_down_load_request_info, &download_request_info, 0, NULL);	
	//uhand[2] = _beginthreadex(NULL, 0, thread_send_imgthread, &send_img, 0, NULL);	

	//	 thread_send_datafile(0);
	//	 thread_down_load_request_info(0);
	//   thread_send_imgthread(0);
	
	while(true)
	{
			if(getchar() == 'q')
				{
				cout << "等待所有线程结束" << endl;
				send_datafile.set_work(false);
				//download_request_info.set_work(false);
				//send_img.set_work(false);

				break;
				};
			Sleep(2000);
	};
	/*
	WaitForMultipleObjects(3
						,(const HANDLE *)uhand
						,TRUE
						,INFINITE
						);
	*/
	cout << "系统退出！" << endl;
	//return 0;
}

