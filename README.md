# Advent of Code 2022
Day 1-10 in C, built using Bazel. 

To build and run the files:
```bash
bazel run src/DayX:DXPY
```

Example: Run Day 6 Part 2 with: 
```bash
bazel run src/Day6:D6P2
```


# Unity test for Day 10 Part 1
Compile the files with the Unity testing framework, outputs testfile:
```bash
gcc -o test_D10P1 test/D10P1UT.c test/TestD10P1UT.c unity/src/unity.c -Isrc/Day10 -Iunity/src  
```
Run the testfile:
```bash
./test_D10P1
```                                                                                                                                                                                                                                                                                                                                                     
