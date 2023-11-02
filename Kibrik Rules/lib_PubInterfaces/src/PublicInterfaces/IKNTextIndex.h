// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
//===================================================================
// Nov                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNTextIndexH
#define IKNTextIndexH

//#include "KNMacros.h"
#include "KNMacros.h"
//---------------------------------------------------------------------------
/** 
 * @interface IKNTextIndex
 * Индекс текста (сообщения), создаваемый при его классификации.
 * @note Индекс текста - это тематического профиля.
 *		 По каждой теме можно получить следующие парамтеры:
 *      - проекция близости
 *      - проекция не близости
 *      - усредненная проекция близости
 *      - является ли тема результирующей
 */
class IKNTextIndex
{
public:
	/** Количество профилей. */
	virtual unsigned GetCount() const = 0;
	/** Количество словарных терминов в тексте. */
	virtual unsigned GetTerminCount() const = 0;

	/**
	 * Get element of text profile 
	 * @param   iThemeIndex - index of theme in based list (0-based) 
	 * @param   oFirst - проекция близости (projection of proximity)
	 * @param   oSecond - проекция не близости (projection of non-proximity)
	 * @param   oThird - усредненная проекция близости (averaged projection of proximity)
	 * @param   isResult - является ли тема результирующей
	 */
	virtual t_errno GetProfile( unsigned iThemeIndex, unsigned * oThemeId, float *oFirst, 
				float *oSecond, float *oThird, bool *isResult ) const = 0;
};
//---------------------------------------------------------------------------
#endif
