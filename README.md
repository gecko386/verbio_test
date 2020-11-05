# Description 
This program is designed to process text input and convert word numbers to numeric format.

## Downloading

Due to some submodules you have to clone repository with '--recurse-submodules' flag

```console
$ git clone https://github.com/gecko386/verbio_test.git --recurse-submodules
```

## Building

from project folder do

```console
project$ mkdir build
project/build$ cd build
project/build$ cmake ../
project/build$ make
```

## Execution

From buil folder execute

```console
project/build$ ./number_translator
```

it will allow you to introduce sentences an see output on carriage return, you can pass a text file redirecting stdin

```console
project/build$ ./number_translator < mifileinput.txt
```

## Testing

By default test are build with the main compilation. It uses GoogleTest but the CMAKE procedure will download these dependencies for you.
To execute test you have to go to test folder an execute 'launch_tests'

```console
project/build$ cd tests
project/build$ ./launch_tests
```
