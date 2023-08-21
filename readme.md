![](docs/header.jpg)

# Gecko 2

In the neverending re-writes of my software ... here is a new version of `gecko`

- python3
- C++20

| Library    | Arduino | Linux |
|------------|---------|-------|
| gciMock    |         | x
| Serialcomm |         | x
| Marko      |         | x
| Messages   | x       | x
| Slurm      | x       | x
| gecko      | x       | x

## Useful CMake

```cmake
FetchContent_Declare(gecko2
    GIT_REPOSITORY "https://github.com/gecko-robotics/gecko2.git"
    GIT_TAG "origin/main"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gecko2"
    SOURCE_SUBDIR "cpp"
)
```

```cmake
# gciSensors -----------------
FetchContent_Declare(gcisensors
  GIT_REPOSITORY "git@github.com:the-guild-of-calamitous-intent/gciSensors.git"
  GIT_TAG "origin/main"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/gcisensors"
)
```

```cmake
# serialcomm -----------------
FetchContent_Declare(serialcomm
    GIT_REPOSITORY "https://github.com/gecko-robotics/serialcomm.git"
    GIT_TAG "origin/main"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/serialcomm"
)
```

```cmake
# yivo -----------------
FetchContent_Declare(yivo
  GIT_REPOSITORY "https://github.com/MomsFriendlyRobotCompany/yivo.git"
  GIT_TAG "origin/main"
  SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/yivo"
  SOURCE_SUBDIR "c++"
)
```

```cmake
# squaternion -----------------
FetchContent_Declare(squaternion
    GIT_REPOSITORY "https://github.com/MomsFriendlyRobotCompany/squaternion.git"
    GIT_TAG "origin/master"
    SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/squaternion"
    SOURCE_SUBDIR "cpp"
)
```
## To Do

- [ ] wrap `gecko` namespace on things
- [ ] write `slurm`
- [ ] evaluate: https://www.foonathan.net/2022/06/cmake-fetchcontent/

# MIT License

**Copyright (c) 2010 gecko-robotics**

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.