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

#ifndef __INCLUDE_RQDQL_EXCEPTION_H
#define __INCLUDE_RQDQL_EXCEPTION_H

#include <string>
#include <boost/format.hpp>

namespace rqdql {

/**
 * Exception
 */
class Exception {

public:

    /**
     * Public constructor
     */
    Exception() : _message("no details") { /* that's it */ }

    /**
     * Public constructor
     */
    Exception(const std::string& s) : _message(s) { /* that's it */ }

    /**
     * Public constructor
     */
    Exception(const boost::format& s) : _message(s.str()) { /* that's it */ }

    /**
     * Get message
     */
    const std::string& getMessage() { return _message; }

private:

    /**
     * The message
     */
    std::string _message;

};
    
}

#endif