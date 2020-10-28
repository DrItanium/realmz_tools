This repo contains tools and research documents relating to reverse engineering Realmz by Fantasoft. 
From what I can tell the game went freeware in 2008 with the Windows version being the easiest
way to still play the game.

However, the windows version is full of unpatched bugs (MyrBitTstLong overflow message is the most apparent)
and also depends on the WinG graphics library which is so ancient that both Windows and WINE have issues supporting
it. 

Several months ago, I decided to install GHIDRA and see what I could do with it. One of the first things I did was
put the Realmz executable into it and was able to start reverse engineering it.

While I am still diving into most of the logic (the Myriad W-ACAM library that Realmz uses on Windows adds quite a bit
of noise and the mac version actually syncs up with the windows version due to
the use of W-ACAM) I have decided to publish my findings so far. Keep in mind this is a tiny subset of what I have 
found but I thought it would be important to preserve my findings. 

Right now the most important parts are going to be:

1) The key generator which will allow you to generate your own registration codes for realmz itself and all scenarios made by fantasoft.
   The logic for custom scenarios is implemented but not hooked up to the tool front end. I do not think this code will run afoul
   of anything because Realmz is not being actively sold at the moment. Hopefully, someone will find it useful :). NOTE: The generator
   only works for the Windows version, the codes generated do not work on the
   classic mac os version (finally got BasiliskII running again).
2) Caste decomposer and printing utility - This was the initial tool to print out the contents of the Data Caste file, 
   this tool will eventually be used to convert Data Caste to something like JSON so it can be read regardless of platform 
   (right now bytes have to be swapped)

Also, here are the codes that Skip Meier released at the same time as declaring Realmz freeware:
```
I haven't tried them yet but supposedly they work. 

FOR THE WINDOWS VERSION :
Serial Number : 13706024
Registration Code : 7995820
Reset Serial Number Code : 410
Registration Name : : MEIERS
Prelude to Pestilence : 2846681
Assault on Giant Mountain : 2731903
Castle in the Clouds : 1850227
Destroy the Necronomicon : 300754
White Dragon : 302208
Grilochs Revenge : 687525
Trouble in the Sword Lands : 1533542
Mithril Vault : 162011
Twin Sands of Time : ?
War is the Sword Lands : ?
Half Truth : ?
```

NOTE: This is all for realmz 7.1.2, not the newer 8.0.? release for mac os classic.

I have tested these tools with GCC 9.2.0 on Gentoo Linux x86_64 with Cmake.

This project also contains notes on different file formats as well. See the notes folder for this information
