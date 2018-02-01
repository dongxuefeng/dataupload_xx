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
	int  findHandle;                                 // �����ļ����
	char fileSpec[256];                              // �����ļ�����
	struct _finddata_t  fileInfo;                    // �ļ���Ϣ
	sprintf(fileSpec, "%s/%s%/*.*", mspath.c_str(), sub_path.c_str()); 

	/*   _sFileName.c_str()��ʾ����ƥ����ļ��������磺*.txt
	*   sPath.c_str() ���ļ���·��
	*/

	findHandle = _findfirst(fileSpec, &fileInfo);   // ��ʼ����
	if (findHandle != -1)                            // �ҵ��ļ�
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
			if (fileInfo.attrib & _A_ARCH)  // ������ĵ�������ļ���            
			{ 

				//int ipos = findstr(fileInfo.name,"*.jpg");
				int ipos = 1;
				if(ipos)
				{
					
					cout<<"�ļ���:"     << fileInfo.name << endl;				
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
		}while(_findnext(findHandle, &fileInfo) != -1);    // ������һ���ļ�
	};

	_findclose(findHandle);                          // �رղ���
	return (int)filelist->size();	
};

//bool send_datafile

#include "xxlib\plugin\user_plug_prcdata.h"

bool send_datafile(const char * m_path)
{

	//find datafile ÿ��50��
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


//ͨ���̵߳��÷���
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

#define MAXCLIENTS 15                //�궨�壬���3���ͻ�������
#define MAX_XML_BYTE  1500          //����ǰһ��xml�ļ������ֵ
#define MAX_XML_BYTE_AFTER  1024    //������һ��xml�ļ������ֵ
int existingClientCount = 0;

#include "process_data\process_datatostd.h"
//����ÿһ��xml,��ȡ������Ϣ
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
	SOCKET clientSocket = (SOCKET)client->sock;  //������Ҫǿ��ת����ע�⣺ָ�����͵�
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
		 

		//if(existingClientCount<MAXCLIENTS)       //�ж��Ƿ��Ѿ����������������
		{
			HANDLE	threads = NULL;

			threads = CreateThread(NULL, 0, ProcessClientRequests, (LPVOID)client, 0, NULL);  //�������̣߳����ҽ�socket����

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
		send(clientSocket, msg, strlen(msg)+sizeof(char), NULL);       //���;ܾ�������Ϣ���ͻ���
		printf("***SYS***    REFUSED.\n");
		closesocket(clientSocket);                                     //�ͷ���Դ
		break;
		}*/
	}

	printf("Maximize clients occurred for d%.\r\n", MAXCLIENTS);

//	WaitForMultipleObjects(MAXCLIENTS, &threads, TRUE, INFINITE);           //�ȴ��������̣߳�ֱ�����Ϊֹ
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

	//CloseHandle(threads);                                           //�����߳���Դ
	WSACleanup();
	printf("Cleared all.\r\n");
	getchar();
	exit(0);
}
