# Device_DEV 
## Project Overview
The Device_DEV project is a development environment to create and test libraries/modules meant to be used in embedded C99 programs with C++ syntax and object orientation to be used on Cortex-M processors. The project can be build and ran in either Qt using QTest or in VSCode using the Google test framework. It is a hobby project with the goal of creating a well documented, structured and tested set of libraries/modules. ChatGPT is used (to some extent) to create summaries, descriptions or names for variables/functions/classes etc. The logic should always be checked and tested by the developer, no function may be introduced without a test.

## Development standards
 - No dynamic memory allocation, nor libraries that make use of, may be used (for example <vector>).
   - Rationale: this is not properly supported by the Cortex-M processors.
 - Floating point arithmatic should be avoided if possible, double precision is prohibited, fixed point is allowed.
   - Rationale: Not all Cortex-M processors have floating point units. In some cases floating point usage is inevitable, but should be kept at a minimum.

## Coding standards
 - All code should be formatted using the .clang-format configuration provided. Exceptions are allowed only in certain structures that cannot be handled properly by the formatter.
 - All classes must be placed inside a namespace. Classes with similar usecases should be grouped within the same namespace.

## Naming standards
 - All functions, variables, typenames and classes must use the lowerCamelCase format.
 - All member variables in a class have a "m_" prefix.
 - Namespaces use TLA (three letter abreviation).
 - Abbreviations may not be used in the names of functions, variables, typenames and classes.

## Doxygen standards & code segmentation
 - The following standards must be applied consecutively
 - Each file must provide a documentation segment:
 ```
/*************************************************************************\
 * Documentation
\*************************************************************************/
```


## Project Structure
- **Algorithms/**: Libraries for specific algorithms, suitable for embedded systems.
- **CommunicationManagement/**: Libraries for communication protocols in embedded environments.
- **CoreComponents/**: Core libraries for fundamental functionalities.
- **DeviceManagement/**: Modules for managing embedded devices, including GPS functionalities.
- **MemoryManagement/**: Libraries aimed at efficient memory management in embedded systems.
- **SignalProcessing/**: Libraries for signal processing (Contents not detailed).
- **Tools/Testing/**: Testing tools, including the Google Test framework.
- **build/**: Directory for build artifacts (contents not detailed).
- **.vscode/**: VS Code configuration for development.

## Key Configuration Files

- **CMakeLists.txt**: CMake build configuration.
- **Device_t.code-workspace**: VS Code workspace settings.
- **Device_t.pro**, **Device_t.pro.user**: Qt project files.

## Building the Project

### Using Qt

1. Open the project in Qt Creator using the `Device_t.pro` file.
2. The only required configuration is assigning the compiler.
3. Build the project by selecting `Build -> Build Project`.

### Using VS Code

1. Open the project folder in VS Code.
2. The only required configuration is assigning the compiler.
3. Use the integrated terminal to run build commands (e.g., `cmake`, `make`).

## Testing the Project

### Using QTest with Qt

1. Open the test directories within Qt Creator.
2. Execute tests by right-clicking on them and selecting `Run 'test_name'`.

### Using Google Test with VS Code

1. Google Test should be set up in the project.
2. Navigate to the test files in the VS Code explorer.
3. Run and manage tests using the Test Explorer in VS Code.

