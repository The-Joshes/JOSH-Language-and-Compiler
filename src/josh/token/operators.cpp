#include "operators.h"

using namespace std;

namespace jtoken {

  map<char, operator_fp_t> Operator::single_operator_map;
  map<string, operator_fp_t> Operator::double_operator_map;

  template <class T>
  Operator *createOperator() {
    return new T();
  }

  bool Operator::single_init = false;
  bool Operator::double_init = false;
  
  void init_single_operator_map(map<char, operator_fp_t>&);
  void init_double_operator_map(map<string, operator_fp_t>&);
    
  Operator *Operator::getSingleOperator(char opchar) {
    if(!single_init) {
      init_single_operator_map(single_operator_map);
      single_init = true;
    }
    
    operator_fp_t operator_fn  = single_operator_map[opchar];
    if (operator_fn) {
      return operator_fn();
    }
    return NULL;
  }
  
  Operator *Operator::getDoubleOperator(const string &opstring) {
    if(!double_init) {
      init_double_operator_map(double_operator_map);
      double_init = true;
    }
    
    operator_fp_t operator_fn  = double_operator_map[opstring];
    if (operator_fn) {
      return operator_fn();
    }
    return NULL;
  }
  
  void init_single_operator_map(map<char, operator_fp_t> &single_operator_map) {
    single_operator_map['+'] = &createOperator<PlusOperator>;
    single_operator_map['-'] = &createOperator<SubtractOperator>;
    single_operator_map['*'] = &createOperator<StarOperator>;
    single_operator_map['/'] = &createOperator<SlashOperator>;
    single_operator_map['='] = &createOperator<AssignOperator>;
    single_operator_map['<'] = &createOperator<LessOperator>;
    single_operator_map['>'] = &createOperator<GreaterOperator>;
    single_operator_map['&'] = &createOperator<AmpersandOperator>;
    single_operator_map['^'] = &createOperator<CaratOperator>;
    single_operator_map['%'] = &createOperator<PercentOperator>;
    single_operator_map['$'] = &createOperator<DollarOperator>;
    single_operator_map['#'] = &createOperator<PoundOperator>;
    single_operator_map['@'] = &createOperator<AtOperator>;
    single_operator_map['!'] = &createOperator<BangOperator>;
    single_operator_map['|'] = &createOperator<BarOperator>;
    single_operator_map[';'] = &createOperator<SemicolonOperator>;
    single_operator_map[':'] = &createOperator<ColonOperator>;
    single_operator_map['.'] = &createOperator<DotOperator>;
    single_operator_map[','] = &createOperator<CommaOperator>;
    single_operator_map['?'] = &createOperator<QuestionOperator>;
    single_operator_map['~'] = &createOperator<TildeOperator>;
    single_operator_map['('] = &createOperator<OpenParenOperator>;
    single_operator_map[')'] = &createOperator<CloseParenOperator>;
    single_operator_map['['] = &createOperator<OpenBracketOperator>;
    single_operator_map[']'] = &createOperator<CloseBracketOperator>;
    single_operator_map['{'] = &createOperator<OpenBraceOperator>;
    single_operator_map['}'] = &createOperator<CloseBraceOperator>;
    
    return;
  }
  
  void init_double_operator_map(map<string, operator_fp_t> &double_operator_map) {
    double_operator_map["++"] = &createOperator<IncrementOperator>;
    double_operator_map["--"] = &createOperator<DecrementOperator>;
    double_operator_map["=="] = &createOperator<EqualsOperator>;
    double_operator_map["!="] = &createOperator<NotEqualOperator>;
    double_operator_map["<="] = &createOperator<LTEOperator>;
    double_operator_map[">="] = &createOperator<GTEOperator>;
    double_operator_map["&&"] = &createOperator<AndOperator>;
    double_operator_map["||"] = &createOperator<OrOperator>;
    double_operator_map["+="] = &createOperator<PlusEqualsOperator>;
    double_operator_map["-="] = &createOperator<MinusEqualsOperator>;
    double_operator_map["*="] = &createOperator<TimesEqualsOperator>;
    double_operator_map["/="] = &createOperator<DivideEqualsOperator>;
    double_operator_map["%="] = &createOperator<ModEqualsOperator>;
    double_operator_map["&="] = &createOperator<AndEqualsOperator>;
    double_operator_map["|="] = &createOperator<OrEqualsOperator>;
    double_operator_map["^="] = &createOperator<CaratEqualsOperator>;
    double_operator_map["<<"] = &createOperator<InsertionOperator>;
    double_operator_map[">>"] = &createOperator<ExtractionOperator>;
    double_operator_map["->"] = &createOperator<ArrowOperator>;
    double_operator_map["::"] = &createOperator<ScopeOperator>;
    
    return;
  }
}
