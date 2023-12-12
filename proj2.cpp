# include <iostream>
# include <string>
# include <string.h>
# include <stdio.h>
# include <vector>
# include <sstream>
# include <stack>
using namespace std ;
string gtestnum = "" ;
enum TokenType {
  LEFT_PAREN, // 0
  RIGHT_PAREN, // 1
  INT, // 2
  STRING, // 3
  DOT, // 4
  FLOAT, //5
  NIL, // 6
  T, //7
  QUOTE, //8
  SYMBOL, // 9
  SEXP, // 10
  TREE, // 11
  HOLLOW, // 12
  ERROR, // 13
  END // 14
}; // enum TokenType

struct InstructionNode {
  string tokenname ;
  int tokentype ;
  int column ;
  int line ;
  int resetcolumn ;
  InstructionNode* next ;
}; // struct InstructionNode

struct IntNode {
  int value ;
  IntNode* next ;
} ; // IntNode

class Vectorint {
  public:
  IntNode* mhead ;
  IntNode* mtail ;
  int mindex ;
  Vectorint( ) { 
    mindex = 0 ;
    mtail = NULL ;
    mhead = NULL ;
  }  // Vectorint()

  ~Vectorint() { }

  void Push_back( int newnode ) {
    if ( mhead == NULL ) {
      mhead = new IntNode ;
      mhead -> next = NULL ;
      mhead -> value = newnode ;
      mtail = mhead ;
    } // if
    else {  
      mtail -> next = new IntNode ;
      mtail = mtail -> next ;
      mtail -> next = NULL ;
      mtail -> value = newnode ;
    } // else

    mindex++ ;
  } // Push_back()

  int Size() {
    return mindex ;
  } // Size()

  int Begin() {
    return 0 ;
  } // Begin()

  IntNode* Access( int index ) {
    int count = 0 ;
    IntNode* temp = mhead ;
    while ( count < index && temp != NULL ) {
      temp = temp -> next ;
      count ++ ;
    } // while

    return temp ;
  } // Access()

  bool Insert( int insertindex, int insertnode ) {
    IntNode* newnode = new IntNode ;
    newnode -> next = NULL ;
    newnode -> value = insertnode ;
    if ( mhead == NULL ) {
      mhead = newnode ;
      mtail = newnode ;
      mindex++ ;
      return true ;
    } // if
    else {
      if ( insertindex == 0 ) { // insert head
        newnode -> next = mhead ;
        mhead = newnode ;
      } // if
      else if ( insertindex == mindex ) {
        mtail -> next = newnode ;
        mtail = mtail -> next ;
      } // else if
      else { //  ( insertindex <= mindex ) 
        if ( insertindex < mindex ) {
          int count = 0 ;
          IntNode* nodebeinsertindex = mhead ;
          while ( count < insertindex - 1 ) {
            nodebeinsertindex = nodebeinsertindex -> next ;
            count++ ;
          } // while
  
          newnode -> next = nodebeinsertindex -> next ;
          nodebeinsertindex -> next = newnode ;
        } // if 
        else {
          cout << "error insert out of index " << endl ;
          return false ;
        } // else  
      } // else
  
      mindex++ ;
      return true ;
    } // else
  } // Insert()

  bool Erase( int deleteindex ) {
    if ( deleteindex >=  Size() ) {
      return false ;
    } // if
    else if ( deleteindex == 0 && Size() >= 2 ) {
      IntNode* thedeletenode = mhead ;
      mhead = mhead -> next ;
      delete thedeletenode ;
    } // else if
    else if ( deleteindex == 0 && Size() == 1 ) {
      delete mhead ;
      mhead = NULL ;
      mtail = NULL ;
    } // else if
    else { //  ( Size() >= 2 ) 
      int count = 0 ;
      IntNode* thenodebedel = mhead ;
      while ( count < deleteindex - 1 ) {
        thenodebedel = thenodebedel -> next ;
        count ++ ;
      } // while

      IntNode* thedeletenode = thenodebedel -> next ;
      thenodebedel -> next = thenodebedel -> next -> next ;
      if ( deleteindex == Size() - 1 ) {

        mtail = thenodebedel ;
      } // if

      delete thedeletenode ;
    } // else 
    

    mindex -- ;
    return true ;
  } // Erase()

  bool Clear() {
    int i = 0 ;
    IntNode* temp = mhead ;
    IntNode* temp2 = mhead ;
    while ( i < mindex ) {
      temp2 = temp -> next ;
      temp -> next = NULL ;
      delete temp ;
      temp = NULL ;
      temp = temp2 ;
      i++ ;
    } // while

    mhead = NULL ;
    mtail = NULL ;
    mindex = 0 ;
    return true ;
  } // Clear()

} ; // Vectorint

class Vector {
  public:
  InstructionNode* mhead ;
  InstructionNode* mtail ;
  int mindex ;
  Vector( ) { 
    mindex = 0 ;
    mtail = NULL ;
    mhead = NULL ;
  }  // Vector()

  ~Vector() { }

  void Push_back( InstructionNode newnode ) {
    if ( mhead == NULL ) {
      mhead = new InstructionNode ;
      mhead -> next = NULL ;
      mhead -> tokenname = newnode.tokenname ;
      mhead -> tokentype = newnode.tokentype ;
      mhead -> line = newnode.line ;
      mhead -> column = newnode.column ;
      mhead -> resetcolumn = newnode.resetcolumn ;
      mtail = mhead ;
    } // if
    else {  
      mtail -> next = new InstructionNode ;
      mtail = mtail -> next ;
      mtail -> next = NULL ;
      mtail -> tokenname = newnode.tokenname ;
      mtail -> tokentype = newnode.tokentype ;
      mtail -> line = newnode.line ;
      mtail -> column = newnode.column ;
      mtail -> resetcolumn = newnode.resetcolumn ;
    } // else

    mindex++ ;
  } // Push_back()

  int Size() {
    return mindex ;
  } // Size()

  int Begin() {
    return 0 ;
  } // Begin()

  InstructionNode* Access( int index ) {
    int count = 0 ;
    InstructionNode* temp = mhead ;
    while ( count < index && temp != NULL ) {
      temp = temp -> next ;
      count ++ ;
    } // while

    return temp ;
  } // Access()

  bool Insert( int insertindex, InstructionNode insertnode ) {
    InstructionNode* newnode = new InstructionNode ;
    newnode -> next = NULL ;
    newnode -> tokenname = insertnode.tokenname ;
    newnode -> tokentype = insertnode.tokentype ;
    newnode -> column = insertnode.column ;
    newnode -> line = insertnode.line ;
    newnode -> resetcolumn = insertnode.resetcolumn ;
    if ( mhead == NULL ) {
      mhead = newnode ;
      mtail = newnode ;
      mindex++ ;
      return true ;
    } // if
    else {
      if ( insertindex == 0 ) { // insert head
        newnode -> next = mhead ;
        mhead = newnode ;
      } // if
      else if ( insertindex == mindex ) {
        mtail -> next = newnode ;
        mtail = mtail -> next ;
      } // else if
      else { //  ( insertindex <= mindex ) 
        if ( insertindex < mindex ) {
          int count = 0 ;
          InstructionNode* nodebeinsertindex = mhead ;
          while ( count < insertindex - 1 ) {
            nodebeinsertindex = nodebeinsertindex -> next ;
            count++ ;
          } // while
  
          newnode -> next = nodebeinsertindex -> next ;
          nodebeinsertindex -> next = newnode ;
        } // if 
        else {
          cout << "error insert out of index " << endl ;
          return false ;
        } // else  
      } // else
  
      mindex++ ;
      return true ;
    } // else
  } // Insert()

  bool Erase( int deleteindex ) {
    if ( deleteindex >=  Size() ) {
      return false ;
    } // if
    else if ( deleteindex == 0 && Size() >= 2 ) {
      InstructionNode* thedeletenode = mhead ;
      mhead = mhead -> next ;
      delete thedeletenode ;
    } // else if
    else if ( deleteindex == 0 && Size() == 1 ) {
      delete mhead ;
      mhead = NULL ;
      mtail = NULL ;
    } // else if
    else { //  ( Size() >= 2 ) 
      int count = 0 ;
      InstructionNode* thenodebedel = mhead ;
      while ( count < deleteindex - 1 ) {
        thenodebedel = thenodebedel -> next ;
        count ++ ;
      } // while

      InstructionNode* thedeletenode = thenodebedel -> next ;
      thenodebedel -> next = thenodebedel -> next -> next ;
      if ( deleteindex == Size() - 1 ) {

        mtail = thenodebedel ;
      } // if

      delete thedeletenode ;
    } // else 
    

    mindex -- ;
    return true ;
  } // Erase()

  bool Clear() {
    int i = 0 ;
    InstructionNode* temp = mhead ;
    InstructionNode* temp2 = mhead ;
    while ( i < mindex ) {
      temp2 = temp -> next ;
      temp -> next = NULL ;
      delete temp ;
      temp = NULL ;
      temp = temp2 ;
      i++ ;
    } // while

    mhead = NULL ;
    mtail = NULL ;
    mindex = 0 ;
    return true ;
  } // Clear()

} ; // Vector


class Transfer{
  public : 
  Transfer() { } 

  ~Transfer() { }

  bool Isdigit( char ch ) {
    if ( ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' || 
         ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0' )
      return true ;
    else 
      return false ;
  } // Isdigit()

  float Strtof( string str ) {
    float num = 0 ;
    int index = 0 ;
    int dotindex = 0 ;
    bool isfinddot = false ;
    while ( index < str.length() ) {
      if ( str[ index ] == '.' ) {
        dotindex = index ;
        isfinddot = true ;
      } // if

      index ++ ;
    } // while

    if ( isfinddot == false ) {
      float isint = Strtoint( str ) ;
      return isint ;
    } // if

    index = dotindex + 1 ;
    int count = 1, countnum = 0 ;
    while ( index < str.length() ) {
      if ( Isdigit( str[ index ] ) ) {
        float temp = ( str[ index ] - '0' ) ;
        countnum = 0 ;
        while ( countnum < count ) {
          temp = temp * 0.1 ;
          countnum ++ ;
        } // while

        num += temp ;
      } // if

      count++ ;
      index++ ;
    } // while
    
    index = 0 ;
    int intnum = 0 ;
    while ( index < dotindex ) {
      if ( Isdigit( str[ index ] ) ) {
        intnum = intnum * 10 + ( str[ index ] - '0' ) ;
      } // if

      index ++ ;
    } // while

    num = intnum + num ;
    if ( str[ 0 ] == '-' ) 
      num = num * -1 ;
    return num ;
  } // Strtof()

  int Strtoint( string str ) {
    int index = 0 ;
    int intnum = 0 ;
    while ( index < str.length() ) {
      if ( Isdigit(  str[ index ] ) ) {
        intnum = intnum *10 + ( str[ index ]- '0' ) ;
      } // if

      index ++ ;
    } // while

    if ( str [0] == '-' ) 
      intnum = intnum * -1 ;
    return intnum ;
  } // Strtoint()

} ;// Transfer


class TokenTable {
  public :
  vector < string > mwhitespace ;
  vector < string > mreservedword ;
  Transfer mtransfer ;
  TokenTable() {
    Createtable() ;
  } // TokenTable()

  ~TokenTable() {
  } // ~TokenTable()

  void Createtable() {
    string str = " " ;
    mwhitespace.push_back( str ) ;
    str = "\t" ;
    mwhitespace.push_back( str ) ;
    str = "\n" ;
    mwhitespace.push_back( str ) ;
    str = "\r" ;
    mwhitespace.push_back( str ) ;

	  str = "cons" ;
	  mreservedword.push_back( str ) ;
	  str = "list" ;
	  mreservedword.push_back( str ) ;
    str = "quote" ;
	  mreservedword.push_back( str ) ;
	  str = "\'" ;
	  mreservedword.push_back( str ) ;
	  str = "define" ;
    mreservedword.push_back( str ) ;
	  str = "car" ;
	  mreservedword.push_back( str ) ;
	  str = "cdr" ;
	  mreservedword.push_back( str ) ;
    str = "atom?" ;
    mreservedword.push_back( str ) ;
    str = "pair?" ;
    mreservedword.push_back( str ) ;
    str = "list?" ;
    mreservedword.push_back( str ) ;
    str = "null?" ;
    mreservedword.push_back( str ) ;
    str = "integer?" ;
    mreservedword.push_back( str ) ;
    str = "real?" ;
    mreservedword.push_back( str ) ;
    str = "number?" ;
    mreservedword.push_back( str ) ; // in OurSchem, real? = number?, but not in Scheme (there are complex-numbers)
    str = "string?" ;
    mreservedword.push_back( str ) ;
    str = "boolean?" ;
    mreservedword.push_back( str ) ; 
    str = "symbol?" ;
    mreservedword.push_back( str ) ;
    str = "+" ;
    mreservedword.push_back( str ) ;
    str = "-" ;
    mreservedword.push_back( str ) ;
    str = "*" ;
    mreservedword.push_back( str ) ;
    str = "/" ;
    mreservedword.push_back( str ) ;
    str = "not" ;
    mreservedword.push_back( str ) ;
    str = "and" ;
    mreservedword.push_back( str ) ;
    str = "or" ;
    mreservedword.push_back( str ) ;
    str = ">" ;
    mreservedword.push_back( str ) ;
    str = ">=" ;
    mreservedword.push_back( str ) ;
    str = "<" ;
    mreservedword.push_back( str ) ;
    str = "<=" ;
    mreservedword.push_back( str ) ;
    str = "=" ;
    mreservedword.push_back( str ) ;
    str = "string-append" ;
    mreservedword.push_back( str ) ;
    str = "string>?" ;
    mreservedword.push_back( str ) ;
    str = "string<?" ;
    mreservedword.push_back( str ) ;
    str = "string=?" ;
    mreservedword.push_back( str ) ;
    str = "eqv?" ;
    mreservedword.push_back( str ) ;
    str = "equal?" ;
    mreservedword.push_back( str ) ;
    str = "begin" ;
    mreservedword.push_back( str ) ;
    str = "if" ;
    mreservedword.push_back( str ) ;
    str = "cond" ;
    mreservedword.push_back( str ) ;
    str = "clean-environment" ;
    mreservedword.push_back( str ) ;
  } // Createtable()

  bool Isreservedword( string str ) {
    string temp = "\0" ;
    for ( int it = 0 ; it < mreservedword.size() ; it++ ) {
      temp = mreservedword[ it ] ;
      if ( temp == str ) {
        return true ;
      } // if
    } // for

    return false ;
  } // Isreservedword()

  bool IsWhitespace( string str ) {
    string temp = "\0" ;
    bool returnvalue = false ;
    for ( int it = 0 ; it < mwhitespace.size() ; it++ ) {
      temp = mwhitespace[ it ] ;
      if ( temp == str ) {
        returnvalue = true ;
      } // if
    } // for

    return returnvalue ;
  } // IsWhitespace()

  bool IsWhitespace( char ch ) {
    string str = "" ;
    str += ch ;
    return IsWhitespace( str ) ;
  } // IsWhitespace()

  bool IfSeparatorisAToken( string str ) {
    if ( str == "(" || str == ")" || str == "\'" || str == "\"" || str == ";" ) {
      return true ;
    } // if
    else
      return false ;
  } // IfSeparatorisAToken()

  bool IfSeparatorisAToken( char ch ) {
    string str = "" ;
    str += ch ;
    return IfSeparatorisAToken( str ) ;
  } // IfSeparatorisAToken()

  bool IsSeparators( char ch ) {
    if ( IsWhitespace( ch ) ) {
      return true ;
    } // if
    else if ( IfSeparatorisAToken( ch ) ) {
      return true ;
    } // else if
    else
      return false ;
  } // IsSeparators()

  bool IsINT( string peek ) {
    int pos = 0 ;
    if ( pos < peek.length() && ( peek[ pos ] == '+' || peek[ pos ] == '-' ) )
      pos++ ;
    bool num = false ;
    while ( pos < peek.length() ) {
      char ch = peek[ pos ] ;
      if ( ch == '1' || ch == '2' || ch == '3' || ch == '4' || ch == '5' ||
           ch == '6' || ch == '7' || ch == '8' || ch == '9' || ch == '0' ) {
        pos++ ;
        num = true ;
      } // if
      else
        return false ;
    } // while

    if ( num )
      return true ;
    else 
      return false ;
  } // IsINT()

  bool IsFLOAT( string peek ) {
    int pos = 0;
    bool dot = false;
    bool interger = false;
    bool decimal = false;
    if ( pos < peek.length() && ( peek[ pos ] == '+' || peek[ pos ] == '-' ) )
      pos++ ;

    while ( pos < peek.length() ) {
      if ( !dot && mtransfer.Isdigit( peek[ pos ] ) ) {
        interger = true ;
        pos++ ;
      } // if
      else if ( peek[ pos ] == '.' ) {
        if ( dot )
          return false ;
        dot = true ;
        pos++ ;
      } // else if
      else if ( dot && mtransfer.Isdigit( peek[ pos ] ) ) {
        decimal = true ;
        pos++ ;
      } // else if
      else 
        return false;
    } // while

    if ( interger && dot )
      return true ;
    else if ( decimal && dot )
      return true ;
    else 
      return false ;
  } // IsFLOAT()


  int FindTokenType( string str ) {
    // regex regINT( "[+-]?[0-9]+" ) ;
    // regex regFLOATone( "[+-]?[0-9]*.[0-9]+" ) ;
    // regex regFLOATtwo( "[+-]?[0-9]+.[0-9]*" ) ;
    string falsestmt1 = "nil" ;
    string falsestmt2 = "#f" ;
    string truestmt1 = "t" ;
    string truestmt2 = "#t" ;
    if ( IsINT( str ) )
      return INT ;
    else if ( IsFLOAT( str ) )
      return FLOAT ;
    else if ( str == "(" )
      return LEFT_PAREN ;
    else if ( str == ")" )
      return RIGHT_PAREN ;
    else if ( str == "\"" )
      return STRING ;
    else if ( str == "." )
      return DOT ;
    else if ( str == "\'" || str == "quote" )
      return QUOTE ;
    else if ( str == falsestmt1 || str == falsestmt2 )
      return NIL ;
    else if ( str == truestmt1 || str == truestmt2 )
      return T ;
    else
      return SYMBOL ;
  } // FindTokenType()

  bool Isnextline( char ch ) {
    if ( ch == '\n' || ch == '\r' )
      return true ;
    else
      return false ;
  } // Isnextline()

  int Countlength( string str ) {
    int index = 0 ;
    int length = 0 ;
    while ( index < str.size() ) {
      if ( str[ index ] == '\n' || str[ index ] == '\t' ||
           str[ index ] == '\\' || str[ index ] == '\"' ) {
        length += 2 ;
      } // if
      else 
        length++ ;

      index ++ ;
    } // while
  
    return length ;
  } // Countlength()
}; // class TokenTable

enum Sexpstatus {
  COMPLETE,
  NOTCOMPLETE,
  ERRORSTMT
}; // enum Sexpstatus

class Syntax {

  public :
  Vector mtokengroup ;
  int mindex ;
  TokenTable mtable ;
  Syntax() { mindex = 0 ; }

  ~Syntax() {
  } // ~Syntax()

  void Reset() {
    mindex = 0 ;
    mtokengroup.Clear() ;
  } // Reset()

  void Setsyntaxcheack( Vector input ) {
    // mtokengroup = input ;
    int index = 0 ;
    InstructionNode* memofindex = input.Access( index ) ;
    InstructionNode copy ;
    while ( index < input.Size() ) {
      copy.tokenname = memofindex -> tokenname ;
      copy.tokentype = memofindex -> tokentype ;
      copy.column = memofindex -> column ;
      copy.line = memofindex -> line ;
      copy.resetcolumn = memofindex -> resetcolumn ;
      mtokengroup.Push_back( copy ) ;
      index++ ;
      memofindex = memofindex -> next ;
    } // while
    
  } // Setsyntaxcheack()

  InstructionNode Getnexttoken() {
    if ( mindex < mtokengroup.Size() ) {
      InstructionNode* memloc = mtokengroup.Access( mindex ) ;
      if ( memloc -> tokentype != STRING ) {
        InstructionNode node ;
        node.tokenname = memloc -> tokenname ;
        node.tokentype = memloc -> tokentype ;
        node.line = memloc -> line ;
        node.column = memloc -> column ;
        node.next = NULL ;
        node.resetcolumn = memloc -> resetcolumn ;
        mindex += 1 ;
        return node ;
      } // if
      else { // STRING
        InstructionNode node ;
        if ( mindex + 2 < mtokengroup.Size() ) { // successful string
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 3 ;
        } // if
        else if ( mindex + 1 < mtokengroup.Size() ) {
          memloc = mtokengroup.Access( mindex + 1 ) ;
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + node.tokenname.length() ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 2 ;
        } // else if
        else {
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + 1 ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 1 ;
        } // else

        return node ;        
      } // else
    } // if
    else {
      InstructionNode node ;
      node.tokenname = "error" ;
      node.tokentype = ERROR ;
      return node ;
    } // else
  } // Getnexttoken()

  InstructionNode Peeknexttoken() {
    if ( mindex < mtokengroup.Size() ) {
      InstructionNode* memloc = mtokengroup.Access( mindex ) ;
      if ( memloc -> tokentype != STRING ) {
        InstructionNode node ;
        node.tokenname = memloc -> tokenname ;
        node.tokentype = memloc -> tokentype ;
        node.line = memloc -> line ;
        node.column = memloc -> column ;
        node.next = NULL ;
        node.resetcolumn = memloc -> resetcolumn ;
        return node ;
      } // if
      else { // string
        InstructionNode node ;
        if ( mindex + 2 < mtokengroup.Size() ) { // successful string
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // if
        else if ( mindex + 1 < mtokengroup.Size() ) {
          memloc = mtokengroup.Access( mindex + 1 ) ;
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          // node.column = memloc -> column + node.tokenname.length() ; length() can not deal \n \t
          node.column = ( memloc -> column ) + mtable.Countlength( node.tokenname ) ;
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // else if
        else {
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + 1 ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // else

        return node ;
      } // else
    } // if
    else {
      InstructionNode node ;
      node.tokenname = "null" ;
      node.tokentype = HOLLOW ;
      return node ;
    } // else
  } // Peeknexttoken()

  bool Allisstring() {
    InstructionNode* stringbody = mtokengroup.Access( mindex + 1 ) ;
    InstructionNode* stringmark = mtokengroup.Access( mindex + 2 ) ;
    if ( stringbody -> tokentype == STRING && stringmark -> tokentype == STRING ) {
      return true ;
    } // if
    else
      return false ;
  } // Allisstring()

  int Syntaxforsexp() { // need to deal " string "
    InstructionNode node = Peeknexttoken() ;
    int type = node.tokentype ;
    if ( type == SYMBOL || type == INT || type == FLOAT || type == STRING || type == NIL || type == T ) {
      if ( type == STRING ) {
        if ( mindex + 2 < mtokengroup.Size() && Allisstring() ) {
          node = Getnexttoken() ;
          return COMPLETE ;
        } // if
        else {
          // cout << "string error :"  ;
          cout << "> ERROR (no closing quote) : END-OF-LINE encountered at Line " ;
          cout << node.line << " Column " << node.column << endl << endl ;
          return ERRORSTMT ;
        } // else
      } // if
      else {
        node = Getnexttoken() ;
        return COMPLETE ;
      } // else
    } // if
    else if ( type == LEFT_PAREN ) {
      node = Getnexttoken() ;
      int status = Syntaxforsexp() ;
      if ( status == ERRORSTMT ) {
        return ERRORSTMT ;
      } // if
      else if ( status == NOTCOMPLETE ) {
        return NOTCOMPLETE ;
      } // else if

      bool stop = false ;
      while ( stop != true ) {
        node = Peeknexttoken() ;
        type = node.tokentype ;
        if ( type == LEFT_PAREN || type == QUOTE ||
             type == SYMBOL || type == INT || type == FLOAT || type == STRING || type == NIL || type == T ) {
          status = Syntaxforsexp() ;
          if ( status == ERRORSTMT ) {
            stop = true ;
            return ERRORSTMT ;
          } // if
        } // if
        else if ( node.tokentype == DOT || node.tokentype == RIGHT_PAREN ) {
          stop = true ;
        } // else if
        else if ( node.tokentype == HOLLOW ) {
          return NOTCOMPLETE ;
        } // else if
        else {
          cout << "> ERROR (no closing quote) : END-OF-LINE encountered at Line " ;
          cout << node.line << " Column " << node.column << endl << endl ;
          return ERRORSTMT ;
        } // else
      } // while

      node = Peeknexttoken() ;
      // cout << "810:" << node.tokenname << " " << node.tokentype << endl ;
      if ( node.tokentype == DOT ) { // . sexp ) 
        node = Getnexttoken() ;
        status = Syntaxforsexp() ;
        if ( status == ERRORSTMT ) {
          return ERRORSTMT ;
        } // if
        else if ( status == NOTCOMPLETE ) {
          return NOTCOMPLETE ;
        } // else if

        
        node = Peeknexttoken() ;
        // cout << "819:" << node.tokenname << " " << node.tokentype << endl ;
        if ( node.tokentype == RIGHT_PAREN ) {
          node = Getnexttoken() ;
          return COMPLETE ;
        } // if
        else if ( node.tokentype == HOLLOW ) {
          node = Getnexttoken() ;
          return NOTCOMPLETE ;
        } // else if
        else {
          cout << "> ERROR (unexpected token) : ')' expected when token at Line " ;
          cout << node.line << " Column " << node.column << " is >>" << node.tokenname << "<<\n" << endl ;
          return ERRORSTMT ;
        } // else

      } // if
      else if ( node.tokentype == RIGHT_PAREN ) {
        node = Getnexttoken() ;
        return COMPLETE ;
      } // else if
      else if ( node.tokentype == HOLLOW ) {
        return NOTCOMPLETE ;
      } // else if
      else {
        cout << "Line" << node.line << "column " << node.column ;
        cout << "expect a dot but a " << node.tokenname << endl ;
        return ERRORSTMT ;
      } // else

    } // else if
    else if ( type == QUOTE ) {
      node = Getnexttoken() ;
      return Syntaxforsexp() ;
    } // else if
    else if ( type == HOLLOW ) {
      return NOTCOMPLETE ;
    } // else if
    else {
      cout << "> ERROR (unexpected token) : atom or '(' expected when token at Line " ;
      cout << node.line << " Column " << node.column << " is >>" << node.tokenname << "<<\n" << endl ;
      return ERRORSTMT ;
    } // else
  } // Syntaxforsexp()

}; // Syntax()


class Forproj2Syntax {

  public :
  Vector mtokengroup ;
  int mindex ;
  TokenTable mtable ;
  Forproj2Syntax() { mindex = 0 ; }

  ~Forproj2Syntax() {
  } // ~Syntax()

  void Reset() {
    mindex = 0 ;
    mtokengroup.Clear() ;
  } // Reset()

  void Setsyntaxcheack( Vector input ) {
    // mtokengroup = input ;
    int index = 0 ;
    InstructionNode* memofindex = input.Access( index ) ;
    InstructionNode copy ;
    while ( index < input.Size() ) {
      copy.tokenname = memofindex -> tokenname ;
      copy.tokentype = memofindex -> tokentype ;
      copy.column = memofindex -> column ;
      copy.line = memofindex -> line ;
      copy.resetcolumn = memofindex -> resetcolumn ;
      mtokengroup.Push_back( copy ) ;
      index++ ;
      memofindex = memofindex -> next ;
    } // while
    
  } // Setsyntaxcheack()

  InstructionNode Getnexttoken() {
    if ( mindex < mtokengroup.Size() ) {
      InstructionNode* memloc = mtokengroup.Access( mindex ) ;
      if ( memloc -> tokentype != STRING ) {
        InstructionNode node ;
        node.tokenname = memloc -> tokenname ;
        node.tokentype = memloc -> tokentype ;
        node.line = memloc -> line ;
        node.column = memloc -> column ;
        node.next = NULL ;
        node.resetcolumn = memloc -> resetcolumn ;
        mindex += 1 ;
        return node ;
      } // if
      else { // STRING
        InstructionNode node ;
        if ( mindex + 2 < mtokengroup.Size() ) { // successful string
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 3 ;
        } // if
        else if ( mindex + 1 < mtokengroup.Size() ) {
          memloc = mtokengroup.Access( mindex + 1 ) ;
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + node.tokenname.length() ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 2 ;
        } // else if
        else {
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + 1 ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
          mindex += 1 ;
        } // else

        return node ;        
      } // else
    } // if
    else {
      InstructionNode node ;
      node.tokenname = "error" ;
      node.tokentype = ERROR ;
      return node ;
    } // else
  } // Getnexttoken()

  InstructionNode Peeknexttoken() {
    if ( mindex < mtokengroup.Size() ) {
      InstructionNode* memloc = mtokengroup.Access( mindex ) ;
      if ( memloc -> tokentype != STRING ) {
        InstructionNode node ;
        node.tokenname = memloc -> tokenname ;
        node.tokentype = memloc -> tokentype ;
        node.line = memloc -> line ;
        node.column = memloc -> column ;
        node.next = NULL ;
        node.resetcolumn = memloc -> resetcolumn ;
        return node ;
      } // if
      else { // string
        InstructionNode node ;
        if ( mindex + 2 < mtokengroup.Size() ) { // successful string
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // if
        else if ( mindex + 1 < mtokengroup.Size() ) {
          memloc = mtokengroup.Access( mindex + 1 ) ;
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          // node.column = memloc -> column + node.tokenname.length() ; length() can not deal \n \t
          node.column = ( memloc -> column ) + mtable.Countlength( node.tokenname ) ;
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // else if
        else {
          node.tokenname = memloc -> tokenname ;
          node.tokentype = memloc -> tokentype ;
          node.line = memloc -> line ;
          node.column = memloc -> column + 1 ; // not sure 
          node.next = NULL ;
          node.resetcolumn = memloc -> resetcolumn ;
        } // else

        return node ;
      } // else
    } // if
    else {
      InstructionNode node ;
      node.tokenname = "null" ;
      node.tokentype = HOLLOW ;
      return node ;
    } // else
  } // Peeknexttoken()

  bool Allisstring() {
    InstructionNode* stringbody = mtokengroup.Access( mindex + 1 ) ;
    InstructionNode* stringmark = mtokengroup.Access( mindex + 2 ) ;
    if ( stringbody -> tokentype == STRING && stringmark -> tokentype == STRING ) {
      return true ;
    } // if
    else
      return false ;
  } // Allisstring()

  int Syntaxforsexp() { // need to deal " string "
    InstructionNode node = Peeknexttoken() ;
    int type = node.tokentype ;
    if ( type == SYMBOL || type == INT || type == FLOAT || type == STRING || type == NIL || type == T ) {
        node = Getnexttoken() ;
        return COMPLETE ;
    } // if
    else if ( type == LEFT_PAREN ) {
      node = Getnexttoken() ;
      int status = Syntaxforsexp() ;
      if ( status == ERRORSTMT ) {
        return ERRORSTMT ;
      } // if
      else if ( status == NOTCOMPLETE ) {
        return NOTCOMPLETE ;
      } // else if

      bool stop = false ;
      while ( stop != true ) {
        node = Peeknexttoken() ;
        type = node.tokentype ;
        if ( type == LEFT_PAREN || type == QUOTE ||
             type == SYMBOL || type == INT || type == FLOAT || type == STRING || type == NIL || type == T ) {
          status = Syntaxforsexp() ;
          if ( status == ERRORSTMT ) {
            stop = true ;
            return ERRORSTMT ;
          } // if
        } // if
        else if ( node.tokentype == DOT || node.tokentype == RIGHT_PAREN ) {
          stop = true ;
        } // else if
        else if ( node.tokentype == HOLLOW ) {
          return NOTCOMPLETE ;
        } // else if
        else {
          // cout << "> ERROR (no closing quote) : END-OF-LINE encountered at Line " ;
          // cout << node.line << " Column " << node.column << endl << endl ;
          return ERRORSTMT ;
        } // else
      } // while

      node = Peeknexttoken() ;
      // cout << "810:" << node.tokenname << " " << node.tokentype << endl ;
      if ( node.tokentype == DOT ) { // . sexp ) 
        node = Getnexttoken() ;
        status = Syntaxforsexp() ;
        if ( status == ERRORSTMT ) {
          return ERRORSTMT ;
        } // if
        else if ( status == NOTCOMPLETE ) {
          return NOTCOMPLETE ;
        } // else if

        
        node = Peeknexttoken() ;
        // cout << "819:" << node.tokenname << " " << node.tokentype << endl ;
        if ( node.tokentype == RIGHT_PAREN ) {
          node = Getnexttoken() ;
          return COMPLETE ;
        } // if
        else if ( node.tokentype == HOLLOW ) {
          node = Getnexttoken() ;
          return NOTCOMPLETE ;
        } // else if
        else {
          // cout << "> ERROR (unexpected token) : ')' expected when token at Line " ;
          // cout << node.line << " Column " << node.column << " is >>" << node.tokenname << "<<\n" << endl ;
          return ERRORSTMT ;
        } // else

      } // if
      else if ( node.tokentype == RIGHT_PAREN ) {
        node = Getnexttoken() ;
        return COMPLETE ;
      } // else if
      else if ( node.tokentype == HOLLOW ) {
        return NOTCOMPLETE ;
      } // else if
      else {
        // cout << "Line" << node.line << "column " << node.column ;
        // cout << "expect a dot but a " << node.tokenname << endl ;
        return ERRORSTMT ;
      } // else

    } // else if
    else if ( type == QUOTE ) {
      node = Getnexttoken() ;
      return Syntaxforsexp() ;
    } // else if
    else if ( type == HOLLOW ) {
      return NOTCOMPLETE ;
    } // else if
    else {
      // cout << "> ERROR (unexpected token) : atom or '(' expected when token at Line " ;
      // cout << node.line << " Column " << node.column << " is >>" << node.tokenname << "<<\n" << endl ;
      return ERRORSTMT ;
    } // else
  } // Syntaxforsexp()

}; // Forproj2Syntax()

struct TreeNode {
  string name ;
  int type ;
  TreeNode * left ;
  TreeNode * right ;
}; // struct TreeNode

class Treetool{
  public:
  Treetool() {}
  ~Treetool() {}
  void TransferToTreestmt( Vector &tokengroup ) {
    int index = 0, innerindex = 0, leftparenindex = - 1 ;
    // stack < int > st ;
    Vectorint st ;
    InstructionNode node ;
    node.column = - 1 ;
    node.line = - 1 ;
    node.resetcolumn = -1 ;
    while ( index < tokengroup.Size() ) {
      // cout << "index: " << index << endl ;
      // cout << "tokeli : " << endl ;
      // Printtokenlinklist( tokengroup ) ;
      // cout << endl ;
      InstructionNode* memloc = tokengroup.Access( index ) ;
      if ( memloc -> tokentype == LEFT_PAREN ) {
        st.Push_back( index ) ;
      } // if
      else if ( memloc -> tokentype == RIGHT_PAREN ) {
        // cout << "rightpa" << endl ;
        IntNode* top =  st.Access( st.Size() - 1 ) ; // innerindex = st.top() ;
        innerindex = top -> value ;
        leftparenindex = innerindex ;
        // st.pop() ;
        st.Erase( st.Size() - 1 ) ;
        innerindex++ ;
        FitDOTPair( tokengroup, innerindex, index ) ;
        // cout << "token : " << innerindex << " " << index  << endl ;
        while ( innerindex < index ) {
          InstructionNode* memofinnerindex = tokengroup.Access( innerindex ) ;
          int tokentype = memofinnerindex -> tokentype ;
          if ( tokentype == SYMBOL || tokentype == INT || tokentype == FLOAT || tokentype == STRING ||
               tokentype == NIL || tokentype == T ) { // ( atom sexp .sexp ) 
            innerindex++ ;
            memofinnerindex = memofinnerindex -> next ;
            if ( memofinnerindex -> tokentype == DOT ) { // ( atom . sexp )
              innerindex = index ;
            } // if
            else {  // ( atom sexp . sexp ) -> ( atom . ( sexp . sexp ) )
              node.tokenname = "." ;
              node.tokentype = DOT ;
              tokengroup.Insert( tokengroup.Begin() + innerindex, node ) ;
              innerindex += 1 ;
              node.tokenname = "(" ;
              node.tokentype = SEXP ;
              tokengroup.Insert( tokengroup.Begin() + innerindex, node ) ;
              innerindex += 1 ;
              index += 2 ;
              node.tokenname = ")" ;
              node.tokentype = SEXP ;
              tokengroup.Insert( tokengroup.Begin() + index, node ) ;
              index += 1 ;
              innerindex -= 1 ;
            } // else
            
            // cout << "tokeli : " << leftparenindex << " " << index  << endl ;
            // Printtokenlinklist( tokengroup ) ;
          } // if
          else if ( tokentype == SEXP ) { // case for ( sexp . sexp ) ( sexp sexp1 . sexp2 )
            // stack < int > sexpleft ;
            Vectorint sexpleft ;
            bool stop = false ;
            while ( stop != true ) { // innerindex -> sexp tail -> '.' or sexp1
              InstructionNode* memofinnerindex = tokengroup.Access( innerindex ) ;
              if ( memofinnerindex -> tokenname == "(" ) {
                sexpleft.Push_back( innerindex ) ;
              } // if
              else if ( memofinnerindex -> tokenname == ")" ) {
                // sexpleft.pop() ;
                sexpleft.Erase( sexpleft.Size() -1 ) ;
              } // else if

              innerindex++ ;
              if ( sexpleft.Size() == 0 ) // sexpleft.empty()
                stop = true ;
            } // while

            memofinnerindex = tokengroup.Access( innerindex ) ;
            if ( memofinnerindex -> tokentype == DOT ) { // ( sexp . sexp )
              innerindex = index ;
            } // if
            else { // ( sexp sexp1 . sexp2 )
              node.tokenname = "." ;
              node.tokentype = DOT ;
              tokengroup.Insert( tokengroup.Begin() + innerindex, node ) ;
              innerindex += 1 ;
              node.tokenname = "(" ;
              node.tokentype = SEXP ;
              tokengroup.Insert( tokengroup.Begin() + innerindex, node ) ;
              innerindex += 1 ;
              index += 2 ;
              node.tokenname = ")" ;
              node.tokentype = SEXP ;
              tokengroup.Insert( tokengroup.Begin() + index, node ) ;
              index += 1 ;
              innerindex -= 1 ;

            } // else 
          } // else if

          innerindex++ ;
        } // while

        InstructionNode* temp = tokengroup.Access( leftparenindex ) ;
        // tokengroup[ leftparenindex ].tokentype = SEXP ;
        temp -> tokentype = SEXP ;
        // tokengroup[ index ].tokentype = SEXP ;
        temp = tokengroup.Access( index ) ;
        temp -> tokentype = SEXP ;
      } // else if
      else if ( memloc -> tokentype == QUOTE ) {
        // cout << "qqquote" << endl ;
        DealQUOTEstmt( tokengroup, index ) ;
        index -= 1 ;
      } // else if

      index++ ;
    } // while
  } // TransferToTreestmt()

  int FitDOTPair( Vector &tokengroup, int startindex, int &max ) {
    int index = 0 ;
    int indexofDot = - 1 ;
    // stack < InstructionNode > st 
    Vector st ;
    InstructionNode node ;
    node.resetcolumn = -1 ;
    node.line = -1 ;
    node.next = NULL ;
    node.column = -1 ;
    InstructionNode* memofindex = tokengroup.Access( index ) ;
    while ( index < max ) {
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype != STRING ) {
        node.tokenname = "(" ;
        st.Push_back( node ) ;
      } // if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype != STRING  ) {
        InstructionNode* temp = st.Access( st.Size() - 1 ) ;
        while ( temp -> tokenname != "(" ) { // st.top().tokenname != "("
          // st.pop() ;
          st.Erase( st.Size() - 1 ) ;
          temp = st.Access( st.Size() - 1 ) ;
        } // while

        // st.pop() ;
        st.Erase( st.Size() - 1 ) ;
      } // else if
      else if ( memofindex -> tokenname == "." && memofindex -> tokentype != STRING  ) {
        node.tokenname = "." ;
        node.line = index ;
        st.Push_back( node ) ;
      } // else if

      memofindex = memofindex -> next ;
      index++ ;
      if ( index == max ) {
        InstructionNode* temp = st.Access( st.Size() - 1 ) ;
        if ( temp -> tokenname == "." ) {
          return temp -> line ;
        } // if
      } // if
    } // while

    node.column = - 1 ;
    node.line = - 1 ;
    node.tokenname = "." ;
    node.tokentype = DOT ;
    tokengroup.Insert( tokengroup.Begin() + max, node ) ;
    max++ ;
    node.tokenname = "nil" ;
    node.tokentype = NIL ;
    tokengroup.Insert( tokengroup.Begin() + max, node ) ;
    max++ ;
    return max - 3 ;
  } // FitDOTPair()

  int FindDOtPairindex( Vector &tokengroup, int stindex, int endindex ) {
    int index = 0 ;
    int indexofDot = - 1 ;
    // stack < InstructionNode > st ;
    Vector st ;
    InstructionNode node ;
    InstructionNode* memofindex = tokengroup.Access( index ) ;
    while ( index < endindex ) {
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == SEXP ) {
        node.tokenname = "(" ;
        st.Push_back( node ) ;
      } // if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == SEXP ) {
        InstructionNode* temp = st.Access( st.Size() - 1 ) ;
        while ( temp -> tokenname != "(" ) {
          // st.pop() ;
          st.Erase( st.Size() - 1 ) ;
          temp = st.Access( st.Size() - 1 ) ;
        } // while

        // st.pop() ;
        st.Erase( st.Size() - 1 ) ;
      } // else if
      else if ( memofindex -> tokentype == DOT ) {
        node.tokenname = "." ;
        node.line = index ;
        st.Push_back( node ) ;
      } // else if

      memofindex = memofindex -> next ;
      index++ ;
      if ( index == endindex ) {
        InstructionNode* temp = st.Access( st.Size() - 1 ) ;
        if ( temp -> tokenname == "." ) {
          return temp -> line ;
        } // if
      } // if
    } // while

    return -1 ;
  } // FindDOtPairindex()

  TreeNode * CreateTree( Vector tokengroup, int stindex, int endindex ) {
    TreeNode * head = new TreeNode ;
    head -> name = " " ;
    head -> type = TREE ;
    head -> left = NULL ;
    head -> right = NULL ;
    int index = 0 ;

    int dotindex = FindDOtPairindex( tokengroup, stindex, endindex ) ;
    if ( dotindex == -1 ) {
      return NULL ;
    } // if

    InstructionNode* memofbedotindex = tokengroup.Access( dotindex - 1 ) ;
    if ( memofbedotindex -> tokentype == SEXP ) { //  tokengroup[ dotindex - 1 ].tokentype == SEXP
      TreeNode * lefttree = CreateTree( tokengroup, stindex + 1, dotindex - 1 ) ;
      head -> left = lefttree ;
    } // if
    else {
      TreeNode * left = new TreeNode ;
      left -> name = memofbedotindex -> tokenname ;
      left -> type = memofbedotindex -> tokentype ;
      left -> left = NULL ;
      left -> right = NULL ;
      head -> left = left ;
    } // else

    InstructionNode* memofafdotindex = tokengroup.Access( dotindex + 1 ) ;
    if ( memofafdotindex -> tokentype == SEXP ) {
      TreeNode * righttree = CreateTree( tokengroup, dotindex + 1, endindex - 1 ) ;
      head -> right = righttree ;
    } // if
    else {
      TreeNode * right = new TreeNode ;
      right -> name = memofafdotindex -> tokenname ;
      right -> type = memofafdotindex -> tokentype ;
      right -> left = NULL ;
      right -> right = NULL ;
      head -> right = right ;
    } // else

    return head ;
  } // CreateTree()

  void Deletetree( TreeNode * tree ) {
    if ( tree == NULL ) {
      return ;
    } // if

    Deletetree( tree -> left ) ;
    Deletetree( tree -> right ) ;
    delete tree ;
    tree = NULL ;
    return ;
  } // Deletetree()

  void DealQUOTEstmt( Vector &tokengroup, int index ) {
    InstructionNode* memlocofindexplus = tokengroup.Access( index + 1 ) ;
    if ( memlocofindexplus -> tokentype == QUOTE ) {
      DealQUOTEstmt( tokengroup, index + 1 ) ;
      memlocofindexplus = tokengroup.Access( index + 1 ) ;
    } // if

    int type = memlocofindexplus -> tokentype ;
    if ( type == LEFT_PAREN ) {
      InstructionNode node ;
      node.resetcolumn = -1 ;
      node.line = - 1 ;
      node.column = - 1 ;
      node.next = NULL ;
      InstructionNode* memofindex = tokengroup.Access( index ) ;
      memofindex -> tokentype = INT ;
      node.tokenname = "(" ;
      node.tokentype = LEFT_PAREN ;
      tokengroup.Insert( tokengroup.Begin() + index, node ) ;
      node.tokenname = "." ;
      node.tokentype = DOT ;
      tokengroup.Insert( tokengroup.Begin() + index + 2, node ) ;
      bool stop = false ;
      // stack < int > st ;
      Vectorint st ;
      int pairindex = - 1 ;
      index++ ;
      memofindex = tokengroup.Access( index ) ;
      while ( stop != true && index < tokengroup.Size() ) {
        if ( memofindex -> tokentype == LEFT_PAREN ) {
          st.Push_back( index ) ;
        } // if
        else if ( memofindex -> tokentype == RIGHT_PAREN ) {
          pairindex = index ;
          st.Erase( st.Size() - 1 ) ; // st.pop() ;
          if ( st.Size() == 0 ) {
            stop = true ;
          } // if

        } // else if
        
        memofindex = memofindex -> next ;
        index++ ;
      } // while

      node.tokenname = ")" ;
      node.tokentype = RIGHT_PAREN ;
      tokengroup.Insert( tokengroup.Begin() + pairindex, node ) ;
    } // if
    else if ( type == SYMBOL || type == INT || type == STRING || 
              type == FLOAT || type == NIL || type == T ) {
      InstructionNode* memofindex = tokengroup.Access( index ) ;
      memofindex -> tokentype = INT ;
      InstructionNode node ;
      node.tokenname = "(" ;
      node.tokentype = LEFT_PAREN ;
      node.line = - 1 ;
      node.column = - 1 ;
      tokengroup.Insert( tokengroup.Begin() + index, node ) ;
      node.tokenname = "." ;
      node.tokentype = DOT ;
      tokengroup.Insert( tokengroup.Begin() + index + 2, node ) ;
      node.tokenname = ")" ;
      node.tokentype = RIGHT_PAREN ;
      tokengroup.Insert( tokengroup.Begin() + index + 4, node ) ;
    } // else if

  } // DealQUOTEstmt()

  void Inorder( TreeNode * head ) {
    if ( head == NULL ) {
      cout << "null " ;
      return ;
    } // if

    Inorder( head -> left ) ;
    cout << head -> name << " " ;
    Inorder( head -> right ) ;
    return ;
  } // Inorder()

} ; // Treetool

struct ParaNode {
  string name ;
  TreeNode* root ;
  int tokentype ;
  ParaNode* next ;
}; // struct InstructionNode

class Vectorpara {
  public:
  ParaNode* mhead ;
  ParaNode* mtail ;
  int mindex ;
  Vectorpara( ) { 
    mindex = 0 ;
    mtail = NULL ;
    mhead = NULL ;
  }  // Vectorint()

  ~Vectorpara() { }

  void Push_back( ParaNode newnode ) {
    if ( mhead == NULL ) {
      mhead = new ParaNode ;
      mhead -> next = NULL ;
      mhead -> root = newnode.root ;
      mhead -> tokentype = newnode.tokentype ;
      mhead -> name = newnode.name ;
      mtail = mhead ;
    } // if
    else {  
      mtail -> next = new ParaNode ;
      mtail = mtail -> next ;
      mtail -> next = NULL ;
      mtail -> root = newnode.root ;
      mtail -> name = newnode.name ;
      mtail -> tokentype = newnode.tokentype ;
    } // else

    mindex++ ;
  } // Push_back()

  int Size() {
    return mindex ;
  } // Size()

  int Begin() {
    return 0 ;
  } // Begin()

  ParaNode* Access( int index ) {
    int count = 0 ;
    ParaNode* temp = mhead ;
    while ( count < index && temp != NULL ) {
      temp = temp -> next ;
      count ++ ;
    } // while

    return temp ;
  } // Access()

  bool Insert( int insertindex, ParaNode insertnode ) {
    ParaNode* newnode = new ParaNode ;
    newnode -> next = NULL ;
    newnode -> root = insertnode.root ;
    if ( mhead == NULL ) {
      mhead = newnode ;
      mtail = newnode ;
      mindex++ ;
      return true ;
    } // if
    else {
      if ( insertindex == 0 ) { // insert head
        newnode -> next = mhead ;
        mhead = newnode ;
      } // if
      else if ( insertindex == mindex ) {
        mtail -> next = newnode ;
        mtail = mtail -> next ;
      } // else if
      else { //  ( insertindex <= mindex ) 
        if ( insertindex < mindex ) {
          int count = 0 ;
          ParaNode* nodebeinsertindex = mhead ;
          while ( count < insertindex - 1 ) {
            nodebeinsertindex = nodebeinsertindex -> next ;
            count++ ;
          } // while
  
          newnode -> next = nodebeinsertindex -> next ;
          nodebeinsertindex -> next = newnode ;
        } // if 
        else {
          cout << "error insert out of index " << endl ;
          return false ;
        } // else  
      } // else
  
      mindex++ ;
      return true ;
    } // else
  } // Insert()

  bool Erase( int deleteindex ) {
    if ( deleteindex >=  Size() ) {
      return false ;
    } // if
    else if ( deleteindex == 0 && Size() >= 2 ) {
      ParaNode* thedeletenode = mhead ;
      mhead = mhead -> next ;
      delete thedeletenode ;
    } // else if
    else if ( deleteindex == 0 && Size() == 1 ) {
      delete mhead ;
      mhead = NULL ;
      mtail = NULL ;
    } // else if
    else { //  ( Size() >= 2 ) 
      int count = 0 ;
      ParaNode* thenodebedel = mhead ;
      while ( count < deleteindex - 1 ) {
        thenodebedel = thenodebedel -> next ;
        count ++ ;
      } // while

      ParaNode* thedeletenode = thenodebedel -> next ;
      thenodebedel -> next = thenodebedel -> next -> next ;
      if ( deleteindex == Size() - 1 ) {

        mtail = thenodebedel ;
      } // if

      delete thedeletenode ;
    } // else 
    

    mindex -- ;
    return true ;
  } // Erase()

  bool Clear() {
    int i = 0 ;
    ParaNode* temp = mhead ;
    ParaNode* temp2 = mhead ;
    while ( i < mindex ) {
      temp2 = temp -> next ;
      temp -> next = NULL ;
      delete temp ;
      temp = NULL ;
      temp = temp2 ;
      i++ ;
    } // while

    mhead = NULL ;
    mtail = NULL ;
    mindex = 0 ;
    return true ;
  } // Clear()

} ; // Vectorpara

class Functionbehaviordefined{
  public:
  TokenTable mtable ;
  Vectorpara paratable ; // not reset in Retset
  Vectorpara mreservewordtable ;
  Forproj2Syntax msyntax ;
  Treetool mtreetool ;
  Vector mtokenlinklist ;
  bool errormessageisbuild ;
  bool errorneedatree ;
  Vector errormessagetokengroup ;
  int levelcall ;
  Functionbehaviordefined() {
    errormessageisbuild = false ;
    errorneedatree = false ;
    levelcall = 0 ;
    Createreservewordtable() ;
  } // Functionbehaviordefined()

  ~Functionbehaviordefined() {}

  void Reset() {
    errormessageisbuild = false ;
    errorneedatree = false ;
    mtokenlinklist.Clear() ;
    msyntax.Reset() ;
    errormessagetokengroup.Clear() ;
    levelcall = 0 ;
  } // Reset()

  void Createreservewordtable() {
    int index = 0 ;
    ParaNode varnode ;
    string name = "" ;
    while ( index < mtable.mreservedword.size() ) {
      name = mtable.mreservedword[ index ] ;
      varnode.name = name ;
      varnode.tokentype = SYMBOL ;
      varnode.next = NULL ;
      TreeNode* varroot = new TreeNode ;
      varroot -> name = name ;
      varroot -> type = SYMBOL ;
      varroot -> left = NULL ;
      varroot -> right = NULL ;
      varnode.root = varroot ;
      mreservewordtable.Push_back( varnode ) ;
      index++ ;
    } // while
  } // Createreservewordtable

  TreeNode* Findreservewordtree( string str ) {
    ParaNode* target = mreservewordtable.Access( 0 ) ;
    while ( true ) {
      if ( target -> name == str ) {
        return target -> root ;
      } // if

      target = target -> next ;
    } // while
  } // Findreservewordtree

  void Constructerrormessagetokengroup( int index ) {
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    InstructionNode copy ;
    int syntax = NOTCOMPLETE ;
    while ( index < mtokenlinklist.Size() && syntax != COMPLETE ) {
      copy.tokenname = memofindex -> tokenname ;
      copy.tokentype = memofindex -> tokentype ;
      copy.column = memofindex -> column ;
      copy.line = memofindex -> line ;
      copy.resetcolumn = memofindex -> resetcolumn ;
      errormessagetokengroup.Push_back( copy ) ;
      msyntax.Reset() ;
      msyntax.Setsyntaxcheack( errormessagetokengroup ) ;
      syntax = msyntax.Syntaxforsexp() ;
      index++ ;
      memofindex = memofindex -> next ;
    } // while

    errorneedatree = true ;
  } // Constructerrormessagetokengroup()

  void Printpara() {
    cout << "print paratable :" << endl ;
    int index = 0 ;
    ParaNode* temp = paratable.Access( 0 ) ;
    while ( temp != NULL ) {
      cout << temp -> name << "  " ;
      cout << temp -> tokentype << endl ;
      temp = temp -> next ;
    } // while

    cout << "\n end paratable" << endl ;
  } // Parintpara

  void Settokenlinklist( Vector input ) {
    // mtokengroup = input ;
    int index = 0 ;
    InstructionNode* memofindex = input.Access( index ) ;
    InstructionNode copy ;
    while ( index < input.Size() ) {
      copy.tokenname = memofindex -> tokenname ;
      copy.tokentype = memofindex -> tokentype ;
      copy.column = memofindex -> column ;
      copy.line = memofindex -> line ;
      copy.resetcolumn = memofindex -> resetcolumn ;
      mtokenlinklist.Push_back( copy ) ;
      index++ ;
      memofindex = memofindex -> next ;
    } // while
    
  } // Settokenlinklist()

  TreeNode* Getanparatree( int &index ) {
    Vector buffer ;
    InstructionNode* node = mtokenlinklist.Access( index ) ;
    if ( node == NULL ) {
      TreeNode* root = new TreeNode ;
      root -> name = "ERROR" ;
      root -> type = HOLLOW ;
      root -> left = NULL ;
      root -> right = NULL ;
      return root ;
    } // if
    else {
      InstructionNode tempnode ;
      tempnode.tokenname = node -> tokenname ;
      tempnode.tokentype = node -> tokentype ;
      tempnode.line = node -> line ;
      tempnode.column = node -> column ;
      tempnode.resetcolumn = node -> resetcolumn ;
      tempnode.next = NULL ;
      index++ ;
      buffer.Push_back( tempnode ) ;
      msyntax.Reset() ;
      msyntax.Setsyntaxcheack( buffer ) ;
      int syntax = msyntax.Syntaxforsexp() ;
      if ( syntax == ERRORSTMT && tempnode.tokenname == ")" && 
          tempnode.tokentype == RIGHT_PAREN  ) {
        TreeNode* root = new TreeNode ;
        root -> name = "end" ;
        root -> type = END ;
        root -> left = NULL ;
        root -> right = NULL ;
        buffer.Clear() ;
        return root ;
      } // if

      while ( syntax != COMPLETE && syntax != ERRORSTMT ) {
        node = node -> next ;
        if ( node == NULL ) {
          TreeNode* root = new TreeNode ;
          root -> name = "ERROR" ;
          root -> type = HOLLOW ;
          root -> left = NULL ;
          root -> right = NULL ;
          buffer.Clear() ;
          return root ;
        } // if

        tempnode.tokenname = node -> tokenname ;
        tempnode.tokentype = node -> tokentype ;
        tempnode.line = node -> line ;
        tempnode.column = node -> column ;
        tempnode.resetcolumn = node -> resetcolumn ;
        tempnode.next = NULL ;
        index++ ;
        buffer.Push_back( tempnode ) ;
        msyntax.Reset() ;
        msyntax.Setsyntaxcheack( buffer ) ;
        syntax = msyntax.Syntaxforsexp() ;
      } // while

      if ( syntax == ERRORSTMT ) {
        TreeNode* root = new TreeNode ;
        root -> name = "ERROR" ;
        root -> type = ERROR ;
        root -> left = NULL ;
        root -> right = NULL ;
        buffer.Clear() ;
        return root ;
      } // if
      else {
        TreeNode* pararoot = NULL ;
        if ( buffer.Size() != 1 ) { 
          mtreetool.TransferToTreestmt( buffer ) ;
          pararoot = mtreetool.CreateTree( buffer, 0, buffer.Size() - 1 ) ;
          buffer.Clear() ;
          return pararoot ;
        } // if
        else {
          TreeNode* root = new TreeNode ;
          root -> name = buffer.Access( 0 ) -> tokenname ;
          root -> type = buffer.Access( 0 ) -> tokentype ;
          root -> left = NULL ;
          root -> right = NULL ;
          return root ;
        } // else 

        
      } // else
    } // else 

  } // GetanSexp()

  TreeNode* Deepcopytree( TreeNode* root ) {
    // base case
    if ( root == NULL ) {
        return NULL ;
    } // if
    // create a new node with the same data as the root node
    TreeNode* root_copy = new TreeNode ;  // Node(root->data);
    root_copy -> name  = root -> name ;
    root_copy -> type = root -> type ;
    // clone the left and right subtree
    root_copy -> left = Deepcopytree( root -> left ) ;
    root_copy -> right = Deepcopytree( root -> right)  ;
    // return cloned root node
    return root_copy;
  } // Deepcopytree()

  ParaNode* Isinparatable( string strname ) {
    int index = 0 ;
    ParaNode* traversal = paratable.Access( 0 ) ;
    while ( traversal != NULL ) {
      if ( traversal -> name == strname ) {
        ParaNode* temp = new ParaNode ;
        temp -> name = traversal -> name ;
        temp -> tokentype = traversal -> tokentype ;
        temp -> next = NULL ;
        temp -> root = Deepcopytree( traversal -> root ) ;
        return temp ;
      } // if
      
      traversal = traversal -> next ;
    } // while

    return NULL ;
  } // Isinparatable()

  ParaNode* Findreallocinparatable( string strname ) {
    int index = 0 ;
    ParaNode* traversal = paratable.Access( 0 ) ;
    while ( traversal != NULL ) {
      if ( traversal -> name == strname ) {
        return traversal ;
      } // if
      
      traversal = traversal -> next ;
    } // while

    return NULL ;
  } // Isinparatable()

  TreeNode* Cons( int &index, bool &isasinglenode ) {
    int errorstindex = index - 1 ;
    index ++ ;
    TreeNode* returntree = NULL ;
    TreeNode* para1 = NULL, * endstmt = NULL ; 
    // ( cons a b ) <- index to deal this ")" anf index pointer to next para
    TreeNode* para2 = NULL ;
    bool errorocurredonpara1 = false ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      para1 = Getanparatree( index ) ; 
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      para1 = Run( index, isasinglenode ) ; // ( cons ( cons 7 b ) a )
    } // else if
    else {
      ParaNode* boundvar = NULL ;
      if ( memofindex -> tokentype == SYMBOL ) {
        boundvar = Isinparatable( memofindex -> tokenname ) ;
        if ( boundvar != NULL ) {
          para1 = boundvar -> root ;
          index++ ;
        } // if
        else {
          TreeNode* errornode = new TreeNode ;
          errornode -> type = ERROR ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          errorocurredonpara1 = true ;
          Constructerrormessagetokengroup( index ) ;
          return errornode ;
        } // else 
      } // if
      else {
        para1 = Getanparatree( index ) ;
      } // else
    } // else
    
    if ( para1 -> type != ERROR && para1 -> type != HOLLOW ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index ++ ;
        para2 = Getanparatree( index ) ;
        endstmt = Getanparatree( index ) ; // -> ) 
      } // if
      else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        para2 = Run( index, isasinglenode ) ;
        endstmt = Getanparatree( index ) ;
      } // else if
      else {
        ParaNode* boundvar = NULL ;
        if ( memofindex -> tokentype == SYMBOL ) {
          boundvar = Isinparatable( memofindex -> tokenname ) ;
          if ( boundvar != NULL ) {
            para2 = boundvar -> root ;
            index++ ;
            endstmt = Getanparatree( index ) ;
          } // if
          else {
            TreeNode* errornode = new TreeNode ;
            errornode -> type = ERROR ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            errorocurredonpara1 = true ;
            Constructerrormessagetokengroup( index ) ;
            return errornode ;
          } // else 
        } // if
        else {
          para2 = Getanparatree( index ) ;
          endstmt = Getanparatree( index ) ;
        } // else
      } // else 
    } // if
    else {
      para2 = new TreeNode ;
      para2 -> type = ERROR ;
      para2 -> name = "ERROR" ;
      para2 -> left = NULL ;
      para2 -> right = NULL ;
      errorocurredonpara1 = true ;
    } // else 

    if ( para1 -> type != ERROR  && para2 -> type != ERROR &&
         para1 -> type != HOLLOW  && para2 -> type != HOLLOW && 
         endstmt -> type == END ) { // all correct 
      returntree = new TreeNode ;
      returntree -> name = " " ;
      returntree -> type = TREE ;
      returntree -> left = para1 ;
      returntree -> right = para2 ;
      isasinglenode = false ;
      return returntree ;
    } // if
    else { 
      if ( errormessageisbuild == false ) { 
        // check nonlist -> check incorrect number of arguments
        TreeNode* errornode = new TreeNode ;
        if ( para1 -> type == ERROR || para2 -> type == ERROR ) {
          errornode -> name = "ERROR (non-list) : " ; // construct errormessagetokengroup
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorstindex ) ;
        } // if
        else { // ( para1 -> type == HOLLOW || para2 -> type == HOLLOW || para3 -> type != END )
          // incorrect number of arguments
          errornode -> name = "ERROR (incorrect number of arguments) : cons" ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
        } // else
      
        errormessageisbuild = true ;
        isasinglenode = true ;
         mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( para2 ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // if
      else { // a error in deep sexp and error is constructored
        if ( errorocurredonpara1 ) {
          mtreetool.Deletetree( para2 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para1 ;
        } // if
        else {
          mtreetool.Deletetree( para1 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para2 ;
        } //else
      } // else 
    } // else 

  } // Cons()

  TreeNode* Car( int &index, bool &isasinglenode ) { // retrieve array[ 0 ]
    int errorindexfornonlist = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* returntree = NULL, *endstmt = NULL ; // ( car'( 5 6 )  ) <- index to deal this ")" anf index pointer to next para
    TreeNode* target = NULL ;
    int errorstindex = index ; // this is error token stindex may be wrong
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
    } // if
    else {
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        returntree = Run( index, isasinglenode ) ;
      } // if
    } // else 

    if ( returntree == NULL ) {
      TreeNode* root = NULL ;
      int unbounderrorindex = index ;
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokentype == SYMBOL ) {
        ParaNode* targetpara = NULL ;
        targetpara = Isinparatable( memofindex -> tokenname ) ;
        if ( targetpara == NULL ) {
          TreeNode* errornode = new TreeNode ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( unbounderrorindex ) ;
          errormessageisbuild = true ;
          return errornode ;
        } // if
        else {
          root = targetpara -> root ;
          index++ ;
        } // else 
      } // if
      else {
        root = Getanparatree( index ) ;
      } // else

      endstmt = Getanparatree( index ) ;
      // ( car'( 5 6 )  ) <- index to deal this ")" anf index pointer to next para
      if ( root -> right != NULL && endstmt -> type == END ) { // correct for car
        target = root -> left ;
        root -> left = NULL ;
        mtreetool.Deletetree( root ) ;
        if ( target -> right == NULL && target -> left == NULL ) {
          isasinglenode = true ;
        } // if
        else
          isasinglenode = false ;
        
        return target ;
      } // if
      else if ( endstmt -> type != END ) {
        TreeNode* errornode = new TreeNode ;
        errormessageisbuild = true ;
        if ( endstmt -> type == ERROR ) {
          errornode -> name = "ERROR (non-list) : " ; // construct errormessagetokengroup
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorindexfornonlist ) ;
        } // else
        else {
          // incorrect number of arguments
          errornode -> name = "ERROR (incorrect number of arguments) : car" ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorstindex ) ;
        } // else 

        mtreetool.Deletetree( root ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else if
      else { //root -> right == NULL
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (car with incorrect argument type) : " ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        mtreetool.Deletetree( root ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else
    } // if  
    else if ( returntree -> type == ERROR ) {
      return returntree ;
    } // else if
    else { // ( car ( funxt .....) )  returntree != error
      endstmt = Getanparatree( index ) ;
      if ( returntree -> left != NULL ) {
        if ( endstmt -> type == END ) { // all correct
          target = returntree -> left ;
          returntree -> left = NULL ;
          mtreetool.Deletetree( returntree ) ;
          if ( target -> right == NULL && target -> left == NULL ) { 
            isasinglenode = true ;
          } // if
          else
            isasinglenode = false ;

          return target ;
        } // if
        else { 
          TreeNode* errornode = new TreeNode ;
          errormessageisbuild = true ;
          if ( endstmt -> type == ERROR ) {
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindexfornonlist ) ;
          } // if
          else {
            errornode -> name = "ERROR (incorrect number of arguments) : car" ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
          } // else

          mtreetool.Deletetree( returntree ) ;
          mtreetool.Deletetree( endstmt ) ;
          return errornode ;
        } // else 
      } // if
      else {  
        TreeNode* errornode = new TreeNode ;
        errormessageisbuild = true ;
        if ( endstmt -> type == END ) {
          errornode -> name = "ERROR (car with incorrect argument type) : " ;
          Constructerrormessagetokengroup( errorstindex ) ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
        } // if
        else {
          errornode -> name = "ERROR (non-list) : " ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorindexfornonlist ) ;
        } // else

        mtreetool.Deletetree( returntree ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else
    } // else 

  } // Car()

  TreeNode* Cdr( int &index, bool &isasinglenode ) {
    int errorindexfornuonlist = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* returntree = NULL, *endstmt = NULL ; // ( cdr'( 5 6 )  ) <- index to deal this ")" anf index pointer to next para
    TreeNode* target = NULL ;
    int errorstindex = index ; // this is error token stindex may be wrong
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
    } // if
    else {
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        returntree = Run( index, isasinglenode ) ;
      } // if
    } // else 

    if ( returntree == NULL ) {
      TreeNode* root = NULL ;
      int unbounderrorindex = index ;
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokentype == SYMBOL ) {
        ParaNode* targetpara = NULL ;
        targetpara = Isinparatable( memofindex -> tokenname ) ;
        if ( targetpara == NULL ) {
          TreeNode* errornode = new TreeNode ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( unbounderrorindex ) ;
          errormessageisbuild = true ;
          return errornode ;
        } // if
        else {
          root = targetpara -> root ;
          index++ ;
        } // else 
      } // if
      else {
        root = Getanparatree( index ) ;
      } // else

      endstmt = Getanparatree( index ) ;
      if ( root -> right != NULL && endstmt -> type == END ) { // correct for cdr
        target = root -> right ;
        root -> right = NULL ;
        mtreetool.Deletetree( root ) ;
        if ( target -> right == NULL && target -> left == NULL ) {
          isasinglenode = true ;
        } // if
        else
          isasinglenode = false ;
        
        return target ;
      } // if
      else if ( endstmt -> type != END ) {
        TreeNode* errornode = new TreeNode ;
        errormessageisbuild = true ;
        if ( endstmt -> type == ERROR ) {
          errornode -> name = "ERROR (non-list) : " ; // construct errormessagetokengroup
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorindexfornuonlist  ) ;
        } // else
        else {
          // incorrect number of arguments
          errornode -> name = "ERROR (incorrect number of arguments) : cdr" ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
        } // else 

        mtreetool.Deletetree( root ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else if
      else { //root -> right == NULL
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (cdr with incorrect argument type) : " ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        mtreetool.Deletetree( root ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else
    } // if  
    else if ( returntree -> type == ERROR ) {
      return returntree ;
    } // else if
    else { // ( car ( funxt .....) )  returntree != error
      endstmt = Getanparatree( index ) ;
      if ( returntree -> left != NULL ) {
        if ( endstmt -> type == END ) { // all correct
          target = returntree -> right ;
          returntree -> right = NULL ;
          mtreetool.Deletetree( returntree ) ;
          if ( target -> right == NULL && target -> left == NULL ) { 
            isasinglenode = true ;
          } // if
          else
            isasinglenode = false ;

          return target ;
        } // if
        else { 
          TreeNode* errornode = new TreeNode ;
          errormessageisbuild = true ;
          if ( endstmt -> type == ERROR ) {
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindexfornuonlist  ) ;
          } // if
          else {
            errornode -> name = "ERROR (incorrect number of arguments) : cdr" ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
          } // else

          mtreetool.Deletetree( returntree ) ;
          mtreetool.Deletetree( endstmt ) ;
          return errornode ;
        } // else 
      } // if
      else {  
        TreeNode* errornode = new TreeNode ;
        errormessageisbuild = true ;
        if ( endstmt -> type == END ) {
          errornode -> name = "ERROR (cdr with incorrect argument type) : " ;
          Constructerrormessagetokengroup( errorstindex ) ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
        } // if
        else {
          errornode -> name = "ERROR (non-list) : " ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorstindex ) ;
        } // else

        mtreetool.Deletetree( returntree ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // else
    } // else 
    
  } // Cdr()

  TreeNode* Quote( int &index, bool &isasinglenode ) {
    index++ ;
    int errorstindex = index ;
    TreeNode* root = Getanparatree( index ) ;
    // if ( endstmt -> type == END ) {
    if ( root -> left == NULL && root -> right == NULL ) { // all correct 
      isasinglenode = true ;
    } // if
    else
      isasinglenode = false ;
    return root ;
    // } // if
    // else {
    //   TreeNode* errornode = new TreeNode ;
    //   errormessageisbuild = true ;
    //   if ( endstmt -> type == ERROR ) {
    //     errornode -> name = "ERROR (non-list) : " ;
    //     errornode -> type = ERROR ;
    //     errornode -> left = NULL ;
    //     errornode -> right = NULL ;
    //     Constructerrormessagetokengroup( errorstindex ) ;
    //   } // if
    //   else {
    //     errornode -> name = "ERROR (incorrect number of arguments) : quote" ;
    //     errornode -> type = ERROR ;
    //     errornode -> left = NULL ;
    //     errornode -> right = NULL ;
    //   } // else

    //   mtreetool.Deletetree( root ) ;
    //   mtreetool.Deletetree( endstmt ) ;
    //   return errornode ;
    // } // else
  } // Quote()

  TreeNode* Define( int &index, bool &isasinglenode ) { // must in top level
    int errorstindex = index - 1 ;
    index++ ;
    InstructionNode* varname = mtokenlinklist.Access( index ) ; // varname
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ; // index -> (
    ParaNode var ; // new define
    TreeNode* varroot = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      varroot = Run( index, isasinglenode ) ;
      if ( varroot -> type == ERROR )
        return varroot ;
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      varroot = Getanparatree( index ) ;
    } // else if
    else {
      cout << "2533  index : " << index << endl ;
      varroot = Getanparatree( index ) ;
    } // else 

    TreeNode* endstmt = Getanparatree( index ) ;
    var.next = NULL ;
    if ( endstmt -> type == END ) { 
      mtreetool.Deletetree( endstmt ) ;
      if ( varroot -> type == SYMBOL ) {
        if ( mtable.Isreservedword( varroot -> name ) ) {
          TreeNode* reservewordtree = Findreservewordtree( varroot -> name ) ;
          mtreetool.Deletetree( varroot ) ;
          varroot = reservewordtree ;
        } // if
        else {
          ParaNode* samedefine = Findreallocinparatable( varroot -> name ) ;
          if ( samedefine == NULL ) {
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (DEFINE format) : " ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            errornode -> type = ERROR ;
            errormessageisbuild = true ;
            Constructerrormessagetokengroup( errorstindex ) ;
            mtreetool.Deletetree( varroot ) ;
            return errornode ;
          } // if
          else {
            mtreetool.Deletetree( varroot ) ;
            varroot = samedefine -> root ;
          } // else
        } // else
      } // if

      ParaNode* redefine = Findreallocinparatable( varname -> tokenname ) ;
      string returntreename = "" ;
      if ( redefine != NULL ) {
        // cout << "2554 : " << redefine -> name << endl ;
        Cleanpararoot( redefine -> root ) ;
        redefine -> root = varroot ;
        redefine -> tokentype = varroot -> type ;
        returntreename = redefine -> name ;
        returntreename += " defined" ;
      } // if
      else {
        var.name = varname -> tokenname ;
        var.next = NULL ;
        if ( varroot -> left == NULL && varroot -> right == NULL ) {
          var.root = varroot ;
          var.tokentype = varroot -> type ;
        } // if
        else {  // a list 
          var.root = varroot ;
          var.tokentype = TREE ;
        } // else 
  
        paratable.Push_back( var ) ;
        returntreename = var.name ;
        returntreename += " defined" ;
        // cout << "2591" << endl ;
      } // else 
      isasinglenode = true ;
      TreeNode* returntree = new TreeNode ;
      returntree -> name = returntreename ;
      returntree -> type = SYMBOL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // if
    else {
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (DEFINE format) : " ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      errornode -> type = ERROR ;
      errormessageisbuild = true ;
      Constructerrormessagetokengroup( errorstindex ) ;
      mtreetool.Deletetree( varroot ) ;
      mtreetool.Deletetree( endstmt ) ;
      return errornode ;
    } // else 
  } // Define()

  void Cleanpararoot( TreeNode* root ) {
    int anotherpointtohrer = 0 ;
    ParaNode* travseral = paratable.Access( 0 ) ;
    while ( travseral != NULL ) {
      if ( travseral -> root == root ) {
        travseral++ ;
        anotherpointtohrer = true ;
      } // if
      else  
        travseral = travseral -> next ;
    } // while

    if ( anotherpointtohrer == 0 ) {
      travseral = mreservewordtable.Access( 0 ) ;
      while ( anotherpointtohrer != true && travseral != NULL ) {
        if ( travseral -> root == root ) {
          travseral = NULL ;
          anotherpointtohrer++ ;
        } // if
        else  
          travseral = travseral -> next ;
      } // while

      if ( anotherpointtohrer == 0 )
        mtreetool.Deletetree( root ) ;
      else {
        cout << "this is reservedword 2641 " << endl ;
        root = NULL ;
      } // else
    } // if
    else {
      if ( anotherpointtohrer == 1 )
        mtreetool.Deletetree( root ) ;
      else {
        cout << "inparatable two pointer point a smae space 2649 " << endl ;
        root = NULL ;
      } // else
    } // esle 
  } // cleanpararoot()

  TreeNode* CleanENV ( int &index, bool &isasinglenode ) {
    index ++ ;
    TreeNode* endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : clean-environment" ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      errormessageisbuild = true ;
      return errornode ;  
    } // if
    else {
    ParaNode* node, *samemem ;
    node = paratable.Access( 0 ) ;
    while ( node != NULL ) {
      samemem = node -> next ;
      while ( samemem != NULL ) {
        if ( samemem -> root == node -> root ) 
          samemem -> root = NULL ;
        samemem = samemem -> next ;
      } // while
      
      if ( mtable.Isreservedword( node -> root -> name ) == false )
        mtreetool.Deletetree( node -> root ) ;

      node -> root = NULL ; 
      node = node -> next ;
    } // while

    paratable.Clear() ;
    TreeNode* returnnode = new TreeNode ;
    returnnode -> name = "environment cleaned" ;
    returnnode -> type = SYMBOL ;
    returnnode -> left = NULL ;
    returnnode -> right = NULL ;
    isasinglenode = true ;
    return returnnode ; 
    } // else
  } // CleanENV()

  TreeNode* List( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    while ( stop != true ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
        if ( paranode -> type == ERROR )
          return paranode ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        // memofindex = mtokenlinklist.Access( index ) ;
        int errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {          
            paranode = Getanparatree( index ) ;
        } // else
      } // else 

      // create newnode
      if ( paranode -> type == ERROR ) {
        mtreetool.Deletetree( root ) ;
        TreeNode* errornode = new TreeNode ;
        errormessageisbuild = true ;
        errornode -> name = "ERROR (non-list) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( errornonlistindex ) ;
        return errornode ;
      } // if
      else if ( lastmaketree == NULL ) { // only run once
        lastmaketree = new TreeNode ;
        lastmaketree -> name = " " ;
        lastmaketree -> left = paranode ;
        lastmaketree -> right = new TreeNode ;
        lastmaketree -> right -> name = "nil" ;
        lastmaketree -> right -> type = NIL ;
        lastmaketree -> right -> left = NULL ;
        lastmaketree -> right -> right = NULL ;
        lastmaketree -> type = TREE ;
        root = lastmaketree ;
        isasinglenode = false ;
      } // if
      else {
        TreeNode* newtree = new TreeNode ;
        mtreetool.Deletetree( lastmaketree -> right ) ;
        lastmaketree -> right = newtree ;
        newtree -> name = " " ;
        newtree -> type = TREE ;
        newtree -> left = paranode ;
        newtree -> right = new TreeNode ;
        newtree -> right -> name = "nil" ;
        newtree -> right -> type = NIL ;
        newtree -> right -> left = NULL ;
        newtree -> right -> right = NULL ;
        lastmaketree = newtree ;
      } // else
    } // while

  } // List()

  TreeNode* IsAtom( int &index, bool &isasinglenode  ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 

    if ( paranode -> type == ERROR ) {
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;

    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : atom?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "nil" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // IsAtom()

  TreeNode* IsPair( int &index, bool &isasinglenode  ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( endstmt ) ;
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 

    if ( paranode -> type == ERROR ) {
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : pair?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL ) {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "nil" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // IsPair()

  TreeNode* Islist( int &index, bool &isasinglenode  ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( endstmt ) ;
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 


    if ( paranode -> type == ERROR ) {
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : list?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL ) {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "nil" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // Islist()

  TreeNode* IsNull( int &index, bool &isasinglenode  ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( endstmt ) ;
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 

    if ( paranode -> type == ERROR ) {
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : null?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL && 
              paranode -> type == NIL ) {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "nil" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // IsNull()

  TreeNode* IsINT( int &index, bool &isasinglenode  ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( endstmt ) ;
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 

    if ( paranode -> type == ERROR ) {
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : integer?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL && 
              paranode -> type == INT ) {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "NIL" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // IsINT()

  TreeNode* IsReal( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else if ( memofindex -> tokentype == SYMBOL ) {
      ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
      int errorindex = index ;
      if ( target == NULL ) {
           mtreetool.Deletetree( endstmt ) ;
           mtreetool.Deletetree( paranode ) ;
           TreeNode* errornode = new TreeNode ;
           errornode -> name = "ERROR (unbound symbol) : " ;
           errornode -> type = ERROR ;
           errornode -> left = NULL ;
           errornode -> right = NULL ;
           Constructerrormessagetokengroup( errorindex ) ;
           errormessageisbuild = true ;
           return errornode ;
         } // if
         else {
           paranode = target -> root ;
           index++ ;
         } // else 
    } // else if
    else { // atom
      paranode = Getanparatree( index ) ;
    } // else 

    if ( paranode -> type == ERROR ) {
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      errornode -> name = "ERROR (non-list) : " ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      Constructerrormessagetokengroup( errornonlistindex ) ;
      return errornode ;
    } // if
    else 
      endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( endstmt ) ;
      mtreetool.Deletetree( paranode ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : real?" ;
      errormessageisbuild = true ;
      errornode -> type = ERROR ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      return errornode ;
    } // if
    else if ( paranode -> left == NULL && paranode -> right == NULL && 
              paranode -> type == FLOAT ) {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "#t" ;
      returntree -> type = T ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else if
    else {
      TreeNode* returntree = new TreeNode ;
      isasinglenode = true ;
      returntree -> name = "NIL" ;
      returntree -> type = NIL ;
      returntree -> left = NULL ;
      returntree -> right = NULL ;
      return returntree ;
    } // else
  } // IsReal()

  TreeNode* IsNumber( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
     InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
     TreeNode* paranode = NULL, *endstmt = NULL ;
     if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
       index++ ;
       paranode = Run( index, isasinglenode ) ;
       if ( paranode -> type == ERROR ) {
         return paranode ;
       } // if
     } // if
     else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
       index++ ;
       paranode = Getanparatree( index ) ;
     }  // else if
     else if ( memofindex -> tokentype == SYMBOL ) {
       ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
       int errorindex = index ;
       if ( target == NULL ) {
            mtreetool.Deletetree( endstmt ) ;
            mtreetool.Deletetree( paranode ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = target -> root ;
            index++ ;
          } // else 
     } // else if
     else { // atom
       paranode = Getanparatree( index ) ;
     } // else 

     if ( paranode -> type == ERROR ) {
       return paranode ;
     } // if
     else 
       endstmt = Getanparatree( index ) ;

     if ( endstmt -> type != END ) {
       mtreetool.Deletetree( endstmt ) ;
       mtreetool.Deletetree( paranode ) ;
       TreeNode* errornode = new TreeNode ;
       errornode -> name = "ERROR (incorrect number of arguments) : number?" ;
       errormessageisbuild = true ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       return errornode ;
     } // if
     else if ( paranode -> left == NULL && paranode -> right == NULL && 
               paranode -> type == FLOAT ) {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "#t" ;
       returntree -> type = T ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else if
     else {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "NIL" ;
       returntree -> type = NIL ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else
  } // IsNumber()

  TreeNode* IsString( int &index, bool &isasinglenode ) {
     int errornonlistindex = index - 1 ;
     index++ ;
     InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
     TreeNode* paranode = NULL, *endstmt = NULL ;
     if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
       index++ ;
       paranode = Run( index, isasinglenode ) ;
       if ( paranode -> type == ERROR ) {
         return paranode ;
       } // if
     } // if
     else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
       index++ ;
       paranode = Getanparatree( index ) ;
     }  // else if
     else if ( memofindex -> tokentype == SYMBOL ) {
       ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
       int errorindex = index ;
       if ( target == NULL ) {
            mtreetool.Deletetree( endstmt ) ;
            mtreetool.Deletetree( paranode ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = target -> root ;
            index++ ;
          } // else 
     } // else if
     else { // atom
       paranode = Getanparatree( index ) ;
     } // else 

     if ( paranode -> type == ERROR ) {
       TreeNode* errornode = new TreeNode ;
       errormessageisbuild = true ;
       errornode -> name = "ERROR (non-list) : " ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       Constructerrormessagetokengroup( errornonlistindex ) ;
       return errornode ;
     } // if
     else 
       endstmt = Getanparatree( index ) ;

     if ( endstmt -> type != END ) {
       mtreetool.Deletetree( endstmt ) ;
       mtreetool.Deletetree( paranode ) ;
       TreeNode* errornode = new TreeNode ;
       errornode -> name = "ERROR (incorrect number of arguments) : string?" ;
       errormessageisbuild = true ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       return errornode ;
     } // if
     else if ( paranode -> left == NULL && paranode -> right == NULL && 
               paranode -> type == STRING ) {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "#t" ;
       returntree -> type = T ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else if
     else {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "NIL" ;
       returntree -> type = NIL ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else
  } // IsString()

  TreeNode* IsBool( int &index, bool &isasinglenode ) {
     int errornonlistindex = index - 1 ;
     index++ ;
     InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
     TreeNode* paranode = NULL, *endstmt = NULL ;
     if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
       index++ ;
       paranode = Run( index, isasinglenode ) ;
       if ( paranode -> type == ERROR ) {
         return paranode ;
       } // if
     } // if
     else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
       index++ ;
       paranode = Getanparatree( index ) ;
     }  // else if
     else if ( memofindex -> tokentype == SYMBOL ) {
       ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
       int errorindex = index ;
       if ( target == NULL ) {
            mtreetool.Deletetree( endstmt ) ;
            mtreetool.Deletetree( paranode ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = target -> root ;
            index++ ;
          } // else 
     } // else if
     else { // atom
       paranode = Getanparatree( index ) ;
     } // else 

     if ( paranode -> type == ERROR ) {
       TreeNode* errornode = new TreeNode ;
       errormessageisbuild = true ;
       errornode -> name = "ERROR (non-list) : " ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       Constructerrormessagetokengroup( errornonlistindex ) ;
       return errornode ;
     } // if
     else 
       endstmt = Getanparatree( index ) ;

     if ( endstmt -> type != END ) {
       mtreetool.Deletetree( endstmt ) ;
       mtreetool.Deletetree( paranode ) ;
       TreeNode* errornode = new TreeNode ;
       errornode -> name = "ERROR (incorrect number of arguments) : bool?" ;
       errormessageisbuild = true ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       return errornode ;
     } // if
     else if ( paranode -> left == NULL && paranode -> right == NULL && 
               ( paranode -> type == T || paranode -> type == NIL ) ) {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "#t" ;
       returntree -> type = T ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else if
     else {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "NIL" ;
       returntree -> type = NIL ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else
  } // IsBool()

  TreeNode* IsSymbol( int &index, bool &isasinglenode ) {
     int errornonlistindex = index - 1 ;
     index++ ;
     InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
     TreeNode* paranode = NULL, *endstmt = NULL ;
     if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
       index++ ;
       paranode = Run( index, isasinglenode ) ;
       if ( paranode -> type == ERROR ) {
         return paranode ;
       } // if
     } // if
     else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
       index++ ;
       paranode = Getanparatree( index ) ;
     }  // else if
     else if ( memofindex -> tokentype == SYMBOL ) {
       ParaNode* target = Isinparatable( memofindex -> tokenname ) ;
       int errorindex = index ;
       if ( target == NULL ) {
            mtreetool.Deletetree( endstmt ) ;
            mtreetool.Deletetree( paranode ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = target -> root ;
            index++ ;
          } // else 
     } // else if
     else { // atom
       paranode = Getanparatree( index ) ;
     } // else 

     if ( paranode -> type == ERROR ) {
       TreeNode* errornode = new TreeNode ;
       errormessageisbuild = true ;
       errornode -> name = "ERROR (non-list) : " ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       Constructerrormessagetokengroup( errornonlistindex ) ;
       return errornode ;
     } // if
     else 
       endstmt = Getanparatree( index ) ;

     if ( endstmt -> type != END ) {
       mtreetool.Deletetree( endstmt ) ;
       mtreetool.Deletetree( paranode ) ;
       TreeNode* errornode = new TreeNode ;
       errornode -> name = "ERROR (incorrect number of arguments) : symbol?" ;
       errormessageisbuild = true ;
       errornode -> type = ERROR ;
       errornode -> left = NULL ;
       errornode -> right = NULL ;
       return errornode ;
     } // if
     else if ( paranode -> left == NULL && paranode -> right == NULL && 
               paranode -> type == SYMBOL  ) {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "#t" ;
       returntree -> type = T ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else if
     else {
       TreeNode* returntree = new TreeNode ;
       isasinglenode = true ;
       returntree -> name = "NIL" ;
       returntree -> type = NIL ;
       returntree -> left = NULL ;
       returntree -> right = NULL ;
       return returntree ;
     } // else
  } // IsSymbol()

  void Computeadd( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    stringstream ss ;
    int resulttype = 0 ;
    if ( str1 -> type == INT && str2 -> type == INT ) {
      int a = transfer.Strtoint( str1 -> name ) ;
      int b = transfer.Strtoint( str2 -> name ) ;
      resulttype = INT ;
      int sum = a + b ;
      ss << sum ;
    } // if
    else {
      resulttype = FLOAT ;
      if ( str1 -> type == FLOAT && str2 -> type == INT ) {
        float a = transfer.Strtof( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        float sum = a + b ;
        ss << sum ;
      } // if
      else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a + b ;
        ss << sum ;
      } // else if
      else {
        float a = transfer.Strtof( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a + b ;
        ss << sum ;
      } // else
    } // else 
    
    treenode -> name = ss.str() ;
    treenode -> type = resulttype ;
    treenode -> left = NULL ;
    treenode -> right = NULL ;
  } // computeadd

  TreeNode* Add( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (+ with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = new TreeNode ;
          root -> name = "0" ;
          root -> type = INT ;
          root -> left = NULL ;
          root -> right = NULL ;
        } // if

        Computeadd( root, paranode, root ) ;
        mtreetool.Deletetree( paranode ) ;
      } // else
    } // while

  } // Add()

  void Computesubtraction( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    stringstream ss ;
    int resulttype = 0 ;
    if ( str1 -> type == INT && str2 -> type == INT ) {
      int a = transfer.Strtoint( str1 -> name ) ;
      int b = transfer.Strtoint( str2 -> name ) ;
      resulttype = INT ;
      int sum = a - b ;
      ss << sum ;
    } // if
    else {
      resulttype = FLOAT ;
      if ( str1 -> type == FLOAT && str2 -> type == INT ) {
        float a = transfer.Strtof( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        float sum = a - b ;
        ss << sum ;
      } // if
      else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a - b ;
        ss << sum ;
      } // else if
      else {
        float a = transfer.Strtof( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a - b ;
        ss << sum ;
      } // else
    } // else 
    
    treenode -> name = ss.str() ;
    treenode -> type = resulttype ;
    treenode -> left = NULL ;
    treenode -> right = NULL ;
  } // computesubtraction

  TreeNode* Subtraction( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (- with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = new TreeNode ;
          root -> name = "0" ;
          root -> type = INT ;
          root -> left = NULL ;
          root -> right = NULL ;
          Computesubtraction( paranode, root ,root ) ;
        } // if
        else 
          Computesubtraction( root, paranode, root ) ;

        mtreetool.Deletetree( paranode ) ;
      } // else

    } // while

  } // subtraction()

  void Computemul( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    stringstream ss ;
    int resulttype = 0 ;
    if ( str1 -> type == INT && str2 -> type == INT ) {
      int a = transfer.Strtoint( str1 -> name ) ;
      int b = transfer.Strtoint( str2 -> name ) ;
      resulttype = INT ;
      int sum = a * b ;
      ss << sum ;
    } // if
    else {
      resulttype = FLOAT ;
      if ( str1 -> type == FLOAT && str2 -> type == INT ) {
        float a = transfer.Strtof( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        float sum = a * b ;
        ss << sum ;
      } // if
      else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a * b ;
        ss << sum ;
      } // else if
      else {
        float a = transfer.Strtof( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a * b ;
        ss << sum ;
      } // else
    } // else 
    
    treenode -> name = ss.str() ;
    treenode -> type = resulttype ;
    treenode -> left = NULL ;
    treenode -> right = NULL ;
  } // computemul

  TreeNode* Mul( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (- with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = new TreeNode ;
          root -> name = "1" ;
          root -> type = INT ;
          root -> left = NULL ;
          root -> right = NULL ;
          Computemul( paranode, root ,root ) ;
        } // if
        else 
          Computemul( root, paranode, root ) ;

        mtreetool.Deletetree( paranode ) ;
      } // else
    } // while
  } // Mul()

  void Computedvision( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    stringstream ss ;
    int resulttype = 0 ;
    if ( str1 -> type == INT && str2 -> type == INT ) {
      int a = transfer.Strtoint( str1 -> name ) ;
      int b = transfer.Strtoint( str2 -> name ) ;
      resulttype = INT ;
      int sum = a / b ;
      ss << sum ;
    } // if
    else {
      resulttype = FLOAT ;
      if ( str1 -> type == FLOAT && str2 -> type == INT ) {
        float a = transfer.Strtof( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        float sum = a / b ;
        ss << sum ;
      } // if
      else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a / b ;
        ss << sum ;
      } // else if
      else {
        float a = transfer.Strtof( str1 -> name ) ;
        float b = transfer.Strtof( str2 -> name ) ;
        float sum = a / b ;
        ss << sum ;
      } // else
    } // else 
    
    treenode -> name = ss.str() ;
    treenode -> type = resulttype ;
    treenode -> left = NULL ;
    treenode -> right = NULL ;
  } // computedvision

  TreeNode* Dvision( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (- with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = new TreeNode ;
          root -> name = "1" ;
          root -> type = INT ;
          root -> left = NULL ;
          root -> right = NULL ;
          Computedvision( paranode, root ,root ) ;
        } // if
        else 
          Computedvision( root, paranode, root ) ;

        mtreetool.Deletetree( paranode ) ;
      } // else
    } // while
  } // Dvision()

  void Computeisbigger( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> type == INT && str2 -> type == INT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        if ( a > b )
          bigger = true ; 
      } // if
      else {
        if ( str1 -> type == FLOAT && str2 -> type == INT ) {
          float a = transfer.Strtof( str1 -> name ) ;
          int b = transfer.Strtoint( str2 -> name ) ;
          if ( a > b )
            bigger = true ;
        } // if
        else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
          int a = transfer.Strtoint( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a > b )
            bigger = true ;
        } // else if
        else {
          float a = transfer.Strtof( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a > b )
            bigger = true ;
        } // else
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computeisbigger

  TreeNode* Isbigger( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (> with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computeisbigger( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else 
      } // else
    } // while
  } // Isbigger()

  void Computeisbiggerequal( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> type == INT && str2 -> type == INT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        if ( a >= b )
          bigger = true ; 
      } // if
      else {
        if ( str1 -> type == FLOAT && str2 -> type == INT ) {
          float a = transfer.Strtof( str1 -> name ) ;
          int b = transfer.Strtoint( str2 -> name ) ;
          if ( a >= b )
            bigger = true ;
        } // if
        else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
          int a = transfer.Strtoint( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a >= b )
            bigger = true ;
        } // else if
        else {
          float a = transfer.Strtof( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a >= b )
            bigger = true ;
        } // else
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computeisbiggerequal

  TreeNode* Isbiggerequal( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (>= with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computeisbiggerequal( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isbiggerequal()

  void Computeissmaller( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> type == INT && str2 -> type == INT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        if ( a < b )
          bigger = true ; 
      } // if
      else {
        if ( str1 -> type == FLOAT && str2 -> type == INT ) {
          float a = transfer.Strtof( str1 -> name ) ;
          int b = transfer.Strtoint( str2 -> name ) ;
          if ( a < b )
            bigger = true ;
        } // if
        else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
          int a = transfer.Strtoint( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a < b )
            bigger = true ;
        } // else if
        else {
          float a = transfer.Strtof( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a < b )
            bigger = true ;
        } // else
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computeissmaller

  TreeNode* Issmaller( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (< with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computeissmaller( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Issmaller()

  void Computeissmallerequal( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> type == INT && str2 -> type == INT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        if ( a <= b )
          bigger = true ; 
      } // if
      else {
        if ( str1 -> type == FLOAT && str2 -> type == INT ) {
          float a = transfer.Strtof( str1 -> name ) ;
          int b = transfer.Strtoint( str2 -> name ) ;
          if ( a <= b )
            bigger = true ;
        } // if
        else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
          int a = transfer.Strtoint( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a <= b )
            bigger = true ;
        } // else if
        else {
          float a = transfer.Strtof( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a <= b )
            bigger = true ;
        } // else
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computeissmallerequal

  TreeNode* Issmallerequal( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (>= with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computeissmallerequal( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Issmallerequal()

  void Computeisnumequal( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> type == INT && str2 -> type == INT ) {
        int a = transfer.Strtoint( str1 -> name ) ;
        int b = transfer.Strtoint( str2 -> name ) ;
        if ( a == b )
          bigger = true ; 
      } // if
      else {
        if ( str1 -> type == FLOAT && str2 -> type == INT ) {
          float a = transfer.Strtof( str1 -> name ) ;
          int b = transfer.Strtoint( str2 -> name ) ;
          if ( a == b )
            bigger = true ;
        } // if
        else if ( str1 -> type == INT && str2 -> type == FLOAT ) {
          int a = transfer.Strtoint( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a == b )
            bigger = true ;
        } // else if
        else {
          float a = transfer.Strtof( str1 -> name ) ;
          float b = transfer.Strtof( str2 -> name ) ;
          if ( a == b )
            bigger = true ;
        } // else
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computeisnumequal

  TreeNode* Isnumequal( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == INT || type == FLOAT ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != INT && paranode -> type != FLOAT ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (>= with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computeisnumequal( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isnumequal()

  void Computestringappend( TreeNode* str1, TreeNode* str2 ) {
    str1 -> name += str2 -> name ;
    str2 -> name = "" ;
  } // Computestringappend()

  TreeNode* Isstringappend( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == STRING ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != STRING ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR ( string-append with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computestringappend( root, paranode ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isstringappend()

  void Computestringbigger( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> name > str2 -> name ) {
        bigger = true ;
      } // if
      else {
        bigger = false ;
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computestringbigger

  TreeNode* Isstringbigger( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == STRING ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != STRING ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR ( string>=? with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computestringbigger( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isstringbigger()

  void Computestringsmaller( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> name < str2 -> name ) {
        bigger = true ;
      } // if
      else {
        bigger = false ;
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computestringsmaller

  TreeNode* Isstringsmaller( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == STRING ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != STRING ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR ( string<=? with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computestringsmaller( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isstringsmaller()

  void Computestringequal( TreeNode* str1, TreeNode* str2, TreeNode* treenode ) {
    Transfer transfer ;
    bool bigger = false ;
    if ( treenode -> type != NIL ) {
      if ( str1 -> name == str2 -> name ) {
        bigger = true ;
      } // if
      else {
        bigger = false ;
      } // else 
      
      if ( bigger ) {
        treenode -> name = "T" ;
        treenode -> type = T ;
      } // if
      else {
        treenode -> name = "nil" ;
        treenode -> type = NIL ;
      } // else
  
      treenode -> left = NULL ;
      treenode -> right = NULL ;
    } // if
  } // computestringequal

  TreeNode* Isstringequal( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL ;
    InstructionNode* memofindex = NULL ;
    bool stop = false ; 
    TreeNode* lastmaketree = NULL ; 
    TreeNode* root = NULL ;
    int errorstindex = index ;
    while ( stop != true ) { 
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        index++ ;
        return root ; // stop = true
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          int type =  memofindex -> tokentype ;
          if ( type == STRING ) {
            paranode = Getanparatree( index ) ;
          } // if
          else {
            mtreetool.Deletetree( root ) ;
            TreeNode* errornode = new TreeNode ;
            errormessageisbuild = true ;
            errornode -> name = "ERROR (non-list) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( errornonlistindex ) ;
            return errornode ;
          } // else
        } // else
      } // else 

      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
      else if ( paranode -> type != STRING ) {
        mtreetool.Deletetree( paranode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (string=? with incorrect argument type) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        isasinglenode = true ;
        if ( root == NULL ) {
          root = paranode ;
        } // if
        else {
          Computestringequal( root, paranode, root ) ;
          mtreetool.Deletetree( paranode ) ;
        } // else
      } // else
    } // while
  } // Isstringequal()

  TreeNode* Computenot( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL, *endstmt = NULL ;
    InstructionNode* memofindex = NULL ;
    int errorstindex = index ;
    memofindex = mtokenlinklist.Access( index ) ;
    if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      paranode = Run( index, isasinglenode ) ;
      if ( paranode -> type == ERROR ) {
        return paranode ;
      } // if
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      paranode = Getanparatree( index ) ;
    }  // else if
    else { // atom
      int unbounderrorindex = index ;
      errorstindex = index ;
      if ( memofindex -> tokentype == SYMBOL ) {
        ParaNode* targetpara = NULL ;
        targetpara = Isinparatable( memofindex -> tokenname ) ;
        if ( targetpara == NULL ) {
          TreeNode* errornode = new TreeNode ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( unbounderrorindex ) ;
          errormessageisbuild = true ;
          return errornode ;
        } // if
        else {
          paranode = targetpara -> root ;
          index++ ;
        } // else 
      } // if
      else {
        paranode = Getanparatree( index ) ;
      } // else
    } // else 

    endstmt = Getanparatree( index ) ;
    if ( endstmt -> type != END ) {
      mtreetool.Deletetree( paranode ) ;
      mtreetool.Deletetree( endstmt ) ;
      TreeNode* errornode = new TreeNode ;
      errormessageisbuild = true ;
      if ( endstmt -> type != ERROR ) { 
        errornode -> name = "ERROR (incorrect number of arguments) : not" ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
      } // if
      else {
        errornode -> name = "ERROR (non-list) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( errornonlistindex ) ;
      } // else 

      return errornode ;
    } // if
    else { // correct
      isasinglenode = true ;
      if ( paranode -> type == NIL ) {
        paranode -> name = "#t" ;
        paranode -> type = T ;
      }  // if
      else {
        paranode -> name = "nil" ;
        paranode -> type = NIL ;
      } // else

      return paranode ;
    } // else 
  } // Computenot()

  TreeNode* Computeand( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL, *root = NULL ;
    InstructionNode* memofindex = NULL ;
    int errorstindex = index ;
    while ( true ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
        if ( paranode -> type == ERROR ) {
          return paranode ;
        } // if
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        return root ;
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          paranode = Getanparatree( index ) ;
        } // else
      } // else 

      if ( paranode -> type == NIL ) {
        isasinglenode = true ;
        return paranode ;
      } // else if
      else { // correct
        mtreetool.Deletetree( root ) ;
        root = NULL ;
        root = paranode ;
        if ( root -> left == NULL && root -> right == NULL )
          isasinglenode = true ;
        else 
          isasinglenode = false ;
      } // else
    } // while 
  } // Computeand()

  TreeNode* Computeor( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* paranode = NULL, *root = NULL ;
    InstructionNode* memofindex = NULL ;
    int errorstindex = index ;
    while ( true ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        paranode = Run( index, isasinglenode ) ;
        if ( paranode -> type == ERROR ) {
          return paranode ;
        } // if
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        paranode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        return root ;
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            paranode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          paranode = Getanparatree( index ) ;
        } // else
      } // else 

      if ( paranode -> type != NIL ) {
        if ( paranode -> left == NULL && paranode -> right == NULL )
          isasinglenode = true ;
        else 
          isasinglenode = false ;

        return paranode ;
      } // else if
      else { // correct
        mtreetool.Deletetree( root ) ;
        root = paranode ;
        if ( root -> left == NULL && root -> right == NULL )
          isasinglenode = true ;
        else 
          isasinglenode = false ;
      } // else
    } // while 
  } // Computeor()

  TreeNode* Comparetwoparawitheqv( TreeNode* para1, TreeNode* para2 ) {
    Transfer transfer ;
    int type1 = para1 -> type ;
    int type2 = para2 -> type ;
    bool isequal = false ;
    if( type1 == type2 && type1 == INT ) {
      int num1 = transfer.Strtoint( para1 -> name ) ;
      int num2 = transfer.Strtoint( para2 -> name ) ;
      if ( num1 == num2 )
        isequal = true ;
    } // if
    else if ( type1 == type2 && type1 == FLOAT ) {
      int float1 = transfer.Strtof( para1 -> name ) ;
      int float2 = transfer.Strtof( para2 -> name ) ;
      if ( float1 == float2 )
        isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == T ) {
      isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == NIL ) {
      isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == TREE ) {
      if ( para1 == para2 )
        isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == SYMBOL ) {
      if ( para1 == para2 )
        isequal = true ;
    } // else if
    else {
      isequal = false ;
    } // else 
      
    TreeNode* result = new TreeNode ;
    result -> left = NULL ;
    result -> right = NULL ;
    if ( isequal ) {
      result -> name = "#t" ;
      result -> type = T ;
    } // if
    else {
      result -> name = "nil" ;
      result -> type = NIL ;
    } // else

    return result ;
  } // Comparetwoparawitheqv

  TreeNode* Findcomparepara( string str, int &index ) {
    ParaNode* boundvar = NULL ;
    boundvar = Findreallocinparatable( str ) ;
    if ( boundvar != NULL ) {
      index++ ;
      return boundvar -> root ;
    } // if
    else {
      if ( mtable.Isreservedword( str ) ) {
        index++ ;
        return Findreservewordtree( str ) ;
      } // if
      else {
        TreeNode* errornode = new TreeNode ;
        errornode -> type = ERROR ;
        errornode -> name = "ERROR (unbound symbol) : " ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( index ) ;
        return errornode ;
      } // else
    } // else
  } // Findcomparepara

  TreeNode* Computeeqv( int &index, bool &isasinglenode ) {
    int errorstindex = index - 1 ;
    index ++ ;
    TreeNode* returntree = NULL ;
    TreeNode* para1 = NULL, *endstmt = NULL ; 
    // ( cons a b ) <- index to deal this ")" anf index pointer to next para
    TreeNode* para2 = NULL ;
    bool errorocurredonpara1 = false ;
    bool para1canbedelete = true , para2canbedelete = true ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      para1 = Getanparatree( index ) ; 
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      para1 = Run( index, isasinglenode ) ; // ( cons ( cons 7 b ) a )
      if ( para1 -> type == ERROR ) {
        return para1 ;
      } // if
    } // else if
    else {
      if ( memofindex -> tokentype == SYMBOL ) {
        para1canbedelete = false ;
        para1 = Findcomparepara(  memofindex -> tokenname, index ) ;
        if ( para1 -> type == ERROR ) 
          errorocurredonpara1 = true ;
      } // if
      else {
        para1 = Getanparatree( index ) ;
      } // else
    } // else
    
    if ( para1 -> type != ERROR && para1 -> type != HOLLOW ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index ++ ;
        para2 = Getanparatree( index ) ;
        endstmt = Getanparatree( index ) ; // -> ) 
      } // if
      else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        para2 = Run( index, isasinglenode ) ;
        if ( para2 -> type == ERROR ) {
          return para2 ;
        } // if

        endstmt = Getanparatree( index ) ;
      } // else if
      else {
        ParaNode* boundvar = NULL ;
        if ( memofindex -> tokentype == SYMBOL ) {
          para2canbedelete = false ;
          para2 = Findcomparepara(  memofindex -> tokenname, index ) ;
          endstmt = Getanparatree( index ) ;
        } // if
        else {
          para2 = Getanparatree( index ) ;
          endstmt = Getanparatree( index ) ;
        } // else
      } // else 
    } // if
    else {
      para2 = new TreeNode ;
      para2 -> type == ERROR ;
    } // esle

    
    if ( para1 -> type != ERROR  && para2 -> type != ERROR &&
         para1 -> type != HOLLOW  && para2 -> type != HOLLOW && 
         endstmt -> type == END ) { // all correct 
      //  cout << " run correct eqv? : 5648" << endl ; 
       returntree = Comparetwoparawitheqv( para1, para2 ) ;
       isasinglenode = true ;
       if ( para1canbedelete )
         mtreetool.Deletetree( para1 ) ;
       if ( para2canbedelete ) 
         mtreetool.Deletetree( para2 ) ;
        
       mtreetool.Deletetree( endstmt ) ;
       return returntree ;
    } // if
    else { 
      if ( errormessageisbuild == false ) { 
        // check nonlist -> check incorrect number of arguments
        returntree = new TreeNode ;
        returntree -> type = ERROR ;
        returntree -> left = NULL ;
        returntree -> right = NULL ;
        if ( para1 -> type == ERROR || para2 -> type == ERROR ) {
          returntree -> name = "ERROR (non-list) : " ; // construct errormessagetokengroup
          Constructerrormessagetokengroup( errorstindex ) ;
        } // if
        else { // ( para1 -> type == HOLLOW || para2 -> type == HOLLOW || para3 -> type != END )
          // incorrect number of arguments
          returntree -> name = "ERROR (incorrect number of arguments) : eqv?" ;
        } // else
      
        if ( para1canbedelete )
          mtreetool.Deletetree( para1 ) ;
        if ( para2canbedelete ) 
          mtreetool.Deletetree( para2 ) ;

        errormessageisbuild = true ;
        isasinglenode = true ;
        return returntree ;
      } // if
      else { // a error in deep sexp and error is constructored
        if ( errorocurredonpara1 ) {
          if ( para2canbedelete )
            mtreetool.Deletetree( para2 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para1 ;
        } // if
        else {
          if ( para1canbedelete )
            mtreetool.Deletetree( para1 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para2 ;
        } //else
      } // else 


    } // else 
  } // Computeeqv()

  int Istwotreequal( TreeNode* para1, TreeNode* para2 ) {
    /*1. both empty */
    if ( para1 == NULL && para2 == NULL)
        return 1 ;
 
    /* 2. both non-empty -> compare them */
    if ( para1 != NULL && para2 != NULL) {
        return (  ( para1 -> name == para2 -> name && para1 -> type == para2 -> type )
                && Istwotreequal( para1 -> left, para2 -> left )
                && Istwotreequal( para1 -> right, para2 -> right ) );
    }
 
    /* 3. one empty, one not -> false */
    return 0 ;

  } // istwotreequal

  TreeNode* Comparetwoparawithequal( TreeNode* para1, TreeNode* para2 ) {
    Transfer transfer ;
    int type1 = para1 -> type ;
    int type2 = para2 -> type ;
    bool isequal = false ;
    if( type1 == type2 && type1 == INT ) {
      int num1 = transfer.Strtoint( para1 -> name ) ;
      int num2 = transfer.Strtoint( para2 -> name ) ;
      if ( num1 == num2 )
        isequal = true ;
    } // if
    else if ( type1 == type2 && type1 == FLOAT ) {
      int float1 = transfer.Strtof( para1 -> name ) ;
      int float2 = transfer.Strtof( para2 -> name ) ;
      if ( float1 == float2 )
        isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == T ) {
      isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == NIL ) {
      isequal = true ;
    } // else if
    else if ( type1 == type2 && type1 == TREE ) {
        if ( Istwotreequal( para1, para2 ) )
          isequal = true ;
    } // else if
    else {
      isequal = false ;
    } // else 
      
    TreeNode* result = new TreeNode ;
    result -> left = NULL ;
    result -> right = NULL ;
    if ( isequal ) {
      result -> name = "#t" ;
      result -> type = T ;
    } // if
    else {
      result -> name = "NIL" ;
      result -> type = NIL ;
    } // else

    return result ;
  } // Comparetwoparawithequal

  TreeNode* Computeequal( int &index, bool &isasinglenode ) {
    int errorstindex = index - 1 ;
    index ++ ;
    TreeNode* returntree = NULL ;
    TreeNode* para1 = NULL, * endstmt = NULL ; 
    // ( cons a b ) <- index to deal this ")" anf index pointer to next para
    TreeNode* para2 = NULL ;
    bool errorocurredonpara1 = false ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      para1 = Getanparatree( index ) ; 
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      para1 = Run( index, isasinglenode ) ; // ( cons ( cons 7 b ) a )
    } // else if
    else {
      ParaNode* boundvar = NULL ;
      if ( memofindex -> tokentype == SYMBOL ) {
        boundvar = Isinparatable( memofindex -> tokenname ) ;
        if ( boundvar != NULL ) {
          para1 = boundvar -> root ;
          index++ ;
        } // if
        else {
          TreeNode* errornode = new TreeNode ;
          errornode -> type = ERROR ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          errorocurredonpara1 = true ;
          Constructerrormessagetokengroup( index ) ;
          return errornode ;
        } // else 
      } // if
      else {
        para1 = Getanparatree( index ) ;
      } // else
    } // else
    
    if ( para1 -> type != ERROR && para1 -> type != HOLLOW ) {
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index ++ ;
        para2 = Getanparatree( index ) ;
        endstmt = Getanparatree( index ) ; // -> ) 
      } // if
      else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        para2 = Run( index, isasinglenode ) ;
        endstmt = Getanparatree( index ) ;
      } // else if
      else {
        ParaNode* boundvar = NULL ;
        if ( memofindex -> tokentype == SYMBOL ) {
          boundvar = Isinparatable( memofindex -> tokenname ) ;
          if ( boundvar != NULL ) {
            para2 = boundvar -> root ;
            index++ ;
            endstmt = Getanparatree( index ) ;
          } // if
          else {
            TreeNode* errornode = new TreeNode ;
            errornode -> type = ERROR ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            errorocurredonpara1 = true ;
            Constructerrormessagetokengroup( index ) ;
            return errornode ;
          } // else 
        } // if
        else {
          para2 = Getanparatree( index ) ;
          endstmt = Getanparatree( index ) ;
        } // else
      } // else 
    } // if
    else {
      para2 = new TreeNode ;
      para2 -> type = ERROR ;
      para2 -> name = "ERROR" ;
      para2 -> left = NULL ;
      para2 -> right = NULL ;
      errorocurredonpara1 = true ;
    } // else 

    if ( para1 -> type != ERROR  && para2 -> type != ERROR &&
         para1 -> type != HOLLOW  && para2 -> type != HOLLOW && 
         endstmt -> type == END ) { // all correct 
       returntree = Comparetwoparawithequal( para1, para2 ) ;
       isasinglenode = true ;
       mtreetool.Deletetree( para1 ) ;
       mtreetool.Deletetree( para2 ) ;
       mtreetool.Deletetree( endstmt ) ;
       return returntree ;
    } // if
    else { 
      if ( errormessageisbuild == false ) { 
        // check nonlist -> check incorrect number of arguments
        TreeNode* errornode = new TreeNode ;
        if ( para1 -> type == ERROR || para2 -> type == ERROR ) {
          errornode -> name = "ERROR (non-list) : " ; // construct errormessagetokengroup
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( errorstindex ) ;
        } // if
        else { // ( para1 -> type == HOLLOW || para2 -> type == HOLLOW || para3 -> type != END )
          // incorrect number of arguments
          errornode -> name = "ERROR (incorrect number of arguments) : cons" ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
        } // else
      
        errormessageisbuild = true ;
        isasinglenode = true ;
         mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( para2 ) ;
        mtreetool.Deletetree( endstmt ) ;
        return errornode ;
      } // if
      else { // a error in deep sexp and error is constructored
        if ( errorocurredonpara1 ) {
          mtreetool.Deletetree( para2 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para1 ;
        } // if
        else {
          mtreetool.Deletetree( para1 ) ;
          mtreetool.Deletetree( endstmt ) ;
          return para2 ;
        } //else
      } // else 
    } // else 

  } // Computeequal()

  TreeNode* Stmtget( int &index, bool &isasinglenode ) {
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* stmt = NULL ;
    if ( memofindex == NULL || 
       ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) ) {
      stmt = new TreeNode ;
      stmt -> name = "end" ;
      stmt -> type = END ;
      stmt -> left = NULL ;
      stmt -> right = NULL ;
      return stmt ;
    } // if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index ++ ;
      return Getanparatree( index ) ;
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      return Run( index, isasinglenode ) ;
    } // else if
    else { // stmt part
      ParaNode* boundvar = NULL ;
      if ( memofindex -> tokentype == SYMBOL ) {
        boundvar = Isinparatable( memofindex -> tokenname ) ;
        if ( boundvar != NULL ) {
          stmt = boundvar -> root ;
          index++ ;
        } // if
        else {
          TreeNode* errornode = new TreeNode ;
          errornode -> type = ERROR ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( index ) ;
          return errornode ;
        } // else 
      } // if
      else 
        stmt = Getanparatree( index ) ;

      return stmt ;
    } // else
  } // Stmtget()

  TreeNode* Computeif( int &index, bool &isasinglenode ) {
    int errorstindex = index - 1 ;
    index ++ ;
    TreeNode* para1 = NULL, * endstmt = NULL ; 
    // ( cons a b ) <- index to deal this ")" anf index pointer to next para
    TreeNode* truestmt = NULL, *falsestmt = NULL ;
    int narg = 0 ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      index++ ;
      para1 = Getanparatree( index ) ; 
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
      index++ ;
      para1 = Run( index, isasinglenode ) ; // ( cons ( cons 7 b ) a )
      if ( para1 -> type == ERROR ) {
        return para1 ;
      } // if
    } // else if
    else {
      ParaNode* boundvar = NULL ;
      if ( memofindex -> tokentype == SYMBOL ) {
        boundvar = Isinparatable( memofindex -> tokenname ) ;
        if ( boundvar != NULL ) {
          para1 = boundvar -> root ;
          index++ ;
        } // if
        else {
          TreeNode* errornode = new TreeNode ;
          errornode -> type = ERROR ;
          errornode -> name = "ERROR (unbound symbol) : " ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          Constructerrormessagetokengroup( index ) ;
          return errornode ;
        } // else 
      } // if
      else {
        para1 = Getanparatree( index ) ;
      } // else
    } // else
    
    narg++ ;
    truestmt = Stmtget( index, isasinglenode ) ;
    if ( truestmt -> type == ERROR ) {
      return truestmt ;
    } // if
    else 
      narg++ ;

    falsestmt = Stmtget( index, isasinglenode ) ;
    if ( falsestmt -> type == ERROR ) {
      return truestmt ;
    } // if
    else if ( falsestmt -> type != END ) {
      narg++ ;
    } // else if

    endstmt = Stmtget( index, isasinglenode ) ;

    if ( narg == 2 ) {
      if ( para1 -> type == T ) {
        if ( truestmt -> left == NULL && truestmt -> right == NULL ) 
          isasinglenode = true ;
        else
          isasinglenode = false ;  

        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( falsestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        return truestmt ;
      } // if
      else if ( para1 -> type == NIL ) { // no return value
        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( truestmt ) ;
        mtreetool.Deletetree( falsestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (no return value) : " ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else if
      else {
        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( truestmt ) ;
        mtreetool.Deletetree( falsestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (if with incorrect argument type) : " ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else 
    } // if
    else if ( narg == 3 ) { 
      if ( para1 -> type == T ) {
        if ( truestmt -> left == NULL && truestmt -> right == NULL ) 
          isasinglenode = true ;
        else
          isasinglenode = false ;  

        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( falsestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        return truestmt ;
      } // if
      else if ( para1 -> type == NIL ) { // no return value
        if ( falsestmt -> left == NULL && falsestmt -> right == NULL ) 
          isasinglenode = true ;
        else
          isasinglenode = false ;  

        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( truestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        return falsestmt ;
      } // else if
      else {
        mtreetool.Deletetree( para1 ) ;
        mtreetool.Deletetree( truestmt ) ;
        mtreetool.Deletetree( falsestmt ) ;
        mtreetool.Deletetree( endstmt ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (if with incorrect argument type) : " ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        Constructerrormessagetokengroup( errorstindex ) ;
        return errornode ;
      } // else 
    } // else
    else {
      mtreetool.Deletetree( para1 ) ;
      mtreetool.Deletetree( truestmt ) ;
      mtreetool.Deletetree( falsestmt ) ;
      mtreetool.Deletetree( endstmt ) ;
      TreeNode* errornode = new TreeNode ;
      errornode -> name = "ERROR (incorrect number of arguments) : if" ;
      errornode -> left = NULL ;
      errornode -> right = NULL ;
      isasinglenode = true ;
      return errornode ;
    }  // else   

  } // Computeif()

  TreeNode* Computecond( int &index, bool &isasinglenode ) {
    int errornonlistindex = index - 1 ;
    index++ ;
    TreeNode* condnode = NULL ;
    InstructionNode* memofindex = NULL ;
    int errorstindex = index ;
    while ( true ) { // ( cond ( p1 e1 ) ( p2 e2 ) )
      index++ ; // -> pi
      memofindex = mtokenlinklist.Access( index ) ;
      if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN ) {
        index++ ;
        condnode = Run( index, isasinglenode ) ;
        if ( condnode -> type == ERROR ) {
          return condnode ;
        } // if
      } // if
      else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
        index++ ;
        condnode = Getanparatree( index ) ;
      }  // else if
      else if ( memofindex -> tokenname == ")" && memofindex -> tokentype == RIGHT_PAREN ) {
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (no return value) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errornonlistindex ) ;
      } // else if
      else { // atom
        int unbounderrorindex = index ;
        errorstindex = index ;
        if ( memofindex -> tokentype == SYMBOL ) {
          ParaNode* targetpara = NULL ;
          targetpara = Isinparatable( memofindex -> tokenname ) ;
          if ( targetpara == NULL ) {
            TreeNode* errornode = new TreeNode ;
            errornode -> name = "ERROR (unbound symbol) : " ;
            errornode -> type = ERROR ;
            errornode -> left = NULL ;
            errornode -> right = NULL ;
            Constructerrormessagetokengroup( unbounderrorindex ) ;
            errormessageisbuild = true ;
            return errornode ;
          } // if
          else {
            condnode = targetpara -> root ;
            index++ ;
          } // else 
        } // if
        else {
          condnode = Getanparatree( index ) ;
        } // else
      } // else 

      if ( condnode -> type == T ) { // run ei
        TreeNode* truestmt = Stmtget( index, isasinglenode ) ;
        if ( truestmt -> left == NULL && truestmt -> right == NULL ) 
          isasinglenode = true ;
        else 
          isasinglenode = false ;

        mtreetool.Deletetree( condnode ) ;
        return truestmt ;
      } // if
      else if ( condnode -> type == NIL ) { 
        mtreetool.Deletetree( condnode ) ;
        isasinglenode = true ;
      } // else if
      else {
        mtreetool.Deletetree( condnode ) ;
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (COND format) : " ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        Constructerrormessagetokengroup( errornonlistindex ) ;
        return errornode ;
      } // else
    } // while
  } // Computecond()

  TreeNode* Run( int &index, bool &isasinglenode ) {
    levelcall++ ;
    InstructionNode* memofindex = mtokenlinklist.Access( index ) ;
    TreeNode* result = NULL ;
    if ( memofindex == NULL ) {
       return NULL ;
    } // if
    else if ( memofindex -> tokenname == "(" && memofindex -> tokentype == LEFT_PAREN  ) {
      index ++ ;
      levelcall-- ;
      result = Run( index, isasinglenode ) ;
    } // if
    else if ( memofindex -> tokenname == "cons" && memofindex -> tokentype == SYMBOL ) {
      result = Cons( index, isasinglenode ) ;
    } // if
    else if ( memofindex -> tokenname == "car" && memofindex -> tokentype == SYMBOL ) {
      result = Car( index, isasinglenode ) ;
    } // else if 
    else if ( memofindex -> tokenname == "cdr" && memofindex -> tokentype == SYMBOL ) {
      result = Cdr( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "quote" && memofindex -> tokentype == QUOTE ) {
      result = Quote( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "define" && memofindex -> tokentype == SYMBOL ) {
      if ( levelcall != 1 ) {
        TreeNode* errornode = new TreeNode ;
        errornode -> name = " error not top" ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        return errornode ;
      } // if
      else
        result = Define( index , isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "clean-environment" && memofindex -> tokentype == SYMBOL ) {
      if ( levelcall != 1 ) {
        TreeNode* errornode = new TreeNode ;
        errornode -> name = " error not top" ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        return errornode ;
      } // if
      else 
        result = CleanENV( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "list" && memofindex -> tokentype == SYMBOL ) {
      result = List( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "atom?" && memofindex -> tokentype == SYMBOL ) {
      result = IsAtom( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "pair?" && memofindex -> tokentype == SYMBOL ) {
      result = IsPair( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "integer?" && memofindex -> tokentype == SYMBOL ) {
      result = IsINT( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "real?" && memofindex -> tokentype == SYMBOL ) {
      result = IsReal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "string?" && memofindex-> tokentype == SYMBOL ) {
      result = IsString( index, isasinglenode ) ;
    } // else if 
    else if ( memofindex -> tokenname == "number?" && memofindex -> tokentype == SYMBOL ) {
      result = IsNumber( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "boolean?" && memofindex -> tokentype == SYMBOL ) {
      result = IsBool( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "symbol?" && memofindex -> tokentype == SYMBOL ) {
      result = IsSymbol( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "+" && memofindex -> tokentype == SYMBOL ) {
      result = Add( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "-" && memofindex -> tokentype == SYMBOL ) {
      result = Subtraction( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "*" && memofindex -> tokentype == SYMBOL ) {
      result = Mul( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "/" && memofindex -> tokentype == SYMBOL ) {
      result = Dvision( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == ">" && memofindex -> tokentype == SYMBOL ) {
      result = Isbigger( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == ">=" && memofindex -> tokentype == SYMBOL ) {
      result = Isbiggerequal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "<" && memofindex -> tokentype == SYMBOL ) {
      result = Issmaller( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "<=" && memofindex -> tokentype == SYMBOL ) {
      result = Issmallerequal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "=" && memofindex -> tokentype == SYMBOL ) {
      result = Isnumequal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "string-append" && memofindex -> tokentype == SYMBOL ) {
      result = Isstringappend( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "string>?" && memofindex -> tokentype == SYMBOL ) {
      result = Isstringbigger( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "string<?" && memofindex -> tokentype == SYMBOL ) {
      result = Isstringsmaller( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "string=?" && memofindex -> tokentype == SYMBOL ) {
      result = Isstringequal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "not" && memofindex -> tokentype == SYMBOL ) {
      result = Computenot( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "and" && memofindex -> tokentype == SYMBOL ) {
      result = Computeand( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "or" && memofindex -> tokentype == SYMBOL ) {
      result = Computeor( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "eqv?" && memofindex -> tokentype == SYMBOL ) {
      result = Computeeqv( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "equal?" && memofindex -> tokentype == SYMBOL ) {
      result = Computeequal( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "if" && memofindex -> tokentype == SYMBOL ) {
      result = Computeif( index, isasinglenode ) ;
    } // else if
    else if ( memofindex -> tokenname == "cond" && memofindex -> tokentype == SYMBOL ) {
      result = Computecond( index, isasinglenode ) ;
    } // else if
    else {
      ParaNode* redefine = Isinparatable( memofindex -> tokenname ) ;
      if ( redefine != NULL ) {
        bool isredefineword = mtable.Isreservedword( redefine -> name ) ;
        if ( isredefineword ) {
          memofindex -> tokenname = redefine -> name ;
          levelcall-- ;
          result = Run( index, isasinglenode ) ;
        } // if
        else {
          TreeNode* errornode = new TreeNode ;
          errornode -> name = "ERROR (attempt to apply non-function) : " ;
          errornode -> name = errornode -> name + memofindex -> tokenname ;
          errornode -> type = ERROR ;
          errornode -> left = NULL ;
          errornode -> right = NULL ;
          errormessageisbuild = true ;
          return errornode ;
        } // else
      } // if
      else { 
        TreeNode* errornode = new TreeNode ;
        errornode -> name = "ERROR (attempt to apply non-function) : " ;
        errornode -> name = errornode -> name + memofindex -> tokenname ;
        errornode -> type = ERROR ;
        errornode -> left = NULL ;
        errornode -> right = NULL ;
        errormessageisbuild = true ;
        return errornode ;
      } // else
    } // else

    return result ;
  } // Run()

  void Printtokenlinklist( Vector tokengroup ) {
    cout << "tokenlinklist.size: " << tokengroup.Size() << endl ;
    InstructionNode *cur = tokengroup.mhead ;
    int i = 0 ;
    while ( cur != NULL ) {
      cout << cur->tokenname << "  " ;
      cout << cur->tokentype << "  " ;
      cout << cur->line << "  " ;
      cout << cur->column << " " ; 
      cout << cur->resetcolumn << endl ;
      cur = cur -> next ;
    } // while
  } // Printtokenlinklist()

} ; // Functionbehaviordefined

class Scaner {
  public :
  Scaner() { mtreeroot = NULL ; }

  ~Scaner() {
  } // ~Scaner()

  TreeNode * mtreeroot ;
  TokenTable mtable ;
  Syntax msyntax ;
  Functionbehaviordefined mfunctrun ;
  Treetool mtreetool ;
  Transfer transfer ;

  void Interpreter() {
    Vector tokengroupinput ;
    Vector tokenlinklist ;
    Vector tokenlinklist2 ;
    InstructionNode lastnode ;
    int syntaxstatus = - 1 ;
    int currentline = 1, recurrentline = 1 ;
    string projinput = "" ;
    bool sysstop = false ;
    char* str = new char[ 1000 ] ;
    cin.getline( str, 1000 ) ;
    gtestnum = str ;
    bool nextstop = false ;
    
    while ( sysstop != true ) {
      if ( syntaxstatus == NOTCOMPLETE && tokenlinklist2.Size() != 0 ) {
        lastnode =  Catchfirstnode( tokenlinklist, tokenlinklist2 ) ;
        // cout << "tokenlist :" << endl ;
        SpiltleftrightParan( tokenlinklist ) ;
        // Printtokenlinklist( tokenlinklist ) ;
        // cout << "tokenlinklist2 : " << endl ;
        // Printtokenlinklist( tokenlinklist2 ) ;
        msyntax.Reset() ;
        msyntax.Setsyntaxcheack( tokenlinklist ) ;
        syntaxstatus = msyntax.Syntaxforsexp() ;
        if ( syntaxstatus == COMPLETE ) {
          Mergestringstmt( tokenlinklist ) ;
        } // if
      } // if
      else if ( tokenlinklist.Size() == 0 || tokenlinklist2.Size() == 0 ) {
        if ( nextstop == false ) {
          projinput = "" ;
          tokengroupinput.Clear() ;
          tokenlinklist2.Clear() ;
          cout << "cin command line " << endl ;
          if ( !cin.getline( str, 1000 ) ) {
            nextstop = true ;
          } // if

          projinput = str ;
          // projinput = "( cons 5 6  )" ;
          projinput += " " ;
          cout << "proj :" << projinput << endl ;
          GetTokenGroup( tokengroupinput, projinput, currentline ) ;
          currentline++ ;
          syntaxstatus = Lexicalpraser( tokengroupinput, tokenlinklist2 ) ;
        } // if
        else {
          cout << "> ERROR (no more input) : END-OF-FILE encountered\n" ;
          sysstop = true ;
          syntaxstatus = NOTCOMPLETE ;
        } // else 
      } // else if

      if ( syntaxstatus == COMPLETE ) {
        recurrentline = currentline ;
        currentline = 1 ;
        ParaNode* paranode = NULL ;
        if ( tokenlinklist.Size() == 1 ) {
          Singlenodeprint( tokenlinklist ) ;
          tokenlinklist.Clear() ;
        } // if
        else {
          cout << " syntax correct " << endl ;
          Printtokenlinklist( tokenlinklist ) ;
          if ( Stopsys( tokenlinklist ) ) {
            cout << "> \n" ;
            sysstop = true ;
            return ;
          } // if
                                    // sysstop = true ; // important // important // important // important
          mfunctrun.Reset() ;
          int result_tempindex = 0 ;
          bool resultissingle = false ;
          mfunctrun.Settokenlinklist( tokenlinklist ) ;
          TreeNode* result = mfunctrun.Run( result_tempindex, resultissingle ) ;
          if ( mfunctrun.errormessageisbuild == true ) {
            cout << " run error " << endl ;
            cout << "> " << result -> name ;
            if ( mfunctrun.errorneedatree == true ) {
              if ( mfunctrun.errormessagetokengroup.Size() == 1 ) {
                cout << mfunctrun.errormessagetokengroup.Access( 0 ) -> tokenname << endl ;
              } // if
              else {
                mtreetool.TransferToTreestmt( mfunctrun.errormessagetokengroup ) ;
                TreeNode* errorroot = mtreetool.CreateTree( mfunctrun.errormessagetokengroup, 0, 
                                                  mfunctrun.errormessagetokengroup.Size() - 1 ) ;
                int spacenum = 2 ;
                bool prettyprint_temp = true ;
                cout << "( " ;
                Prettyprint( NULL, errorroot, spacenum, prettyprint_temp ) ;
                spacenum -= 2 ;
                Printspace( spacenum ) ;
                cout << ")\n" ;
              } // else 
            } // if
          }  // if
          else {
            cout << " print result tree for debug : " << endl ;
            Inorder( result ) ;
            cout << endl ;
  
            if ( resultissingle == false  ) { // result is a tree
              int spacenum = 2 ;
              bool prettyprint_temp = true ;
              cout << "> " ;
              cout << "( " ;
              Prettyprint( NULL, result, spacenum, prettyprint_temp ) ;
              spacenum -= 2 ;
              Printspace( spacenum ) ;
              cout << ")\n" ;
            } // if
            else { // result is a single node
              cout << "> " ;
              if ( result -> type == FLOAT ) {
                float floatnum = transfer.Strtof( result -> name ) ;
                printf( "%.3f\n", floatnum ) ;
              } // if
              else if ( result -> type == STRING ) {
                cout << "\"" << result -> name << "\"" << endl ;
              } // else if
              else if ( result -> type == INT ) { 
                // if ( cur -> name != "quote" && cur -> type != STRING )
                if ( result -> name != "quote" && result -> type != STRING ) 
                  cout << transfer.Strtoint( result -> name ) << endl ;
                else
                  cout << result -> name << endl ;
              } // else if
              else {
                cout << result -> name << endl ;
              } // else
            } // else 
          } // else  mfunctrun.errormessageisbuild 

          tokenlinklist.Clear() ;
          mtreetool.Deletetree( result ) ; 
        } // else

        if ( tokenlinklist2.Size() != 0 ) {
          // cout << "reset node line column " << endl ;        
          Resetcolumnforsameline( tokenlinklist2, lastnode ) ;
          syntaxstatus = NOTCOMPLETE ;
          currentline = 2 ;
        } // if

        cout << "\n" ;
      } // if
      else if ( syntaxstatus == ERRORSTMT ) {
        currentline = 1 ;
        tokengroupinput.Clear() ;
        tokenlinklist.Clear() ;
        tokenlinklist2.Clear() ;
      } // else if

      // cout << " ======= next turn ======  " << endl ;    
    } // while
  } // Interpreter()

  void Singlenodeprint( Vector tokenlinklist ) {
    InstructionNode* temp = tokenlinklist.Access( 0 ) ;
    if ( temp -> tokentype == FLOAT ) {
      float floatnum = transfer.Strtof( temp -> tokenname ) ;
      cout << "> " ;
      printf( "%.3f\n", floatnum ) ;
    } // if
    else if ( temp -> tokentype == STRING ) {
      cout << "> " ;
      cout << "\"" << temp -> tokenname << "\"" << endl ;
    } // else if
    else if ( temp -> tokentype == INT ) {
      cout << "> " ;
      cout << transfer.Strtoint( temp -> tokenname ) << endl ;
    } // else if
    else {
      ParaNode* paranode = NULL ;
      cout << " 6543 :" ;
      mfunctrun.Printpara() ;
      paranode = mfunctrun.Isinparatable( temp -> tokenname ) ;

      if ( paranode != NULL && paranode -> tokentype == FLOAT ) {
        float floatnum = transfer.Strtof( paranode -> root -> name ) ;
        cout << "> " ;
        printf( "%.3f\n", floatnum ) ;
      } // if
      else if ( paranode != NULL && paranode -> tokentype == STRING ) {
        cout << "> " ;
        cout << "\"" << paranode -> root -> name << "\"" << endl ;
      } // else if
      else if ( paranode != NULL && paranode -> tokentype == INT ) {
        cout << "> " ;
        cout << transfer.Strtoint( paranode -> root -> name ) << endl ;
      } // else if
      else if ( paranode != NULL && paranode -> tokentype == TREE ) {
        cout << "> " ;
        cout << "( " ;
        int spacenum = 2 ;
        bool prettyprint_temp = true ;
        Prettyprint( NULL, paranode -> root, spacenum, prettyprint_temp ) ;
        spacenum -= 2 ;
        Printspace( spacenum ) ;
        cout << ")\n" ;
      } // else if 
      else {
        string errornode = "ERROR (unbound symbol) : " ;
        errornode = errornode + temp -> tokenname ;
        cout << errornode << endl ;
      } // else
    } // else
  } // Singlenodeprint

  string DealSYMNOLstring( string str ) {
    int index = 0 ;
    string returnstr = "" ;
    while ( index < str.length() ) {
      if ( str[ index ] == '\\' && index + 1 < str.length() ) {
        index ++ ;
        char nextch = str [ index ] ;
        if ( nextch == 't' || nextch == 'n' || nextch == '\"' || nextch == '\\' ) {
          returnstr += nextch ;
        } // if
        else {
          returnstr += '\\' ;
          returnstr += nextch ;
        } // else
      } // if
      else {
        returnstr += str[ index ] ;
      } // else

      index++ ;
    } // while

    return returnstr ;
  } // DealSYMNOLstring()

  int Lexicalpraser( Vector tokengroup, Vector  &tokenlinklist ) {
    int index = 0 ;
    InstructionNode node ;
    while ( index < tokengroup.Size() ) {
      InstructionNode* memlocofindex = tokengroup.Access( index ) ;
      InstructionNode* memlocofindexplus = tokengroup.Access( index + 1 ) ;
      InstructionNode* memlocofindexplusplus = tokengroup.Access( index + 2 ) ;
      node.column = memlocofindex -> column ;
      if ( index < tokengroup.Size() - 1 && 
           mtable.FindTokenType( memlocofindex -> tokenname ) == LEFT_PAREN 
           && mtable.FindTokenType( memlocofindexplus -> tokenname ) == RIGHT_PAREN ) {
        node.line = memlocofindex -> line ;
        node.tokenname = "nil" ;
        node.tokentype = NIL ;
        node.resetcolumn = memlocofindexplus -> column ;
        index += 2 ;
        tokenlinklist.Push_back( node ) ;
      } // if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == LEFT_PAREN ) {
        node.line = memlocofindex -> line ;
        node.tokenname = memlocofindex -> tokenname ;
        node.tokentype = LEFT_PAREN ;
        node.resetcolumn = memlocofindex -> column ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == RIGHT_PAREN ) {
        node.line = memlocofindex -> line ;
        node.tokenname = memlocofindex -> tokenname ;
        node.resetcolumn = memlocofindex -> column ;
        node.tokentype = RIGHT_PAREN ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == INT ) {
        node.line = memlocofindex -> line ;
        node.tokenname = memlocofindex -> tokenname ;
        node.tokentype = INT ;
        node.resetcolumn = memlocofindex -> column + memlocofindex -> tokenname.length() - 1 ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == STRING ) {
        if ( index + 2 < tokengroup.Size() && memlocofindex -> tokenname == "\"" 
             && memlocofindexplusplus -> tokenname == "\"" ) {
          node.tokenname = "\"" ;
          node.tokentype = STRING ;
          node.column = memlocofindex -> column ;
          node.line = memlocofindex -> line ;
          node.resetcolumn = memlocofindex -> column ;
          tokenlinklist.Push_back( node ) ; // "

          node.line = memlocofindexplus -> line ;
          node.column = memlocofindexplus -> column ;
          node.tokenname = memlocofindexplus -> tokenname ;
          node.tokentype = STRING ;
          node.resetcolumn = memlocofindexplusplus -> column ; // " string " <- re
          tokenlinklist.Push_back( node ) ; // string body

          node.tokenname = "\"" ;
          node.tokentype = STRING ;
          node.column = memlocofindexplusplus -> column ;
          node.line = memlocofindexplusplus -> line ;
          node.resetcolumn = memlocofindexplusplus -> column ;
          tokenlinklist.Push_back( node ) ; // "
          index = index + 3 ;
        } // if
        else {
          if ( index + 1 < tokengroup.Size() ) {
            node.tokenname = "\"" ;
            node.tokentype = STRING ;
            node.column = memlocofindex -> column ;
            node.line = memlocofindex -> line ;
            node.resetcolumn = memlocofindex -> column ;
            tokenlinklist.Push_back( node ) ; // "

            node.tokenname = memlocofindexplus -> tokenname ;
            node.line = memlocofindexplus -> line ;
            node.column = memlocofindexplus -> column ;
            node.tokentype = STRING ;
            node.resetcolumn = memlocofindexplus -> column ;
            tokenlinklist.Push_back( node ) ; // string body
            index = index + 2 ;
          } // if
          else {
            node.tokenname = memlocofindex -> tokenname ;
            node.line = memlocofindex -> line ;
            node.column = memlocofindex -> column ;
            node.tokentype = STRING ;
            node.resetcolumn = memlocofindex -> column ;
            tokenlinklist.Push_back( node ) ; // "
            index ++ ;
          } // else

          // cout << "> ERROR (no closing quote) : END-OF-LINE encountered at Line " ;
          // cout << node.line << " Column " << node.column + node.tokenname.length() << endl << endl ;
          // return ERRORSTMT ;
        } // else
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == DOT ) {
        node.line = memlocofindex -> line ;
        node.tokenname = memlocofindex -> tokenname ;
        node.resetcolumn = memlocofindex -> column ;
        node.tokentype = DOT ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == FLOAT ) {
        node.line = memlocofindex -> line ;
        node.tokenname = memlocofindex -> tokenname ;
        node.resetcolumn = memlocofindex -> column + memlocofindex -> tokenname.length() - 1 ;
        node.tokentype = FLOAT ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == NIL ) {
        node.line = memlocofindex -> line ;
        node.tokenname = "nil" ;
        node.resetcolumn = memlocofindex -> column + memlocofindex -> tokenname.length() - 1 ;
        node.tokentype = NIL ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == T ) {
        node.line = memlocofindex -> line ;
        node.tokenname = "#t" ;
        node.resetcolumn = memlocofindex -> column + memlocofindex -> tokenname.length() - 1 ;
        node.tokentype = T ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType( memlocofindex -> tokenname ) == QUOTE ) {
        node.line = memlocofindex -> line ;
        node.tokenname = "quote" ;
        node.resetcolumn = memlocofindex -> column ;
        node.tokentype = QUOTE ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if
      else if ( mtable.FindTokenType(  memlocofindex -> tokenname ) == SYMBOL ) {
        node.line = memlocofindex -> line ;
        // node.tokenname = tokengroup[ index ].tokenname ;
        node.tokenname = DealSYMNOLstring( memlocofindex -> tokenname ) ;
        node.resetcolumn = memlocofindex -> column + memlocofindex -> tokenname.length() - 1 ;
        node.tokentype = SYMBOL ;
        index++ ;
        tokenlinklist.Push_back( node ) ;
      } // else if

    } // while

    return NOTCOMPLETE ;
  } // Lexicalpraser()

  void GetTokenGroup( Vector &tokengroup, string projinput, 
                      int &currentline ) {
    string buffer = "" ;
    InstructionNode node ;
    char curch = ' ' ;
    int index = 0 ;
    bool stop = false ;
    int column = 0 ;
    while ( index < projinput.size() ) {
      while ( index < projinput.size() && mtable.IsWhitespace( curch ) ) {
        curch = projinput[ index ] ;
        column++ ;
        index++ ;
      } // while

      node.column = column ;
      node.line = currentline ;
      while ( index < projinput.size() && mtable.IsSeparators( curch ) != true ) {
        buffer += curch ;
        if ( curch == '\\' && index < projinput.size() ) {
          char nextch = projinput[ index ] ;
          if ( nextch == 't' || nextch == 'n' || nextch == '\"' || nextch == '\\' ) {
            buffer += nextch ;
          } // if
          else {
            buffer += '\\' ;
            buffer += nextch ;
          } // else

          index++ ;
          column++ ;
        } // if

        curch = projinput[ index ] ;
        column++ ;
        index++ ;
      } // while

      if ( !buffer.empty() ) {
        node.tokenname = buffer ;
        tokengroup.Push_back( node ) ;
      } // if

      if ( mtable.IfSeparatorisAToken( curch ) == true ) {
        if ( curch == ';' ) {
          while ( index < projinput.size() ) {
            curch = projinput[ index ] ;
            index++ ;
            column++ ;
          } // while
        } // if
        else if ( curch == '\"' ) {
          Dealstring( tokengroup, projinput, index, curch, currentline, column ) ;
          // cout << "aa835" ;
        } // else if
        else {
          buffer = "" ;
          buffer += curch ;
          node.tokenname = buffer ;
          node.column = column ;
          node.line = currentline ;
          tokengroup.Push_back( node ) ;
          curch = projinput[ index ] ;
          index++ ;
          column++ ;
        } // else
      } // if

      buffer.clear() ;
    } // while
  } // GetTokenGroup()

  InstructionNode Catchfirstnode( Vector &current, Vector &target ) {
    InstructionNode* firstoftarget = target.Access( 0 ) ;
    InstructionNode node ;
    if ( firstoftarget -> tokentype != STRING ) {
      node.next = NULL ;
      node.tokenname = firstoftarget -> tokenname ;
      node.tokentype = firstoftarget -> tokentype ;
      node.line = firstoftarget-> line ;
      node.column = firstoftarget-> column ;
      node.resetcolumn = firstoftarget-> resetcolumn ;
      target.Erase( target.Begin() ) ;
      current.Push_back( node ) ;
      return node ;
    } // if
    else {
      if ( 2 < target.Size() ) { // complete string
        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // "
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        firstoftarget = firstoftarget -> next ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;
        
        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // string body 
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        firstoftarget = firstoftarget -> next ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;

        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // "
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;
        return node ;
      }  // if
      else if ( 1 < target.Size() ) { // " string
        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // "
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        firstoftarget = firstoftarget -> next ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;
        
        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // string body 
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;
      } // else if
      else { // "
        node.next = NULL ;
        node.tokenname = firstoftarget -> tokenname ; // "
        node.tokentype = firstoftarget -> tokentype ;
        node.line = firstoftarget-> line ;
        node.column = firstoftarget-> column ;
        node.resetcolumn = firstoftarget-> resetcolumn ;
        target.Erase( target.Begin() ) ;
        current.Push_back( node ) ;
      } // else

      return node ;
    } // else
  } // Catchfirstnode()

  bool Stopsys( Vector tokengroup ) {
    if ( tokengroup.Size() == 5 ) {
      InstructionNode* memloc = tokengroup.Access( 0 ) ; // 0
      InstructionNode* memlocplus = memloc -> next ; // 1
      InstructionNode* memlocplusplus = memlocplus -> next ; // 2
      InstructionNode* memlocof3 = memlocplusplus -> next ; // 3
      InstructionNode* last = memlocof3 -> next ; // 4
      if ( memloc -> tokenname == "(" && memlocplus -> tokenname == "exit" && 
           memlocplusplus -> tokenname == "." && memlocof3 -> tokenname == "nil" &&  
           last -> tokenname == ")" ) {
        if ( memlocplus -> tokentype == SYMBOL )
          return true ;
      } // if

    } // if

    return false ;
  } // Stopsys()

  void Resetcolumnforsameline( Vector &tokenlinklist, InstructionNode lastnode ) { 
    int index = 0 ;
    InstructionNode* temp = NULL ;
    while ( index < tokenlinklist.Size() ) {
      temp = tokenlinklist.Access( index ) ;
      if ( lastnode.line == temp -> line ) {
        temp -> line = 1 ;
        temp -> column -= lastnode.resetcolumn ;
        temp -> resetcolumn -= lastnode.resetcolumn ;
      } // if

      index ++  ;
    } // while

  } // Resetcolumnforsameline()

  void Dealstring( Vector &tokengroup, string projinput, int &index, 
                    char &curch, int &line, int &column ) {
    // cout << "1266 : "<<  index << " " << column << endl ;
    string buffer = "" ;
    InstructionNode node ;
    buffer += curch ;
    node.tokenname = buffer ;
    node.line = line ;
    node.column = column ;
    tokengroup.Push_back( node ) ; // "
    column++ ;
    int strbodystartcolumn = column ;
    curch = projinput[ index ] ;
    bool stop = false ;
    node.column = index ;
    node.tokenname = "" ;
    string strinput = "" ;
    if ( index < projinput.size() - 1 ) {
      while ( stop != true && index < projinput.size() - 1  ) {
        if ( projinput[ index ] == '\\' && index + 1 < projinput.size() ) {
          index++ ;
          column ++ ;
          char nextchar = projinput[ index ] ;
          if ( nextchar == '\"' || nextchar == '\\' ) {
            strinput += nextchar ;
          } // if
          else if ( nextchar == 't' ) {
            strinput += '\t' ;
          } // else if
          else if ( nextchar == 'n' ) {
            strinput += '\n' ;
          } // else if
          else {
            strinput += '\\' ;
            strinput += nextchar ;
          } // else 

          curch = projinput[ index ] ;
          index ++ ;
          column++ ;
        } // if
        else if ( projinput[ index ] != '\"' ) {
          curch = projinput[ index ] ;
          strinput += projinput[ index ] ;
          index ++ ;
          column++ ;
        } // if
        else {
          stop = true ;
        } // else 
      } // while

      node.tokenname = strinput ;
      node.column = strbodystartcolumn ;
      node.line = line ;
      // cout << "1288strbody : " << index << endl ;
      tokengroup.Push_back( node ) ; // stringbody
      curch = projinput[ index ] ;
      if ( curch == '\"' ) {
        node.tokenname = curch ; // " or \0
        node.line = line ;
        node.column = column ;
        tokengroup.Push_back( node ) ;
        index++ ;
        column++ ;
        curch = projinput[ index ] ;
        index++ ;
        column++ ;
      } // if
      else {
        index++ ;
        column++ ;
        curch = projinput[ index ] ;
        index++ ;
        column++ ;
      } // else
    } // if

    column-- ;
  }  // Dealstring()


  void SpiltleftrightParan( Vector &tokenlinklist ) {
    int index = 0 ;
    InstructionNode* temp = tokenlinklist.Access( index ) ;
    while ( index < tokenlinklist.Size() ) {
      if ( index + 1 < tokenlinklist.Size() ) {
        InstructionNode* temp2 = temp -> next ;
        if ( temp -> tokentype == LEFT_PAREN
             && temp2 -> tokentype == RIGHT_PAREN ) {
          temp -> tokenname = "nil" ;
          temp -> tokentype = NIL ;
          tokenlinklist.Erase( tokenlinklist.Begin() + index + 1 ) ;
        } // if
      } // if

      index++ ;
      temp = temp -> next ;
    }  // while
  } // SpiltleftrightParan()

  void Mergestringstmt( Vector &tokenlinklist ) {
    int index = 0 ;
    InstructionNode* cur = tokenlinklist.Access( 0 ) ;
    while ( index < tokenlinklist.Size() ) {
      if ( cur -> tokentype == STRING && index + 2 < tokenlinklist.Size() ) {
        InstructionNode* curnext = cur -> next ;
        InstructionNode* curnextnext = curnext -> next ;    
        if ( curnext -> tokentype == STRING && curnextnext -> tokentype == STRING ) {
          tokenlinklist.Erase( index ) ;
          tokenlinklist.Erase( index + 1 ) ;
        } // if
        
        cur = tokenlinklist.Access( index ) ;
        cur = cur -> next ;
      } // if
      else {
        cur = cur -> next ;
      } // else 

      index++ ;
    } // while
  } // Mergestringstmt()

  void Printtokenlinklist( Vector tokengroup ) {
    cout << "tokenlinklist.size: " << tokengroup.Size() << endl ;
    InstructionNode *cur = tokengroup.mhead ;
    int i = 0 ;

    while ( cur != NULL ) {
      cout << cur->tokenname << "  " ;
      cout << cur->tokentype << "  " ;
      cout << cur->line << "  " ;
      cout << cur->column << " " ; 
      cout << cur->resetcolumn << endl ;
      cur = cur -> next ;
    } // while
  } // Printtokenlinklist()

  void Inorder( TreeNode * head ) {
    if ( head == NULL ) {
      cout << "null " ;
      return ;
    } // if

    Inorder( head -> left ) ;
    cout << head -> name << " " ;
    Inorder( head -> right ) ;
    return ;
  } // Inorder()

  void Printspace( int num ) {
    int index = 0 ;
    while ( index < num ) {
      cout << " " ;
      index++ ;
    } // while
  } // Printspace()

  void Prettyprint( TreeNode* father, TreeNode* cur, int &spacenum, bool &lastisLEFTPAREN ) {
    Transfer transfer ;
    if ( cur -> left != NULL && cur -> right != NULL 
         && cur -> left -> name == " " && cur -> right -> name == " " ) { // sub <- o -> sub 
      if ( lastisLEFTPAREN == false ) {
        Printspace( spacenum ) ;
      } // if

      cout << "( " ;
      spacenum += 2 ;
      lastisLEFTPAREN = true ;
      Prettyprint( cur, cur -> left, spacenum, lastisLEFTPAREN ) ;
      spacenum -= 2 ;
      Printspace( spacenum ) ;
      cout << ")\n" ;
      Prettyprint( cur, cur -> right, spacenum, lastisLEFTPAREN ) ;
    } // if
    else if ( cur -> left != NULL && cur -> right != NULL && 
              cur -> left -> name != " " && cur -> right -> name == " " ) { // atom <- o -> sub
      Prettyprint( cur, cur -> left, spacenum, lastisLEFTPAREN ) ;
      if ( cur -> left -> name == "quote" && cur -> left -> type != STRING ) {
        Printspace( spacenum ) ;
        spacenum += 2 ;
        cout << "( " ;
        lastisLEFTPAREN = true ;
      } // if

      Prettyprint( cur, cur -> right, spacenum, lastisLEFTPAREN ) ;
      if ( cur -> left -> name == "quote" && cur -> left -> type != STRING ) {
        spacenum -= 2 ;
        Printspace( spacenum ) ;
        cout << ")\n" ;
      } // if
    } // else if
    else if ( cur -> left != NULL && cur -> right != NULL 
              && cur -> left -> name == " " && cur -> right -> name != " " ) { // sub <- o -> atom
      if ( lastisLEFTPAREN == false ) {
        Printspace( spacenum ) ;
      } // if

      cout << "( " ;
      spacenum += 2 ;
      lastisLEFTPAREN = true ;
      Prettyprint( cur, cur -> left, spacenum, lastisLEFTPAREN ) ;
      lastisLEFTPAREN = false ;
      spacenum -= 2 ;
      Printspace( spacenum ) ;
      cout << ")\n" ;
      if ( cur -> right -> type != NIL ) {
        Printspace( spacenum ) ;
        cout << "." << endl ;
      } // if


      Prettyprint( cur, cur -> right, spacenum, lastisLEFTPAREN ) ;
    } // else if
    else if ( cur -> left != NULL && cur -> right != NULL 
              && cur -> left -> name != " " && cur -> right -> name != " " ) { // atom <- o -> atom
      Prettyprint( cur, cur -> left, spacenum, lastisLEFTPAREN ) ;
      Prettyprint( cur, cur -> right, spacenum, lastisLEFTPAREN ) ;
    } // else if
    else if ( cur -> left == NULL && cur -> right == NULL && father == NULL ) { // root only one node
      if ( lastisLEFTPAREN == false ) {
          Printspace( spacenum ) ;
      } // if

      if ( cur -> type == FLOAT ) {
          float floatnum = transfer.Strtof( cur -> name ) ;
          printf( "%.3f\n", floatnum ) ;
        } // if
        else if ( cur -> type == STRING ) {
          cout << "\"" << cur -> name << "\"" << endl ;
        } // else if
        else if ( cur -> type == INT ) {
          if ( cur -> name != "quote" && cur -> type != STRING )
            cout << transfer.Strtoint( cur -> name ) << endl ;
          else 
            cout << cur -> name << endl ;
        } // else if
        else {
          cout << cur -> name << endl ;
        } // else

    } // else if 
    else if ( cur -> left == NULL && cur -> right == NULL ) { // this is leaf
      if ( father -> right == cur && cur -> type == NIL ) {
        if ( father -> left != NULL && father -> left -> type == INT && father -> left -> name == "quote" ) {
          Printspace( spacenum ) ;
          cout << "nil\n" ;
        } // if

        return ;
      } // if
      else if ( father -> left == cur && father -> right != NULL &&
                ( father -> right -> type == STRING || father -> right -> type == INT || 
                  father -> right -> type == FLOAT || father -> right -> type == T || 
                  father -> right -> type == SYMBOL ) ) { // left <- o
        if ( lastisLEFTPAREN == false ) {
          Printspace( spacenum ) ;
        } // if

        if ( cur -> type == FLOAT ) {
          float floatnum = transfer.Strtof( cur -> name ) ;
          printf( "%.3f\n", floatnum ) ;
        } // if
        else if ( cur -> type == STRING ) {
          cout << "\"" << cur -> name << "\"" << endl ;
        } // else if
        else if ( cur -> type == INT ) {
          if ( cur -> name != "quote" && cur -> type != STRING )
            cout << transfer.Strtoint( cur -> name ) << endl ;
          else 
            cout << cur -> name << endl ;
        } // else if
        else {
          cout << cur -> name << endl ;
        } // else 

        if ( cur -> name == "quote" ) {
          if ( cur -> type == STRING ) {
            Printspace( spacenum ) ;
            cout << "." << endl ;
          }  // if         
        } // if 
        else {
          Printspace( spacenum ) ;
          cout << "." << endl ;
        } // else

      } // else if
      else { // o -> right
        if ( lastisLEFTPAREN != true ) {
          Printspace( spacenum ) ;
        } // if
        
        if ( cur -> type == FLOAT ) {
          float floatnum = transfer.Strtof( cur -> name ) ;
          printf( "%.3f\n", floatnum ) ;
        } // if
        else if ( cur -> type == STRING ) {
          cout << "\"" << cur -> name << "\"" << endl ;
        } // else if
        else if ( cur -> type == INT ) {
          if ( cur -> name != "quote" && cur -> type != STRING )
            cout << transfer.Strtoint( cur -> name ) << endl ;
          else 
            cout << cur -> name << endl ;
        } // else if
        else
          cout << cur -> name << endl ;
      } // else

      lastisLEFTPAREN = false ;
    } // else if
  } // Prettyprint()
}; // Scaner()

int main() {
  Scaner scaner ;
  cout << "Welcome to OurScheme!\n" << endl ;
  scaner.Interpreter() ;
  cout << "Thanks for using OurScheme!" ;
} // main()
