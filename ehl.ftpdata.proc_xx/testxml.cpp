// testxml.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "cxx_xml.h"
using namespace std;
bool getPassCarXmlInfo(const char * xml, string &filename);
const char * get_default_cllx(const char * hpys);
bool get_datetime(const char * str, string &datetime);
bool getVioXmlInfo(const char * xml, string &filename);
int _tmain(int argc, _TCHAR* argv[])
{


		    string requestxml = "";
			requestxml = requestxml + "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
			+ "<?xml version = \"1.0\" encoding = \"UTF-8\"?>"
			+ "<rootInfo>"
			+		"<headInfo>"
			+		"<devCode>6109010004</devCode>"
			+		"<license>00000000</license>"
			+		"<comName>0000000</comName>"
			+		"<comWord>000000</comWord>"
			+		"<sendTime>2015 - 08 - 21 16:51 : 25</sendTime>"
			+		"<ver>1.2</ver>"
			+	"</headInfo>"
			+	"<listInfo>"
			+	"<roadcode>610901000004</roadcode>"
			+	"<dcode>04</dcode>"
			+	"<dcodeOther>2</dcodeOther>"
			+	"<lcode>1</lcode>"
			+	"<ltype>01</ltype>"
			+	"<plateTime>2015 - 08 - 21 16:51 : 19 : 967</plateTime>"
			+	"<plateFlag>1</plateFlag>"
			+	"<fplateNum>陕a200</fplateNum>"
			+	"<fplateColor>4</fplateColor>"
			+	"<fplateType>99</fplateType>"
			+	"<carColor>Z</carColor>"
			+	"<carType>X99</carType>"
			+	"<carBrand></carBrand>"
			+	"<carLength>0</carLength>"
			+	"<carWidth>0</carWidth>"
			+	"<img1_path>/20150821/6109010004/04/1/K_20150821165119967_2.jpg</img1_path>"
			+	"<img2_path>/20150821/6109010004/04/1/K_20150821165119670_1.jpg</img2_path>"
			+	"<img3_path></img3_path>"
			+	"<img4_path></img4_path>"
			+	"<img5_path></img5_path>"
			+	"<img1_s_path></img1_s_path>"
			+	"<img2_s_path></img2_s_path>"
			+	"<img3_s_path></img3_s_path>"
			+	"<img4_s_path></img4_s_path>"
			+	"<img5_s_path></img5_s_path>"
			+	"<img1_s_prm></img1_s_prm>"
			+	"<img2_s_prm></img2_s_prm>"
			+	"<img3_s_prm></img3_s_prm>"
			+	"<img4_s_prm></img4_s_prm>"
			+	"<img5_s_prm></img5_s_prm>"
			+	"<img_flag>2</img_flag>"
			+	"<ftp_flag>2</ftp_flag>"
			+	"<platePos></platePos>"
			+	"<driverPos></driverPos>"
			+	"<carSpeed>67</carSpeed>"
			+	"<valdate>4781</valdate>"
			+	"<isUpFile>1</isUpFile>"
			+	"</listInfo>"
			+ "</rootInfo>";
			printf("-----------------%s\n", requestxml.c_str());
		cxx_xml myxml;
		myxml.readxml(requestxml.c_str());
		myxml.print_xmldata();
		string str;
		myxml.xpath_gettext("/rootInfo/listInfo/plateTime", str);
		string filename = "";
		getPassCarXmlInfo(requestxml.c_str(), filename);


		string vioxml = "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>";
			  vioxml += "<rootInfo><headInfo><devCode>6109010011</devCode><license>00000000</license><comName>0000000</comName><comWord>000000</comWord><sendTime>2015-08-21 16:51:40</sendTime><ver>1.2</ver></headInfo><vioInfo><roadcode>610901000011</roadcode><dcode>04</dcode><lcode>2</lcode><ltype>01</ltype><vioType>1303</vioType><vioTime>2015-08-21 16:51:36:805</vioTime><red_end_time>2015-08-21 16:51:36:805</red_end_time><red_start_time>2015-08-21 16:51:36:805</red_start_time><plateNum>...C97516</plateNum><plateColor>2</plateColor><plateType>02</plateType><carClass>E</carClass><carColor>E</carColor><carType>X99</carType><carBrand> </carBrand><speedCar>120</speedCar><speedStd>100</speedStd><speedStd_big>80</speedStd_big><speedStd_sml>100</speedStd_sml><img1_path>/20150821/6109010011/04/2/K_20150821165136805_2.jpg</img1_path><img2_path>/20150821/6109010011/04/2/K_20150821165136577_1.jpg</img2_path><img3_path></img3_path><img4_path></img4_path><video_path></video_path><img_flag>2</img_flag><ftp_flag>2</ftp_flag><valdate>4764</valdate><isUpFile>1</isUpFile></vioInfo></rootInfo>";
		cxx_xml vioxx;
		vioxx.readxml(vioxml.c_str());
		vioxx.print_xmldata();
		string ss = "";
		getVioXmlInfo(vioxml.c_str(), ss);
//		printf(str.c_str());
		getchar();
		int i;
		cin >> i;
		return 0;

}

bool getPassCarXmlInfo(const char * xml, string &filename)
{
	string str = "";
	cxx_xml myxml;
	myxml.readxml(xml);
	//2015 - 08 - 21 16:51 : 19 : 967
	myxml.xpath_gettext("/rootInfo/listInfo/plateTime", str);
	get_datetime(str.c_str(), str);
	filename += str;
	filename += "_0_";
	str = "";
	//carspeed
	myxml.xpath_gettext("/rootInfo/listInfo/carSpeed", str);
	filename += str;
	filename += "_";
	str = "";
	//plate
	myxml.xpath_gettext("/rootInfo/listInfo/fplateNum", str);
	filename += str;
	filename += "_";
	str = "";
	//platecolor
	myxml.xpath_gettext("/rootInfo/listInfo/fplateType", str);
	filename += get_default_cllx(str.c_str());
	filename += "_";
	str = "";
	//platetype
	myxml.xpath_gettext("/rootInfo/listInfo/fplateType", str);
	filename += str;
	filename += "_";
	str = "";
	//cartype
	myxml.xpath_gettext("/rootInfo/listInfo/carType", str);
	filename += str;
	filename += "_";
	str = "";
	//direction
	myxml.xpath_gettext("/rootInfo/listInfo/dcode", str);
	filename += str;
	filename += "_";
	str = "";
	//cdid
	myxml.xpath_gettext("/rootInfo/listInfo/lcode", str);
	filename += str;
	filename += "";
	str = "";
	//sbbh
	myxml.xpath_gettext("/rootInfo/headInfo/devCode", str);
	filename += str;
	filename += "_0_hik.jpg";
	//20160603100033774_0_92_鄂CEH786_蓝_0_1_由西向东_02_6109010000204_0_hik.jpg
	return true;
}
bool get_datetime(const char * str, string &datetime)
{
	int i = 0;
	char time[18] = { 0 };
	while (true)
	{
		if (*(str + i) >= 48 && *(str + i) <= 57)
		{

			memcpy(time + strlen(time), str + i, 1);
			i++;
		}
		else
		{
			i++;
		}
		if (i > strlen(str))
			break;
	}
	datetime = time;
	return 1;
}
const char * get_default_cllx(const char * hpys)
{
	const char * strtmpdef[5][2] = { { "黄", "01" }, { "蓝", "02" }, { "白", "23" }, { "黑", "03" }, { "其它", "99" } };
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(strtmpdef[i][0], hpys))
		{
			return strtmpdef[i][0];
		}
	}
	return "99";
}

bool getVioXmlInfo(const char * xml, string &filename)
{
	string str = "";
	filename = "";
	cxx_xml myxml;
	myxml.readxml(xml);
	myxml.xpath_gettext("/rootInfo/headInfo/sendTime", str);
	get_datetime(str.c_str(), str);
	filename += str;
	filename += "_1_";
	str = "";
	//speed
	myxml.xpath_gettext("/rootInfo/vioInfo/speedCar", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/plateNum", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/plateType", str);
	filename += get_default_cllx(str.c_str());
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/plateType", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/dcode", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/lcode", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/headInfo/devCode", str);
	filename += str;
	filename += "_";
	str = "";
	myxml.xpath_gettext("/rootInfo/vioInfo/vioType", str);
	filename += str;
	filename += "_hik.jpg";
	return 1;
	//【YYYY】【MM】【DD】【HH】【FF】【SS】【SSS】_1_【CLSD】_【CPHM】_【CPYS】_【CPLX】_【CLLX】_【JCFX】_【CDBH】_6109010005_【WFDM】_hik.jpg
}//20160510131045767_1_64_鄂M08585_黄_0_2_由西向东_02_6109010028_1240_hik.jpg