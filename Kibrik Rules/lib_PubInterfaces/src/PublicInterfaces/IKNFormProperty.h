// Copyright (c) 2010 by IIS. All rights reserved.
//===================================================================
// Usage notes: Свойства формы слова.
//===================================================================
// Используется :   IKNParadigm
//===================================================================
// Dec 2010                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNFormPropertyH
#define IKNFormPropertyH
//---------------------------------------------------------------------------
#include "KNMacros.h"
//#include "KNMacrosType.h"
#include "IKNMorphProperties.h"
//---------------------------------------------------------------------------
/** К свойствам формы слова относится: окончание, приставка 
 *	омонимичные наборы морф.признаков формы.
 */
class IKNFormProperty
{
public:
    /** Получить окончание. */
	virtual const char * GetFlex() const = 0;
    /** Получить приставку. */
	virtual const char *  GetPrefix() const = 0;
    /** Проверить наличие приставки. */
	virtual bool IsPrefix() const = 0;

// Работа с ПРИЗНАКАМИ
    /** Получить количество наборов морф. признаков формы. */
	virtual uint GetGroupCount() = 0;
    /** Получить набор морф. признаков с индексом iIndexGroup, соответствующих
     *	словоформе с окончанием iIndex в виде строки (длина PHRASE_LENGTH).
     */
	virtual t_errno GetGroupAsString( uint iIndexGroup, char* oProp ) = 0;
//	virtual t_errno GetAsString( char* oProp ) = 0;

    /** Получить iIndexGroup-набор морф. признаков у iIndex-окончания */
	virtual IKNMorphProperties* GetGroup( uint iIndexGroup ) = 0;
};

#endif
