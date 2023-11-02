// Copyright (c) 2009 by IIS. All rights reserved.
//===================================================================
// July 2009                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNPhraseShellH
#define IKNPhraseShellH
//---------------------------------------------------------------------------
#include "IKNPhrase.h"
#include "IKNWordShell.h"
//-------------------------------------------------------------------
/**
 *	@interface IKNWordShell
 *	фраза словаря, найденная в тексте, со набором атрибутов, характеризующих 
 *	особенности его использования в тексте.
 *	@note 	Набор атрибутов это позиция в тексте, словоформа и 
 *			морф. атрибуты данной словоформы (не лексические)
 */
class IKNPhraseShell
{
public:
	/** Получить главное слово в фразе и ее текстовую оболочку. */
	virtual IKNWordShell* GetMainWord() =0;
	/** Получить словарный словокомплекс (фразу),найденному в тексте. */
	virtual IKNPhrase* GetPhrase() const = 0;

	/** Получить начальный индекс фразы в тексте. */
	virtual uint GetPosId() const = 0;
	virtual uint GetPosEndId() const = 0;
	/** Получить количество фраз в тексте. */
//	virtual uint GetNum() const = 0;

	/** Получить начальную и конечную позицию фразы в тексте. */
	virtual uint GetTextPos( uint* end_pos ) const = 0;
	/** Получить форму фразы в тексте. */
//	virtual char* GetForm() const = 0;
	virtual t_errno GetForm( char* oForm ) const = 0;

	/** Получить количество групп признаком (морфологическая омонимия). */
	virtual IKNWordShell* GetPartShell( unsigned iPartId ) const = 0;
};

#endif
