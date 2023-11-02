/*
 * MorphAnalyzer.h
 *
 *  Created on: 14.11.2013
 *      Author: stepan
 */

#ifndef MORPHANALYZER_H_
#define MORPHANALYZER_H_


// std:
#include <vector>

// klan:
#include <IKNWordVoc.h>
#include <IKNWord.h>


namespace klan {
  using std::vector;


  /// Possible lexeme and morph. attributes' values
  /// of the processed word-form.
  struct Hypothesis {

    /// Lexeme the word-form belongs to.
    IKNWord* lexeme;

    /// Index of word-form flexion in lexeme's paradigm
    /// (thus values of morph. attrs are also known).
    unsigned int flex_index;
  };




  /// Result of single word processing
  class ProcessedWord {
  private:
    bool predicted;
    vector<Hypothesis> hypothesis;

  public:
    /// @return true iff the processed word is not in the vocabulary
    bool isPrediction(void);

    /// @return all possible lexemes+morhp.tags of the processed word
    vector<Hypothesis> getHypthesis(void) = 0;
  };




  /// IMorphAnalyzer is an interface for word-by-word morphological parser
  class IMorphAnalyzer {
  public:
    /**
     * @param word null-terminated string to be processed
     * @return possible morph. parsings of the word
     */
    ProcessedWord processWord(const char* word) = 0;

    /**
     * @param begin pointer to the first charater of the word to be processed
     * @param end pointer to the last character+1 of the word
     * @return possible morph. parsings of the word
     */
    ProcessedWord processWord(const char* begin, const char* end) = 0;
    ~IMorphAnalyzer(void) {}
  };




  /**
   * @brief Abstract factory for MorphAnalyzers.
   * Hide the actual class of provided morph. analyzer.
   */
  class IMorphAnalyzerFactory {
  public:
    /**
     * @brief Create new instance of MorphAnalyzer
     * Creates new instance of MorphAnalyzer and pass the ownership
     * of this instance to the caller. Since MorphAnalyzer need to
     * know which lexemes are known for the particular vocabulary,
     * corresponding vocabularies (domain-specific and universal
     * lexicons) must be provided regardless particular algorithm
     * applied by analyzer.
     *
     * @param voc domain-specific lexicon
     * @param uni_voc general-purpose lexicon
     * @return new instance of MorphAnalyzer
     */
    MorphAnalyzer* createMorphAnalyzer(IKNWordVoc* voc, IKNWordVoc* uni_voc) = 0;
    ~IMorphAnalyzerFactory(void) {}
  };

} // namespace klan



#endif /* MORPHANALYZER_H_ */
