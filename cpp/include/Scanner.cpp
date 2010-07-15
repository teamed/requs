/**
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * rqdql.com. located at www.rqdql.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id$
 */

#include <string>
#include <boost/format.hpp>
#include "Scanner.h"
#include "Logger.h"

typedef union {
    std::string* name;
    int num;
    void* ptr;
} YYSTYPE;

// bison/flex file
// this define will protect us against BISON default YYSTYPE
#define YYSTYPE_IS_DECLARED 1
#define YYSTYPE_IS_TRIVIAL 1

/**
 * These files are auto-generated by FLEX/BISON tools called from
 * Makefile. Without these files we can't proceed here
 * and compilation will be failed.
 */
#include "Scanner/rqdql.y.c-symbols.h"

/**
 * Declaration here, implementation later
 */
void yyerror(const char*, ...);

/**
 * Declaration here, implementation later
 */
void lyyerror(YYLTYPE, const char*, ...);

/**
 * Protocol the appearance of an object in input stream
 * 
 * Declaration here, implementation later in this file.
 * @see rqdql.y
 */
void protocol(YYLTYPE, void*);

/**
 * Set left-hand value
 *
 * Declaration here, implementation later in this file.
 * @see rqdql.l
 */
void yySet(std::string*&, const boost::format&);
void yySet(std::string*&, char*&);

/**
 * Different levels of logging
 */
enum LogLevel {
    L_DEBUG   = 1,
    L_VERBOSE = 2,
    L_INFO    = 3,
    L_WARNING = 4,
    L_ERROR   = 5
};

/**
 * Simple logging
 *
 * Declaration here, implementation later in this file.
 * @see rqdql.l
 */
void log(const LogLevel, const std::string&);
void log(const std::string&);
void log(const boost::format&);
void log(const LogLevel, const boost::format&);

/**
 * These files are auto-generated by FLEX/BISON tools called from
 * Makefile. Without these files we can't proceed here
 * and compilation will be failed.
 */
#include "Scanner/rqdql.l.c"
#include "Scanner/rqdql.y.c"

void rqdql::Scanner::scan(const std::string& s) {
    yylineno = 1; // reset line number to 1
    yy_switch_to_buffer(yy_scan_string(s.c_str()));
    yyparse();
}

LogLevel level;

void yyerror(const char *error, ...) {
    // if (YYRECOVERING()) {
    //     return;
    // }
    va_list args;
    va_start(args, error);
    char s[1000];
    vsprintf(s, error, args);
    va_end(args);
    rqdql::get<rqdql::Logger>().log((int)yylloc.first_line, s);
}
    
void lyyerror(YYLTYPE t, const char *error, ...) {
    va_list args;
    va_start(args, error);
    char s[1000];
    vsprintf(s, error, args);
    va_end(args);
    rqdql::get<rqdql::Logger>().log((int)t.first_line, s);
}

void protocol(YYLTYPE t, void* x) {
    rqdql::get<rqdql::Logger>().addSubject(x, t.first_line);
}

void yySet(std::string*& lhs, const boost::format& rhs) {
    lhs = new std::string(rhs.str());
}

void yySet(std::string*& lhs, char*& rhs) {
    lhs = new std::string(rhs);
}

void log(const LogLevel lvl, const std::string& line) {   
    std::string label;
    switch (lvl) {
        case L_DEBUG:
            label = "DEBUG";
            break;
        case L_VERBOSE:
            label = "VERB";
            break;
        case L_INFO:
            label = "INFO";
            break;
        case L_WARNING:
            label = "WARN";
            break;
        case L_ERROR:
            label = "ERR";
            break;
    }
    if (lvl >= level) {
        rqdql::get<rqdql::Logger>().log(0, "[" + label + "] " + line);
    }
}


void log(const std::string& line) {
    return log(L_DEBUG, line);
}

void log(const boost::format& line) {
    return log(L_DEBUG, line.str());
}

void log(const LogLevel lvl, const boost::format& line) {
    return log(lvl, line.str());
}
