#pragma once

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CWnd* m_pParent;
	CImage m_image;

	int nRadius = 10;
	int nCircleR = 0;
	int nBorder = 10;
private:
	CPoint Numbers[3];
	CPoint center;

	int R[3];
	int nNum = 0;

	bool isDraging = false;
	CPoint* pDragTarget = nullptr;
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void InitImage();
	void ResetImage();
	void UpdateCoordLabel();
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	void MakeCircle(int x, int y, int r, int color = 0);

	void Random();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int GetDistance( CPoint& A,  CPoint& B);

private:
	
	void ClearImage(int v = 255);
	void RenderAllCircles();
	bool FindCenter();
	void DrawBorder();
	void GetBorder();
};
