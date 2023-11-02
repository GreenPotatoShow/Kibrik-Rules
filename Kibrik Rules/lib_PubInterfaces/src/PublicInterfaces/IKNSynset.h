/*
 * IKNSynset.h
 *
 *  Created on: 08.12.2013
 *      Author: stepan
 */

#ifndef IKNSYNSET_H_
#define IKNSYNSET_H_

// std:
#include <set>
#include <vector>

// klan:
#include "IKNConcept.h"
#include "IKNPhrase.h"
#include "IKNTheme.h"



/// predicate defined on the set of themes
/*
 * Predicate behavior is defined by a list of explicitly included themes and
 * a list of explicitly excluded themes. Uses the most specific parent theme
 * from the lists to decide wether condition is satisfied or not.
 */
class IKNThemeCondition {
public:
  /// add theme to inclusion list
  virtual void includeTheme(IKNTheme* t) = 0;
  /// add theme to exclusion list
  virtual void excludeTheme(IKNTheme* t) = 0;
  /// remove theme from all lists
  virtual void unmarkTheme(IKNTheme* t) = 0;
  /// get basic set of themes where condition is satisfied
  virtual const std::set<IKNTheme*>& includedThemes(void) const = 0;
  /// get basic set of themes where condition is unsatisfied
  virtual const std::set<IKNTheme*>& excludedThemes(void) const = 0;
  /// get default result
  virtual bool getDefault(void) const = 0;
  /// set default result
  virtual void setDefault(bool) = 0;
  /// check condition for the given theme
  /**
   * For given theme t predicate searches for the most specific theme
   * t_min that is a parent of t orequals to t. If t_min is from
   * inclusion list, then condition is satisfied; else if t_min is
   * from exclusion list, then condition is not satisfied. If no such
   * t_min is found, then default truth value is returned. */
  virtual bool check(IKNTheme* t) const = 0;
  /// check condition for the given theme
  virtual bool operator () (IKNTheme* t) const = 0;
};


/// group of synonymes
/**
 * synset is defined by its
 *  -# descriptor (most distinctive representative)
 *  -# full list of members (including descriptor)
 *  -# condition on themes (determins which themes\n
 *     synset is relevant to)
 */
class IKNSynset {
public:
  /// get synset descriptor
  virtual IKNConcept* getDescr(void) = 0;
  /// set synset descriptor
  virtual void setDescr(IKNConcept* c) = 0;
  /// add new term to synonyme group
  virtual void add(IKNConcept* c) = 0;
  /// remove word from synonyme group
  /**
   * @note Descriptor cannot be removed. It can only be substituted. \n
   *       I.e. descriptor removal is considered to be equivalent to \n
   *       the synset deletion.
   */
  virtual void remove(IKNConcept* c) = 0;
  /// list all members of synonymes group
  virtual const std::vector<IKNConcept*>& getMembers(void) const = 0;
  /// check if given term is element of synset
  virtual bool contains(IKNConcept* c) const = 0;
  /// get condition on themes
  /**
   * @return mutable condition on themes
   */
  virtual IKNThemeCondition* getCondition(void) = 0;
  /// check if group is applicable on given theme
  virtual bool check(IKNTheme* t) const = 0;
  /// check if term is a member of the synset
  /// and given theme satisfies condition
  virtual bool check(IKNConcept* c, IKNTheme* t) = 0;
  /// check if terms are members of the synset
  /// and given theme satisfies condition
  virtual bool check(IKNConcept* c1, IKNConcept* c2, IKNTheme* t) = 0;
};

#endif /* IKNSYNSET_H_ */
