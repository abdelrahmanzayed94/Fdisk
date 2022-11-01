# Fdisk
This program imitates the "fdisk -l" command for MBR hard disks.
"myhdd" is a hard disk example including the following paritions:
```
$ fdisk myhdd -l
Disk myhdd: 1 MiB, 1048576 bytes, 2048 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes
Disklabel type: dos
Disk identifier: 0xd6533049

Device     Boot Start   End Sectors   Size Id Type
myhdd1              1   201     201 100.5K 83 Linux
myhdd2            202   402     201 100.5K 83 Linux
myhdd3            403   603     201 100.5K 83 Linux
myhdd4            604  2047    1444   722K  5 Extended
myhdd5            605   705     101  50.5K 83 Linux
myhdd6            707   907     201 100.5K 83 Linux
myhdd7            909  1309     401 200.5K 83 Linux
myhdd8           1311  1511     201 100.5K 83 Linux
myhdd9           1513  1613     101  50.5K 83 Linux
myhdd10          1615  1815     201 100.5K 83 Linux
myhdd11          1817  2047     231 115.5K 83 Linux
```
command used for compilation:
```
gcc myfdisk.c -o myfdisk
```
run example:
```
$ ./myfdisk myhdd 
Device: myhdd1
Boot:  
Start: 1
End: 201
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd2
Boot:  
Start: 202
End: 402
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd3
Boot:  
Start: 403
End: 603
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd4
Boot:  
Start: 604
End: 2047
Sectors: 1444
Size: 739328 Bytes
Id: 5
Type: Extended
Device: myhdd5
Boot:  
Start: 605
End: 705
Sectors: 101
Size: 51712 Bytes
Id: 83
Type: Linux
Device: myhdd6
Boot:  
Start: 707
End: 907
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd7
Boot:  
Start: 909
End: 1309
Sectors: 401
Size: 205312 Bytes
Id: 83
Type: Linux
Device: myhdd8
Boot:  
Start: 1311
End: 1511
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd9
Boot:  
Start: 1513
End: 1613
Sectors: 101
Size: 51712 Bytes
Id: 83
Type: Linux
Device: myhdd10
Boot:  
Start: 1615
End: 1815
Sectors: 201
Size: 102912 Bytes
Id: 83
Type: Linux
Device: myhdd11
Boot:  
Start: 1817
End: 2047
Sectors: 231
Size: 118272 Bytes
Id: 83
Type: Linux
```
