This is a reimplementation of the Realmz Character Editor 1.0 as found on windows.

Realmz is a rpg from the 90s which is just fun. I purchased the game way back in the day but
was saddened to find out that it really was not patched after it's initial windows release to
fix bugs in either the main game or the character editor. I have been painstakingly reverse
enginnering both executables (and by proxy the mac versions of them as well, A-line traps...).

This implementation is meant to be as close to the design of the original character editor as possible.
It is the full version too so you're able to save as well :). I also want to fix the bugs found in the
windows version around segfaulting on editing saved games and such.

The mac demo version was invaluable because the names of functions were left in the executable sections of the
binary. It also doesn't use the Myriad W-ACAM library like the windows version so I have a guide as to what is
toolbox routines and what is not.

Thanks to the following for the character editor:

- Fantasoft for making Realmz and the Character Editor
- GHIDRA for being awesome when it comes to reverse enginnering
- The original author of resource_dasm (I had to fork the code but without your initial research it would've taken longer). It can be found at: https://github.com/fuzziqersoftware/resource_dasm
- http://mirror.informatimago.com/next/developer.apple.com/documentation/macos8/mac8.html <- THANK YOU!!!
- http://www.cebix.net/viewvc/cebix/mon/src/mon_atraps.h
- http://www.mac.linux-m68k.org/devel/macalmanac.php

Realmz is Copyright of Fantasoft LLC. This program is completely unofficial.
