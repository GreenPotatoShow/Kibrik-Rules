// Copyright (c) 2008 by IIS. All rights reserved.
//===================================================================
// Dec 2008                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNMorphTableH
#define IKNMorphTableH
//---------------------------------------------------------------------------
#include "IKNMorphAttribute.h"
#include "IKNMorphType.h"
//---------------------------------------------------------------------------
// надо выделить IKNMorphType + IKNParadigmType

/** 
 * @interface IKNMorphTable
 * Таблица морфолигических классов.
 */
class IKNMorphTable {
public:

	virtual unsigned GetCount() const = 0;
	//virtual IKNMorphType * GetById(uint) const = 0;
	virtual IKNMorphType * GetType(uint) const = 0;

	/** Get atributes count. */
	virtual unsigned GetAttrCount() const = 0;
	/** Get atribute.
	 * @param iIndex - index of morph attribute in list (0-based) 
	 */
	virtual IKNMorphAttribute* GetAttr( unsigned iIndex ) const = 0;
	/** Get part of speech count. */
	virtual unsigned GetPoSCount() const = 0;
	/** Get atribute.
	 * @param iIndex - index of morph attribute in list (0-based) 
	 */
	virtual const char* GetPoS( unsigned iIndex ) const = 0;
	virtual void GetPoS( unsigned iIndex, char* oPoS ) const = 0;
	virtual IKNMorphType* GetByIndex(byte_t imorph) = 0; /**< Получить тип по идентификатору. */


/**
 * Get lexical attributes of active morph type
 * @return code of error
 * @param   iIndex - index of attribute in list (0-based) 
 * @param   oAttrName - name of attribute (length = NAME_LENGTH)
 * @param   oAttrValue - value of attribute (length = NAME_LENGTH)
 */
//virtual int KNGetLexAttr( unsigned iIndex, char* oAttrName, char* oAttrValue ) = 0;

};
//---------------------------------------------------------------------------
#endif
