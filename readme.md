# mpos
A super simple but powerful command line tool to set the cursor position on Windows.  

Usage:  
Set an absolute mouse position  
```mpos.exe -x 420 -y 120```

Only set the x position, keep y as is  
```mpos.exe -x 420```

Only set the y position, keep x as is  
```mpos.exe -y 120```

Move the mouse by 40 pixels on the x axis, and by 100 pixels on the y axis  
```mpos.exe -dx 40 -dy 100```

Move the mouse by 100 pixels on the x axis  
```mpos.exe -dx 100```

Move the mouse by 100 pixels on the y axis  
```mpos.exe -dy 100```

Move the mouse by 50 pixels on the x axis, and set the y position to 30  
```mpos.exe -dx 50 -y 30```

etc...

You can add `--no-dpi` to disable DPI scaling, which might lead to inaccurate results. For example, with `--no-dpi` the bottom-right cornor of my 4k(=3840x2160) monitor is at (2560x1440) pixels.

## Documentation:
```
A super simple command line tool to set the mouse position.

==== AVAILABLE PARAMETERS ====

--x   -x   INT   incompatibilities=[--delta-x]   The x coordinate to set the cursor to. If no information on x is supplied, the current position will be used.

--delta-y   -dy   INT   incompatibilities=[--y]   Move the cursor by --delta-y pixels on the y axis. If no information on y is supplied, the current position will be used.

--y   -y   INT   incompatibilities=[--delta-y]   The y coordinate to set the cursor to. If no information on y is supplied, the current position will be used.

--delta-x   -dx   INT   incompatibilities=[--x]   Move the cursor by --delta-x pixels on the x axis. If no information on x is supplied, the current position will be used.

--disable-dpi-scaling   --no-dpi   VOID   Don't make this process DPI aware. This may result in inaccurate cursor positions.

--version   -v   VOID   Will just print the version and exits.
```