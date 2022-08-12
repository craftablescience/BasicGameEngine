<div align="center">
  <img width="400px" src="https://github.com/craftablescience/ChiraEngine/blob/main/branding/github/readme_banner.png?raw=true" alt="Chira Engine"/>

  ![Windows Workflow Status](https://img.shields.io/github/workflow/status/craftablescience/ChiraEngine/Build%20Engine?label=Builds%20and%20Tests)
  ![License](https://img.shields.io/github/license/craftablescience/ChiraEngine?label=License)
  ![Discord](https://img.shields.io/discord/678074864346857482?label=Discord&logo=Discord&logoColor=%23FFFFFF)

  A fully customizable (and heavily work-in-progress) MIT-licensed game engine, written in C++20.
</div>

## Features
To summarize the major features:
- Native Windows and Linux support (OpenGL 4.1)
- As extensible as possible: register custom logging hooks, resource types and providers, etc.
- Custom preprocessing of GLSL shaders, with macros and #include directives
- Robust resource loading and management to facilitate sharing of congruent data
- Data-oriented design, using entities as building blocks
- Hassle-free Discord Rich Presence and Steamworks API wrappers
- Inline text localization
- Event queue to communicate between entities (or other parts of the engine)
- Console commands to run actions on the fly, with the ability to pass arguments
- Variables modifiable from the console, with support for caching between sessions
- Logger built-in with colored text and hooks

The goal of the engine is to have as much customization as possible, while still maintaining ease of use.

## Supported Compilers

| Compiler (Latest) | Windows            | Linux     | macOS                      |
|-------------------|--------------------|-----------|----------------------------|
| GCC               | Supported (MinGW)\* | Supported | Unsupported                |
| Clang             | Unsupported        | Supported | Supported (Homebrew LLVM)\*\*|
| MSVC              | Supported          | N/A       | N/A                        |
| Clang-CL          | Supported          | N/A       | N/A                        |

(\*) MinGW builds on Windows will work, but running the application outside your IDE will require you to copy some DLLs
next to the executable. Check the GitHub Actions script to see which DLLs need copied from the MinGW bin directory.

(\*\*) Homebrew LLVM is required because Apple Clang as of this time does not support certain C++ features that are used inside ChiraEngine

## Bundled Dependencies
- AngelScript v2.35.1
- Dear ImGui v1.89
- Discord RPC
- {fmt} v9.0.0
- GLAD (OpenGL 4.1 Core, GL_KHR_debug extension)
- GLFW v3.3.9
- GLM v0.9.9.9
- nlohmann_json v3.10.5
- stb_image v2.27
- stduuid v1.1
- TinyFileDialogs v3.8.8

## Development (Windows)
- **CLion**: The project will compile without any prior configuration, but you will most likely need to install the Windows SDK (see below).

- **Visual Studio 2022**: You will need to install (most of) the following components. Some are not required, like the AddressSanitizer and Just-In-Time debugger. This is an old screenshot, make any upgrades to the versions of these components that you see fit.
  ![image](https://user-images.githubusercontent.com/26600014/128105644-cfa92f30-dc96-4476-a4c9-8d8b5f3ce129.png)

## Development (Linux)
- **CLion (recommended)**: The project will compile without any prior configuration, but you will need to install a few things first.

  On Debian-based distros, run:
    - `sudo apt update && sudo apt install cmake build-essential xorg-dev mesa-common-dev mesa-utils`
    
## Development (macOS)
- **To Setup CMake**: You must install llvm from homebrew as the default Apple Clang does not work properly. use the command `brew install llvm` and then run `cmake_config_macos.sh` to create the build folder
    
        To compile using cmake in the terminal run `cmake --build build --config Debug`
        
- **XCode**: coming soon!

## Usage
I recommend adding this repository as a submodule to your project.
Make sure if you add a new resource folder, copy it to the `resources` folder in the executable directory in your buildscript, or the program will fail at runtime due to missing assets.
