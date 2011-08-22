#include "keywords.h"

using namespace std;

Keyword::init = false;

template <typename T>
T *create<T>() {
  return new T();
}

void init_keyword_map(map<string, (Keyword*)()>&);
		      
Keyword *Keyword::getKeyword(const string &keyword) {
  if(!init) {
    init_keyword_map(keyword_map);
    init = true;
  }

  (Keyword*)() keyword = keyword_map[keyword];
  return keyword ? keyword() : NULL;
}

void init_keyword_map(map<string, (Keyword*)()> &keyword_map) {
  // Control Flow
  keyword_map["if"] = create<If>;
  keyword_map["for"] = create<For>;
  keyword_map["while"] = create<While>;
  keyword_map["do"] = create<Do>;
  keyword_map["switch"] = create<Switch>;
  keyword_map["break"] = create<Break>;

  // OO and Polymorphism
  keyword_map["class"] = create<Class>;
  keyword_map["struct"] = create<Struct>;
  keyword_map["extends"] = create<Extends>;
  keyword_map["abstract"] = create<Abstract>;
  keyword_map["final"] = create<Final>;
  keyword_map["const"] = create<Const>;

  // Primitive Types
  keyword_map["int"] = create<Int>;
  keyword_map["char"] = create<Char>;
  keyword_map["bool"] = create<Bool>;

  return;
}
