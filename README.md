# Tool plugin standart 
## Basic concepts.
1. Plugin is shared library file nammed ```*.aboba.so``` where * is any valid OS file name.
2. To properly work with plugins you should include suggested .hpp file where all main structures are specified.
3. Color has format **0xRRGGBBAA**
## Requirements from plugin developer.
1. Next function must be implemented. 
```C
 extern "C" void init_module() 
```
 It will be called as module is loaded. During this function only add_widget add_tool can be called.
## Possiblilities of module system.

