Searches for (and prints the line containing) the given regular expression pattern in the given file/stream input.

Supports star (*), disjunction (|), beginning(^)/end($) specifiers, and concatenation.

Compiled code can be run with the following syntax:
main-egrep <pattern> <file1> <file2> ...

where:
  <pattern> represents the regular expression pattern to search for,
  the <file>s are optional (if no files are given, then the user provides the input directly through cin).
