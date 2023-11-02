// Copyright (c) 2010 by IIS. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNManagerH
#define IKNManagerH
//---------------------------------------------------------------------------
#include "IKNWordVoc.h"
#include "IKNPhraseVoc.h"
#include "IKNMorphTable.h"
#include "IKNThemeList.h"
#include "IKNResultList.h"
#include "IKNTextIndex.h"
#include "IKNEngine.h"
#include "IKNSynRelation.h"
//---------------------------------------------------------------------------
/**
 * @mainpage
 * <HR>
 * @section intro ОБЩИЕ КОММЕНТАРИИ К МЕТОДАМ API
 * - При успешном завершении все методы API, возвращающие код ошибки.
 * - При неуспешном завершении все методы API, возвращающие указатель, возвращают 0.
 * - Все индексы начинаются с нуля.
 * - Интерфейсам API нельзя делать delete.
 * - Главный интерфейс IKNManager удаляется методом Release(), остальные интерфейсы не удаляются.
 */

/** 
 * @interface IKNManager
 * Менеджер вызова основных функциональных классов API.
 * Создается с помощью единственной глобальной функции DLL-библиотеки GenerateAPIManager().
 */
class IKNManager {
public:
	/** UnInitialize. Close Vocabulary. */
	virtual void Release() = 0;

	/** Создать новый проект.
	 *	@note По умолчанию загружается классичсекая морф. таблица и
	 *	создаются 11 тем общей тематики
	 * !! EDIT: По умолчанию создается пустая иерархия
	 */
	virtual t_errno Create( bool is_themes_create = false ) = 0;
    /** Очистка словарей, таблиц и пр. */
	virtual t_errno Clear() = 0;
    /** Очистка del-словарей. */
	virtual void ClearDel() = 0;

	/** Установить путь и имя файла проекта. */
	virtual t_errno SetPath(const char* iFileName) = 0;
	/** Load Vocabulary. */
	virtual t_errno Load() = 0;
	/** Save Vocabulary. */
	virtual t_errno Save() = 0;
	/** Объединение словарей.
	 * @note Темы идентифицируются по названию, новые добавляются.
	 * 		 Морфологические таблицы должны совпадать (вплоть до индексов)
	 *		 или быть не противоречивыми.
	 */
	virtual t_errno JoinVoc(const char* iFile/*, byte_t iMode*/) = 0;

	/** Save Vocabulary as Text. */
	virtual t_errno SaveAsText(const char* iFileName) = 0;
	/** Load Vocabulary from Text.
	 * @note format as function SaveAsText.
	 * @note допустимо удаление слов из словарей вручную из текстового файла (например, del слова)
	 */
	virtual t_errno LoadFromText(const char* iFileName) = 0;

	/** Save morphology table and morph rules for Lemmatizer. */
// В IKNMorphTable (когда будет реализовано).
	virtual t_errno SaveMorphTables(const char* iMorphFile, const char* iRulesFile) = 0;

	/**
	 * Cохранение иерархии тем в файл, указанный пользователем.
	 * @note Сохраение независимо от словаря.
	 * @param iName - имя файла (расширением задает пользователь)
	 */
	virtual t_errno SaveThemes( const char* iFileName ) const = 0;

	/**
	 * Загрузка иерархии тем из файла и замена текущей иерархии словаря.
	 * @note Осуществляется проверка совместимости новой иерархии
	 * 		 со словарем в указанном пользователем режиме iMode.
	 * 		 При несовместимости иерархия тем останется старой.
	 *
	 * @param iName - имя файла (расширением задает пользователь)
	 * @param iMode - режим замены иерархии
	 *		iMode = false - Темы идентифицируются по id + названию
	 *		iMode = true - Темы идентифицируются по id, названия заменяются
	 */
	virtual t_errno LoadThemes(const char* iFileName, bool iMode) = 0;

	/**
	 * Check Vocabulary empty
	 * @return true - if vocabulary empty / false - else
	 */
	virtual bool IsEmpty() const = 0;

//===================================================================
	/** Получить доступ к словарю.
	 *	@param voc_type - тип словаря
	 */
//    virtual IConceptVec* GetConceptVoc( int voc_type ) const = 0;
	/** Получить доступ к словарю слов по его типу.
	 *	@param voc_type - тип словаря
	 */
	virtual IKNWordVoc* GetWordVoc( int voc_type ) const = 0;
	/** Получить доступ к словарю словокомплексов (СК) по его типу.
	 *	@param voc_type - тип словаря
	 */
	virtual IKNPhraseVoc* GetPhraseVoc( int voc_type ) const = 0;

	/// get synonymy relation between vocabulary terms
	virtual IKNSynRelation* GetSynonymy(void) = 0;


	/** Получить доступ к таблице морфологических классов. */
	virtual IKNMorphTable* GetMorphTable()  const = 0;

	/** Получить доступ к иерархии тем. */
	virtual IKNThemeList* GetThemesTable() const = 0;

	/** Получить доступ к модулю обучения и классификации. */
	virtual IKNEngine* GetEngine()  const = 0;

//===================================================================
//*********************** SPESHIAL FUNCTIONS ************************
//===================================================================
	/** Изменение статуса всех новых/обновленных словарных терминов на обычный. */
	virtual void ClearNews() = 0;

	/** Раскрытие категориальных терминов на подкатегории. */
	virtual void TransformCategoryTerms() = 0;

	/** Очистка статистики обучения. */
	virtual void ClearStatisticClassify() =0;
	
	/** Инициализация списка СК, содержащих слово w. */
	virtual IKNPhrase* InitRelation( IKNWord* w ) = 0;
	/** Взятие следующего элемента из списка СК. */
	virtual IKNPhrase* GetRelation() = 0;

//===================================================================
//************************* VALUES TABLE ****************************
//===================================================================
	/** Get Rules count	 */
	virtual uint GetRulesCount() const = 0; 

	/** Get rule name. Максимальная длина строки NAME_LENGTH. */
	virtual t_errno GetRule(unsigned iIndex, char* oRule) const = 0; 
	virtual const char* GetRule(unsigned iIndex) const = 0; 

	/** Get Part of Speech count */
	virtual uint GetPSCount() const = 0; 

	/** Get Part of Speech. Максимальная длина строки PART_SPEECH_LENGTH. */
	virtual t_errno GetPS(unsigned iIndex, char* oPS) const = 0; 
	virtual const char* GetPS(unsigned iIndex) const = 0; 

};
//---------------------------------------------------------------------------
#endif

