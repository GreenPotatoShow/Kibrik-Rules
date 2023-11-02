// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Usage notes: Декларация базового объекта работающего со статистикой.
// элемент type определяет тип словаря понятия + тип словаря получения 
//===================================================================
//===================================================================
// Использует   :   IKNParadigm
//===================================================================
// Sep 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNWordH
#define IKNWordH
//---------------------------------------------------------------------------
#include "IKNConcept.h"
#include "IKNParadigm.h"
#include "KNMacros.h"
#include "IKNParadigmUpdater.h"
//#include "KNMacrosType.h"
//---------------------------------------------------------------------------
/**
 * @interface IKNWord
 * Объект словаря типа слово. Имеет набор морфолигических атрибутов и
 * парадигму - список окончаний слова.
 */
class IKNWord : virtual public IKNConcept
{
public:
	/** Получить основу слова. */
	virtual t_errno GetStem( char* oStem ) const = 0;
	/** Получить идентификатор морфологического класса слова. */
	virtual byte_t GetMorph() const = 0;
	/** Получить часть речи.
	 *	@note в случае предсказания вставляется знак *
	 */
	virtual t_errno GetPartSpeech( char* oPart ) const = 0;
	/** Получить чистую часть речи (без учета предсказания). */
	virtual const char* GetPartSpeech() const = 0;
	/** Получить список морф. признаков лексемы в виде строки (длина PHRASE_LENGTH). */
	virtual t_errno GetLex( char* oProp ) const = 0;
	/** Взятие количество лексических параметров слова. */
	virtual unsigned GetLexCount() const = 0;
	/** Взятие лексических параметров слова по-элементно.
	 *	@param oAttrName - имя параметра
	 *	@param oAttrValue - значение параметра
	 */
	virtual t_errno GetLexElement( unsigned iIndex, char* oAttrName, char* oAttrValue ) const = 0;
	/** Получить лексический признак.
	 *	@param oValNum - номер значение морфологического атрибута
     *	@return морфологический атрибут (из морфологической таблицы) 
	 */
	virtual IKNMorphAttribute* GetAttr( unsigned iIndex, unsigned* oValNum ) const = 0;
	
	/** Получить указатель на парадигму слова. */
	virtual IKNParadigm* GetParadigm() const = 0;
//-------------------------------------------------------------------
	/** Слить слова, объединить статистику и формы слова (опционально).
	 *	@note this - главное слово, iAddWord - второстепенное, удаляется.
	 *	@note this->IsDel = true, то опреация не проводится, iAddWord удаляется
	 *	@note this->IsStop = true, то статистика и формы объединяются, iAddWord удаляется
	 *	@note статистика топиков не должна изменяться за исключением случая 1
	 */
	virtual t_errno MixWords(IKNWord* iAddWord, bool is_paradigm = false) = 0;
	/** Создание/редактирование парадигмы слова.
	 *	@note создается копия парадигмы (с двумя одновременно работать нельзя),
	 *		затем методом UpdateParadigm старая парадигма удалается, а новая вносится
	 *	@note метод CreateParadigm создает пустую парадигму, ModifyParadigm копирует старую
	 */
	virtual IKNParadigmUpdater* CreateParadigm() const = 0;
	virtual IKNParadigmUpdater* ModifyParadigm() const = 0;
	virtual t_errno UpdateParadigm( IKNParadigmUpdater* ) = 0;

	/**
	 * Edit word.
	 */
//	virtual int KNEditNorm( char* iNormForm );
//	virtual int KNEditWordBase( char* iBase );
//	virtual int KNEditMorphType( char iType );
	
};
//-------------------------------------------------------------------
#endif
