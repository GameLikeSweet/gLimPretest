#pragma once

// CProcess 명령 대상

class CProcess : public CObject
{
public:
	CProcess();

	void GetStartInfo(CImage* pImage);
	static void threadProcess(CImage* pImage, int* pRet);

	virtual ~CProcess();
};


