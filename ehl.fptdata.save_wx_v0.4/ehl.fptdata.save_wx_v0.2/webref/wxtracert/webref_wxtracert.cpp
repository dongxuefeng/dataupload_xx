//#include "webref_wxtracert.h"
//#include "soapH.h"
//#include "TransSoapBinding.nsmap"
#include "../../wchar_utf.h"
#include <tchar.h>
#include "../../lib/write_log.h"
#include "../../lib/iconv.h"
using namespace std;
#include "tmriagent.h"
//#define __debug
#ifdef __debug
#define __noserver
#endif
char soap_endpointwx[256] = "http://10.176.100.185:9080/rminf/services/Trans";
TmriAgent tmage;

int code_convert(char *from_charset, char *to_charset, const char *inbuf, unsigned int inlen, 
	char *outbuf, unsigned int outlen)
{
	iconv_t cd;
	const char **pin = &inbuf;
	char **pout = &outbuf;
	cd = iconv_open(to_charset, from_charset);
	if (cd == 0) return -1;
	memset(outbuf, 0, outlen);
	if (iconv(cd, pin, &inlen, pout, &outlen) == -1) return -1;
	iconv_close(cd);
	return 0;
}

//初始化
/*
int wx_upload_data_inittrans(struct _ns1__InitTrans ns1__InitTrans, struct _ns1__InitTransResponse ns1__InitTransResponse)
{
#ifdef	__noserver
	return 0;
#endif
	struct soap * soap1 = soap_new();
	//soap_set_mode(soap1, SOAP_C_UTFSTRING);
	soap_set_mode(soap1, SOAP_C_MBSTRING);
	int iresult = -1;
	WriteLog("....web service inittrans proc....");

	iresult = soap_call___ns1__InitTrans(soap1, soap_endpointwx, "", &ns1__InitTrans, &ns1__InitTransResponse);
	if (iresult == SOAP_OK)
	{
		char strtmp[256];
		sprintf(strtmp,"%d", ns1__InitTransResponse.InitTransReturn);
		iresult = atoi(strtmp);
		sprintf(strtmp, "WX_WEBSERVICE_INITTRANS_REPONSE:[%lld]", iresult);
		WriteLog(strtmp);
	}
	else
	{
		soap_print_fault(soap1, stderr);
		WriteLog("WX_WEBSERVICE_INITTRANS_REPONSE Error:Connectioned Fail.");
	}

	soap_end(soap1);
	soap_free(soap1);
	return iresult;
}

*/

//上传
/*
int wx_upload_data_inpasscar(struct _ns1__WriteVehicleInfo InPassCarInfo, struct _ns1__WriteVehicleInfoResponse InPassCarInfoResponse)
{


	struct soap * soap1 = soap_new();
	soap_set_mode(soap1, SOAP_C_UTFSTRING);

	//code_convert("GB2312", "utf-8", xml, len, strtmp, olen);

	int iresult = -1;
	WriteLog("....web service inpasscarinfo proc....");
	//iresult = soap_call___ns1__InPassCarInfo(soap1, soap_endpoint, "", &InPassCarInfo, &ns1__InPassCarInfoResponse);
	iresult = soap_call___ns1__WriteVehicleInfo(soap1, soap_endpointwx, "", &InPassCarInfo, &InPassCarInfoResponse);
	if (iresult == SOAP_OK)
	{

		char strtmp[256];
		char reponse[20];
		sprintf(reponse,"%lld", InPassCarInfoResponse.WriteVehicleInfoReturn);
		iresult = atoi(reponse);
		sprintf(strtmp, "WX_WEBSERVICE_TRACERT_reponse:[%d]", iresult);
		WriteLog(strtmp);
	}
	else
	{
		soap_print_fault(soap1, stderr);
		WriteLog("WX_WEBSERVICE_TRACERT Error:Connectioned Fail.");
	}

	soap_end(soap1);
	soap_free(soap1);
	return iresult;
};
*/
int call_wx_upload_data_inittrans(std::string kkbh, std::string fxlx, long cdh,
	std::string info, std::string hostip)
{
	
	int iresult = tmage.InitTrans(kkbh.c_str(), fxlx.c_str(), cdh ,info.c_str(), hostip.c_str());
/*	struct _ns1__InitTrans InitTrans;
	struct _ns1__InitTransResponse InitTransResponse;
	InitTrans.cdh = cdh;
	InitTrans.fxlx = fxlx;
	InitTrans.info = info;
	InitTrans.kkbh = kkbh;
	
	*/
	//int iresult = wx_upload_data_inittrans(InitTrans, InitTransResponse);
	
	//sprintf(refxml, "%d", InitTransResponse.InitTransReturn);
	//iresult = InitTransResponse.InitTransReturn;
	char strtmp[1024];
	sprintf(strtmp, "\n init trans hostip(%s),kkbh(%s),fxlx(%s),cdh(%d),info(%s),return(%d)\n", hostip.c_str(),kkbh.c_str(), fxlx.c_str(), cdh, info.c_str(), iresult);
	WriteLog(strtmp);

	return iresult;
}

int call_wx_upload_data_inpasscar(std::string kkbh, std::string fxlx, long cdh,
	 std::string hphm, std::string hpzl
	, std::string gcsj, long clsd, long clxs, std::string wfdm,
	long cwkc, std::string hpys, std::string cllx
			, std::string fzhpzl, std::string fzhphm, std::string fzhpys,
			std::string clpp, std::string clwx, std::string csys
			, std::string tplj, std::string tp1, std::string tp2, std::string tp3, std::string tztp)
{
	char log_info[2048] = {0};
	WriteLog("+++++++++++++++++++  start loginfo");
	sprintf(log_info, "\nkkbh(%s),fxlx(%s),cdh(%d),hphm(%s),hpzl(%s)\
			  gcsj(%s),clsd(%d),clxs(%d),wfdm(%s),cwkc(%d),hpys(%s)\
			 ,cllx(%s),fzhpzl(%s),fzhphm(%s),fzhpys(%s),clpp(%s),clwx(%s),csys(%s)\
             ,tplj(%s),tp1(%s),tp2(%s),tp3(%s),tztp(%s)\n"
		, kkbh.c_str(), fxlx.c_str(), cdh, hphm.c_str(),hpzl.c_str()
		,gcsj.c_str(),clsd,clxs,wfdm.c_str(),cwkc,hpys.c_str()
		, cllx.c_str(), fzhpzl.c_str(), fzhphm.c_str(), fzhpys.c_str(), clpp.c_str(), clwx.c_str(), csys.c_str()
		, tplj.c_str(), tp1.c_str(), tp2.c_str(), tp3.c_str(), tztp.c_str());
	WriteLog(log_info);
	WriteLog("+++++++++++++++++++  end loginfo");

#ifdef	__noserver
	return 0;
#endif
	WriteLog("+++++++++++++++++++  start writevehicleinfo");
	int iresult = tmage.WriteVehicleInfo(kkbh.c_str(), fxlx.c_str(), cdh, hphm.c_str(), hpzl.c_str(), gcsj.c_str()
		, clsd, clxs, wfdm.c_str(), cwkc, hpys.c_str(), cllx.c_str()
		, ""
		, "", "", "", "", csys.c_str(), tplj.c_str()
		, tp1.c_str(), tp2.c_str(), tp3.c_str(), tztp.c_str());
	sprintf(log_info, "write vehicle info return [%d]", iresult);
	WriteLog(log_info);
	WriteLog("+++++++++++++++++++  end writevehicleinfo");
	/*
	struct _ns1__WriteVehicleInfo InPassCarInfo;
	struct _ns1__WriteVehicleInfoResponse InPassCarInfoResponse;
	InPassCarInfo.cdh = cdh;
	InPassCarInfo.cllx = cllx;
	InPassCarInfo.clpp = clpp;
	InPassCarInfo.clsd = clsd;
	InPassCarInfo.clwx = clwx;
	InPassCarInfo.clxs = clxs;
	InPassCarInfo.csys = csys;
	InPassCarInfo.cwkc = cwkc;
	InPassCarInfo.fxlx = fxlx;


	InPassCarInfo.fzhphm = fzhphm;
	InPassCarInfo.fzhpys = fzhpys;
	InPassCarInfo.fzhpzl = fzhpzl;
	InPassCarInfo.gcsj = gcsj;

	char utf8[256];
	//code_convert("GB2312", "utf-8", hphm.c_str(), hphm.size(), utf8, 256);
	//InPassCarInfo.hphm = utf8;
	InPassCarInfo.hphm = hphm.c_str();
	InPassCarInfo.hpys = hpys;
	InPassCarInfo.hpzl = hpzl;
	InPassCarInfo.kkbh = kkbh;
	//code_convert("GB2312", "utf-8", tp1.c_str(), tp1.size(), utf8, 256);
	//InPassCarInfo.tp1 = utf8;
	InPassCarInfo.tp1 = tp1.c_str();
	InPassCarInfo.tp2 = tp2;
	InPassCarInfo.tp3 = tp3;
	InPassCarInfo.tplj = tplj;
	InPassCarInfo.tztp = tztp;
	InPassCarInfo.wfdm = wfdm;
	int iresult = wx_upload_data_inpasscar(InPassCarInfo, InPassCarInfoResponse);
	//sprintf(refxml, "%s", InPassCarInfoResponse.WriteVehicleInfoReturn);
	*/
	return iresult;
}