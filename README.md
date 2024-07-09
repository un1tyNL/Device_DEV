# Device_DEV 
## Project Overview
The Device_DEV project is a device development environment to create and test libraries/modules meant to be used on (Cortex-M) embedded systems using mainly C and some C++ (syntax and object orientation), using the STM32F446 as a target device. The project can be build and tested in either QtCreator using QTest or in VSCode using the Google test framework. It is a hobby project with the goal of creating a well documented, structured and tested set of libraries/modules much like the popular Arduino libraries. By no means should these libraries end up in production code, it's only meant to be used to jumpstart development by providing quick acces to proven, documented and understandable code. Each module is fully implemented in the header file making portability easier. ChatGPT is used (to some extent) to create more expressive documentation, descriptions or names for variables/functions/classes etc. The logic should always be checked and tested by the developer, no function may be introduced without a test.

## Development standards
 - No dynamic memory allocation, nor libraries that make use of, may be used (for example <vector>).
   - Rationale: dynamic memory allocation is not properly supported by the Cortex-M processors.
 - Floating point arithmatic should be avoided if possible, double precision is prohibited, fixed point is allowed.
   - Rationale: Not all Cortex-M processors have floating point arithmatic units. In some cases floating point usage is inevitable, but should be kept at a minimum.

## Coding standards
See StandardRules/CodingStandards.md

## Naming standards
See StandardRules/NamingStandard.md

## Doxygen standards & code segmentation
See StandardRules/DoxygenStandards.md

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

## Building & testing the project

### Using Qt

 - 1 Open the project in Qt Creator using the `Device_t.pro` file.
 - 2 Configure the project by selecting a kit (development was done using Qt 5.9.9, MinGW5.30 32bit)
 - 3 Build the project by selecting `Build -> Build Project`.
 - 4 After building, scan for tests `Tools -> Tests`
 - 5 Run the tests from `Tools -> Tests -> Run All Tests`, output should be visible in the `Test Results` tab.

### Using VS Code
 - 1. Open the project folder in VS Code.
 - 2 Make sure to have the following extensions installed to make life easier:
   - 1. C/C++
   - 2 C/C++ Extension Pack
   - 3 C++ TestMate
   - 4 CMake
   - 5 CMake Tools
 - 3 Configure the project in the `CMake` tab (development in VSC was done using Clang 17.0.6 x86_64 from LLVM).
 - 4 Build all projects from the `CMake` tab.
 - 5 In the `Test Explorer` tab, the test can be seen and ran:
   - 1 Under `CTest` all components are listed, showing the build status of each component.
   - 2 Under `TestMate C++` all components are listed, showing the result of each individual test.

  




