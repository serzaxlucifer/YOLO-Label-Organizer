# YOLO-Label-Organizer (for YOLO format Labels)
This program re-organizes/changes existing class labels. For example, say you have a labelled dataset with classes `0, 1, 2`. And for some reason, you wish to change class `0` to `5` in all the labels, then this program can do that in just few clicks.

It contains one source code file: `organizer.cpp`
Compile that using the GCC compiler using command in the directory that has the folder containing the label (.txt) files. Note that this program should compile on a Windows system only.

`gcc organizer.c`

After this run,

`./a.exe foldername`
(Name of folder that has the labels)

The program will guide you further with what it can do.

[NOTE THAT IT ONLY WORKS ON LABEL FILES THAT HAVE AT MAX. 99 LABELLINGS]
To increase this, simply tweak the source code on line,

`char line[100][150]`  to  `char line[?][150]`
