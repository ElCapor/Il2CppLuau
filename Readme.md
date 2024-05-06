# Work note
check feature-global-state
and feature-sandbox branches to see current work
# IL2CPP Lua
Lua Implementation of UnityResolve.hpp
Opens an UI in game where you can write luau scripts

# Building
```
git clone https://github.com/ElCapor/Il2CppLuau.git --recursive
cd Il2CppLuau
xmake
```
# UML Diagram
Represents the current architecture of the project.

```
// conventions
// <state> = namespace
// <abstract> = virtual class
// + method
// only exposed & public functions are documented
```
![Class diagram](diagram.png)