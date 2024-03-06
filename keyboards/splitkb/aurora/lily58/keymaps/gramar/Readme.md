# Custom nordic ansi-compatible keymap with some extras

This is my old iris-keyboard layout, ported to the lily58 with some added
encoder and oled code.

I haven't spent much effort with feature gating, so this only works 
with oled and encoders enabled, but that shouldn't be particularly hard to change 
if needed.

## Build info

Some build info so that I don't forget the details.

Pretty simple, I'm currently using `liatris` microcontrollers (a `rp2040` design).  
Therefore, the build command looks like this:

`qmk compile -kb splitkb/aurora/lily58 -km gramar -e CONVERT_TO=liatris && ls -lah .build/splitkb_aurora_lily58_rev1_gramar_liatris.uf2`

The final `ls -lah` is just to check the resulting size on disk.

The important part is `-e CONVERT_TO=liatris`, which should be changed to whatever 
microcontroller is used, for example `-e CONVERT_TO=elite-pi` for an elite-pi, which is another 
`rp2040` pro-micro compatible microcontroller.


## Layouts

There are 4 layouts.

### SE-Dvorak

The default is `se`-(swedish language)compatible dvorak, assuming the OS understands
that it's supposed to interpret inputs as Swedish symbols, it'll be able to print å, ä, and ö.

### ANSI-Dvorak

ANSI-compatible Dvorak, has the exact same mapping as above if the OS expects ANSI, 
which is nice, since then the layout is the same as normal in for example bootloaders, grub, or anywhere
else that defaults to en-ANSI

### ANSI-Qwerty

Just keeping a qwerty-layout around for the sake of it mostly.

### Qwerty gaming

A querty layout that's a bit more suited to gaming.

## Extras

The keymap uses two extras

### Oled

My keyboards have oled displays, so some features are relevant to those.

#### CPM and WPM

I wrote a simple CPM/WPM-implementation (different from the one QMK ships).  

I later looked at it, and the implementation is fairly similar, it uses a
ring-buffer and writes timestamps into that buffer, then calculates 
WPM from a rolling window. 

It takes CPM (actually presses per 10 seconds rolling interval), calculates WPM
(just by dividing by 5), writes those into a buffer which is then mapped onto the oled display.

#### Total keypresses

Just a simple counter with a `uint32_t`
