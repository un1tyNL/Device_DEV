Since the implementation and documentation of the modules/classes must be provided within the header file, the following rules need to be applied to keep code structured and modular.
 - The following standards must be applied consecutively for code segmentation.
   - First, the file must have a comment block segment at the top indicating the start of documentation, after which the current file can be documented.
 ```
/*************************************************************************\
 * Documentation
\*************************************************************************/
```
   - Next, the developer must provide a doxygen description of the file, starting with the file name using '''@file''', version of the implementation using '''@version''', a one line brief description using '''@brief''', a detailed description using '''@detail''' and usage description of the classes using '''@note'''.
```
/**
 * @file     <name>.hpp
 * @version  n.n
 * @brief    short description
 * @details  detailed description
 * @note     usage description
 */
```
   - Next, there must be a comment block segment indicating the start of include list.
 ```
/*************************************************************************\
 * Includes
\*************************************************************************/
```
   - Next, there must be a comment block segment indicating the start of class/function prototypes. After which the class and function prototypes can be placed.
 ```
/*************************************************************************\
 * Prototypes
\*************************************************************************/
```
   - Second to last, there must be a comment block segment indicating the start of class/function implementation. After which the function implemenations can be placed.
 ```
/*************************************************************************\
 * Implementation
\*************************************************************************/
```
   - Last, there must be a comment block segment signaling the end of the file.
/*************************************************************************\
 * Implementation
\*************************************************************************/
```

 - Doxygen has to be provided with each class/public function in the prototype segment, and must not be repeated in the implementation segment.
  - Rationale: documentation should only be required once. Maintaining documentation in multiple places is next to impossible.
 - In the documentation of parameters, the doxygen needs to provide the information wether the arguments are inputs, outputs or both input and output.
  - Since we're working with a mixture of C99/C++17 it's important to indicate when you parse a pointer as an argument to a function what the purpose is. Parsing the variabel by pointer because it points to a large object that you do not want to copy? Inserting data into a function that needs to be transformed and returned? or should the owernship of the data belong to the called of the function?
