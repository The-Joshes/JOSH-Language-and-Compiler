#include "keywords.h"

using namespace std;

namespace jtoken {

  map<string, keyword_map_fp_t> Keyword::keyword_map;

  template <class T>
  Keyword *createKeyword() {
    return new T();
  }

  Keyword *createIf() {return new If(); }

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
    keyword_map["if"] = &createKeyword<If>;
    keyword_map["for"] = &createKeyword<For>;
    keyword_map["while"] = createKeyword<While>;
    keyword_map["do"] = createKeyword<Do>;
    keyword_map["switch"] = createKeyword<Switch>;
    keyword_map["break"] = createKeyword<Break>;
    
    // OO and Polymorphism
    keyword_map["class"] = createKeyword<Class>;
    keyword_map["struct"] = createKeyword<Struct>;
    keyword_map["extends"] = createKeyword<Extends>;
    keyword_map["abstract"] = createKeyword<Abstract>;
    keyword_map["final"] = createKeyword<Final>;
    keyword_map["const"] = createKeyword<Const>;
    
    // Primitive Types
    keyword_map["int"] = createKeyword<Int>;
    keyword_map["char"] = createKeyword<Char>;
    keyword_map["bool"] = createKeyword<Bool>;
    
    return;
  }
}
