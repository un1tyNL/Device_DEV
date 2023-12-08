## Coding standards
 - All code should be formatted using the .clang-format configuration provided. Exceptions are allowed only in certain structures that cannot be handled properly by the formatter.
 - All classes must be placed inside a namespace. Classes with similar usecases should be grouped within the same namespace.
 - Circular includes must be protected using the ``` #pragma once ```  as a define guard.