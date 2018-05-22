# MemDynEdition

This project is a draft to test how edit memory during a executable is running though scanmem/gameconqueror in GNU/Linux. The equivalent program in Windows is CheatEngine.

# Dependencies

## scanmem/gameconqueror

Install in you computer. In Fedora:

```
sudo dnf install scanmem gameconqueror
```

## Reed-Solomon

For add redundant info in order to recovery corrupted data I found 2 repositories:
* [nceruchalu repository](https://github.com/nceruchalu/reed_solomon): It was develop by Nnoduka Eruchalu. The code is not ready to be user with common messages but it is interesting to study.
* [Schifra repository](https://github.com/ArashPartow/schifra) repository is better to use as dependency and its license allows to use for learning purpose. I use this as 3rdParty to recovery info using Reed Solomon.

If you didn't clone with recursive option use:

```
git submodule update --init --recursive
```
 
# Compiling

```
mkdir build && cd build
cmake ..
make -j4
make install
```

# How to use

After compile and install (default path install inside build folder) go to install path an execute them. *TODO*
