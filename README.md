Generate
```
cmake -S . -B .\build\ -G "MinGW Makefiles"
```
(-G is optional but preffered)

Build
```
cmake --build .\build\
```

Pack
In the generated directory
```
cpack
```