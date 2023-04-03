# ini-parser

ini-parser is a simple C++ library that enables users to read and write INI files, allowing the creation of objects that can easily preserve their state between executions by reading and writing data to and from INI files. To achieve this, the object intended for saving its data to an INI file must inherit from the `saveable` class (found in `saveable.hpp`) and override the `read()` and `write()` methods. The library provides easy-to-use functions for creating new sections and managing entries within those sections.

## Features

- Simple and straightforward C++ library for reading and writing INI files
- Ability to create objects that can preserve their state between executions
- Inheritance from the `saveable` class for custom objects
- Easy management of sections and entries within INI files

## Dependencies

- [debug-tools](https://github.com/Ismael99Bueno/debug-tools): A set of tools for debugging the parser

## Usage

To use ini-parser, include the `saveable.hpp` header. Implement your custom objects by inheriting from the `saveable` class and overriding the `read()` and `write()` methods.

Build the project using premake5 as a static library. You must create a premake5 workspace with a user-implemented entry point that uses the ini-parser library. You can then build the workspace with premake5 to create an executable.

It is advisable to include ini-parser in a user-made repository as a git submodule. This allows you to keep the ini-parser code separate from your own code, making it easier to manage dependencies and track changes.

For more information on how to use ini-parser, please refer to the documentation.

## License

ini-parser is licensed under the MIT License. See LICENSE for more information.
