#pragma once
#include "CRes.h"
class CTexture :
    public CRes
{

private:
    //�̹��� �����ʹ� �ϳ��� �޸𸮿� �ø���, �װ� ��� ������Ʈ�� ���� ���� ��.
    //��Ʈ���� �ϳ� ������ٰ�, �װ� �Űٰܴ� ��ĥ���ָ��
    HDC         m_dc;
    HBITMAP     m_hBit;


    //������ �ȼ� �����͸� �����ϰ� ���� ��. �׸��� �װ� �������� DC�� �ʿ�. 
    //��Ʈ�� + dc�� �ؽ���. 

    BITMAP      m_bitInfo;

public:
    void Load(const wstring& _strFilePath);

    UINT Width() { return m_bitInfo.bmWidth; }
    UINT Height() { return m_bitInfo.bmHeight; }

    HDC GetDC() { return m_dc; }

private:
    CTexture();
    ~CTexture();


    friend class CResMgr;
};

