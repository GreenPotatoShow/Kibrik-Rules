// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Usage notes: Декларация базового объекта работающего со статистикой.
// элемент type определяет тип словаря понятия + тип словаря получения 
//===================================================================
// Используется :   IKNWord, IKNPhrase, KNConcept
//===================================================================
// Использует   :  
//===================================================================
// Sep 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNConceptH
#define IKNConceptH
//---------------------------------------------------------------------------
//#include "KNMacrosVoc.h"
#include "KNMacros.h"
//#include "IKNTheme.h"
#include "IKNConceptParameterGroup.h"
//---------------------------------------------------------------------------
/** Базовый объект для всех элементов словаря (слов, словокомплексов) */
class IKNConcept
{
public:
	/** Название (нормальная форма) понятия.
	 *    @param oNorm is a name of attribute.
	 */
//	virtual t_errno GetNorm( char* oNorm ) = 0;
	virtual const char* GetNorm( ) = 0;

    /** Возвращает класс объекта: CONCEPT_TYPE, WORD_TYPE, PHRASE_TYPE */
	virtual int GetType() const = 0;

    /** Термин добавлен автоматом/экспертом (false/true). */
	virtual bool IsExpert() const = 0;
    /** Термин является обычным/стоп-термином (false/true). */
	virtual bool IsStop() const = 0;
    /** Термин является прозрачным/удаленным (false/true). */
	virtual bool IsDelete() const = 0;
    /** Термин имя нарицательное/имя собственное (false/true). */
//	virtual bool IsName() const = 0;
    /** Омонимия отсутствует/есть (false/true). */
	virtual bool IsSameExist() const = 0;
    /** Термин не изменился/изменился (false/true). */
	virtual bool IsEdit() const = 0;
    /** Термин старый/новый (false/true). */
	virtual bool IsNew() const = 0;
    /** Термин неизменяемый/изменяемый (false/true). */
	virtual bool IsFix() const = 0;
    /** Термин предсказание да/нет. */
	virtual bool IsPrediction() const = 0;

    /** Снять статус обновления. */
	virtual void SetTypical() = 0;
//-------------------------------------------------------------------
	/** Взять встречаемость термина. */
	virtual uint GetCount() const = 0;
	/** Взять кол-во текстов, в которым встретился термин. */
	virtual uint GetTextCount() const = 0;
	/** Частота термина. */	                               	
	virtual float GetTF() const = 0;
	/** Текстовая частота термина. Отношение кол-ва документов, в которых
	 *	встретился термин к общему кол-ву обработанных документов.
	 */
	virtual float GetDF() const = 0;
	/** Обратная текстовая частота термина. **/
	virtual float GetIDF() const = 0;
	virtual float GetTF_IDF() const = 0;
	/** Взять усредненную частоту термина (средняя по всем темам). */
	virtual float GetFrequency() const = 0;
//-------------------------------------------------------------------
    /** Установить экспертную норму соответствия теме.
     *  @param iExpertNorm - экспертная норма, выраженная в процентах (%).
     *  @param iTheme_id - индекс темы
     *  @param iThemeName - имя темы
     */
	virtual t_errno SetExpertNorm( char* iThemeName, int iExpertNorm ) = 0;
	virtual t_errno SetExpertNormById( uint iTheme_id, int iExpertNorm ) = 0;

	/** Добавить параметр. */
	virtual IKNConceptParameter* AddParameter( IKNTheme* iT, int iExpertNorm = 1 ) = 0;
//	virtual IKNConceptParameter* AddParameter( uint iTheme_id, int iExpertNorm = 1 ) = 0;
	
	/** Удалить статистику по теме, по ее имени. */
	virtual void DeleteThemeStatistic( char* iThemeName ) = 0;
	/** Удалить статистику по теме, по ее индексу. */
	virtual void DeleteThemeStatisticById( uint iTheme_id ) = 0;

	/** Удалить статистику по теме с индексом iid. */
//	virtual void DeleteT( unsigned iid ) = 0;
	/** Изменить стоп-статус термина (на противоположный). */
	virtual t_errno Transfer() = 0;
//-------------------------------------------------------------------

	/** Установить итератор по статистикам на начало.
	 *	@return кол-во тем, в которым встретился термин (кол-во статистик).
	 */
	virtual uint InitStatistic() const = 0;

	/** Взять параметр термина и его статистику.
	 *	Необходимо использовать функцию InitStatistic(),
	 *	которая установит итератор на начало списка статистик данного объекта.
	 *
	 *    @param oTheme_id is a index of theme.
	 *    @param oCount is a count of term in theme.
	 *    @param oTextCount is a count of text of theme.
	 *    @param oExpertNorm is a expert norm.
	 */
	 /// {
//	virtual t_errno GetStatistic( uint* oTheme_id, uint* oCount,
//				uint* oTextCount, int* oExpertNorm ) = 0;
	virtual IKNConceptParameter* GetStatistic() const = 0;
	/** Установить семантичексое значение параметра для данного термина.
	 *	@note не применяется для тематических параметров THEME_TYPE_STAT и THEME_TYPE_STAT_HEAD
	 */
	virtual void SetParameterValue(IKNConceptParameter* iPar, const char* iVal) = 0;

	/** Создать новую группу. */
	virtual IKNConceptParameterGroup* CreateGroup(IKNConceptParameter* iElem) = 0;
	/** Взять количество групп. */
	virtual uint GetCountGroup() const = 0;
	/** Взять группу по индексу. */
	virtual IKNConceptParameterGroup* GetGroup(uint i) = 0;
	/** Удалить группу. */
	virtual void DeleteGroup(uint i) = 0;
	/** Проверка, входит ли элемент в какую-либо группу. 
	 *	@note елемент может входить в несколько групп
	 *	@note группа может состоять из одного элемента 
	 *		  (осмысленно, когда есть еще группа содержащая этот элемент с каким-либо другим)
	 */
	virtual bool InGroup(IKNConceptParameter* iElem) const = 0;

	
	virtual t_errno GetShortStatistic( uint* oTheme_id ) const = 0;
	/** Взять дополнительную статистику термина по одному параметру.
	 *	Необходимо использовать функцию InitStatistic().
	 *    @param oDirectNorm вес термина в теме.
	 *    @param oRelativeNorm относительная частота термина в теме.
	 */
//	virtual t_errno GetFullStatistic( char* oThemeName, uint* oCount, uint* oTextCount,
//				int* oExpertNorm, float* oDirectNorm, float* oRelativeNorm ) = 0;
	virtual IKNConceptParameter* GetFullStatistic( float* oDirectNorm, float* oRelativeNorm ) const = 0;
	 /// }
	
	/** Найти статистику по теме.
	 *	Чтобы взять остальные параметры достаточно (после того как тема найдена)
	 *	вызвать далее GetStatistic, GetFullStatistic или GetTStatistic
	 *    @param oTheme_id is a index of theme.
	 *    @param oExpertNorm is a expert norm.
	 */
	 /// {
//	virtual bool FindTStatistic( uint iTheme_id ) = 0;
	virtual IKNConceptParameter* FindTStatistic( uint iTheme_id ) const = 0;
//	virtual bool FindThemeStatistic( char* oThemeName ) = 0;
	virtual IKNConceptParameter* FindThemeStatistic( char* iThemeName ) const = 0;
//	virtual t_errno GetTStatistic( IKNTheme* iTheme, uint* oCount, uint* oTextCount,
//				int* oExpertNorm, float* oDirectNorm, float* oRelativeNorm ) = 0;
	virtual IKNConceptParameter* GetTStatistic( IKNTheme* iTheme, float* oDirectNorm, float* oRelativeNorm ) const = 0;
	/// }

	/// { Проверяет наличие темы или ее наследников/родителей у термина
	/** Найти статистику по индексу темы. Включая наследников темы с индексом iTheme_id. */
	virtual bool FindTStatChild( uint iTheme_id ) const = 0;
	/** Найти статистику по индексу темы. Включая родителей темы с индексом iTheme_id. */
	virtual bool FindTStatParent( uint iTheme_id ) const = 0;
	 /// }

	/** Очистка статистики обучения. */
	virtual void ClearStatisticClassify() =0;

	/**
	 * Get count of addition statistics of active concept
	 * @return count of plus statistics
	 * 		- 1 if error
	 */
//	virtual int GetCountPlusStatistics(); //FindActiveThemesPlus

	/**
	 * Get addition concept statistics, corresponding i-theme
	 * @return code of error
	 */
/*	virtual int GetPlusStatistics( unsigned iThemeIndex, char* oThemeName,
                    int* oCountTextsWithWord, int* oCountWordsInTheme,
                    int* oExpertNorm, float* oDirectNorm, float* oRelativeNorm );
//*/
//-------------------------------------------------------------------
};

#endif
