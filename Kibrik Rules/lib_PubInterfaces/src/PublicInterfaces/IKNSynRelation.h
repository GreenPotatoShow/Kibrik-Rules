/*
 * IKNSynRelation.h
 *
 *  Created on: 08.12.2013
 *      Author: stepan
 */

#ifndef IKNSYNRELATION_H_
#define IKNSYNRELATION_H_

// std:
#include <vector>

// klan:
#include "IKNSynset.h"

/// synonymy relation between words
/**
 * synonymy relation defined terms of synonymy groups (IKNSynset)
 */
class IKNSynRelation {
public:
  /// check if two concepts are synonymes in given theme
  virtual bool areSynonymes(IKNConcept* a, IKNConcept* b, IKNTheme* t) = 0;
  /// list all terms that are synonymes of term c in given theme
  virtual std::vector<IKNConcept*> getSynonymes(IKNConcept* c, IKNTheme* t) = 0;
  /// list all posible synymes in all possible themes
  virtual std::vector<IKNConcept*> listAllSynonymes(IKNConcept* c) = 0;
  /// get all synsets that given concept belongs to
  virtual std::vector<IKNSynset*> getSynsets(IKNConcept* c) = 0;
  /// get all existing synsets
  virtual const std::vector<IKNSynset*>& getAllSynsets(void) const = 0;
  /**
   * @name Factory methods
   * creation/deletion of synsets
   * @note deletion of descriptor will couse deletion of corresponding synset, while\n
   * deletion of non-descriptor word will couse removing it from all its synsets
   */
  /// @{
  virtual IKNSynset* createSynset(IKNConcept* descr) = 0;
  virtual void deleteSynset(IKNSynset* synset) = 0;
  /// @}
};


#endif /* IKNSYNRELATION_H_ */
