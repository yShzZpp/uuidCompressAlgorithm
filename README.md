# compressUUID

Compress the uuid of 32 bytes into 16 bytes.


&nbsp;

compiling the project:
```bash
mkdir build

cd build

cmake ../

make

./test
```

&nbsp;

example:

uuid:8b57917d-7745-4a4d-b645-cd2b661cfe0a

in the past, we would send 32 bytes(do not send the '-')
8 b 5 7 9 1 7 d 7 7 4 5 4 a 4 d b 6 4 5 c d 2 b 6 6 1 c f e 0 a

```c++
0b0000_1000 //8
0b0000_1011 //b
0b0000_0101 //5
0b0000_0111 //7
0b0000_1001 //9
0b0000_0001 //1
0b0000_0111 //7
0b0000_1110 //d
....
....
```

after compression, we send 16 bytes(do not send the '-')
8b 57 91 7d 77 45 4a 4d b6 45 cd 2b 66 1c fe 0a

```c++
0b1000_1011 //8b
0b0101_0111 //57
0b1011_0001 //91
0b0111_1110 //7d
...
...
```

