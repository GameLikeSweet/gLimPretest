// CProcess.cpp: 구현 파일
//

#include "pch.h"
#include "MFCGlimpretest.h"
#include "CProcess.h"


// CProcess

CProcess::CProcess()
{
}

CProcess::~CProcess()
{
}


// CProcess 멤버 함수

void CProcess::GetStartInfo(CImage* pImage)
{
	unsigned char* fm = (unsigned char*)pImage->GetBits();
	int nWidth = pImage->GetWidth();
	int nHeight = pImage->GetHeight();
	int nPitch = pImage->GetPitch();

	for (int y = 0; y < nHeight; y++)
	{
		memset(fm + y * nPitch, 128, nWidth);
	}
}


void CProcess::threadProcess(CImage* pImage, int* pRet)
{
	CProcess process;
	process.GetStartInfo(pImage);  
	if (pRet) *pRet = 0;            
}
