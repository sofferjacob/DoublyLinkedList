/*
Jacobo Soffer Levy
A01028653
Utility functions declaration.
Modified: 04/04/21
*/
#ifndef PI_UTIL_H
#define PI_UTIL_H

#include <string>

bool validNumber(std::string& str);
int getOption();
int getInt();
std::string getString();

// Trims a string (in place) from the left side.
// Parameter: The string to trim.
// Return value: None.
inline void leftTrim(std::string& str);
// Trims a string (in place) from the right side.
// Parameter: The string to trim.
// Return value: None.
inline void rightTrim(std::string& str);
// Trims a string (in place) from both sides.
// Parameter: The string to trim.
// Return value: None.
inline void trim(std::string& str);

#endif