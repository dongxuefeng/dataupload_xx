#include "public.h"
#include "file_ctrl.h"
#include <vector>
#include "write_log.h"

using namespace std;

int findstr(const char *str,const char * substr)
{
	int pos = 0;
	char * pstr = (char *)str;
	int lenstr = strlen(str);
	int lensub = strlen(substr);
	bool bresult = false;

	for(int i=0;i<lenstr;i++)
	{
		pstr = (char *)str+i;
		if(*pstr == *substr)
		{
			bresult = true;
			for(int i=0;i<lensub;i++)
			{

				if(*(pstr+i) != *(substr+i))
				{
					bresult = false;
					break;
				}
			}

			if(bresult)
			{
				pos = i+1;
				break;
			}

		}

	}

		return pos;
}

int find_file(vector<string> * filelist,string mspath,string sub_path="")
{
	int  findHandle;                                 // 查找文件句柄
	char fileSpec[256];                              // 查找文件条件
	struct _finddata_t  fileInfo;                    // 文件信息
	sprintf(fileSpec, "%s/%s%/*.*", mspath.c_str(), sub_path.c_str()); 

	/*   _sFileName.c_str()表示的是匹配的文件名：比如：*.txt
	*   sPath.c_str() 是文件的路径
	*/

	findHandle = _findfirst(fileSpec, &fileInfo);   // 开始查找
	if (findHandle != -1)                            // 找到文件
	{
		do
		{
			if (fileInfo.attrib & _A_SUBDIR)
			{
				//cout << (strcmp(fileInfo.name,"."))<< endl;
				if((strcmp(fileInfo.name,"."))&&strcmp(fileInfo.name,".."))
				{
					string tmpsub_path = sub_path;
					int len = tmpsub_path.length();
					if(len != 0)
					{
						len -= 1;
					}
					if(tmpsub_path[len] != '/')
					{
						tmpsub_path += "/";
					}
					tmpsub_path += fileInfo.name;
					find_file(filelist,mspath,tmpsub_path);
				};
			};
			if (fileInfo.attrib & _A_ARCH)  // 如果是文档，输出文件名            
			{ 

				//int ipos = findstr(fileInfo.name,"*.jpg");
				int ipos = 1;
				if(ipos)
				{
					
					cout<<"文件名:"     << fileInfo.name << endl;				
					string strfilename = sub_path;
					strfilename += "/";
					strfilename += fileInfo.name;
					filelist->push_back(strfilename);
					if(filelist->size()>= max_find_count)
					{
						break;
					}
				}
			}
		}while(_findnext(findHandle, &fileInfo) != -1);    // 查找下一个文件
	};

	_findclose(findHandle);                          // 关闭查找
	return (int)filelist->size();	
};

//bool send_datafile

#include "xxlib\plugin\user_plug_prcdata.h"

bool send_datafile(const char * m_path)
{

	//find datafile 每组50个
	vector<string> file_list;
	int ifilecount = find_file(&file_list,m_path);
	//for
	for(vector<string>::iterator iter = file_list.begin();
		iter != file_list.end();
		iter ++)
	{
		char strdata[256];


		string strtmp = m_path;
		strtmp += "/";
		strtmp += iter->c_str();

		string ftpfile = g_local_dir.m_backdir;
		ftpfile += "/";
		ftpfile += iter->c_str();

		string ftpfail = g_local_dir.m_faildir;
		ftpfail += "/";
		ftpfail += iter->c_str();


		sprintf(strdata, "%s", iter->c_str());
		int iresult_code = 0;
		int ipos = findstr(strdata, "_xx.jpg");
		if (ipos)
		{
//			plug_proc_data(strdata,&iresult_code, strref);
		}

		if (iresult_code == 0)
		{
			string strdir = ftpfile.c_str();
			get_parent_dir(strdir);
			check_file_path((char *)strdir.c_str());

			for (int i = 0; i < 100; i++)
			{
				BOOL bmove =
					MoveFile(strtmp.c_str(), ftpfile.c_str());
				if (bmove)
				{
					break;
				}
				else
				{

					DWORD errno1 = GetLastError();
						printf("move file is fail!,error(%d)", errno1);
						if (errno1 == 183)
						{
							DeleteFile(strtmp.c_str());
							break;
						}
						

					Sleep(1000);
				};

			}

		}	   
		else
		{
			string strdir = ftpfail.c_str();
			get_parent_dir(strdir);
			check_file_path((char *)strdir.c_str());

			check_file_path((char *)strtmp.c_str());

			for (int i = 0; i < 100; i++)
			{
				BOOL bmove =
					MoveFile(strtmp.c_str(), ftpfail.c_str());
				if (bmove)
				{

					break;
				}
				else
				{
					DWORD errno1 = GetLastError();
					printf("move file is fail!,error(%d)", errno1);
					if (errno1 == 183)
					{
						DeleteFile(strtmp.c_str());
						break;
					}
					Sleep(1000);
				};

			}


		}
		
		/*
		//send datafile	
		string strtmp = m_path;
		strtmp += "/";
		strtmp += iter->c_str();

		//ftp datafile
		string ftpfile = g_ftp_dir.m_datafile;
		ftpfile += "/";
		ftpfile += iter->c_str();
		//

		cout << "send file ..." << strtmp;
		if(g_ftp_info.send_ftp_file(strtmp.c_str(),ftpfile.c_str()))
		{
			cout << "succer" << endl;
			remove(strtmp.c_str());
		}
		else
		{
			cout << "fail" << endl;
		}
		*/


	};
	return true;
};


//通过线程调用发送
//datafile
/*
unsigned int __stdcall thread_send_datafile(void * param)
{
	_run_station * p_run_station = (_run_station *)param;
	while (p_run_station->get_work())
		{
			send_datafile(g_local_dir.m_datafile.c_str());
			Sleep(1000);
		}
	return 1;
}
*/


struct client_info
{
	SOCKET sock;
	char ip[26];
};

#define MAXCLIENTS 15                //宏定义，最多3个客户端连接
#define MAX_XML_BYTE  1500          //解析前一个xml文件的最大值
#define MAX_XML_BYTE_AFTER  1024    //解析后一个xml文件的最大值
int existingClientCount = 0;

#include "process_data\process_datatostd.h"
//解析每一个xml,提取车辆信息
int parse_xiangx_xml(const char *xmlBuff, string &valdate, string &filename, int &imgcount, string &img1, string &img2, string &img3)
{
	if (strstr(xmlBuff, "listInfo") != NULL)
	{
		if (!getPassCarXmlInfo(xmlBuff, filename, valdate, imgcount, img1, img2, img3))
		{
			WriteLog((char *)(filename.c_str()));
			return -1;
		}

	}
	if (strstr(xmlBuff, "vioInfo") != NULL)
	{
		if (!getVioXmlInfo(xmlBuff, filename, valdate, imgcount, img1, img2, img3))
		{
			WriteLog((char *)(filename.c_str()));
			return -2;
		}

	}
	return 0;
}




DWORD WINAPI ProcessClientRequests(LPVOID lpParam)
{
	client_info *client = (client_info *)lpParam;
	SOCKET clientSocket = (SOCKET)client->sock;  //这里需要强制转换，注意：指针类型的
	char buffer[MAX_XML_BYTE] = { 0 };
	char strtmp[MAX_XML_BYTE] = { 0 };//
	int result = -1;
	int count = 0;
	string msg = "error";
	
	int recv_count = 0;
	fd_set         fdread;
	int             ret;
	struct timeval tv = { 10, 0 };
	int iresultcode = 0;
	char resultstr[256];

	while (TRUE)
	{
		memset(buffer, 0, MAX_XML_BYTE);
		memset(strtmp, 0, MAX_XML_BYTE);


		FD_ZERO(&fdread);

		FD_SET(clientSocket, &fdread);
		// We only care read event 
		ret = select(clientSocket + 1, &fdread, NULL, NULL, &tv);
		if (ret == 0)
		{       // Time expired 
			printf("time out clientSocket ===============%d\n", clientSocket);
			break;
		}
		recv_count = recv(clientSocket, buffer, MAX_XML_BYTE, NULL);
		//	printf("recv_count ===========%d\n",recv_count);
		if (recv_count > 0)
		{

			//code_convert("UTF-8", "GB2312", buffer, MAX_XML_BYTE, strtmp, MAX_XML_BYTE);
			//printf(strtmp);
			sprintf(strtmp,buffer);
			string filename = "";
			string valdate = "";
			int imgcount = 0;
			string img1 = "";
			string img2 = "";
			string img3 = "";
			try
			{
				result = parse_xiangx_xml(strtmp, valdate, filename, imgcount, img1, img2, img3);
			}
			catch (...)
			{
				result = -1;
			};
			if (0 == result)
			{
				int res = send(clientSocket, valdate.c_str(), sizeof(int), NULL);
				if (res == SOCKET_ERROR)
				{
					WriteLog("send FAILD\n");
				}
				else
				{
					WriteLog("send ok\n");

				}
				//call upload data proc
				if (filename != "" || filename.length() < 39)
				{
					try
					{
						plug_proc_data(filename.c_str(), &iresultcode, resultstr, imgcount, (char *)img1.c_str(), (char *)img2.c_str(), (char *)img3.c_str());
					}
					catch (...)
					{
						WriteLog("Error");
						break;
					};
					
				}
				count++;
				printf("socket = %d,count = %d\n", clientSocket, count);
//				WriteLog((char *)valdate.c_str());
				
			}
			else
			{
				printf("parse error!");
				printf(strtmp);
				send(clientSocket, msg.c_str(), strlen(msg.c_str()) + sizeof(char), NULL);
			}


		}
		else if (recv_count == 0)
		{
			break;
			//	printf("socket = %d\n",clientSocket);
		}
		else if (recv_count == -1)
		{
			printf("erorr === %d\n", WSAGetLastError());
			break;
		}
		Sleep(5);
	}
	existingClientCount--;
	closesocket(clientSocket);
	delete client;
	return 0;
}

unsigned int __stdcall thread_send_datafile(void * param)
{
	_run_station * p_run_station = (_run_station *)param;
	WSADATA wsaData;
	vector<HANDLE> handlist;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	

	SOCKET socLink = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in sockAddr;
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	sockAddr.sin_port = htons(5511);
	bind(socLink, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	listen(socLink, 1);

	string test = "";
	//parse_xiangx_xml("",test);//gengming test
	while (p_run_station->get_work())
	{

		SOCKADDR clientAddr;
		int size = sizeof(SOCKADDR);

		SOCKET clientSocket;

			if (handlist.size() > 0)
			{
				printf("\nproc thread count = %d\n", handlist.size());
				for (vector<HANDLE>::const_iterator iter = handlist.begin(); iter != handlist.end();)
				{
					if (WaitForSingleObject(*iter, 10) != WAIT_TIMEOUT)
					{
						printf("\n free handle %d \n", *iter);
						if (*iter != 0)
						{

							CloseHandle(*iter);
							iter = handlist.erase(iter);
							if (iter == handlist.end())
							{
								break;
							}
						}
					}
					else
						iter++;
				};
			};


		clientSocket = accept(socLink, &clientAddr, &size);
		if (-1 == clientSocket)
		{
			continue;
		}
		//

		


		client_info *client = new client_info;
		client->sock = clientSocket;
		sockaddr_in *p = (sockaddr_in *)(&clientAddr);
		strcpy(client->ip, inet_ntoa(p->sin_addr));
		 

		//if(existingClientCount<MAXCLIENTS)       //判断是否已经超出最大连接数了
		{
			HANDLE	threads = NULL;

			threads = CreateThread(NULL, 0, ProcessClientRequests, (LPVOID)client, 0, NULL);  //启动新线程，并且将socket传入

			if (threads == 0)
			{
				printf("create thread failed!");
				closesocket(clientSocket);
				delete client;
				continue;
			}
			printf("/n  add handle = %d /n", threads);
			if (threads != 0)
			 handlist.push_back(threads);
			existingClientCount++;
			printf("existingClientCount===%d\n", existingClientCount);
		}
		/*else
		{
		char* msg="Exceeded Max incoming requests, will refused this connect!\r\n";
		send(clientSocket, msg, strlen(msg)+sizeof(char), NULL);       //发送拒绝连接消息给客户端
		printf("***SYS***    REFUSED.\n");
		closesocket(clientSocket);                                     //释放资源
		break;
		}*/
	}

	printf("Maximize clients occurred for d%.\r\n", MAXCLIENTS);

//	WaitForMultipleObjects(MAXCLIENTS, &threads, TRUE, INFINITE);           //等待所有子线程，直到完成为止
	if (handlist.size() > 0)
	{
		printf("\nproc thread count = %d\n", handlist.size());
		for (vector<HANDLE>::const_iterator iter = handlist.begin(); iter != handlist.end(); )
		{
			if (WaitForSingleObject(*iter, INFINITE) != WAIT_TIMEOUT)
			{
				CloseHandle(*iter);
				iter = handlist.erase(iter);
			}
			else
				iter++;
		};
	};




	closesocket(socLink);

	//CloseHandle(threads);                                           //清理线程资源
	WSACleanup();
	printf("Cleared all.\r\n");
	getchar();
	exit(0);
}
