# MemDynEdition

This project is a draft to test how edit memory during a executable is running though scanmem/gameconqueror in GNU/Linux. The equivalent program in Windows is CheatEngine.

# Dependencies

## scanmem/gameconqueror

Install in you computer. In Fedora:

```
sudo dnf install scanmem gameconqueror
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
