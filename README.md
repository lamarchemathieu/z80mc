# z80mc
Z80 Membership Card experimentations

[http://www.sunrise-ev.com/z80.htm](http://www.sunrise-ev.com/z80.htm)

# Install tools

```
sudo apt-get install -y sdcc build-essential lrzsz minicom
```

# Build test1

```
cd z80mc/test1
make clean
make
```

# Upload and run

With minicom configured to 9600, 8n1,
Run command in the Z80MC monitor :
```
Main Menu >x u 8000
[Type Ctrl-A s, choose xmodem, then choose the out.bin file]
[Wait complete]
Main Menu >g 8000                                                                                 
```
