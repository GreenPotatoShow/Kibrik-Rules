// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNMorphPropertiesH
#define IKNMorphPropertiesH
//---------------------------------------------------------------------------
#include "IKNMorphAttribute.h"
//---------------------------------------------------------------------------
/**
 *	@interface IKNMorphProperties
 *	Список морфологических признаков.
 *	@note Признак представляется парой: имя атрибута - значение атрибута
 */
class IKNMorphProperties
{
public:
	/** Получить количество найденных словарных объектов. */
	virtual unsigned GetCount() const = 0;

	/**
	 * Взятие морфологического признака.
	 * @param   iIndex - index of property in list(0-based)
	 * @param   oName - имя морфологического атрибута
	 * @param   oVal - значение морфологического атрибута
	 */
	virtual t_errno GetProperty( unsigned iIndex, char* oName, char* oVal ) const = 0;
	virtual const char* GetPropertyName( unsigned iIndex ) const = 0;
	virtual const char* GetPropertyValue( unsigned iIndex ) const = 0;
//	virtual t_errno GetProperty( unsigned iIndex, IKNMorphAttribute* oAttrType, char* oVal ) = 0;

	/** Взятие морфологического признака.
	 *	@param oValNum - номер значение морфологического атрибута
     *	@return морфологический атрибут (из морфологической таблицы) 
	 */
	virtual IKNMorphAttribute* GetPropertyType( unsigned iIndex, unsigned* oValNum ) const = 0;

	/** Добавление морфологического признака.
	 *	@param oValueNum - номер значение морфологического атрибута
     *	@return морфологический атрибут (из морфологической таблицы) 
	 */
	virtual t_errno AddProperty( IKNMorphAttribute* iAttrType, unsigned iValNum ) = 0;
	virtual t_errno AddProperty( IKNMorphAttribute* iAttrType, char* iVal ) = 0;
};

#endif
