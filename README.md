### Compiler boilerplate
This repo contains flex/bison basic tempalte to create interpreters/compilers. In order to demonstrate it - we can do simplified version of AWK which is using direct input or file input

### Limitations
* Currently byte code compilation is not implemented
* Conditions execution order is not implemented
* String literls are not implemented

### Build
```
make gen
mkdir -p build && cd build && cmake ../ && cmake --build .
```

Simplified version
```
make all
```

Test run
```
make test
```

### Some examples of code
```                                                                      
$1 == 123 { $1 }
$1 == $2 { $1 }
$1 > $2 { $1 }
$1 >= 3 { $1 }
$1 > 3 && $2 == 1 {$1}
$1 > 3 || $2 == 1 {$1}
$1 == 4 { print($1, $2, $3) }
```
