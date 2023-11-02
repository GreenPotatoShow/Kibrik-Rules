// Copyright (c) 2008 by IIS. All rights reserved.
//===================================================================
// Dec 2008                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNMorphAttributeH
#define IKNMorphAttributeH
//---------------------------------------------------------------------------
#include "KNMacros.h"
//#include "KNMacrosType.h"
//---------------------------------------------------------------------------
/** 
 * @interface IKNMorphAttribute
 * Морфолигический (или лексико-семантический) атрибут.
 */
class IKNMorphAttribute {
public:
	/** Get attribute name. */
	virtual const char* GetName() const = 0;
	/** Название атрибута.
	 * @param oName - name of attribute (length <= NAME_LENGTH)
	 */
	virtual t_errno GetName( char* oName ) const = 0;
	
	/** Get values count */
	virtual unsigned GetValueCount() const = 0;

	/** Get value. */
	virtual const char* GetValue( unsigned iId ) const = 0;
	/** Значение атрибута.
	 * @param oVal - attribute value (length <= NAME_LENGTH)
	 */
	virtual t_errno GetValue( unsigned iId, char* oVal ) const = 0;
};
//---------------------------------------------------------------------------
#endif
