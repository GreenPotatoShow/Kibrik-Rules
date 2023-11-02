// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNWordShellH
#define IKNWordShellH
//---------------------------------------------------------------------------
#include "IKNMorphProperties.h"
#include "IKNWord.h"
//-------------------------------------------------------------------
/**
 *	@interface IKNWordShell
 *	Слово словаря, найденное в тексте, с набором атрибутов, характеризующих 
 *	особенности его использования в тексте.
 *	@note 	Набор атрибутов это позиция в тексте, словоформа и 
 *			морф. атрибуты данной словоформы (не лексические)
 */
class IKNWordShell
{
public:
	/** Получить словарный термин, соответствующий слову, найденному в тексте. */
	virtual IKNWord* GetWord() const = 0;
	/** Получить индекс слова в тексте. */
	virtual uint GetPosId() const = 0;
	/** Получить позицию слова в тексте. */
	virtual uint GetTextPos( uint* end_pos ) const = 0;

	virtual const char* GetForm() const = 0;

	/** Получить морфологические параметры слова, найденного в тексте.
	 *	@note Параметры выдаются одной строкой в формате внешнего обработчика.
	 *	@note Длина строки определяется PHRASE_LENGTH
	 */
//	virtual t_errno PropertyEFormat( char* oProperty ) = 0;

	/** Получить морфологические параметры слова, найденного в тексте.
	 *	@note Параметры выдаются одной строкой в формате внешнего обработчика.
	 *	@note Длина строки определяется PHRASE_LENGTH
	 */
//	virtual char* PropertyEFormat() = 0;

	/** Получить морфологические параметры слова, найденного в тексте.
	 *	@note Параметры выдаются одной строкой во внутреннем формате.
	 */
	virtual t_errno GetPropertyAsString( char* oProperty ) = 0;

	/** Получить количество групп признаком (морфологическая омонимия). */
	virtual uint GetPropertyGroupCount() = 0;

	/** Получить группу признаков. */
	virtual IKNMorphProperties* GetPropertyGroup( uint iGroupIndex ) = 0;
};

#endif
