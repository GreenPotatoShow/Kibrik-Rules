// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Usage notes: �������. �������� ������ ����� �������� �� �����������
//				� ������� ��������.
//	����������� ���������������� (���������� ������������� ������) ���.
//	� ����� ������ �������� ( norm )
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNConceptVocH
#define IKNConceptVocH
//---------------------------------------------------------------------------
#include "IKNConcept.h"
//---------------------------------------------------------------------------
// !!! �� ������������
/** 
 * @interface IKNVoc
 * �������. ���������� ��������.
 */
class IKNConceptVoc : public IKNVoc {
public:
	/** ������ ���������� �������. ������� �������� � ���������� �������.
	 *  ��� ������� ���������� �������� � ���������� ���������, ��� �����������.
     *	@return 0 ���� ������ �������.
	 */
	virtual IKNConcept* GetNext() = 0;

    /** �������������� ������ ��������� � ���������� ��������� � �������� �������. */
//	virtual void InitSame( IKNConcept* oTerm ) = 0;

	/** ����� ������� � �������� ������� �� ��������� �����.
	 *	���� ����� �������� ���������, �� ������������ ��������� ������
	 *	�������� � ������ ���������� ������.
     *  ������ ������������ ������ �������� �� ��������� ������.
     *	��� ������������� ���� ������� �� ��������� �������� InitSame.
	 *	@return true - ���� ��� ��������������� ������ ��������� ���������.
	 */
	virtual bool FindConcept( char* iNorm, IKNConcept* oTerm ) = 0;

	/** ������ ���������� ������� (�������� �� ������ �������� � ���������� ���������).
	 *	@return 0 ���� ������ ������� (��� �� ����������).
	 */
	virtual IKNConcept* GetSame() = 0;

	/** �������� ������� �� �������.
	 *	@note 	�������� �� ������� ������� ������� � ������� � 
	 *			������������ ���� ������� ������� �� ��������.
	 */
	virtual void Delete( IKNConcept* iTerm ) = 0;

	/** ������� � �������� ������ (�����������) � �������.
	 *	������ ����������� � 0 �����������.
	 * @param iNorm - ���������� ����� �����
	 * @return 	0 - ���� ������ ��� ���� � �������
	 */
	virtual IKNConcept* CreateConcept( char* iNorm ) = 0;

	/** ����������� ����� �������� � �������� ���. �������, ������������� � ���������� 
	 *	���������� ������� FindConcept (��� FindWord).
     *	@param iSemClass - ������������� ����� �������
	 *	@return ���-�� �������� � ����� �������
     *			0 ���� ����� �������� ���
	 */
//	virtual int FindConceptSem( char* iSemClass, IKNConcept* oTerm ) = 0;
};
//---------------------------------------------------------------------------
#endif
