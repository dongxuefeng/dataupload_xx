// ehl.fptdata.save.cpp : 定义 DLL 应用程序的导出函数。
//

#include <iostream>
#include "ehl.ftpdata.save.h"
//#include "webref\ehl_webref.h"
#include "webref\wxtracert\webref_wxtracert.h"
#include "lib\write_log.h"

#include <string>
#include <map>
#include <windows.h>
#include <list>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <ostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char * deffilename = "./config/wxs_device_info.ini";
using namespace std;

class mux
{
public:
	CRITICAL_SECTION critcal;
public:
	mux()
	{
		InitializeCriticalSection(&critcal);
	}
	~mux()
	{
		DeleteCriticalSection(&critcal);
	}
public:
	void lock()
	{
		EnterCriticalSection(&critcal);
	}
	void unlock()
	{
		LeaveCriticalSection(&critcal);
	}
} gmux;


const char * strtmpdef[5][2] = { { "黄", "01" }, { "蓝", "02" }, { "白", "23" }
, { "黑", "03" }, { "其它", "99" } };
char * strnull = "";
class c_data_convert_hkfilename
{

public:
	c_data_convert_hkfilename()
	{
		load_param();
//		init_kkinfo();
	}
	~c_data_convert_hkfilename()
	{
		free_param();
	}



private:
	//	SBBH 为索引参数表 key sbbh_prop_name  value prop_value
	// 速度参数据信息表 key cllx_csb   value wfxw
	map<string, string> msbinfo;

private:

	void write_param(const char * sbbh, const char * prop_key, const char * default_value)
	{
		char param_file[256];
		get_parent_dir(get_current_exe(), param_file);
		strcat(param_file, deffilename);
		WritePrivateProfileString(sbbh, prop_key, default_value, param_file);
	};
	void load_param_value(const char * secname, const char * key, const char * filename, map<string, string> * mt)
	{
		char value[256];
		char keyname[256];
		sprintf(keyname, "%s_%s", secname, key);
		GetPrivateProfileString(secname, key, "", value, 256, (LPCTSTR)filename);
		mt->insert(pair<string, string>(keyname, value));

	}

	void load_param_section(const char * secname, const char * filename, map<string, string> * mt)
	{
		char ac_Result1[2000];
		int m_lRetValue1 = GetPrivateProfileSection(secname, ac_Result1, 2000, (LPCTSTR)filename);
		char * p = ac_Result1;
		for (int j = 0; j < m_lRetValue1; j++)
		{
			if (*p == '\0')
				break;
			char strtmp[256];
			sprintf(strtmp, p);
			char * strtmp1 = strtok(strtmp, "=");
			char * strtmp2 = strtok(NULL, "=");
			if (strtmp2 == NULL)
				strtmp2 = strnull;
			printf("%s,%s", strtmp1, strtmp);
			char keyname[256];
			sprintf(keyname, "%s_%s", secname, strtmp1);

			mt->insert(pair<string, string>(keyname, strtmp2));
			printf("init map :%s = %s \n", keyname, strtmp2);

			//load_param_value(secname,p, filename, mt);
			p = p + strlen(p) + 1;
		}
	}
	void load_param_sections(const char * filename, map<string, string> * mt)
	{
		char ac_Result[2000];

		int m_lRetValue;
		m_lRetValue = GetPrivateProfileSectionNames(ac_Result, 2000, filename);
		char * p = ac_Result;

		for (int i = 0; i < m_lRetValue; i++)
		{
			load_param_section(p, filename, mt);

			p = p + strlen(p) + 1;
		};
	}

	char szFilePath[MAX_PATH + 1];
	const char * get_current_exe()
	{
		GetModuleFileName(NULL, szFilePath, MAX_PATH);
		return szFilePath;
	};

	void load_param()
	{
		char param_file[256];
		get_parent_dir(get_current_exe(), param_file);
		strcat(param_file, deffilename);
		load_param_sections(param_file, &msbinfo);

	};
	void free_param()
	{
		msbinfo.empty();
	};
private:

	const char * read_csinfo(const char * appname, const char * prop_key, const char * default_value)
	{
		string strkey = appname;
		strkey += "_";
		strkey += prop_key;
		map<string, string>::const_iterator iter = msbinfo.find(strkey);
		if (iter != msbinfo.end())
		{
			return iter->second.c_str();
		}
		else
		{
			msbinfo.insert(pair<string, string>(strkey, default_value));
			write_param(appname, prop_key, default_value);
			return default_value;
		};
	};
private:
	//基本信息
	string sbid;
	string sj;
	string cs;
	string hphm;
	string hpys;
	string hplx;
	string cllx;
	string fxid;
	string cdid;
	string datatype; //数据类型
	//string tpmc;
	string tmpdata;
	int imgcount;
	string img1;
	string img2;
	string img3;
	string wfdm;
public:
	//testdata:20150427111212999_0_70_陕A12345_黄_01_01_4_3_6109001_hik.jpg
	char sdatainfo[256];
	int read_baseinfo(char * datainfo,int timgcount, const char * timg1, const char * timg2, const char * timg3)
	{

		char ext[10];
		_splitpath(datainfo, 0, 0, sdatainfo, ext);
		int iresult = 0;

		sj = strtok(sdatainfo, "_");
		datatype = strtok(NULL, "_");
		cs = strtok(NULL, "_");
		hphm = strtok(NULL, "_");
		hpys = strtok(NULL, "_");
		hplx = strtok(NULL, "_");
		cllx = strtok(NULL, "_");
		fxid = strtok(NULL, "_");
		cdid = strtok(NULL, "_");
		sbid = strtok(NULL, "_");
		wfdm = strtok(NULL, "_");
		tmpdata = datainfo;
		imgcount = timgcount;
		img1 = timg1;
		img2 = timg2;
		img3 = timg3;
		return iresult;
	}
public:
	int get_datatype()
	{
		return atoi(datatype.c_str());
	}

private:
	char kkid[256];
	const char * get_kkid()
	{

		//return "371600000001";
		sprintf(kkid,read_csinfo(sbid.c_str(), "kkid", sbid.c_str()));
		return kkid;

	}
	//	<!--号牌号码[不能为空]-->
	//	<hphm>京A12345</hphm>
	const char *get_hphm()
	{
		return hphm.c_str();
	};

	const char *get_hpys()
	{
		//<!--号牌颜色[不能为空，输入：黄，蓝，白，黑，其它]-->
		//<hpys>黄< / hpys>
		return hpys.c_str();
		//return "1";
	};

	//	<!--车辆类型[不可空，符合GA24.4的要求]输入编码：01 - 大型车辆，02 - 小型车辆，03 - 外籍车辆，23 - 公安警用车辆，99 - 其它-->
	//	<cllx>01< / cllx>

	//	1 其他车辆 0 ----
	//		2 小型车 1 ----
	//		3 大型车 2 ----
	//		4 行人 3 ----
	//		5 二轮车 4 ----
	//		6 三轮车 5 ----

	const char * get_default_cllx(const char * hpys)
	{
		for (int i = 0; i < 5; i++)
		{
			if (strcmp(strtmpdef[i][0], hpys))
			{
				return strtmpdef[i][1];
			}
		}
		return "99";
	}
	char ffid_cdid[256];
	map<string, int> unregkkcdlist;
	const char * get_ffid_cdid()
	{
		sprintf(ffid_cdid, "%s_%s", get_fxbh(), get_cdbh());
		return ffid_cdid;
	}
	bool isreg()
	{
		char reg_ff_cd[256];
		char reg_kk_ff_cd[256];
		sprintf(reg_kk_ff_cd, "%s_%s", get_kkid(), get_ffid_cdid());
		map<string, int>::const_iterator iter = unregkkcdlist.find(reg_kk_ff_cd);
		if (iter == unregkkcdlist.end())
		{
			//map中未添加该选项，这里需要添加
			WriteLog("添加车道注册：");
			WriteLog(reg_kk_ff_cd);
			sprintf(reg_ff_cd, "isreg_%s", get_ffid_cdid());
			int isreg = atoi(read_csinfo(sbid.c_str(), reg_ff_cd, "-1"));
			if (isreg != -1)
			{
				unregkkcdlist[reg_kk_ff_cd] = init_wxdata(get_kkid(), get_fxbh(), atoi(get_cdbh()));
			}
			else
			{
				WriteLog("该车道未初始化");
				return false;
			};
		}
		else
		{
			
			if (unregkkcdlist[reg_kk_ff_cd] > 0)
			{
				WriteLog("车道初始化成功");
				return true;
			}

			if (unregkkcdlist[reg_kk_ff_cd] <= 0)
			{
				//重新尝试注册
				Sleep(3000);
				WriteLog("车道重新注册");
				WriteLog(reg_kk_ff_cd);
				unregkkcdlist[reg_kk_ff_cd] = init_wxdata(get_kkid(), get_fxbh(), atoi(get_cdbh()));
			};
		};
		return (unregkkcdlist[reg_kk_ff_cd] >0 );
	}
	
		
	const char *get_cllx()
	{
		//return read_csinfo("cllx", cllx.c_str(), cllx.c_str());
		return read_csinfo("cllx", hpys.c_str(), get_default_cllx(hpys.c_str()));

	};

	//	<!--过往时间[不能为空，时间格式：yyyy - MM - dd hh24 : mm : ss]-->
	//	<gwsj>2009 - 09 - 23 04:11 : 55< / gwsj>
	
	char wfsj[256];
	const char *get_gwsj()
	{
		sprintf(wfsj,"%c%c%c%c-%c%c-%c%c %c%c:%c%c:%c%c"
			, sj.at(0), sj.at(1), sj.at(2), sj.at(3), sj.at(4), sj.at(5), sj.at(6)
			, sj.at(7), sj.at(8), sj.at(9), sj.at(10), sj.at(11), sj.at(12), sj.at(13));
		return wfsj;
	};

	//	<!--方向编号[不能为空，输入（1 - 4）。定义如下：南向北1：东向西2：北向南3:西向东4-->
	//	<fxbh>1</fxbh>
	const char * get_fxbh()
	{
		char strtmp[256];
		sprintf(strtmp, "fx_%s", fxid.c_str());
		return read_csinfo(sbid.c_str(), strtmp, fxid.c_str());
		//return fxid.c_str();
	};

	//	<!--车道编号[不能为空，输入：1 - 99]-->
	//	<cdbh>2< / cdbh>

	const char * get_cdbh()
	{
		//return cdid.c_str();
		return read_csinfo("cdbh", cdid.c_str(), cdid.c_str());
	};
	//	<!--车辆速度[不能为空，输入：1 - 300]-->
	//	<clsd>76< / clsd>
	const char * get_clsd()
	{
		return cs.c_str();
	};
	//	<!--证据文件1[不能为空，全景图片，输入有效的http路径-->
	//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
	string strimg1;
	const char * get_zjwj1()
	{
		strimg1 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
		strimg1.append(img1.c_str());
		return strimg1.c_str();
	};
	//<!--证据文件2[能空，特写图片，输入有效的http路径-->
	//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>

	string strimg2;
	const char * get_zjwj2()
	{
		if (imgcount > 1)
		{
			strimg2 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
			strimg2.append(img2.c_str());
			return strimg2.c_str();
		}
		else
		{
			return "";
		}

	};
	//	<!--证据文件3[可空，号牌图片，输入有效的http路径]-->
	//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
	string strimg3;
	const char * get_zjwj3()
	{
		if (imgcount > 2)
		{
			strimg3 = read_csinfo("imgurl", "server", "http://10.176.102.4/image/");
			strimg3.append(img3.c_str());
			return strimg3.c_str();
		}
		else
		{
			return "";
		}
	};
	//	<!--证据文件4[[可空，录像文件，输入有效的http路径-->
	//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
	const char * get_zjwj4()
	{
		return "";
	};
	//	<!--记录类型 : [不能为空, 0：正常车辆1：黑名单车辆2：特殊勤务车辆3：布控车辆4：占道车辆5：历史违法车辆6：畅行车辆7：区间超速车辆8：超速违法车辆9：逆行 10：转入违法  11.闯红灯违法 12.不按车道行驶 13.违法停车  14.压黄线] -->
	//	<jllx>0< / jllx>
	const char * get_jllx()
	{
		return datatype.c_str();
	};
	//	<!--车速毫秒[可空, 车速的毫秒部分，3位]-->
	//	<cshm>869< / cshm>
	char cshm[256];
	const char * get_cshm()
	{
		sprintf(cshm, "%c%c%c"
			, sj.at(14), sj.at(15), sj.at(16));
		return cshm;
	};

	//<!--数据来源[不能为空，数据来源“1 - 闯红灯设备，2 - 公路卡口设备，3 - 测速设备，4 - 闭路电视（违法抓拍），5 - 移动摄像，6 - 行车记录仪，9 - 其它电子设备]-->
	//	<sjly>2< / sjly>
	const char * get_sjly()
	{
		return read_csinfo(sbid.c_str(), "sjlx", "2");
	};

	//	<!--号牌种类[不能为空，符合GA标准] 输入编码：01 - 大型车辆，02 - 小型车辆，03 - 外籍车辆，23 - 公安警用车辆，99 - 其它-->
	//	<hpzl>01< / hpzl>

	const char * get_hpzl()
	{
		return hplx.c_str();
	};

	//	<!--违法时间[不能为空，时间格式：yyyy - MM - dd hh24 : mm : ss]-->
	//	<wfsj>2009 - 09 - 23 04:11 : 55< / wfsj>
	const char * get_wfsj()
	{
		return get_gwsj();
	};
	//	<!--违法行为[不能为空，符合GA标准]-->
	//	<wfxw>1030</wfxw>
	string strwfxw;
	const char * get_wfxw()
	{
		
		
		/*
		int ispeed = atoi(cs.c_str());
		int ilimitspeed = atoi(get_clxs());
		int csb = (ispeed * 100) / ilimitspeed;
		if (csb < 20)
		{
			strtmp = read_csinfo(get_cllx(), "csb20", "1020");
		}
		else
		{
			if (csb > 50)
			{
				strtmp = read_csinfo(get_cllx(), "csb50", "1020");
			}
			else
			{
				strtmp = read_csinfo(get_cllx(), "csb205050", "1020");
			}
		};
		return strtmp.c_str();
		*/
		strwfxw = read_csinfo("wfdm", wfdm.c_str(), wfdm.c_str());
		return strwfxw.c_str();
	};

	//	<!--违法内容[可空，对违反行为简单的描述]-->
	//	<wfnr>超速50%< / wfnr>
	string strwfnr;
	const char * get_wfnr()
	{
		strwfnr = read_csinfo("wfnr", wfdm.c_str(), "");
		return strwfnr.c_str();
	};
	//<!--违法地点[不可空]-->
	//	<wfdd>208300315500</wfdd>
	string strwfdd;
	const char * get_wfdd()
	{
		 strwfdd = read_csinfo(sbid.c_str(), "wfdd", sbid.c_str());
		 return strwfdd.c_str();
	};

	//<!--违法地址[不可空，违法地点的描述]-->
	//<wfdz>北京路—天津路< / wfdz>
	const char * get_wfdz()
	{
		return read_csinfo(sbid.c_str(), "wfdz", "十天高速");
	};



	//<!--车辆限速[可空，输入：1 - 300]-->
	//<clxs>70< / clxs>
	const char * get_clxs()
	{
		string strtmp = "speedlimit_";
		strtmp += cllx.c_str();
		return  read_csinfo(sbid.c_str(), strtmp.c_str(), "80");
	};
	//<!--最低限速[可空，输入：1 - 300]-->
	//<zdxs>60< / zdxs>
	const char * get_zdxs()
	{
		return "1";
	};
	//<!--采集机关[不能为空，-->
	//<cjjg>371600000001< / cjjg>
	const char * get_cjjg()
	{
		return  read_csinfo(sbid.c_str(), "cjjg", "371600000001");
	};
	//<!--采集用户[可空，-->
	//<cjyh>抓拍员< / cjyh>
	const char * get_cjyh()
	{
		return read_csinfo(sbid.c_str(), "cjyh", "9999");
	};
	//<!--采集时间[可空，-->
	//<cjsj>2009 - 09 - 23 04:11 : 55< / cjsj>
	const char * get_cjsj()
	{
		return get_wfsj();
	};
	//<!--执勤名警[不可空] -->
	//<zqmj>012321< / zqmj>
	const char * get_zqmj()
	{
		return read_csinfo(sbid.c_str(), "cjyh", "9999");
	};
	//<!--备注信息[可空]-->
	//<bz>< / bz>
	const char * get_bz()
	{
		return read_csinfo(sbid.c_str(), "bz", "");
	};

public:
	//void plug_proc_viodata(int itype, const wchar_t * datastr, wchar_t * proc_msg)
	
	int get_viodata_xml(string &strxml)
	{
		//
		char xml[1024];
		strxml = "";
		sprintf(xml, "<?xml version = \"1.0\" encoding = \"GB2312\"?>");
		strxml.append(xml);
		sprintf(xml, "<message System = \"ATMS\" Ver = \"1.0\">");
		strxml.append(xml);

		sprintf(xml, "<systemtype>TGS</systemtype>");
		strxml.append(xml);
		sprintf(xml, "<messagetype>NOTICE</messagetype>");
		strxml.append(xml);
		sprintf(xml, "<sourceIP>3.0</sourceIP>");
		strxml.append(xml);
		sprintf(xml, "<targetIP></targetIP>");
		strxml.append(xml);
		sprintf(xml, "<user>PECCANCY</user>");
		strxml.append(xml);
		sprintf(xml, "<password>PECCANCY</password>");
		strxml.append(xml);
		sprintf(xml, "<peccancyinfo>");
		strxml.append(xml);


		//<!--数据来源[不能为空，数据来源“1 - 闯红灯设备，2 - 公路卡口设备，3 - 测速设备，4 - 闭路电视（违法抓拍），5 - 移动摄像，6 - 行车记录仪，9 - 其它电子设备]-->
		//	<sjly>2< / sjly>
		sprintf(xml, "<sjly>%s</sjly>", get_sjly());
		strxml.append(xml);

		//	<!--号牌号码[不能为空]-->
		//	<hphm>京A12345< / hphm>
		sprintf(xml, "<hphm>%s</hphm>", get_hphm());
		strxml.append(xml);

		//	<!--号牌种类[不能为空，符合GA标准] 输入编码：01 - 大型车辆，02 - 小型车辆，03 - 外籍车辆，23 - 公安警用车辆，99 - 其它-->
		//	<hpzl>01< / hpzl>

		sprintf(xml, "<hpzl>%s</hpzl>", get_hpzl());
		strxml.append(xml);

		//	<!--违法时间[不能为空，时间格式：yyyy - MM - dd hh24 : mm : ss]-->
		//	<wfsj>2009 - 09 - 23 04:11 : 55< / wfsj>
		sprintf(xml, "<wfsj>%s</wfsj>", get_wfsj());
		strxml.append(xml);


		//	<!--违法行为[不能为空，符合GA标准]-->
		//	<wfxw>1030< / wfxw>
		sprintf(xml, "<wfxw>%s</wfxw>", get_wfxw());
		strxml.append(xml);

		//	<!--违法内容[可空，对违反行为简单的描述]-->
		//	<wfnr>超速50%< / wfnr>
		sprintf(xml, "<wfnr>%s</wfnr>", get_wfnr());
		strxml.append(xml);


		//<!--违法地点[不可空]-->
		//	<wfdd>208300315500< / wfdd>
		sprintf(xml, "<wfdd>%s</wfdd>", get_wfdd());
		strxml.append(xml);
		//<!--违法地址[不可空，违法地点的描述]-->
		//<wfdz>北京路—天津路< / wfdz>
		sprintf(xml, "<wfdz>%s</wfdz>", get_wfdz());
		strxml.append(xml);
		//<!--车道编号[不可空，输入：1 - 99]-->
		//<cdbh>2< / cdbh>
		sprintf(xml, "<cdbh>%s</cdbh>", get_cdbh());
		strxml.append(xml);
		//<!--方向编号[不可空违法地点加上 + 1位方向编号 ，方向编号输入（1 - 4）。定义如下南向北2：东向西3：北向南4:西向东 - ->
		//<fxbh>6400000000001< / fxbh>
		sprintf(xml, "<fxbh>%s%s</fxbh>",get_wfdd(), get_fxbh());
		strxml.append(xml);
		//<!--车辆速度[可空，输入：1 - 300]-->
		//<clsd>76< / clsd>
		sprintf(xml, "<clsd>%s</clsd>", get_clsd());
		strxml.append(xml);
		//<!--车辆限速[可空，输入：1 - 300]-->
		//<clxs>70< / clxs>
		sprintf(xml, "<clxs>%s</clxs>", get_clxs());
		strxml.append(xml);
		//<!--最低限速[可空，输入：1 - 300]-->
		//<zdxs>60< / zdxs>
		sprintf(xml, "<zdxs>%s</zdxs>", get_zdxs());
		strxml.append(xml);
		//<!--采集机关[不能为空，-->
		//<cjjg>371600000001< / cjjg>
		sprintf(xml, "<cjjg>%s</cjjg>", get_cjjg());
		strxml.append(xml);
		//<!--采集用户[可空，-->
		//<cjyh>抓拍员< / cjyh>
		sprintf(xml, "<cjyh>%s</cjyh>", get_cjyh());
		strxml.append(xml);
		//<!--采集时间[可空，-->
		//<cjsj>2009 - 09 - 23 04:11 : 55< / cjsj>
		sprintf(xml, "<cjsj>%s</cjsj>", get_cjsj());
		strxml.append(xml);
		//<!--执勤名警[不可空] -->
		//<zqmj>012321< / zqmj>
		sprintf(xml, "<zqmj>%s</zqmj>", get_zqmj());
		strxml.append(xml);
		//<!--备注信息[可空]-->
		//<bz>< / bz>
		sprintf(xml, "<bz>%s</bz>", get_bz());
		strxml.append(xml);

		//	<!--证据文件1[不能为空，全景图片，输入有效的http路径-->
		//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
		sprintf(xml, "<zjwj1>%s</zjwj1>", get_zjwj1());
		strxml.append(xml);
		//<!--证据文件2[能空，特写图片，输入有效的http路径-->
		//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>
		sprintf(xml, "<zjwj2>%s</zjwj2>", get_zjwj2());
		strxml.append(xml);
		//	<!--证据文件3[可空，号牌图片，输入有效的http路径]-->
		//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
		sprintf(xml, "<zjwj3>%s</zjwj3>", get_zjwj3());
		strxml.append(xml);
		//	<!--证据文件4[[可空，录像文件，输入有效的http路径-->
		//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
		sprintf(xml, "<zjwj4>%s</zjwj4>", get_zjwj4());
		strxml.append(xml);

		sprintf(xml, "</peccancyinfo>");
		strxml.append(xml);
		//	< / message>
		sprintf(xml, "</message>");
		strxml.append(xml);
		return 0;
	};
	int get_passcar_xml(string &strxml)
	{
		//
		//	FILE * fp = wfopen("test.data",);
		char xml[1024];
		sprintf(xml, "<?xml version = \"1.0\" encoding = \"GB2312\"?>");
		strxml.append(xml);
		sprintf(xml, "<message System = \"ATMS\" Ver = \"1.0\">");
		strxml.append(xml);
		sprintf(xml, "<systemtype>TGS</systemtype>");
		strxml.append(xml);
		sprintf(xml, "<messagetype>NOTICE</messagetype>");
		strxml.append(xml);
		sprintf(xml, "<sourceIP>3.0</sourceIP>");
		strxml.append(xml);
		sprintf(xml, "<targetIP></targetIP>");
		strxml.append(xml);
		sprintf(xml, "<user>PASSCAR</user>");
		strxml.append(xml);
		sprintf(xml, "<password>PASSCAR</password>");
		strxml.append(xml);
		sprintf(xml, "<passcarinfo>");
		strxml.append(xml);

		//		<!--卡口编号[不能为空] -->
		//<kkid>371600000001< / kkid>
		sprintf(xml, "<kkid>%s</kkid>", get_kkid());
		strxml.append(xml);

		//	<!--号牌号码[不能为空, 输入:识别的车牌号码，未完全识别写‘拒识无牌’-->
		//	<hphm>京A12345< / hphm>
		sprintf(xml, "<hphm>%s</hphm>", get_hphm());
		strxml.append(xml);
		//<!--号牌颜色[不能为空，输入：黄，蓝，白，黑，其它]-->
		//<hpys>黄< / hpys>
		sprintf(xml, "<hpys>%s</hpys>", get_hpys());
		strxml.append(xml);

		//	<!--车辆类型[不可空，符合GA24.4的要求]输入编码：01 - 大型车辆，02 - 小型车辆，03 - 外籍车辆，23 - 公安警用车辆，99 - 其它-->
		//	<cllx>01< / cllx>
		sprintf(xml, "<cllx>%s</cllx>", get_cllx());
		strxml.append(xml);

		//	<!--过往时间[不能为空，时间格式：yyyy - MM - dd hh24 : mm : ss]-->
		//	<gwsj>2009 - 09 - 23 04:11 : 55< / gwsj>
		sprintf(xml, "<gwsj>%s</gwsj>", get_gwsj());
		strxml.append(xml);

		//	<!--方向编号[不能为空，输入（1 - 4）。定义如下：南向北1：东向西2：北向南3:西向东4-->
		//	<fxbh>1< / fxbh>
		sprintf(xml, "<fxbh>%s</fxbh>", get_fxbh());
		strxml.append(xml);

		//	<!--车道编号[不能为空，输入：1 - 99]-->
		//	<cdbh>2< / cdbh>
		sprintf(xml, "<cdbh>%s</cdbh>", get_cdbh());
		strxml.append(xml);
		//	<!--车辆速度[不能为空，输入：1 - 300]-->
		//	<clsd>76</clsd>
		sprintf(xml, "<clsd>%s</clsd>", get_clsd());
		strxml.append(xml);
		//	<!--证据文件1[不能为空，全景图片，输入有效的http路径-->
		//	<zjwj1>http://10.2.61.209/capture/2009/09/10120420070204150006_1.jpg</zjwj1>
		sprintf(xml, "<zjwj1>%s</zjwj1>", get_zjwj1());
		strxml.append(xml);
		//<!--证据文件2[能空，特写图片，输入有效的http路径-->
		//	<zjwj2>http ://10.2.61.209/capture/2009/09/10120420070204150006_2.jpg</zjwj2>
		sprintf(xml, "<zjwj2>%s</zjwj2>", get_zjwj2());
		strxml.append(xml);
		//	<!--证据文件3[可空，号牌图片，输入有效的http路径]-->
		//	<zjwj3>http ://10.2.61.209/capture/2009/09/10120420070204150006_3.jpg</zjwj3>
		sprintf(xml, "<zjwj3>%s</zjwj3>", get_zjwj3());
		strxml.append(xml);
		//	<!--证据文件4[[可空，录像文件，输入有效的http路径-->
		//	<zjwj4>http ://10.2.61.209/capture/2009/09/10120420070204150006_4.MP4</zjwj4>
		sprintf(xml, "<zjwj4>%s</zjwj4>", get_zjwj4());
		strxml.append(xml);
		//	<!--记录类型 : [不能为空, 0：正常车辆1：黑名单车辆2：特殊勤务车辆3：布控车辆4：占道车辆5：历史违法车辆6：畅行车辆7：区间超速车辆8：超速违法车辆9：逆行 10：转入违法  11.闯红灯违法 12.不按车道行驶 13.违法停车  14.压黄线] -->
		//	<jllx>0</jllx>
		sprintf(xml, "<jllx>%s</jllx>", get_jllx());
		strxml.append(xml);
		//	<!--车速毫秒[可空, 车速的毫秒部分，3位]-->
		//	<cshm>869< / cshm>
		sprintf(xml, "<cshm>%s</cshm>", get_cshm());
		strxml.append(xml);
		//	< / passcarinfo>
		sprintf(xml, "</passcarinfo>");
		strxml.append(xml);
		//	< / message>
		sprintf(xml, "</message>");
		strxml.append(xml);
		return 0;
	};

	int inittype;	//初始化未完成

	/*
		先调用init_kkinfo()初始化所有卡口信息
		当初始化完成后，将inittype状态改为1，表明初始化完成，可传数据。
		初始化失败的卡口信息放入unregkkcdlist中，由线程thread_regkkinfo每十分钟再初始化一次
		然后调用init_wxdata传数据，调用时会先检测要传的数据的卡口信息是否初始化，只传已经初始化成功的数据。未初始化的数据返回值为2；
	*/
	/*
	int init_kkinfo()
	{
		inittype = 0;
		printf("开始注册卡口\n");
		int kkcount = atoi(read_csinfo("kklist", "count", "0"));
		printf("获取需要注册卡口数为%d\n", kkcount);
		for(int i = 0; i < kkcount; i ++)
		{
			char kkkey[24] = {0};
			sprintf(kkkey, "%d", i);
			string kkid = read_csinfo("kklist", kkkey, "0000000000000");
			string fxlx = read_csinfo(kkid.c_str(), "fxlx", "1");
			int cdcount = atoi(read_csinfo(kkid.c_str(), "cdcount", "0"));
			
			for(int j = 0; j < cdcount; j ++)
			{
				int res = init_wxdata(kkid, fxlx, j + 1);
				if(res <= 0)
				{
					char tmp[2] = {0};
					sprintf(tmp, "_%d", j+1);
					string tstr = kkid;
					tstr.append(tmp);
					gmuxunreg.lock();
					unregkkcdlist[tstr] = 1;
					gmuxunreg.unlock();
				}
			}
		}
		return 0;
	}
	void reinit_kkinfo()
	{
		while(1)
		{
			for(map<string,int> :: iterator iter = unregkkcdlist.begin(); iter != unregkkcdlist.end(); iter ++)
			{
				string it = iter->first.c_str();
				string kk = strtok((char*)it.c_str(), "_");
				int cd = atoi(strtok(NULL,"_"));
				string fxlx = read_csinfo(kk.c_str(), "fxlx", "1");
				int res = init_wxdata(kk, fxlx, cd);
				if(res > 0)
				{
					gmuxunreg.lock();
					unregkkcdlist[it] = 0;
					gmuxunreg.unlock();
				}
			}
			Sleep(10*60*1000);
		}
	};
	*/
	int init_wxdata(string kkbh, string fxlx, long cdh)
	{

		char refxml[254];
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		char tmp[30] = { 0 };
		sprintf(tmp, "%4d-%02d-%02d %02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
		string jkid = read_csinfo("wxjkinfo", "jkid", "62C01");
		string jkxlh = read_csinfo("wxjkinfo", "jkxlh", "791F09090306170309158E9882DB8B8E8FEEF681FF8B9AEB92CFD0A1A1C5A5D3CCA8");
		string info = "<info><jkid>";
		string hostip = read_csinfo("wxjkinfo", "hostip", "10.176.100.185");
		info += jkid;
		info += "</jkid><jkxlh>";
		info += jkxlh;
		info += "</jkxlh><time>";
		info += tmp;
		info += "</time></info>";
	
		printf("卡口注册信息：%s,%s,%d\n", kkbh.c_str(), fxlx.c_str(), cdh);
		printf("info:%s\n", info.c_str());
		//		return -1;

		return call_wx_upload_data_inittrans(kkbh, fxlx, cdh, info, hostip);
	}

	int put_wxdata()
	{
		/*
		for(map<string,int> :: iterator iter = unregkkcdlist.begin(); iter != unregkkcdlist.end(); iter ++)
		{

			string kk = strtok((char *)iter->c_str(), "_");
			int cd = atoi(strtok(NULL,"_"));
			if((kk.compare(get_kkid()) == 0) && (cd == atoi(get_cdbh())))
			{
				char tmp[24] = {0};
				sprintf(tmp, "%s_%d", kk.c_str(), cd);
				string tt(tmp);
				gmuxunreg.lock();
				//unregkkcdlist.push_back(tt);
				unregkkcdlist[tt] = 1;
				gmuxunreg.unlock();
				return 2;
			}
		}
		*/
		
		
		if (isreg() == false)
		{
			WriteLog("卡口注册失败！");
			return -1;
		};
		
		char refxml[512] = {0};
		string ikkbh(get_kkid());	//卡口编号不变，直接用
//		string ifxlx = "1";			//不能为空（1-上行/进城/环线顺时针、2-下行/出城/环线逆时针）
		//string ifxlx = read_csinfo(ikkbh.c_str(), "fxlx", "1");
		string ifxlx = get_fxbh();
		LONG64 icdh = atol(get_cdbh());	//车道号，1位的东西干嘛定义了long64
		string ihphm(get_hphm());	//号牌号码，直接用
		string ihpzl(get_cllx());	//号牌种类，直接用
		if(strcmp(get_cllx(), "99") == 0)
			ihpzl = "44";
		string igcsj(get_gwsj());	//过车时间，格式一致，直接用
		LONG64 iclsd = atol(get_clsd());//车辆速度，最长三位
		LONG64 iclxs = atol(get_clxs());		//车辆限速
		string iwfdm(get_wfxw());		//违法代码
		LONG64 icwkc = 0;				//车外廓长
		string ihpys = get_hpys();				//0-白色，1-黄色，2-蓝色，3-黑色，4-绿色，9-其它颜色
		if(strcmp(get_cllx(), "01") == 0)
			ihpys = "1";
		else
			if(strcmp(get_cllx(), "02") == 0)
				ihpys = "2";
			else
				if(strcmp(get_cllx(), "23") == 0)
					ihpys = "0";
				else
					ihpys = "9";
		if (ihphm.length() == 6)
		{
			ihphm = "-";
			ihpzl = "41";
			ihpys = "9";
			//			icllx = "K11";
		}
		string icllx(get_cllx());		//参考GA24.4（K11-大型普通客车，K21-中型普通客车，K31-小型普通客车，K33-轿车，H11-重型普通客车，H21-中型普通客车，M22-轻便二轮摩托车）
		string ifzhpzl = ihpzl;			//辅助号牌种类	参考GA24.7
		string ifzhphm = ihphm;			//辅助号牌号码	无牌、未识别、无法识别均用半角“-”表示，其中无号牌要注意hpzl填41
		string ifzhpys = ihpys;			//辅助号牌颜色	0-白色，1-黄色，2-蓝色，3-黑色，4-绿色，9-其它颜色
		string iclpp = "";				//车辆品牌
		string iclwx = "";				//车辆外形
		string icsys = "";				//车身颜色	参考GA24.8（A-白，B-灰，C-黄，D-粉，E-红，F-紫，G-绿，H-蓝，I-棕，J-黑，Z-其他）
		char url[256] = {0};
		char pic[128] = {0};
		char ext[128] = {0};
		_splitpath(get_zjwj1(), NULL, url,pic , ext);
		string itplj(url);				//文件路径
		string itp1(pic);				//图片文件名1
		itp1 += ext;
		memset(pic, 0, 128);
		memset(ext, 0, 128);
		_splitpath(get_zjwj2(), NULL, NULL, pic, ext);
		string itp2(pic);				//图片文件名2
		itp2 += ext;
		memset(pic, 0, 128);
		memset(ext, 0, 128);
		_splitpath(get_zjwj3(), NULL, NULL, pic, ext);
		string itp3(pic);				////图片文件名3
		itp3 += ext;
		string itztp = "";				//特征图片	扩展预留，为空
		/*
		int call_wx_upload_data_inpasscar(std::string kkbh, std::string fxlx, long long cdh, char * refxml, std::string hphm, std::string hpzl
			, std::string gcsj, long long clsd, long long clxs, std::string wfdm, long long cwkc, std::string hpys, std::string cllx
			, std::string fzhpzl, std::string fzhphm, std::string fzhpys, std::string clpp, std::string clwx, std::string csys
			, std::string tplj, std::string tp1, std::string tp2, std::string tp3, std::string tztp);
			*/
		int iresult = call_wx_upload_data_inpasscar(ikkbh, ifxlx, icdh,  ihphm, ihpzl
			, igcsj, iclsd, iclxs, iwfdm, icwkc, ihpys, icllx
			, ifzhpzl, ifzhphm, ifzhpys, iclpp, iclwx, icsys
			, itplj, itp1, itp2, itp3, itztp);
			
		return iresult;
	};
	
} ;



c_data_convert_hkfilename g_datafile_convert_hkfilename;
#include ".\lib\write_log.h"
class waitproc_info
{
private:
	struct _tmpdata
	{
		string datainfo;
		int imgcount;
		string img1;
		string img2;
		string img3;
	};

private:
	list<_tmpdata *> m_waitproc_info;
public:
	int waitcount()
	{
		return m_waitproc_info.size();
	}
	void add_proc(const char * datainfo, int imgcount, char * img1, char * img2, char * img3)

	{
		gmux.lock();
		_tmpdata * tmpdata = new _tmpdata;
		tmpdata->datainfo = datainfo;
		tmpdata->imgcount = imgcount;
		tmpdata->img1 = img1;
		tmpdata->img2 = img2;
		tmpdata->img3 = img3;
		m_waitproc_info.push_back(tmpdata);
		gmux.unlock();
	};
private:
	/*
	< ? xml version = "1.0" encoding = "GB2312" ? >
	<message System = "ATMS" Ver = "1.0">
	<systemtype>TGS< / systemtype>
	<messagetype>FEEDBACK< / messagetype>
	<sourceIP>3.0< / sourceIP>
	<targetIP>< / targetIP>
	<user>< / user>
	<password>< / password>
	<executeresult>
		<!- 如果成功，返回执行成功后记录编号]-->
		<recordid>< / recordid>
		<!- 错误描述]-->
		<errordescription>不是正确的xml格式！< / errordescription>
		<!- 成功所影响的条数]-->
		<resultnum>0< / resultnum>
		<!- 成功后的描述]-->
		<resultdescription>< / resultdescription>
		<!- 错误代码]-->
		<errorcode>0< / errorcode>
	< / executeresult>
	< / message>
	*/
	int check_result_xml(const char * xml)
	{
		string str = "";
		
		char * p = (char *)strstr((const char *)xml, ((const char *)"<errorcode>"));
		p += strlen("<errorcode>");
		while (*p != '<' && *p != '\0')
		{
			if (*p >= '0' && *p <= '9')
				str += *p;
			p++;
		};
		return atoi(str.c_str());
	};
public:
	void proc_info(const char * datastr, int * iresult_code, char * reset_msg, int imgcount, const char * img1, const char * img2, const char * img3)
	{
		gmux.lock();
		g_datafile_convert_hkfilename.read_baseinfo((char *)datastr,imgcount,img1,img2,img3);
		
		char stmp[256];
		//strxml.append(g_datafile_convert_hkfilename.sdatainfo);
		int iresult = 0;
		iresult = g_datafile_convert_hkfilename.put_wxdata();
		gmux.unlock();
		/*
		if (g_datafile_convert_hkfilename.get_datatype() == 0)
		{
			//tracert car
			 iresult = g_datafile_convert_hkfilename.get_passcar_xml(strxml);
			 printf(strxml.c_str());
			 if (iresult == 0)
				 iresult = upload_data_inpasscar(strxml.c_str(), reset_msg);
		}
		else
		{
			//vio car
			 iresult = g_datafile_convert_hkfilename.get_viodata_xml(strxml);
			 printf(strxml.c_str());
			 if (iresult == 0)
				 iresult = upload_data_inviocar(strxml.c_str(), reset_msg);
		};
		*/
		//WriteLog((char *)strxml.c_str());
		
		/*
		if (iresult == 0)
		{
			
			if (reset_msg != "\0")
			{
				
				WriteLog((char *)reset_msg);
				iresult = check_result_xml(reset_msg);
			}
			else
			{
				iresult = 100;
			}
			
		}
	   */

		if (iresult<0)
		{
			*iresult_code = iresult;
			sprintf(stmp, "error[%d]:web service upload data fail!", iresult);
			WriteLog(stmp);
		};
	
	}
	bool gproc_flag;
	void proc_info()
	{
		while (gproc_flag)
		{
			gmux.lock();
			list<_tmpdata*>::const_iterator iter = m_waitproc_info.begin();
			gmux.unlock();
			if (iter != m_waitproc_info.end())
			{
				proc_info((*iter)->datainfo.c_str(), 0, 0, (*iter)->imgcount, (*iter)->img1.c_str(), (*iter)->img2.c_str(), (*iter)->img3.c_str());
				gmux.lock();
				m_waitproc_info.remove(*iter);
				delete (_tmpdata*)(*iter);
				gmux.unlock();
				Sleep(1);
			}
			else
			{
				Sleep(100);
			}
		}
	}
} gwaitproc_info;



static void __cdecl thread_proc_datainfo(void * param)
{
	gwaitproc_info.proc_info();
};

/*
static void __cdecl thread_regkkinfo(void * param)
{
	while(1)
	{
		Sleep(500);
		if(g_datafile_convert_hkfilename.inittype == 1)
			g_datafile_convert_hkfilename.reinit_kkinfo();
	}
	
};
*/

#include <process.h>
class c_work
{
private:
	uintptr_t thread;
	
public:
	c_work()
	{
		WriteLog("thread work begin!");
		gwaitproc_info.gproc_flag = true;
		thread = _beginthread(thread_proc_datainfo, NULL, NULL);
		
	};
	~c_work()
	{
		gwaitproc_info.gproc_flag = false; 
		//SignalObjectAndWait()
	}
} g_work;

void __stdcall plug_proc_data(int itype, const char * datastr, int * irescode, char * proc_msg,int imgcount,char * img1,char * img2,char * img3)
{
	if (itype == 0)
	{
		gwaitproc_info.proc_info(datastr, irescode, proc_msg,imgcount,img1,img2,img3);
	}
	else
	{
		gwaitproc_info.add_proc(datastr, imgcount, img1, img2, img3);
	}
		//sprintf(proc_msg, "process [*s]", strxml);
		sprintf(proc_msg, "process [%s],wait_proc[%d]", datastr,gwaitproc_info.waitcount());
 };

void  __stdcall init_work_mode(int workmode /*= 0*/, const char * webserviceurl /*= "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx"*/)
{
//	sprintf(soap_endpoint, webserviceurl);
}


int __cdecl main(int argc, char * argv[])
{

	printf(argv[1]);
	char reftest[1024];
	//void  plug_proc_data(int itype, const char * datastr, char * proc_msg)
	plug_proc_data(0, (const char *)argv[1],NULL, reftest,1,argv[1],"","");
	printf("\n");
	printf(reftest);
	system("PAUSE");

	return 0;
}

