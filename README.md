
# RemoteDictionary client/server

Library and executable thats implements dictionary server.

Library thats implements client to send requests.

## Appendix

Used Judy Arrays to store key/value pairs.

Used LibUV to implements wire connections.

Used CJSON (https://github.com/DaveGamble/cJSON) to serialize.

## Installation

Install with cmake

Supported_platform: Linux

```bash
    cmake . -Bbuild
    cd build
    make run_server
```
    
## Running Tests

To run tests, run the following command

First up the server

```bash
  ./run_server
```

After, build and run tests

```bash
  make utest_client
  ./utest_client
```
## Usage/Examples

```javascript
/home/adauga/AdaProjects/RemoteDictionary/cmake-build-debug/run_server 127.0.0.1 7000

/home/adauga/AdaProjects/RemoteDictionary/cmake-build-debug/utest/utest_client
allocated 0x55c8e75433f0
connected. 0x55c8e75433f0 0
wrote.
on_read. 0x55c8e75432f0
read: {
	"operation":	"set",
	"key":	"grJHpAmjvcBk",
	"value":	"dguAmqlihDwkwdBpjc",
	"status":	"done"
}
closed.
```


## Roadmap

- Benchmark

![Logo](https://i.postimg.cc/cLrC7vbn/3de10b32-c5c5-4bb0-b34e-72e78a44f670-progress-image-100.webp)


## Authors
Dmitriy Popov.

Elapsed time: 24 h 00 m (58 pomodoros).

IDE: CLion 2021.1, Sublime 3

gcc 9.4.0
