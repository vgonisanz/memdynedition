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

# How I face the memory edition in these examples

I have developed this repository in order to evaluate how memory can be edited in execution to change the behavior of a program. I focused the problem to a video-game, where the "hacker" edit struct in its own benefit. After thinking about this kind of problem, remember some thinks I learned on the University, and research of this topic I tried to implement some strategies to face the problem. In a computer you cannot control when CPU execute a program, and if someone want to be unfair in its own computer, you cannot prevent this. I think that is impossible to solve this problem, but that you cannot prevent this 100% doesn't mean that you cannot put it hard sacrificing some CPU instruction and memory.

# Goals

* Protect from memory edition
* Optimize resources like memory and CPU if possible
* Make minimal changes in the original data structure

# Player description

* **player**: Basic player contain raw memory attributes and methods to manage into "legality" and print the info. The basic sample shows how interactuate with the binary normally. This example can be easy edited using scanmem/cheat engine without notice.
* **playerCP**: Copy info raw in other part. This is the easier method to be detected. It is so trivial that I didn't implement it at the beginning because it is so easy to notice that the value is copied in other places. But as exercise it is interesting to see the result, so I did it.
* **playerAntiCP**: As additional trick, I tried to make a basic operation with that. Negating the value of each bit. Other transformation like shift bits would be valid but it implies to don't lost important info.
playerCRC32: This player ONLY detect when something was edited. This class generate a crc32 based on the last "legal" struct edition. When binary is going to update the struct, check if current struct have the same crc32 as expected. If not, someone edited the struct. This compute have a low impact in performance and only require 32 additional bits. It is easy to notice what is going on observing the raw memory and with patience, it is possible to detect what 32bit word is changing, but not how unless source code is available (or check assembly).
* **playerRS**: This player can detect and recover all edited values. This class also have to check if message bits have changed, but in this case the original info can be recovered using redundancy. The price to pay is that require 2/3 redundancy against 1/3 info. Additionally, some calculation to encode/decode are required. It is possible to improve the redundancy ratio using less data. In this case, while the external edition is lesser than error recovery, it is possible to have the original values. If not, it is detected that something happened and act accordingly. You have to choose some values and sacrifice something to get something. At this time, the part to save the info is manually, and limited one struct per block. This is not efficient because it is configured to use 255 length messages, son the extra bits are unused.

# Other strategies:

* ???? think about it.

# Future work

* Another ways to save the info
* Performance study
* Hacking assembly/memory edition study
* bash scripts to make automatically sample execution and edition
* Memory manager to assign dinamically free space into blocks. Optimize for any request sizes. And without disturb original code. In example: https://www.ibm.com/developerworks/aix/tutorials/au-memorymanager/index.html

# Theory

## CRC32

A cyclic redundancy check (CRC) is an error-detecting code commonly used in digital networks and storage devices to detect accidental changes to raw data. Blocks of data entering these systems get a short check value attached, based on the remainder of a polynomial division of their contents.

## Reed Solomon

Error correcting codes are a signal processing technique to correct errors. Reed-Solomon is a common used for this purpose. Reed-Solomon Encoder and Decoder are commonly used in data transmission and storage applications.

This works as follows, if we take data and encode as "message" or data file into a block with a longer message, we sacrifice space to have additional info. The point is that, this block is capable to reconstruct the original from the longer message even if parts of the longer message have been lost. Reed-Solomon is an erasure code with exactly the properties we needed for file storage, and it is simple and straightforward to implement.

Instead of just seeing a message (or memory addresses) as a series of bytes, it is possible to see it as a polynomial following the very well-defined rules of finite field arithmetic. In other words, it is possible to represent the data using polynomials and finite fields arithmetic adding info to the original data. The values of the message are still the same, but this conceptual structure now allow us to operate on the message, on its characters values, using well defined mathematical rules. This structure, that we always know because it's outside and independent of the data, is what allows us to repair a corrupted message.

To encode the generator polynomial is used as encoding dictionary. Using algebra, polynomial division is the operator to convert our message using the dictionary into a valid Reed Solomon code.

To decode the syndromes polynomial is used to detect if the message is corrupted at all, then a locator polynomial check what characters are corrupted. After know this, evaluator polynomial evaluate how much the message was tampered. At last, corruption polynomial subtracts received messages to get the original, repairing the errors.

* Performance: Taking additional operation with memory has a cost. The cost is proportional to the redundant data added, storing a vast amount of data with redundancy imply a slower system.
* Example: The RAID system built into Linux uses Reed-Solomon.
