# LTVar

Loosely typed variables for C++


## Description

These library was conceived to mimic the loosely typed behaivor of variables in Javascript, to be used in development where data types and structures are not statically defined at compile time or are meant to change in time.
Some posbile uses:

- Configuration
- Managing messages involved in interprocess communication
- Dynamic data storing

An important consideration found deep in the roots of the design, was the need to be easily serializable in any form, so you will find two reference implementation, one for reading from and writing to Json and another to a basic Binary form.


## Getting Started

This project doesn't have any boilerplate dependency, so to build it and start using it is pretty straightforward.

### Prerequisites

#### Mandatory
The only mandatory prerequisites are:
- CMake
- C++14 compiler support
- make

#### Optional
- **Bison/Flex**: required to build the Json serializer.
- **Google Test/Google Mock**: build and run the unit test.
- **lcov**: generate code coverage analisys.


### Getting the Code
```
git clone https://github.com/prohto/ltvar.git
```

### Build

```
mkdir <build path>
cd <build path>
cmake <path to cloned repository>
make
```

### Testing Build

```
mkdir <build path>
cd <build path>
cmake -DCMAKE_BUILD_TYPE=Testing <path to cloned repository>
make
```

## Unit Test
This project was developed following TDD rules, so you will find tests for almost any single line of code in the project. To run the tests you have to build the project for testing.

### Running tests
```
cd <build path>/utest
make utest
```

### Generating coverage analysis
It is posible to generate a report of how much code was covered by the tests, to do so follow the next commands:

```
cd <build path>/utest
make coverage
firefox index.html
```

## Deployment

The deployment is done with CMake:

```
cd <build path>
make intall
```

Deployment includes  the **pkg-config** file ltvar.pc .

## Usage example
The following is a simple example of how to use the Json serializer:

```c++
#include <ltvar.h>
#include <ijson.h>

int main(){
  std::istringstream in_stream( "{bool:true, double: 123.456,integer:\t123,\ntext:\"anything\",void:null,array:[]}");
  LTVar value;
  IJson ijson(value);

  in_stream >> ijson;

  LTVarIterator iter = value.begin();
  while( iter != value.end() ){
    std::cout << "Field Name ["<<static_cast<std::string>(iter.first())<<"] Value ["<<static_cast<std::string>(iter.second())<<"]\n";
    iter++;
  }
  for( auto item: value ){
    std::cout << "Value ["<<static_cast<std::string>(item)<<"]\n";
  }
  return 0;
}
```

To compile the example
```
g++ -o json json.cpp -I/usr/local/include/ltvar -lltvar -L/usr/local/lib64
```

Temporarily for further usage examples, please look at the many unit tests in file **test_ltvar.cpp**.


## Authors

* **Carlos Fangmeier** - *Initial work* - [Prohto](https://github.com/prohto)


## License

This project is licensed under the LGPLv3 License - see the [LICENSE.md](LICENSE.md) file for details

