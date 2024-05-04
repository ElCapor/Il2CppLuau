# feature-global-lua-state branch
When writing lua widgets, i figured out that I needed a global state for the whole dll, instead of creating a new one each time i want to run a script. Since it's a breaking change , it deserves a whole branch for it.

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