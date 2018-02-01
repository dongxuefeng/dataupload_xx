/*
last ver:2011.12.1
修改时间计算错误


*/

#ifndef _c_time_h__
#define _c_time_h__

#include <stdlib.h>
#include <memory.h>
#include <windows.h>

const int _month[] = {31,28,31,30,31,30,31,31,30,31,30,31};
const int _month1[] = {31,29,31,30,31,30,31,31,30,31,30,31};
const int idaysec = 60*60*24;
const int isecMillisec = 1000;

class c_time
{
private:
	long mmilliseconds;	
	long msec;
	long mday;

	//获取字符串时临时变量
	char strtmp[256];

private:
	int get_monthday(int year,int month)
	{
		 int tmpday = 0;
	     if(year%4 == 0)
		 {
			 //闰年
			 for(int i=0;i<month-1;i++)
			 {
				tmpday += _month1[i];
			 };
		 
		 }
		 else
		 {
			 //闰年
			 for(int i=0;i<month-1;i++)
			 {
				tmpday += _month[i];
			 };			
		 };
		 //tmpday += year * 365 + (year/4);
		 tmpday += year * 365 + (year*97/400);
		 return tmpday;
	};
	
public:
	void set_time(int year,int month,int day,int hour,int minute,int seconds,int milliseconds)
	{

		msec = seconds
				+ minute * 60
				+ hour * 60 * 60;

		//mday = (day-1) + get_monthday(year,month);
		mday = day + get_monthday(year,month );
		mmilliseconds = milliseconds;

	};
	void set_time(SYSTEMTIME msystime)
	{
		set_time(msystime.wYear,msystime.wMonth,msystime.wDay
			,msystime.wHour,msystime.wMinute,msystime.wSecond,msystime.wMilliseconds);
	};

	c_time(SYSTEMTIME msystime)
	{
		set_time(msystime);
	};

	void get_local_time()
	{
		SYSTEMTIME msystime;
		GetLocalTime(&msystime);
		set_time(msystime);

	};

	c_time()
	{ 
	};

	c_time(int year,int month,int day,int hour,int minute,int seconds,int milliseconds)
	{

		set_time(year,month,day,hour,minute,seconds,milliseconds);
	};
	c_time(char * strdatetime)
	{
		set_time(strdatetime);
	};


	void set_time(char * strdatetime) //yyyy-MM-dd HH:mm:ss:mms
	{

		char tmpstr[5];
		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=4)
		memcpy(tmpstr,strdatetime+0,4);
		int iyear = atoi(tmpstr);

		
		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=7)
		memcpy(tmpstr,strdatetime+5,2);
		int imonth = atoi(tmpstr);

		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=10)
		memcpy(tmpstr,strdatetime+8,2);
		int iday = atoi(tmpstr);

		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=13)
		memcpy(tmpstr,strdatetime+11,2);
		int ihour = atoi(tmpstr);

		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=16)
		memcpy(tmpstr,strdatetime+14,2);
		int iminute = atoi(tmpstr);

		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=19)
		memcpy(tmpstr,strdatetime+17,2);
		int iseconds = atoi(tmpstr);


		memset(tmpstr,0,5);
		if (strlen(strdatetime)>=22)
		{
			memcpy(tmpstr,strdatetime+20,3);
		};
		int imilliseconds = atoi(tmpstr);
		set_time(iyear,imonth,iday,ihour,iminute,iseconds,imilliseconds);
	};


	int addday(int iday)
	{
		mday += iday;
		return 1;
	};
	

	int addsec(int isec)
	{
		msec += isec;
		if( msec < 0 || msec >= idaysec )
		{
			int itmpday = msec / idaysec;
			addday(itmpday);
			msec = msec % idaysec;
			if(msec<0)
			{
				addday(-1);
				msec += idaysec;
			};
		};
		return 1;
	};

	int addmilliseconds(int imilliseconds)
	{
		mmilliseconds += imilliseconds;
		if(mmilliseconds < 0 || mmilliseconds >= isecMillisec)
		{
			int itmpsec = mmilliseconds/ isecMillisec;
			addsec(itmpsec);
			mmilliseconds %= (isecMillisec);
			if(mmilliseconds < 0)
			{
				addsec(-1);
				mmilliseconds += isecMillisec;
			};
		}
		return 1;
	};

	int get_year()
	{
		//return (int)(mday/365.25);
		return (int)(mday*400/(365*400+97));
	};
	int get_month()
	{
		int iyear = get_year();
		int itmpday = mday - iyear * 365 - (iyear*97/400);

		if( iyear%4 == 0)
		{
			//闰年
			//这个是月天
			//现在该计算月了
			for(int i=0;i<12;i++)
			{
				if (itmpday > _month1[i])
				{
					itmpday -= _month1[i];
				}
				else
				{
					return i+1;
				}

			};
		}
		else
		{
			//闰年
			//这个是月天
			//现在该计算月了
			for(int i=0;i<11;i++)
			{
				if (itmpday > _month[i])
				{
					itmpday -= _month[i];
				}
				else
				{
					return i+1;
				}
			};
		};
		return 12;
	};
	int get_day()
	{
		int iyear = get_year();
		//int itmpday = mday - iyear * 365 - (iyear*97/400);
		int itmpday = mday - get_monthday(iyear,get_month());
		/*
		if( iyear%4 == 0)
		{
			//闰年
			//这个是月天
			//现在该计算月了
			for(int i=0;i<12;i++)
			{
				if (itmpday >= _month1[i])
				{
					itmpday -= _month1[i];
				};
			};
		}
		else
		{
			//闰年
			//这个是月天
			//现在该计算月了
			for(int i=0;i<12;i++)
			{
				if (itmpday >= _month[i])
				{
					itmpday -= _month[i];
				};
			};
		};
		*/
		return itmpday;
	};
	int get_hour()
	{
	    return (msec/(60*60)) % 24;
	};
	int get_minute()
	{
	    return (msec/60) % 60;
	};
	int get_seconds()
	{
		return msec % 60;
	};
	int get_milliseconds()
	{
		return mmilliseconds;
	};

	char * get_datetime(bool bhavepartrtion = true,bool ismms = true)
	{
		if(bhavepartrtion)
		{
			if(ismms)
			{
				sprintf(strtmp,"%0.4d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d:%0.3d"
					,get_year(),get_month(),get_day(),
					get_hour(),get_minute(),get_seconds(),
					get_milliseconds());

			}
			else
			{
				sprintf(strtmp,"%0.4d-%0.2d-%0.2d %0.2d:%0.2d:%0.2d"
					,get_year(),get_month(),get_day(),
					get_hour(),get_minute(),get_seconds(),
					get_milliseconds());

			}

		}
		else
		{
			if (ismms)
			{
				sprintf(strtmp,"%0.4d%0.2d%0.2d%0.2d%0.2d%0.2d%0.3d"
					,get_year(),get_month(),get_day(),
					get_hour(),get_minute(),get_seconds(),
					get_milliseconds());

			}
			else
			{
				sprintf(strtmp,"%0.4d%0.2d%0.2d%0.2d%0.2d%0.2d"
					,get_year(),get_month(),get_day(),
					get_hour(),get_minute(),get_seconds(),
					get_milliseconds());

			}
		}
		return strtmp;
	};

	char * get_date(char * spartrtion="")
	{

		sprintf(strtmp,"%0.4d%s%0.2d%s%0.2d"
			,get_year(),spartrtion,get_month(),spartrtion,get_day());
		return strtmp;

	};

	char * get_time(char * spartrtion="")
	{

		sprintf(strtmp,"%0.2d%s%0.2d%s%0.2d"
			,get_hour(),spartrtion,get_minute(),spartrtion,get_seconds());
		return strtmp;

	};
};


#endif