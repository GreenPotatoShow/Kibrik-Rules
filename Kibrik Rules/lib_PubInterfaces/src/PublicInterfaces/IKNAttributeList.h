// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNAttributeListH
#define IKNAttributeListH
//-------------------------------------------------------------------
#include "IKNAttribute.h"
//-------------------------------------------------------------------
// !!! НЕ РЕАЛИЗОВАНО - на будущее
/**
 *	@interface IKNAttributeList
 *	Список пар <атрибут - значение>.
 *	@note Используется, например, для выражения граммем словоформы.
 *	@note Уникальность атрибута не обязательна.
 */
class IKNAttributeList
{
public:
	/** Тип списка атрибутов.
	 *	@return 0 - морфологические атрибуты
	 *			1 - постоянные морфологические атрибуты
	 *			2 - семантический атрибут
	 */
	virtual int GetType() const = 0;

	/** Получить количество пар. */
	virtual unsigned GetCount() const = 0;

	/**
	 * Взятие пары <атрибут - значение>.
	 * @param   iIndex - index of property in list(0-based) 
	 * @param   oAttrName - имя атрибута
	 * @param   oVal - значение атрибута
	 */
	virtual t_errno Get( unsigned iIndex, char* oAttrName, char* oVal ) const = 0;
	/**
	 * Взятие пары <атрибут - значение>.
	 *	@param   iIndex - index of property in list(0-based) 
	 *	@param oValueNum - номер значения из домена атрибута
     *	@return атрибут
	 */
	virtual IKNAttribute* Get( unsigned iIndex, int* oValNum ) const = 0;

	/** Проверить наличие пары в списке. */
	virtual bool IsPair( char* oAttrName, char* oVal ) const = 0;
	virtual bool IsAttr( char* oAttrName ) const = 0;
	virtual bool IsAttr( IKNAttribute* iAttr ) const = 0;

	/** Поиск пары <атрибут - значение> по значению атрибута. */
	virtual IKNAttribute* FindAttr( char* iVal ) const = 0;
	/** Поиск значения атрибута. */
	virtual bool Find( IKNAttribute* iAttr, char* oVal ) const = 0;

	/** Инициализировать поиск всех значений в спсике по атрибуту. */
	virtual int InitFind( IKNAttribute* iAttr ) = 0;
	virtual int InitFind( char* oAttrName ) = 0;
	
	virtual t_errno GetNext( char* oVal ) = 0;
//-------------------------------------------------------------------
	/** Добавить пару <атрибут - значение>. */
	virtual t_errno Add( IKNAttribute* iAttr, char* iVal ) = 0;
	/** Удалить пару. */
	virtual void Delete( IKNAttribute* iAttr, char* iVal ) = 0;
	/** Удалить все пары атрибута. */
	virtual void Delete( IKNAttribute* iAttr ) = 0;
};

#endif
