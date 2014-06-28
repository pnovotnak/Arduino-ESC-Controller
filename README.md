# Arduino ESC Controller


Arduino ESC controller- maps a pot throttle to a servo output.

 - Keeps things sane when a dirty potentiometer is used
 - Capible of running a sweep to initialize the ESC
 - Set intput and output ranges


## Some gotchas
 
 - Don't run debug in production! Debug (Serial out) seems to change slightly how the Arduino behaves
 - This code could kill you if you use it for something big, fast, heavy, or some combination.
   - I take absolutely no responsibility for your use.
   - The code is provided *as is* with no claims of fitness
 - Floating pins are not handled in software yet! You **NEED** a pulldown resistor.
