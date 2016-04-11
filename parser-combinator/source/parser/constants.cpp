#include "stdafx.h"

#include "constants.h"

const char lexing::char_constants::newline[] = "\\r?\\n";
const char lexing::char_constants::newline_type[] = "newline";
const char lexing::char_constants::whitespace[] = "\\s+";
const char lexing::char_constants::whitespace_type[] = "whitepsace";

const wchar_t lexing::wchar_constants::newline[] = L"\\r?\\n";
const wchar_t lexing::wchar_constants::newline_type[] = L"newline";
const wchar_t lexing::wchar_constants::whitespace[] = L"\\s+";
const wchar_t lexing::wchar_constants::whitespace_type[] = L"whitespace";
