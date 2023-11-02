// Copyright (c) 2010 by IIS. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, IIS
// Feb 2010                  Edited                M. Zagorulko, IIS
//===================================================================
#ifndef IKNMorphTypeH
#define IKNMorphTypeH
//---------------------------------------------------------------------------
#include "IKNMorphAttribute.h"
//---------------------------------------------------------------------------
/** 
 * @interface IKNMorphType
 * Морфолигический тип.
 */
class IKNMorphType {
public:
	/** Get morphology type (class) identificator.	 */
	virtual byte_t GetIdent() const = 0;
	/** Get lexical attributes descriptor (user one-string comment). */
	virtual bool GetLexDesc( char* oLex ) const = 0;

	/**
	 * Get part of speech.
	 * @param oPS - part of speech (length = PART_SPEECH_LENGTH)
	 */
	//virtual void GetPS( char* oPS ) const = 0;
	virtual const char* GetPS() const = 0;
	
	/**
	 * Get type descriptor.
	 * @param  oDescr - descriptor of type (length = NAME_LENGTH)
	 */
//	virtual void GetDescr( char* oDescr ) const = 0;
	virtual const char* GetDescr() const = 0;
	
	/** Get parent morphology type (class).	 */
	virtual IKNMorphType* GetParentType() const = 0;
	
	/** Get count of lexical attributes. */
	virtual unsigned GetLexCount() const = 0;
	
	/**
	 * Взятие морфологического признака. 
	 * @param iIndex - index of property in list (0-based) 
	 * @param oAttrName - имя морфологического атрибута (length = NAME_LENGTH)
	 * @param oAttrValue - значение морфологического атрибута (length = NAME_LENGTH)
	 */
	virtual t_errno GetLexProperty( unsigned iIndex, char* oAttrName, char* oAttrValue ) const = 0;
	virtual IKNMorphAttribute* GetLexProperty( unsigned iIndex, unsigned* oValNum ) const = 0;


	/** Get paradigm type */
//virtual IKNParadigmType* GetParadigmType() const = 0;

	// -----------  Edit functions ---------------
//virtual int KNEditMorphTypeDescr( char* iMorphTypeName ) = 0;
//virtual int KNEditMorphTypePS( char* iMorphPS ) = 0;
//virtual int KNEditMorphTypeParent( byte_t iParentIdent ) = 0;
/**
 * Add/delete lexical attribute of morph type
 * @return code of error
 * @param   oAttrName - name of attribute (length = NAME_LENGTH)
 * @param   oAttrValue - value of attribute (length = NAME_LENGTH)
 */
//virtual int KNAddLexAttr( char* iAttrName, char* iAttrValue ) = 0;
//virtual int KNDeleteLexAttr( char* iAttrName ) = 0;

};
//---------------------------------------------------------------------------
#endif
