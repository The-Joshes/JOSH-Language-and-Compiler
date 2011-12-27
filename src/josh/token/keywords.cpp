#include "keywords.h"

using namespace std;

namespace jtoken {

  map<string, keyword_map_fp_t> Keyword::keyword_map;

  template <class T>
  Keyword *createKeyword() {
    return new T();
  }

  bool Keyword::init = false;
  
  void init_keyword_map(map<string, keyword_map_fp_t>&);
  
  Keyword *Keyword::getKeyword(const string &keyword) {
    if(!init) {
      init_keyword_map(keyword_map);
      init = true;
    }
    
    keyword_map_fp_t keyword_fn  = keyword_map[keyword];
    if (keyword_fn) {
      return keyword_fn();
    }
    return NULL;
  }
  
  void init_keyword_map(map<string, keyword_map_fp_t> &keyword_map) {
    // Control Flow
    keyword_map["if"] = &createKeyword<IfKeyword>;
    keyword_map["for"] = &createKeyword<ForKeyword>;
    keyword_map["while"] = createKeyword<WhileKeyword>;
    keyword_map["do"] = createKeyword<DoKeyword>;
    keyword_map["switch"] = createKeyword<SwitchKeyword>;
    keyword_map["break"] = createKeyword<BreakKeyword>;
    
    // OO and Polymorphism
    keyword_map["class"] = createKeyword<ClassKeyword>;
    keyword_map["struct"] = createKeyword<StructKeyword>;
    keyword_map["extends"] = createKeyword<ExtendsKeyword>;
    keyword_map["abstract"] = createKeyword<AbstractKeyword>;
    keyword_map["final"] = createKeyword<FinalKeyword>;
    keyword_map["const"] = createKeyword<ConstKeyword>;
    
    // Primitive Types
    keyword_map["int"] = createKeyword<IntKeyword>;
    keyword_map["char"] = createKeyword<CharKeyword>;
    keyword_map["bool"] = createKeyword<BoolKeyword>;
    
    return;
  }
}
