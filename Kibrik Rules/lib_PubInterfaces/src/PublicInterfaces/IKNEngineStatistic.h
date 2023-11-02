// Copyright (c) 2014 by IIS. All rights reserved.
//===================================================================
// Usage notes: Набор обработчиков - статистический анализ результата
//    -  подсчет омонимов для слов
//    -  подсчет пересечений для СК
//    -  вычисление топика

// на будущее: перенос остальной статистики
//	- построение таблици частотности для текущего текста
//	- обновление статистики словаря
//	- классификация текста (классическая): несколько вариантов
//	- поиск стоп-терминов ?? (не здесь, т.е. работа не с текстом, а словрем)
//	- поиск кластеризующхся терминов по тексту
//	- объединение статистики нескольких тестов ??
//===================================================================
// Используется : 
//===================================================================
// Использует   :  KNResultList.h
//===================================================================
// May 2014                  Created               L. Sidorova, IIS
//===================================================================
#ifndef IKNEngineStatisticH
#define IKNEngineStatisticH
//-------------------------------------------------------------------
//#include "IKNResultList.h"
//#include "IKNTheme.h"
//-------------------------------------------------------------------
const int UNIVERSAL_WEIGHT = 5;
const uint UNIVERSAL_TOPIC = 1000; // !!! Индекс универсального топика

typedef byte_t t_metod; /**< Metod classification index */
const t_metod UNI_METOD = 0;

//-------------------------------------------------------------------
class IKNTheme;
class IKNResultList;

/** Статистический обработчик данных. */
class IKNEngineStatistic
{
public: // Реализация метода классификации без учета весов.
//	virtual void ClearTopics() = 0;
	/** Установить универсальный топик.
	 *	@note Униврсальный топик не учитывается при расчете и он выставляется 
	 *		  в качестве результата, елси других топиков не найдено.
	 */
	virtual void SetUniversalTopic( IKNTheme* universal_topic ) = 0;
//	virtual bool IsUniversal( IKNConcept* ) = 0;
	/** Вычислить топики для текста и отсортировать по релевантности. */
	virtual uint CalculateTopics( IKNTheme* universal_topic, IKNResultList* res_list ) = 0;

	/** Получить кол-во вычисленных в методе @see CalculateTopics топиков. */
	virtual uint GetTopicCount() const = 0;
	/** Получить топик и оценку его редевантности. */
	virtual IKNTheme* GetTopic( uint id, float* oRel, float* oNorm_rel ) const = 0;
public:
	/** Расчет веса терминов во всем словаре. 
	 *	@note В иерархии топиков могут содержаться несколько классификаторов, а также топикы не
	 *		  относящиеся к тематикам (а, например, семантические признаки).
	 *	@note При расчете вычисляются веса топиков по темам и заносятся в поле.
	 *	@iMetod Индекс метода классификации.
	 *	@iParent Вершина классификатора. Если параемтр равен 0, то используется вся иерархия.
	 */
	virtual void CalculateWeight( t_method_type iMetod, IKNTheme* iParent ) = 0;
	virtual void CalculateWeight( t_method_type iMetod ) = 0;
	virtual void CalculateWeight( const char* iMetodName, IKNTheme* iParent ) = 0;
	virtual void CalculateWeight( const char* iMetodName ) = 0;
};
// --------------------------------------------------------
#endif