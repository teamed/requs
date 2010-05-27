/**
 *
 * FaZend.com, Fully Automated Zend Framework
 * RQDQL.com, Requirements Definition and Query Language
 *
 * Redistribution and use in source and binary forms, with or 
 * without modification, are PROHIBITED without prior written 
 * permission from the author. This product may NOT be used 
 * anywhere and on any computer except the server platform of 
 * FaZend.com. located at www.fazend.com. If you received this 
 * code occasionally and without intent to use it, please report 
 * this incident to the author by email: team@rqdql.com
 *
 * @author Yegor Bugayenko <egor@tpc2.com>
 * @copyright Copyright (c) rqdql.com, 2010
 * @version $Id: UseCase.h 1641 2010-04-16 07:56:07Z yegor256@yahoo.com $
 *
 * This file has to be included ONLY from Analytics.h
 */

/**
 * Convert TC to fact path
 */
TestCase::operator solm::FactPath() const {
    solm::FactPath fp;
    for (vector<TestCase*>::const_iterator i = predecessors.begin(); i != predecessors.end(); ++i) {
        fp = fp + (solm::FactPath)**i;
    }
    fp = fp + after;
    return fp;
}

/**
 * Two test cases are equal?
 */
bool TestCase::operator==(const TestCase& tc) const {
    return (solm::FactPath)*this == (solm::FactPath)tc;
}

/**
 * Show it as string
 */
const string TestCase::toString() const {
    vector<string> lines;
    for (vector<TestCase*>::const_iterator i = predecessors.begin(); i != predecessors.end(); ++i) {
        lines.push_back("gain success in " + (*i)->getName());
    }
    lines.push_back(after.toString());
    return boost::algorithm::join(lines, "\n");
}