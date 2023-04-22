# ini-parser

ini-parser is a simple C++ library that enables users to read and write INI files, allowing the creation of objects that can easily preserve their state between executions by reading and writing data to and from INI files. To achieve this, the object intended for saving its data to an INI file must inherit from the `saveable` class (found in [saveable.hpp](https://github.com/ismawno/ini-parser/include/ini/saveable.hpp)) and override the `read()` and `write()` methods. The library provides easy-to-use functions for creating new sections and managing entries within those sections.

## Features

- Simple and straightforward C++ library for reading and writing INI files
- Ability to create objects that can preserve their state between executions
- Inheritance from the `saveable` class for custom objects
- Easy management of sections and entries within INI files

## Dependencies

- [debug-tools](https://github.com/ismawno/debug-tools)

The [fetch_dependencies.py](https://github.com/ismawno/ini-parser/scripts/fetch_dependencies.py) script will automatically add all the dependencies as git submodules, provided that the user has already created their own repository and included the current project as a git submodule (or at least downloaded it into the repository). To ensure all runs smoothly once the script has been executed, do not rename the folders containing the various dependencies. All external dependencies, those not created by the same author, will be added as submodules within the [vendor](https://github.com/ismawno/ini-parser/vendor) folder.


## Building and Usage

1. Ensure you have `premake5` and `make` installed on your system. `premake5` is used to generate the build files, and `make` is used to compile the project.
2. Create your own repository and include the current project as a git submodule (or at least download it into the repository).
3. Run the [fetch_dependencies.py](https://github.com/ismawno/ini-parser/scripts/fetch_dependencies.py) script located in the [scripts](https://github.com/ismawno/ini-parser/scripts) folder to automatically add all the dependencies as git submodules.
4. Create an entry point project with a `premake5` file, where the `main.cpp` will be located. Link all libraries and specify the kind of the executable as `ConsoleApp`. Don't forget to specify the different configurations for the project.
5. Create a `premake5` file at the root of the repository describing the `premake` workspace and including all dependency projects.
6. Build the entire project by running the `make` command in your terminal. You can specify the configuration by using `make config=the_configuration`.
7. To use ini-parser, include the [saveable.hpp](https://github.com/ismawno/ini-parser/include/ini/saveable.hpp) header. Implement your custom objects by inheriting from the `saveable` class and overriding the `read()` and `write()` methods.

For more information on how to use ini-parser, please refer to the documentation.

## License

ini-parser is licensed under the MIT License. See LICENSE for more information.
