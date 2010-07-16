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
 * @version $Id: Data.h 2308 2010-07-14 12:25:35Z yegor256@yahoo.com $
 */

#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/regex.hpp>
#include "Solm/Term.h"
#include "rqdql.h"
#include "rqdql/Exception.h"

/**
 * These files are auto-generated by FLEX/BISON tools called from
 * Makefile. Without these files we can't proceed here
 * and compilation will be failed.
 */
#include "Solm/Term/term.y.c-symbols.h"

/**
 * Declaration here, implementation later
 */
void termerror(const char*, ...);

/**
 * Global variable, to be used as a target for BISON parser
 *
 * This approach is NOT thread-safe, but good enough for now
 */
solm::Term::Term* term_target;

/**
 * These files are auto-generated by FLEX/BISON tools called from
 * Makefile. Without these files we can't proceed here
 * and compilation will be failed.
 */
#include "Solm/Term/term.l.c"
#include "Solm/Term/term.y.c"

solm::Term::Term(const std::string& s) {
    term_target = this;
    try {
        term_switch_to_buffer(term_scan_string(s.c_str()));
        termparse();
    } catch (...) {
        throw rqdql::Exception(
            boost::format(rqdql::_t("Invalid term syntax: '%s'")) % s
        );
    }
}

bool solm::Term::is(solm::Term::Kind k) const {
    switch (k) {
        case T_RULE:
            return variables().size();
        case T_FACT:
            return is(T_OBJECT) && _terms.size() && !variables().size();
        case T_ATOM:
            return (is(T_OBJECT) || is(T_VARIABLE) || is(T_NUMBER) || is(T_TEXT)) && !_terms.size();
        case T_NUMBER:
            return boost::regex_match(_value, boost::regex("[\\-\\+]?[0-9]+(\\.[0-9]+)?"));
        case T_TEXT:
            return boost::regex_match(_value, boost::regex("'.*'"));
        case T_OBJECT:
            return boost::regex_match(_value, boost::regex("[a-z_][a-zA-Z0-9_]*"));
        case T_VARIABLE:
            return boost::regex_match(_value, boost::regex("[A-Z][a-zA-Z0-9_]*"));
        case T_FALSE:
            return _value == "false";
        default:
            return false;
    }
}

solm::Term::operator std::string() const {
    std::string s(_value);
    if (_terms.size()) {
        std::vector<std::string> v;
        for (std::vector<Term>::const_iterator i = _terms.begin(); i != _terms.end(); ++i) {
            v.push_back((std::string)*i);
        }
        s += "(" + boost::algorithm::join(v, ", ") + ")";
    }
    return s;
}

solm::Term::operator bool() const {
    if (is(T_FALSE)) {
        return false;
    }
    for (Terms::const_iterator i = _terms.begin(); i != _terms.end(); ++i) {
        if (!(*i)) {
            return false;
        }
    }
    return true;
}

const solm::Term::Terms solm::Term::variables() const {
    Terms v;
    if (is(T_VARIABLE)) {
        v.push_back(*this);
    } else {
        for (Terms::const_iterator i = _terms.begin(); i != _terms.end(); ++i) {
            Terms subs = (*i).variables();
            for (Terms::const_iterator j = subs.begin(); j != subs.end(); ++j) {
                v.push_back(*j);
            }
        }
    }
    return v;
}

const solm::Term solm::Term::operator/(const solm::Term&) {
    return Term("false.");
}

solm::Term::Term(const std::string& v, const solm::Term::Terms& t) : _value(v), _terms() {
    for (Terms::const_iterator i = t.begin(); i != t.end(); ++i) {
        if ((*i)._value == ",") {
            for (Terms::const_iterator j = (*i)._terms.begin(); j != (*i)._terms.end(); ++j) {
                _terms.push_back(*j);
            }
        } else {
            _terms.push_back(*i);
        }
    }
}

void termerror(const char*, ...) {
    throw 0;
}