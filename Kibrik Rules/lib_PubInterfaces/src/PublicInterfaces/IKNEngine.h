// Copyright (c) 2004 by RRIAI. All rights reserved.
//===================================================================
// Nov 2005                  Created               L. Sidorova, RRIAI
//===================================================================
#ifndef IKNEngineH
#define IKNEngineH
//-------------------------------------------------------------------
#include "KNMacros.h"
#include "IKNTextIndex.h"
#include "IKNResultList.h"
#include "IKNParsedText.h"
//-------------------------------------------------------------------
class IKNEngineStatistic;
/**
 * @interface IKNEngine
 * Управляющий модуль обучением и классификацией текстов.
 *
 * @note Модуль при работе взаимодействует с внешними обработчиками
 * a. работа с WordFinder dll
 * b. автоматическое наполнение словаря по тексту
 * c. автоматическая классификация текста
 * d. поиск стоп-терминов и стоп-словокомплексов
 * 
 * Настройки WFEngine (WF_C.dll):
 *		- предсказания (да/нет)
 *		- поиск конструкций Алексом (да/нет, путь до словаря)
 *		- сборка СК (да/нет)
 *
 * Настройки TomatEngine (TomatAPI.dll):
 *		- сборка СК (да/нет)
 *		- путь до папки словарей (банки проекта)
 *		- имя системного банка
 *		- имя пользовательского словаря
 *
 * Режим обработки текста:
 *	0 - наполнение словаря + ведение статистики
 *	1 - наполнение словаря
 *	2 - обновление статистики
 *	3 -	морфологический анализ
 *	4 -	классификация 
 *	5 -	классификация + ведение статистики в словаре
 *
 * Для обучения (ведения статистики по темам) необходимо предварительно 
 * установить активные темы IKNThemeList::SetTextTheme (AddTextTheme)
 *
 * Для классификации можно установить пороговые характеристики:
 *      - порог необходимости (необходимое условия для отнесения к теме)
 *      - порог достаточности (достаточное условия для отнесения к теме)
 *
 * По умолчанию все парамтеры заданы в KNMacros.h
 */
class IKNEngine
{
public:
	virtual IKNParsedText* GetParsedText() const = 0;
	virtual IKNEngineStatistic* GetEngineStatistic() = 0;

	/**
	 * Run morpho-analyze of text.
     * @note Длина текста ограничена костантой TEXT_LENGTH.
	 * @param len - возвращаемый параметр, указывает длину обработанного текста
	 *		  len = 0 - обработан весь текст 
	 * @param  iMode - mode of text analisys
	 *		   iMode = 0 - learning (add new termins to vocabulary)
	 *		   iMode = 1 - learning without statistic (add new termins to vocabulary)
	 *		   iMode = 2 - relearning with statistic (only termin in vocabulary)
	 *		   iMode = 3 - morphological analysis
	 *		   iMode = 4 - classificaion text
	 *		   iMode = 5 - classificaion with statistic update (only termin in vocabulary)
	 *		   iMode = 6 - classification by expert rule (topic find)
	 *		   iMode = 7 - statistic analysis
	 */
	virtual t_errno Run( char* text, int iMode, uint* len  ) = 0;

	/**
	 * Find and transfer all stop concept.
	 * Поиск стоп-терминов и перенос в стоп-словарь.
     * @note Механизм: если термин по встречается по всем темам и вес термина,
     * 		 приблизительно соответствует шумовому уровню - 1, то это стоп-термин.
     * 		 Степень приблизительности задает PROXIMITY, вес должен лежать в интервале 
     * 		 значений (1/PROXIMITY, PROXIMITY).
     * Ограничения:
     * 		- тема должна быть достаточно наполнена - THEME_THRESHOLD
     * 		- встречаемость термина в выборке - не менее TERM_THRESHOLD
     * !! Механизм на данный момент устарел, т.к. не учитывается иерархия тем !!
     * !! Для СК-ов нужно другое ограничение !!
	 * @return count of new stop concept
	 *   -1 -- if error
	 */
	virtual int FindStopConcepts() = 0;

	/** Получить доступ к индексу документов. */
	virtual IKNTextIndex* GetTextIndex() const = 0;

	/** Получить доступ к списку полученных в результате анализа объектов. */
	virtual IKNResultList* GetResultList() const = 0;

	virtual void Clear() = 0;	/**< Очистка результатов предыдущей работы. */
//	virtual void Close() = 0;	/**< Выгрузить дополнительные модули (и удалить сам engine). */

	/** Установить пороги для классификации.
	 * @param   iNecessity - threshold of Necessity
	 * @param   iSufficiency - threshold of sufficiency
	 */
	virtual void SetThreshold(unsigned iNecessity, unsigned iSufficiency) = 0;
	/** Установить пороги для поиска стоп-терминов. */
	virtual void SetStopThreshold( float iMin, float iMax ) = 0;

	/** Установить настройки модуля сборки СК WF (WF_C.dll)
	 * @param isPredict - использовать предсказания (да/нет)
	 * @param isWFPhrase - осуществлять сборку СК модулем WF (да/нет)
	 * @param iVocPath - путь до словаря Алекс
	 *		  iVocPath=0 - если Алекс не требуется
	 */
	virtual void SetWFParametrs(bool isPredict, bool isWFPhrase, char* iVocPath = 0) = 0;

	/** Создание слова по норме и классу и добавление в базовый словарь.
	  * Осуществляется предварительный поиск в словарях.
      *		- Если слово найдено в del словаре, оно переносится в базовый.
	  * Используются настройки обработчика (предсказания).
	  * @return новое или найденное слово.
	  */
	virtual IKNWord* CreateWord( char* iNorm, byte_t iMorh ) = 0;
	/** Создание слова по названию (и всех омонимов).
	  * Осуществляется предварительный поиск в словарях, при этом
      *	считается, что если найден хотя бы омоним, то остальные уже присутствуют.
	  * Используются настройки обработчика (предсказания).
	  * @return первое слово (остальные можно взять).
	  */
	virtual IKNWord* CreateWords( char* iNorm ) = 0;
	/**
	 * Сформировать описание СК-а из текстового представления состава.
	 * @param p - СК с заданной нормальной формой
	 * @param part_count - кол-во составляющих 
	 * @param text - состав в нормальной форме (разделитель - пробел)
	 * @return количество сформированных СК (0 - если не удается создать СК)
	 */
	virtual int CreatePhraseParts( IKNPhrase* p, unsigned part_count, char* text ) = 0;

	/** Конвертировать позиционную разбивку текста для корректного отображения.
	 * @param is_bit_para = true абзац представлен 1 символом
	 * 		  is_bit_para = false абзац представлен 2 символами
	 */
	virtual void ConvertTextType( bool is_bit_para ) = 0;

	/* По текстовой позиции получить индекс в списке парсера(бинарный поиск). */
//	uint GetPositionIndex( uint text_pos) const;
	/* По индексу получить текстовую позицию (на начало и конец мин.элемента в тексте). */
//	uint GetTextIndex( uint id_pos, uint* oEndText ) const;
};
// --------------------------------------------------------
#endif
