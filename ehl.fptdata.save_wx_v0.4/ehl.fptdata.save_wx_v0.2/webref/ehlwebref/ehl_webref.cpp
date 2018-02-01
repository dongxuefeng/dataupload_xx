#include "ehl_webref.h"
#include "soapH.h"
#include "OpenInterfaceSoap.nsmap"
#include "../wchar_utf.h"
#include <tchar.h>
#include "../lib/write_log.h"
#include "../lib/iconv.h"
using namespace std;

char soap_endpoint[256] = "http://localhost/Ehl.Atms.Tgs.WebService/OpenInterface.asmx";

int code_convert1(char *from_charset, char *to_charset, const char *inbuf, unsigned int inlen, char *outbuf, unsigned int outlen)
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



int upload_data_inpasscar(const char * xml, char * refxml)
{

	sprintf(refxml, "");
	struct soap * soap1 = soap_new();
	soap_set_mode(soap1, SOAP_C_UTFSTRING);
	
	struct _ns1__InPassCarInfo InPassCarInfo;
	struct _ns1__InPassCarInfoResponse ns1__InPassCarInfoResponse;

	char strtmp[2048];
	unsigned int len = strlen(xml);
	unsigned int olen = 2048;
	code_convert1("GB2312", "utf-8", xml, len, strtmp, olen);
	InPassCarInfo.xmlBody = (char *)strtmp;


	int iresult = -1;
	WriteLog("....web service inpasscarinfo proc....");
	iresult = soap_call___ns1__InPassCarInfo(soap1, soap_endpoint, "", &InPassCarInfo, &ns1__InPassCarInfoResponse);
	 if (iresult == SOAP_OK)
	{	
		 len = strlen(ns1__InPassCarInfoResponse.InPassCarInfoResult);
		 code_convert1("UTF-8", "GB2312", ns1__InPassCarInfoResponse.InPassCarInfoResult
			 , len, refxml, olen);
	}
	else
	{
		soap_print_fault(soap1, stderr);
		WriteLog("Web Service Error:Connectioned Fail.");
	}

	soap_end(soap1);
	soap_free(soap1);
	return iresult;
};

int upload_data_inviocar(const char * xml, char * refxml)
{

	sprintf(refxml, "");
	struct soap * soap1 = soap_new();
	soap_set_mode(soap1, SOAP_C_UTFSTRING);

	struct _ns1__InPeccancyInfo InPassCarInfo;
	struct _ns1__InPeccancyInfoResponse ns1__InPassCarInfoResponse;

	char strtmp[2048];
	unsigned int len = strlen(xml);
	unsigned int olen = 2048;
	code_convert1("GB2312", "utf-8", xml, len, strtmp, olen);
	InPassCarInfo.xmlBody = (char *)strtmp;


	int iresult = -1;
	WriteLog("....web service inpasscarinfo proc....");
	iresult = soap_call___ns1__InPeccancyInfo(soap1, soap_endpoint, "", &InPassCarInfo, &ns1__InPassCarInfoResponse);
	if (iresult == SOAP_OK)
	{
		len = strlen(ns1__InPassCarInfoResponse.InPeccancyInfoResult);
		code_convert1("UTF-8", "GB2312", ns1__InPassCarInfoResponse.InPeccancyInfoResult
			, len, refxml, olen);
	}
	else
	{
		soap_print_fault(soap1, stderr);
		WriteLog("Web Service Error:Connectioned Fail.");
	}

	soap_end(soap1);
	soap_free(soap1);
	return iresult;
};
