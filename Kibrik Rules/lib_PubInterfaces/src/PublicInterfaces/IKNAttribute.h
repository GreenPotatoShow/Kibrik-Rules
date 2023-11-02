// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNAttributeH
#define IKNAttributeH
//-------------------------------------------------------------------
#include "KNMacros.h"
//-------------------------------------------------------------------
// !!! НЕ РЕАЛИЗОВАНО - на будущее
/**
 *	@interface IKNAttribute
 *	Описание строкового атрибута, заданного доменом.
 *  @note Используется для описания морфологических атрибутов. 
 */
class IKNAttribute
{
public:
    /** Тип атрибута.
     *	@return 0 - морфологический атрибут
     *			1 - семантический атрибут
     */
//	virtual int GetType() const = 0;
	/** Название атрибута. */
	virtual t_errno GetName( char* oName ) const = 0;
	/** Маска атрибута. */
//	virtual t_errno GetMask( char* oMask ) = 0;
    /** Количество значений атрибута. */
	virtual unsigned GetCount() const = 0;
	/** Занчение атрибута. */
	virtual t_errno GetValue( unsigned iIndex, char* oVal ) const = 0;
	/** Занчение атрибута. */
	virtual bool IsValue( char* iVal ) const = 0;
	/** Взятие индекса значения элемента. */
	virtual int GetValueIndex( char* iVal ) const = 0;
//----------------------------------------------------------
	/** Добавление занчения атрибута. */
	virtual t_errno AddValue( char* iVal ) = 0;
	/** Удаление занчения атрибута. */
	virtual void DeleteValue( char* iVal ) = 0;
	/** Изменить название атрибута. */
	virtual t_errno EditName( char* iNewName ) = 0;
};

#endif
