// RmAgentDllTestDlg.h : 头文件
//

#pragma once
#include "stdafx.h"
#include "tmriagent.h"

class CPassInfoBean
{
private:
	TCHAR buffer[8];

public:
	tstring  gcxh;
    tstring  kkbh;
	tstring  fxlx;
	int  cdh;
	tstring  gcsj;
	tstring  hpzl;
	tstring  hphm;
	tstring  hpys;

	int cwkc;
	int clsd;

	tstring csys;
	tstring clpp;
	tstring cllx;
	tstring fzhpzl;
	tstring fzhphm;
	tstring fzhpys;
	tstring  tplj;
	tstring  tp1;
	tstring  tp2;
	tstring  tp3;
	
	long ycsj;        // 延迟时间（以秒为单位）

	CPassInfoBean()
	{  
	   gcxh.clear();
	   kkbh.clear();
	   fxlx.clear();
	   cdh = 0;
	   gcsj.clear();
	   hpzl.clear();
	   hphm.clear();
	   hpys.clear();

	   cwkc = 0;
	   clsd = 0;

	   csys.clear();
	   clpp.clear();
	   cllx.clear();
	   fzhpzl.clear();
	   fzhphm.clear();
	   fzhpys.clear();
	   tplj.clear();
	   tp1.clear();
	   tp2.clear();
	   tp3.clear();

	   ycsj = 0;
	};

	void clone(const CPassInfoBean& rhs)
	{
		gcxh = rhs.gcxh;
		kkbh = rhs.kkbh;
		fxlx = rhs.fxlx;
		cdh = rhs.cdh;
		gcsj = rhs.gcsj;
		hpzl = rhs.hpzl;
		hphm = rhs.hphm;
		hpys = rhs.hpys;
		cwkc = rhs.cwkc;
		clsd = rhs.clsd;

		csys = rhs.csys;
		clpp = rhs.clpp;
		cllx = rhs.cllx;
		fzhpzl = rhs.fzhpzl;
        fzhphm = rhs.fzhphm;
		fzhpys = rhs.fzhpys;

		tplj = rhs.tplj;
		tp1 = rhs.tp1;
		tp2 = rhs.tp2;
        tp3 = rhs.tp3;

		ycsj = rhs.ycsj;
	}

	tstring getCdh()
	{
		memset(buffer,0,8);
        _itot( cdh, buffer, 10 );
	    return buffer;
	}

	tstring getClsd()
	{
        memset(buffer,0,8);
        _itot( clsd, buffer, 10 );
	    return buffer;
	}

	tstring getCwkc()
	{
        memset(buffer,0,8);
        _itot( cwkc, buffer, 10 );
	    return buffer;
	}

	tstring getYcsj()
	{
        TCHAR buffer[10];
        _itot( ycsj, buffer, 10 );
	    return buffer;
	}
};

class PassInfoBean : public CPassInfoBean
{
public:
	tstring cllxmc;
	tstring kkmc;
	tstring fxbm;
    
	PassInfoBean()
	{
		cllxmc.clear();
		kkmc.clear();
		fxbm.clear();        
	}

	int getTpsl()
	{
		int nTps = 0;
		if (tp1.length()>0)
			nTps++;
		if (tp2.length()>0)
			nTps++;
		if (tp3.length()>0)
			nTps++;
		return nTps;
	}

	void clone(const PassInfoBean& rhs)
	{
		CPassInfoBean::clone(rhs);
		cllxmc = rhs.cllxmc;
		kkmc = rhs.kkmc;
		fxbm = rhs.fxbm;
	}
};


// CRmAgentDllTestDlg 对话框
class CRmAgentDllTestDlg : public CDialog
{
// 构造
public:
	CRmAgentDllTestDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_RMAGENTDLLTEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
     
	PassInfoBean m_passinfo;

	TmriAgent m_tmriAgent;
	afx_msg void OnBnClickedButInit();
	CString m_kkbh;
	CString m_fxlx;
	long m_cdh;
	CString m_hostport;

	afx_msg void OnBnClickedButPass();
	afx_msg void OnBnClickedButPicup();
	CString m_jkxlh;
	CString m_jkid;
	afx_msg void OnBnClickedButLmt();
	afx_msg void OnBnClickedButTime();
};
