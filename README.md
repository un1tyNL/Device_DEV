
# Device_DEV Project

## Project Overview

The Device_DEV project is tailored for the development and testing of libraries and modules for embedded C programs. It provides a conducive environment for coding and testing, compatible with both Qt using QTest and VS Code using the Google Test framework. This project simplifies the process of creating robust components for embedded systems.

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

## Conclusion

Device_DEV is an ideal platform for developers in the field of embedded C programming. It offers essential tools and a flexible environment for the efficient development and thorough testing of libraries and modules. The project supports cross-platform development and provides options for using either Qt or VS Code as the development environment.
